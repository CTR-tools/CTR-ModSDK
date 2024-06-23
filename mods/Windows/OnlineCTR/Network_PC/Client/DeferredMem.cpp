#include "DeferredMem.h"
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

SOCKET dspineSocket;

void defMemInit()
{
	dspineSocket = getSocket();
}

SOCKET getSocket() //every call to getSocket should be bookmatched by a call to closeSocket.
{
	//https://learn.microsoft.com/en-us/windows/win32/winsock/creating-a-basic-winsock-application
	WSADATA wsadata;
	int ires;
	ires = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (ires != 0)
	{
		printf("WSAStartup failed with code: %d\n", ires);
		return NULL;
	}
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	ires = getaddrinfo("127.0.0.1", "28011", &hints, &result); //DS PINE (switching to 127.0.0.1 may skip local DNS?)
	if (ires != 0)
	{
		printf("getaddrinfo failed with code: %d\n", ires);
		WSACleanup();
		return NULL;
	}
	SOCKET sock = INVALID_SOCKET;
	ptr = result;
	sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (sock == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return NULL;
	}
	ires = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (ires == SOCKET_ERROR)
	{
		closesocket(sock);
		printf("Error trying to connect socket: %ld\n", WSAGetLastError());
		sock = INVALID_SOCKET;
	}
	freeaddrinfo(result);
	if (sock == INVALID_SOCKET)
	{
		printf("Unable to connect to DuckStation PINE!\n");
		WSACleanup();
		return NULL;
	}
	else
		printf("DuckStation PINE socket acquired.\n");
	u_long mode = 1;
	ires = ioctlsocket(sock, FIONBIO, &mode); //make the socket non-blocking
	if (ires == SOCKET_ERROR)
	{
		printf("Unable to put the socket into non-blocking mode.\n");
		return NULL;
	}
	return sock;
}

void closeSocket(SOCKET* socket) //should be preceded by a call to getSocket
{
	if (*socket != INVALID_SOCKET)
		closeSocket(socket);
	WSACleanup();
}

/*
* I'm not sure if I understand the PINE api quite correctly, but it might be possible
* to queue and batch read/write commands (which would probably be good).
*
* send it out when the gigabuffer is full and/or X times per second.
*/

void readMemorySegment(unsigned int addr, size_t len, char* buf)
{
	constexpr unsigned int sendBufLen = 10;
	constexpr unsigned int recvBufLen = 13;
	//sendBuffer is 10 instead of 9 bc of this bug in ds, can revert when fixed.
	//https://github.com/stenzek/duckstation/pull/3230

	//ensure no outstanding recvs() (e.g., from writeMemorySegment)
	//bc we don't want to confuse those recvs with recvs for this function
	//since we're using tcp, we can increment a counter on write sends,
	//and decriment it on write recvs, and just sit and wait until there
	//are no outstanding recvs() (i.e., counter == 0)

	//either make socket blocking again *or* find non-busy wait soln
	//to wait for when recv() is ready to give us data
	char sendBuffer[sendBufLen] = { 0,0,0,0,0,0,0,0,0 }; //10 = packetSize
	sendBuffer[0] = sendBufLen & 0xFF; //10 = packetSize
	sendBuffer[1] = (sendBufLen >> 8) & 0xFF; //10 = packetSize
	sendBuffer[2] = (sendBufLen >> 16) & 0xFF; //10 = packetSize
	sendBuffer[3] = (sendBufLen >> 24) & 0xFF; //10 = packetSize
	sendBuffer[4] = DSPINEMsgRead64;
	char recieveBuffer[recvBufLen];
	size_t roundedLen = len + ((len % 8 != 0) ? (8 - (len % 8)) : 0);
	for (size_t i = 0; i < roundedLen; i += 8)
	{ //8 byte transfer(s)
		//send section
		unsigned int offsetaddr = addr + i;

		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;

		send(dspineSocket, sendBuffer, recvBufLen, 0); //10 = packetSize	
	}
	//poll?
	for (size_t i = 0; i < roundedLen; i += 8)
	{
		//recieve section
		int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
		if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen && recieveBuffer[4] == 0)
			; //very good
		else if (recvLen == SOCKET_ERROR)
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
		else
			exit(-69420); //could be caused by many things.
		for (size_t c = 0; c < 8; c++)
			if (i + c < len)
				buf[i + c] = recieveBuffer[c + 5];
	}
}

