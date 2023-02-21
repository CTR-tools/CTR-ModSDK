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
#include "../../Network_PS1/src/global.h"

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
	octr->CurrState = LAUNCH_ENTER_IP;
}

void ParseMessage()
{
	char recvBuf[8];
	memset(recvBuf, 0xFF, 8);

	int recvByteCount;
	recvByteCount = recv(CtrMain.socket, recvBuf, 8, 0);

	// This happens when the server uses closesocket(),
	// either because you connected to a full server, or
	// a client disconnected so the server reset
	if (recvByteCount == 0)
	{
		Disconnect();
		octr->CurrState = LAUNCH_CONNECT_FAILED;
		return;
	}

	// check for errors
	if (recvByteCount == -1)
	{
		int err = WSAGetLastError();

		// This happens due to nonblock, ignore it
		if (err != WSAEWOULDBLOCK)
		{
			// if server is closed disconnected
			if (err == WSAECONNRESET)
			{
				Disconnect();
			}

			if (err == WSAENOTCONN)
			{
				system("cls");
				printf("Failed to connect to server\n\n");
				printf("Close Client.exe and reopen, try again\n");

				printf("\n");
				system("pause");
				exit(0);
			}

			octr->CurrState = LAUNCH_CONNECT_FAILED;
			return;
		}
	}

	if (recvByteCount != ((struct SG_Header*)recvBuf)->size)
	{
		//printf("Bug! -- Tag: %d, recvBuf.size: %d, recvCount: %d\n",
		//	recvBuf.type, recvBuf.size, receivedByteCount);

		// dont disconnect, just try again next cycle
	}

	// if recvSize is equal to expected, and if type is valid
	else if (((struct SG_Header*)recvBuf)->type < SG_COUNT)
	{
		// switch will compile into a jmp table, no funcPtrs needed
		switch (((struct SG_Header*)recvBuf)->type)
		{
		case SG_NEWCLIENT:
			
			// clientID is "you"
			octr->DriverID = ((struct SG_MessageClientStatus*)recvBuf)->clientID;
			octr->NumDrivers = ((struct SG_MessageClientStatus*)recvBuf)->numClientsTotal;
			printf("New client, you are now: %d/%d\n", octr->DriverID, octr->NumDrivers);
			break;
		
		case SG_DROPCLIENT:
			
			// clientID is the client disconnected
			if (octr->DriverID > ((struct SG_MessageClientStatus*)recvBuf)->clientID)
				octr->DriverID--;

			octr->NumDrivers = ((struct SG_MessageClientStatus*)recvBuf)->numClientsTotal;
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
			
			int slot;
			if (clientID == octr->DriverID) slot = 0;
			if (clientID < octr->DriverID) slot = clientID + 1;
			if (clientID > octr->DriverID) slot = clientID;

			*(short*)&pBuf[(0x80086e84 + 2*slot) & 0xffffff] = characterID;
			octr->boolLockedInCharacter_Others[clientID] = ((struct SG_MessageCharacter*)recvBuf)->boolLockedIn;

			// if everyone locked in,
			// start race

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
	if(CtrMain.socket != 0)
		closesocket(CtrMain.socket);

	printf("\n");
	printf("Enter IP Address: ");
	scanf_s("%s", ip, sizeof(ip));

	// sockAddr
	struct sockaddr_in socketIn;
	
	struct hostent* hostinfo;

	socketIn.sin_family = AF_INET;
	socketIn.sin_port = htons(1234);

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

void StatePC_Lobby_HostTrackPick()
{
	ParseMessage();

	if (!octr->boolLockedInTrack) return;

	printf("Sending Track to Server\n");

	struct CG_MessageTrack mt;
	mt.type = CG_TRACK;
	mt.size = sizeof(struct CG_MessageTrack);
	mt.boolLastMessage = 1;

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
	mc.boolLastMessage = 1;

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

	// chang state to WaitForRace
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

	while (1)
	{
		// To do: Check for PS1 system clock tick,
		// then run client update

		octr->time[0]++;

		ClientState[octr->CurrState]();
		
		// 4ms, 60fps=16ms
		Sleep(4);
	}

	system("pause");
}