#define WIN32_LEAN_AND_MEAN
#include <windows.h>


#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define WINDOWS_INCLUDE
#include "../../../../../decompile/General/AltMods/OnlineCTR/global.h"

char* pBuf;
struct OnlineCTR* octr;
char ip[100];

struct SocketCtr
{
	SOCKET socket;
};

struct SocketCtr CtrMain;

void Disconnect()
{
	// reboot
	octr->CurrState = -1;
}

void ParseMessage()
{
	char recvBufFull[0x20];
	memset(recvBufFull, 0xFF, 0x20);

	// if send() happens 100 times, it all gets picked up
	// in one recv() call, so only call recv one time
	int numBytes = recv(CtrMain.socket, recvBufFull, 0x20, 0);

	if(numBytes == -1)
	{
		int err = WSAGetLastError();

		// This happens due to nonblock, ignore it
		if (err != WSAEWOULDBLOCK)
		{
			// if server is disconnected
			if ((err == WSAENOTCONN) || (err == WSAECONNRESET))
			{
				Disconnect();
			}

			return;
		}
	}

	// parse every message coming in
	for(int offset = 0; offset < numBytes; /**/)
	{
		struct SG_Header* recvBuf = &recvBufFull[offset];
		printf("%d %d %d %d\n", numBytes, offset, recvBuf->size, recvBuf->type);
		offset += recvBuf->size;

		int slot;

		// switch will compile into a jmp table, no funcPtrs needed
		switch (((struct SG_Header*)recvBuf)->type)
		{
		case SG_NEWCLIENT:

			// clientID is "you"
			octr->DriverID = ((struct SG_MessageClientStatus*)recvBuf)->clientID;
			octr->NumDrivers = ((struct SG_MessageClientStatus*)recvBuf)->numClientsTotal;
			printf("New client, you are now: %d/%d\n", octr->DriverID, octr->NumDrivers);
			
			if (octr->CurrState = LAUNCH_FIRST_INIT)
			{
				// choose to get host menu or guest menu
				octr->CurrState = LOBBY_ASSIGN_ROLE;
			}
			
			break;
		
		case SG_DROPCLIENT:

			int clientDropped = ((struct SG_MessageClientStatus*)recvBuf)->clientID;
			octr->NumDrivers = ((struct SG_MessageClientStatus*)recvBuf)->numClientsTotal;

			// fix driver IDs
			if (clientDropped == octr->DriverID) slot = 0;
			if (clientDropped < octr->DriverID) slot = clientDropped + 1;
			if (clientDropped > octr->DriverID) slot = clientDropped;

			for (int i = slot; i < octr->NumDrivers; i++)
			{
				*(short*)&pBuf[(0x80086e84 + 2 * (i)) & 0xffffff] =
					*(short*)&pBuf[(0x80086e84 + 2 * (i + 1)) & 0xffffff];

				octr->boolLockedInCharacter_Others[i] =
					octr->boolLockedInCharacter_Others[i + 1];
			}

			// clientID is the client disconnected
			if (octr->DriverID > clientDropped)
				octr->DriverID--;

			printf("New client, you are now: %d/%d\n", octr->DriverID, octr->NumDrivers);

			// if you are new host
			if (octr->DriverID == 0)
			{
				if (octr->CurrState == LOBBY_GUEST_TRACK_WAIT)
					octr->CurrState = LOBBY_HOST_TRACK_PICK;
			}
			
			break;
		
		case SG_TRACK:
			octr->boolLockedInTrack = 1;
			int trackID = ((struct SG_MessageTrack*)recvBuf)->trackID;
			printf("Got Track: %d\n", trackID);

			// set sdata->gGT->trackID
			*(char*)&pBuf[(0x80096b20 + 0x1a10) & 0xffffff] = trackID;
			octr->CurrState = LOBBY_CHARACTER_PICK;
			break;

		case SG_CHARACTER:
			int characterID = ((struct SG_MessageCharacter*)recvBuf)->characterID;
			int clientID = ((struct SG_MessageCharacter*)recvBuf)->clientID;
			printf("Client: %d, Character: %d\n", clientID, characterID);
			
			if (clientID == octr->DriverID) slot = 0;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			*(short*)&pBuf[(0x80086e84 + 2*slot) & 0xffffff] = characterID;
			octr->boolLockedInCharacter_Others[clientID] = ((struct SG_MessageCharacter*)recvBuf)->boolLockedIn;
			break;

		case SG_STARTLOADING:
			// variable reuse, wait a few frames,
			// so screen updates with green names
			octr->CountPressX = 0;
			octr->CurrState = LOBBY_START_LOADING;
			break;

		default:
			break;
		}
	}
}

void StatePC_Launch_EnterPID()
{
	// if client connected to DuckStation
	// before game booted, wait for boot
	if (octr->IsBootedPS1)
	{
		octr->CurrState = LAUNCH_ENTER_IP;
	}
}