void writeMemorySegment(unsigned int addr, size_t len, char* buf)
{
	constexpr unsigned int sendBufLen = 18;
	constexpr unsigned int recvBufLen = 5;
	//TODO:
	/*
	* Make send non-blocking, and make recv's SOCKET_ERROR check &
	* recieveBuffer[0] == 5 check happen on another thread.
	*
	* Write only needs to be fire & forget, and if a error does occur
	* during this process, it's unrecoverable so we don't need it synced
	*
	* Unfortunately I don't see how this strategy can apply to readMemorySegment()
	* since we actually need the recv() data right now.
	*/

	//ensure socket is set to non-blocking
	char sendBuffer[sendBufLen] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //18 = packetSize
	sendBuffer[0] = sendBufLen & 0xFF; //18 = packetSize
	sendBuffer[1] = (sendBufLen >> 8) & 0xFF; //18 = packetSize
	sendBuffer[2] = (sendBufLen >> 16) & 0xFF; //18 = packetSize
	sendBuffer[3] = (sendBufLen >> 24) & 0xFF; //18 = packetSize
	sendBuffer[4] = DSPINEMsgWrite64;
	char recieveBuffer[recvBufLen]; //idk
	size_t whole = len - (len % 8);
	for (size_t i = 0; i < whole; i += 8)
	{ //8 byte transfer(s)
		//send section
		unsigned int offsetaddr = addr + i;

		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[9] = buf[i + 0];
		sendBuffer[10] = buf[i + 1];
		sendBuffer[11] = buf[i + 2];
		sendBuffer[12] = buf[i + 3];
		sendBuffer[13] = buf[i + 4];
		sendBuffer[14] = buf[i + 5];
		sendBuffer[15] = buf[i + 6];
		sendBuffer[16] = buf[i + 7];

		send(dspineSocket, sendBuffer, sendBufLen, 0); //18 = packetSize
	}
	//recv should call back to a function that ensures 'very good' case, otherwise exit (unrecoverable).
	for (size_t i = 0; i < whole; i += 8)
	{
		//recieve section
		int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
		if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen && recieveBuffer[4] == 0)
			; //very good
		else if (recvLen == SOCKET_ERROR)
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
		else
			exit(-69420); //could be caused by many things.
	}

	//this section takes care of the leftover bit at the end that isn't divisible by 8.
	//unfortunately, this implementation currently reads the existing 8-byte block, then just
	//overwrites the leftover bit at the beginning of said 8-byte block, and recommits it.
	//
	//that means, for any call that isn't exactly a multiple of 8 bytes, will consist of
	//n/8 (rounded down) api write calls, followed by 1 read call, followed by 1 more write call.
	//the limiting behavior of this diminishes api-calls=O(~n), but for small n (which is most
	//of the calls), it's more like api-calls=3*O(~n) (e.g., 15 bytes, one write, one read, one more write).
	//
	//It would be a lot better if the API supported larger memory batch copies, and it very well might,
	//But for the life of me I can't find *good* and *ACCURATE* documentation on PINE.
	//see DSPINE.h for some detail on the inaccuracy of the claims of the API.

	size_t rem = (len % 8 == 0) ? 0 : (8 - (len % 8));
	if (rem != 0) //this section needs testing
	{
		//TODO: change this to not require a read (writes only).
		unsigned int offsetaddr = addr + whole;
		readMemorySegment(offsetaddr, 8, &sendBuffer[9]);
		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
		for (size_t i = 0; i < rem; i++)
			sendBuffer[9 + i] = buf[whole + i];
		send(dspineSocket, sendBuffer, sendBufLen, 0); //18 = packetSize
		int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
		if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen)
			; //very good
		else if (recvLen == SOCKET_ERROR)
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
		else
			exit(-69420); //could be caused by many things.
	}
}

void ps1mem::writeRaw(unsigned int addr, char val) //this should probably use DSPINEMsgWrite8
{
	char buf[sizeof(char)] = { val };
	writeMemorySegment(addr, sizeof(char), buf);
}

void ps1mem::writeRaw(unsigned int addr, short val)
{
	char buf[sizeof(short)];
	buf[0] = val & 0xFF; //this might be the wrong endianness
	buf[1] = (val >> 8) & 0xFF;
	writeMemorySegment(addr, sizeof(short), buf);
}