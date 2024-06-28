//TODO: similar to CL_main.cpp/blockUntilDuckstationIsOpen(), we need to
//make the various includes for this file platform independent & change
//socket impl as necessary.

#include "DeferredMem.h"
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <atomic>
#include <thread>

SOCKET dspineSocket;
std::atomic<int> outstandingReads = 0;
std::thread recvWorker;

void recvThread();

void defMemInit()
{
	dspineSocket = initSocket();
	recvWorker = std::thread{ recvThread };
}

SOCKET initSocket() //every call to initSocket should be bookmatched by a call to closeSocket.
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

void closeSocket(SOCKET* socket) //should be preceded by a call to initSocket
{
	if (*socket != INVALID_SOCKET)
		closeSocket(socket);
	WSACleanup();
}

void recvThread()
{
	constexpr unsigned int recvBufLen = 5;
	char recieveBuffer[recvBufLen];

	while (true)
	{
		while (outstandingReads > 0)
		{
			WSAPOLLFD fdarr = { 0 };
			fdarr.fd = dspineSocket;
			fdarr.events = POLLRDNORM;
			WSAPoll(&fdarr, 1, -1);
			int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
			if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen && recieveBuffer[4] == 0)
				outstandingReads--; //very good
			else 
			{
				if (recvLen < recvBufLen)
					printf("recv returned less than required buffer length ");
				printf("recv AAA failed: %d\n", WSAGetLastError());
				exit(-69420); //could be caused by many things.
			}
		}
	}
}

/* Relevant to read/writeMemorySegment
*
* It seems that the duckstation pine_server.cpp (see void PINEServer::PINESocket::ProcessCommandsInBuffer())
* is written in such a way that if you send a bunch of "concatenated packets" in a single send, it's still handled well
* & splits them up into their individual packets.
*
* However, this only works if https://github.com/stenzek/duckstation/pull/3230 is implemented.
*
* That means if we implement an algorithm to buffer everything, then send either
* 1. when the buffer is full
* 2. a minimum of X times per second (for latency)
*
* might reduce network traffic on localhost, which could be critical in high-throughput gameplay segments.
*/

//static bool formulatePacket(char* resultBuf, size_t maxLen, int DSPINEMode, unsigned int addr = (unsigned int)nullptr, char* data)
//{
//
//}

