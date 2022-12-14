#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#define WINDOWS_INCLUDE
#include "../../Network_PS1/src/global.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

struct SocketCtr
{
	SOCKET socket;

#if 0
	Message sendBuf;
	Message sendBufPrev;
	Message recvBuf;
	Message recvBufPrev;
#endif
};

struct SocketCtr CtrMain;
short characterIDs[8];
#define MAX_CLIENTS 8

unsigned char clientCount = 0;
struct SocketCtr CtrClient[MAX_CLIENTS];

fd_set master;

int state = 0;
enum ServerState
{
	SERVER_BOOT,
	SERVER_LOBBY,
};

void ServerState_Boot()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 480, 240 + 35, TRUE);

	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		system("pause");
	}

	// TCP, port 1234 (call of duty uses 27000), 
	// accept from any (INADDR_ANY) address
	struct sockaddr_in socketIn;
	socketIn.sin_family = AF_INET;
	socketIn.sin_port = htons(1234);
	socketIn.sin_addr.S_un.S_addr = INADDR_ANY;
	CtrMain.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(CtrMain.socket, (struct sockaddr*)&socketIn, sizeof(socketIn));
	listen(CtrMain.socket, SOMAXCONN);
	printf("NodeServer ready on port 1234\n\n");

	// set LISTENING socket to non-blocking
	unsigned long nonBlocking = 1;
	iResult = ioctlsocket(CtrMain.socket, FIONBIO, &nonBlocking);

	FD_ZERO(&master);
	FD_SET(CtrMain.socket, &master);

	for (int i = 0; i < clientCount; i++)
	{
		closesocket(CtrClient[i].socket);
		FD_CLR(CtrClient[i].socket, &master);
	}

	clientCount = 0;
	printf("\nClientCount: 0\n");
	state = SERVER_LOBBY;
}

void CheckNewClients()
{
	fd_set copy = master;

	// See who's talking to us
	int socketCount = select(0, &copy, 0, 0, 0);

	// Loop through all the current connections / potential connect
	for (int i = 0; i < socketCount; i++)
	{
		// Makes things easy for us doing this assignment
		SOCKET sock = copy.fd_array[i];

		// Is it an inbound communication?
		if (sock == CtrMain.socket)
		{
			// Accept a new connection
			SOCKET client = accept(CtrMain.socket, 0, 0);

			if (clientCount == MAX_CLIENTS)
			{
				closesocket(client);
				FD_CLR(CtrClient[i].socket, &master);
				return;
			}

			// Add the new connection to the list of connected clients
			FD_SET(client, &master);

			// set socket to non-blocking
			unsigned long nonBlocking = 1;
			ioctlsocket(client, FIONBIO, &nonBlocking);

			// save client in array,
			// this is bad though, cause if someone disconnects and 
			// reconnects, they'll overwrite another socket in the array,
			// I'll fix it later
			CtrClient[clientCount++].socket = client;

			// Send ClientID and clientCount back to all clients
			for (int j = 0; j < clientCount; j++)
			{
				struct SG_MessageWelcome mw;
				mw.type = SG_WELCOME;
				mw.size = sizeof(struct SG_MessageWelcome);
				mw.boolLastMessage = 1;
				mw.clientID = j;
				mw.numClientsTotal = clientCount;

				// send a message to the client
				send(CtrClient[j].socket, &mw, mw.size, 0);
			}

			printf("ClientCount: %d\n", clientCount);
		}
	}
}

void ParseMessage(int i)
{
	char recvBuf[8];
	memset(recvBuf, 0xFF, 8);

	int recvByteCount;
	recvByteCount = recv(CtrClient[i].socket, recvBuf, 8, 0);

	// This happens when the server uses closesocket(),
	// either because you connected to a full server, or
	// a client disconnected so the server reset
	if (recvByteCount == 0)
	{
		//Disconnect();
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

			// client closed connection
			if (err == WSAENOTCONN)
			{

			}

			return;
		}
	}

	if (recvByteCount != ((struct CG_Header*)recvBuf)->size)
	{
		//printf("Bug! -- Tag: %d, recvBuf.size: %d, recvCount: %d\n",
		//	recvBuf.type, recvBuf.size, receivedByteCount);

		// dont disconnect, just try again next cycle
	}

	// if recvSize is equal to expected, and if type is valid
	else if (((struct CG_Header*)recvBuf)->type < CG_COUNT)
	{
		// switch will compile into a jmp table, no funcPtrs needed
		switch (((struct CG_Header*)recvBuf)->type)
		{
		case CG_TRACK:

			printf("Got Track from %d\n", i);

			int trackID = ((struct CG_MessageTrack*)recvBuf)->trackID;
			
			struct SG_MessageTrack mt;
			mt.type = SG_TRACK;
			mt.size = sizeof(struct CG_MessageTrack);
			mt.boolLastMessage = 1;
			mt.trackID = trackID;

			// send a message all other clients
			for (int j = 0; j < 8; j++)
			{
				if (
						// skip empty sockets, skip self
						(CtrClient[j].socket != 0) &&
						(i != j)
					)
				{
					printf("Give Track to %d\n", j);
					send(CtrClient[j].socket, &mt, mt.size, 0);
				}
			}
			break;
		default:
			break;
		}
	}
}

void ServerState_Lobby()
{
	CheckNewClients();

	// check messages in sockets
	for (int i = 0; i < 8; i++)
	{
		if (CtrClient[i].socket != 0)
		{
			ParseMessage(i);
		}
	}
}

void (*ServerState[]) () =
{
	ServerState_Boot,
	ServerState_Lobby
};

int main()
{
	while (1)
	{
		ServerState[state]();
	}
}