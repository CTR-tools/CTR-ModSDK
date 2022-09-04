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

void ClientState_EnterPID()
{
	// if client connected to DuckStation
	// before game booted, wait for boot
	if (octr->IsBootedPS1)
	{
		octr->CurrState = ENTER_IP;
	}
}

void ClientState_EnterIP()
{
	printf("\n");
	printf("Enter IP Address: ");
	scanf_s("%s", ip, sizeof(ip));

	// sockAddr
	struct sockaddr_in socketIn;
	
	struct hostent* hostinfo;

	socketIn.sin_family = AF_INET;
	socketIn.sin_port = htons(27000);

	hostinfo = gethostbyname(ip);

	if (hostinfo == NULL)
	{
		printf("Unknown host\n");
		octr->CurrState = CONNECT_FAILED;
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
		octr->CurrState = CONNECT_FAILED;
		return;
	}
	
	// failed connection
	if (CtrMain.socket == INVALID_SOCKET)
	{
		octr->CurrState = CONNECT_FAILED;
		return;
	}
	
	unsigned long nonBlocking = 1;
	ioctlsocket(CtrMain.socket, FIONBIO, &nonBlocking);
	
	octr->CurrState = BOOT_GAME;
}

void ClientState_ConnectFailed()
{
	printf("Unable to connect to server!\n");
	system("pause");
	octr->CurrState = ENTER_IP;
}

void ClientState_BootGame()
{
	// do nothing, this lasts one frame on PS1-side
}

void ClientState_Navigate()
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
		//Disconnect();
		octr->CurrState = CONNECT_FAILED;
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
				//Disconnect();
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

			octr->CurrState = CONNECT_FAILED;
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
		case SG_WELCOME:
			octr->DriverID = ((struct SG_MessageWelcome*)recvBuf)->clientID;
			octr->NumDrivers = ((struct SG_MessageWelcome*)recvBuf)->numClientsTotal;
			break;
		default:
			break;
		}
	}

	// Right here, handle sending a response
	{
		// To do: later
	}
}

void ClientState_Minimize()
{
	// this is gameplay, should send and recv position
}

void (*ClientState[]) () =
{
	ClientState_EnterPID,
	ClientState_EnterIP,
	ClientState_ConnectFailed,
	ClientState_BootGame,
	ClientState_Navigate,
	ClientState_Minimize
};

int main()
{
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
		printf("Error: Failed to open DuckStation\n");
		system("pause");
		return;
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

	while (1)
	{
		ClientState[octr->CurrState]();
	}

	system("pause");
}