void StatePC_Launch_EnterIP()
{
	printf("\n");
	printf("Enter IP Address: ");
	scanf_s("%s", ip, sizeof(ip));

	// sockAddr
	struct sockaddr_in socketIn;
	
	struct hostent* hostinfo;

	socketIn.sin_family = AF_INET;
	socketIn.sin_port = htons(1235);

	hostinfo = gethostbyname(ip);

	if (hostinfo == NULL)
	{
		printf("Unknown host\n");
		octr->CurrState = LAUNCH_CONNECT_FAILED;
		return;
	}

	socketIn.sin_addr = *(struct in_addr*)hostinfo->h_addr;

	printf("URL converts to IP: %d.%d.%d.%d\n",
		socketIn.sin_addr.S_un.S_un_b.s_b1,
		socketIn.sin_addr.S_un.S_un_b.s_b2,
		socketIn.sin_addr.S_un.S_un_b.s_b3,
		socketIn.sin_addr.S_un.S_un_b.s_b4);

	// Create a SOCKET for connecting to server
	CtrMain.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	// Setup the TCP listening socket
	int res = connect(CtrMain.socket, (struct sockaddr*)&socketIn, sizeof(socketIn));
	
	// failed connection
	if (res < 0)
	{
		printf("WSAGetLastError: %d\n", WSAGetLastError());
		octr->CurrState = LAUNCH_CONNECT_FAILED;
		return;
	}
	
	// failed connection
	if (CtrMain.socket == INVALID_SOCKET)
	{
		octr->CurrState = LAUNCH_CONNECT_FAILED;
		return;
	}
	
	unsigned long nonBlocking = 1;
	ioctlsocket(CtrMain.socket, FIONBIO, &nonBlocking);
	
	octr->DriverID = -1;

	octr->CurrState = LAUNCH_FIRST_INIT;
}

void StatePC_Launch_ConnectFailed()
{
	printf("Unable to connect to server!\n");
	system("pause");
	octr->CurrState = LAUNCH_ENTER_IP;
}

void StatePC_Launch_FirstInit()
{
	ParseMessage();
}

void StatePC_Lobby_AssignRole()
{
	ParseMessage();
}

void StatePC_Lobby_HostTrackPick()
{
	ParseMessage();

	if (!octr->boolLockedInTrack) return;

	printf("Sending Track to Server\n");

	struct CG_MessageTrack mt;
	mt.type = CG_TRACK;
	mt.size = sizeof(struct CG_MessageTrack);

	// sdata->gGT->levelID
	mt.trackID = *(char*)&pBuf[(0x80096b20 + 0x1a10) & 0xffffff];

	// send a message to the client
	send(CtrMain.socket, &mt, mt.size, 0);

	octr->CurrState = LOBBY_CHARACTER_PICK;
}

void StatePC_Lobby_GuestTrackWait()
{
	ParseMessage();
}

int prev_characterID = -1;
int prev_boolLockedIn = -1;
void StatePC_Lobby_CharacterPick()
{
	ParseMessage();

	struct CG_MessageCharacter mc;
	mc.type = CG_CHARACTER;
	mc.size = sizeof(struct CG_MessageCharacter);

	// data.characterIDs[0]
	mc.characterID = *(char*)&pBuf[0x80086e84 & 0xffffff];
	mc.boolLockedIn = octr->boolLockedInCharacter;

	if(
		(prev_characterID != mc.characterID) ||
		(prev_boolLockedIn != mc.boolLockedIn)
	  )
	{
		prev_characterID = mc.characterID;
		prev_boolLockedIn = mc.boolLockedIn;

		// send a message to the client
		send(CtrMain.socket, &mc, mc.size, 0);
	}
	
	if (mc.boolLockedIn == 1)
	{
		octr->CurrState = LOBBY_WAIT_FOR_LOADING;
	}
}

void StatePC_Lobby_WaitForLoading()
{
	ParseMessage();

	// if recv message to start loading,
	// change state to StartLoading,
	// this check happens in ParseMessage
}

void StatePC_Lobby_StartLoading()
{
	ParseMessage();

	// change state to WaitForRace
}

void StatePC_Game_WaitForRace()
{
	ParseMessage();

	// send message that you're done loading

	// if recv message to start race,
	// change state to StartLoading,
	// this check happens in ParseMessage
}

void StatePC_Game_StartRace()
{
	ParseMessage();

	// this is gameplay, should send and recv position
}

void (*ClientState[]) () =
{
	StatePC_Launch_EnterPID,
	StatePC_Launch_EnterIP,
	StatePC_Launch_ConnectFailed,
	StatePC_Launch_FirstInit,
	StatePC_Lobby_AssignRole,
	StatePC_Lobby_HostTrackPick,
	StatePC_Lobby_GuestTrackWait,
	StatePC_Lobby_CharacterPick,
	StatePC_Lobby_WaitForLoading,
	StatePC_Lobby_StartLoading,
	StatePC_Game_WaitForRace,
	StatePC_Game_StartRace
};

int main()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

	char pid[16];
	printf("Enter DuckStation PID: ");
	scanf_s("%s", pid, sizeof(pid));

	char duckName[100];
	sprintf_s(duckName, 100, "duckstation_%s", pid);

	TCHAR duckNameT[100];
	swprintf(duckNameT, 100, L"%hs", duckName);

	// 8mb RAM
	const unsigned int size = 0x800000;
	HANDLE hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, duckNameT);
	pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, size);

	if (pBuf == 0)
	{
		printf("Error: Failed to open DuckStation\nTry again\n");
		system("pause");
		system("cls");
		main();
	}

	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		system("pause");
		return;
	}

	octr = (struct OnlineCTR*)&pBuf[0x8000C000 & 0xffffff];
	//octr->CurrState = StatePC_Launch_EnterPID;

	int gGT_timer = 0;

	while (1)
	{
		// To do: Check for PS1 system clock tick,
		// then run client update

		octr->time[0]++;

		ClientState[octr->CurrState]();
		
		// wait for next frame
		while (gGT_timer == *(int*)&pBuf[(0x80096b20 + 0x1cec) & 0xffffff]) {}
		gGT_timer = *(int*)&pBuf[(0x80096b20 + 0x1cec) & 0xffffff];
	}

	system("pause");
}