void readMemorySegment(unsigned int addr, size_t len, char* buf)
{
	//TODO: mutex
	while (outstandingReads > 0) { ; } //wait for no more recvs
	constexpr unsigned int sendBufLen = 10;
	constexpr unsigned int recvBufLen = 13;
	//sendBuffer is 10 instead of 9 bc of this bug in ds, can revert when fixed.
	//https://github.com/stenzek/duckstation/pull/3230

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
		
		send(dspineSocket, sendBuffer, sendBufLen, 0); //10 = packetSize	
	}
	for (size_t i = 0; i < roundedLen; i += 8)
	{
		//recieve section
		WSAPOLLFD fdarr = { 0 };
		fdarr.fd = dspineSocket;
		fdarr.events = POLLRDNORM;
		WSAPoll(&fdarr, 1, -1); //blocks until we have some data ready
		int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
		if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen && recieveBuffer[4] == 0)
			; //very good
		else if (recvLen == SOCKET_ERROR)
		{
			if (recvLen < recvBufLen)
				printf("recv returned less than required buffer length "); //if this starts becoming a problem then we need recv in a buffer loop.
			printf("recv BBB failed: %d\n", WSAGetLastError());
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
	//This macro accounts & compensates for a bug present in duckstation that was fixed in
	//https://github.com/stenzek/duckstation/pull/3230 versions of duckstation older than
	//this will not function with this client without this option set to 1.
	//(However, duckstations with this fix will have no issues with the fix applied).
	//Set to 1 to enable the fix, set to 0 to disable it.
	#define applyBufferFix 1
	#define maxSendBufLen 17 * 50 //must be >= 34
#if maxSendBufLen < 34
#error maxSendBufLen must be at least 34
#endif
	char sendBuffer[maxSendBufLen]; //keep in mind this is on the stack
	size_t sendBufPtr = 0;
	size_t whole = len - (len % 8); //is a multiple of 8
	size_t rem = len - whole; //whatever is left over.
	for (size_t i = 0; i < whole; i += 8) //1 loop iter uses 17 bytes.
	{
		sendBuffer[sendBufPtr + 0] = 17 & 0xFF;
		sendBuffer[sendBufPtr + 1] = (17 >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 2] = (17 >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 3] = (17 >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 4] = DSPINEMsgWrite64;
		unsigned int offsetaddr = addr + i;
		sendBuffer[sendBufPtr + 5] = offsetaddr & 0xFF;
		sendBuffer[sendBufPtr + 6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 9] = buf[i + 0];
		sendBuffer[sendBufPtr + 10] = buf[i + 1];
		sendBuffer[sendBufPtr + 11] = buf[i + 2];
		sendBuffer[sendBufPtr + 12] = buf[i + 3];
		sendBuffer[sendBufPtr + 13] = buf[i + 4];
		sendBuffer[sendBufPtr + 14] = buf[i + 5];
		sendBuffer[sendBufPtr + 15] = buf[i + 6];
		sendBuffer[sendBufPtr + 16] = buf[i + 7];
		sendBufPtr += 17;
		outstandingReads++; //this line must come before send or race condition
		if (sendBufPtr + 17 > maxSendBufLen)
		{ //we're full, time to send.
			int res = send(dspineSocket, sendBuffer, sendBufPtr + applyBufferFix, 0);
			if (res != sendBufPtr)
			{
				if (res == SOCKET_ERROR)
				{
					exit(-69420);
				}
				else
				{
					//partial send???
					exit(-69420);
				}
			}
			sendBufPtr = 0;
		}
	}
	int reqSize = ((rem & 4) != 0 ? 13 : 0) + ((rem & 2) != 0 ? 11 : 0) + ((rem & 1) != 0 ? 10 : 0);
	if (sendBufPtr + reqSize > maxSendBufLen)
	{ //we would be >=full if we did the rem sends.
		int res = send(dspineSocket, sendBuffer, sendBufPtr + applyBufferFix, 0);
		if (res != sendBufPtr)
		{
			if (res == SOCKET_ERROR)
			{
				exit(-69420);
			}
			else
			{
				//partial send???
				exit(-69420);
			}
		}
		sendBufPtr = 0;
	}
	unsigned int offsetaddr = addr + whole;
	//note: rem is [0-7] inclusive
	//if all three of these run, sendBuffer must be at least 34 bytes.
	if ((rem & 4) != 0) //we need a 4
	{
		int sz = 9 + 4;
		sendBuffer[sendBufPtr + 0] = sz & 0xFF;
		sendBuffer[sendBufPtr + 1] = (sz >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 2] = (sz >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 3] = (sz >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 4] = DSPINEMsgWrite32;
		sendBuffer[sendBufPtr + 5] = offsetaddr & 0xFF;
		sendBuffer[sendBufPtr + 6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 9] = buf[sendBufPtr + whole + 0];
		sendBuffer[sendBufPtr + 10] = buf[sendBufPtr + whole + 1];
		sendBuffer[sendBufPtr + 11] = buf[sendBufPtr + whole + 2];
		sendBuffer[sendBufPtr + 12] = buf[sendBufPtr + whole + 3];
		outstandingReads++; //this line must come before send or race condition
		offsetaddr += 4;
		sendBufPtr += sz;
	}
	if ((rem & 2) != 0)
	{
		int sz = 9 + 2;
		sendBuffer[sendBufPtr + 0] = sz & 0xFF;
		sendBuffer[sendBufPtr + 1] = (sz >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 2] = (sz >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 3] = (sz >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 4] = DSPINEMsgWrite16;
		sendBuffer[sendBufPtr + 5] = offsetaddr & 0xFF;
		sendBuffer[sendBufPtr + 6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 9] = buf[sendBufPtr + whole + 0];
		sendBuffer[sendBufPtr + 10] = buf[sendBufPtr + whole + 1];
		outstandingReads++; //this line must come before send or race condition
		offsetaddr += 2;
		sendBufPtr += sz;
	}
	if ((rem & 1) != 0)
	{
		int sz = 9 + 1;
		sendBuffer[sendBufPtr + 0] = sz & 0xFF;
		sendBuffer[sendBufPtr + 1] = (sz >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 2] = (sz >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 3] = (sz >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 4] = DSPINEMsgWrite8;
		sendBuffer[sendBufPtr + 5] = offsetaddr & 0xFF;
		sendBuffer[sendBufPtr + 6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[sendBufPtr + 7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[sendBufPtr + 8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[sendBufPtr + 9] = buf[sendBufPtr + whole + 0];
		outstandingReads++; //this line must come before send or race condition
		offsetaddr += 1;
		sendBufPtr += sz;
	}
	if (sendBufPtr != 0)
	{
		int res = send(dspineSocket, sendBuffer, sendBufPtr + applyBufferFix, 0);
		if (res != sendBufPtr)
		{
			if (res == SOCKET_ERROR)
			{
				exit(-69420);
			}
			else
			{
				//partial send???
				exit(-69420);
			}
		}
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