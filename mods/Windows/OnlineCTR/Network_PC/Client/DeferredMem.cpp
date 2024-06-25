#ifdef _WIN64 //windows
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#else //assume posix
#error todo...
//todo:
//include whatever headers we need for posix sockets & posix sockets implementations.
#endif

#include "DeferredMem.h"
#include <atomic>
#include <thread>
#include <semaphore>
#include <condition_variable>

#if _WIN64 //windows
SOCKET dspineSocket;
#else //assume posix
#error todo...
//todo:
//declare a variable of whatever type a posix socket is.
#endif
//std::atomic<int> outstandingReads = std::atomic<int>{ 0 }; //this is covered by mutex
int outstandingReads = 0; //this is covered by mutex
std::thread recvWorker;
std::mutex recvMutex;
std::condition_variable recvCond;

void defMemInit()
{
#if _WIN64 //windows
	dspineSocket = initSocket();
#else //assume posix
#error todo...
	//todo:
	//call posix version of initSocket() and assign to the posix dspineSocket variable.
#endif
	recvWorker = std::thread{ recvThread };
}

#if _WIN64 //windows
SOCKET initSocket() //every call to initSocket should be bookmatched by a call to uninitSocket.
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
		closesocket(sock);
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
	int enable = 1;
	ires = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(int));
	if (ires != 0)
	{
		printf("Unable to enable TCP_NODELAY (disables nagle's algorithm).\n");
		WSACleanup();
		return NULL;
	}
	return sock;
}

void uninitSocket(SOCKET* socket) //should be preceded by a call to initSocket
{
	if (*socket != INVALID_SOCKET)
	{
		WSACleanup();
	}
}
#else //assume posix
#error todo...
//todo:
//implement a posix version of initSocket
//it should:
//	1. create a socket in family AF_INET
//  2. type of SOCK_STREAM (if that granularity exists)
//  3. of protocol TCP
//  4. for ip address 127.0.0.1/localhost and port 28011
//  5. if applicable during socket construction, specify that send()/recv() are *non-blocking*
//	6. ensure that it's connected
//  7. if anything fails, log why, and clean up.
//  8. return the created socket if creation succeeded.

//implement a posix version of uninitSocket
//it should:
//	1. close connection (if open), clean up & invalidate a socket.
#endif

void recvThread()
{
	constexpr unsigned int recvBufLen = 5;
	char recieveBuffer[recvBufLen];

	while (true) //todo: std::condition_variable or similar
	{
		//.notify_all() is necessary here because if writeMemorySegment().notify_all() is called and neither
		//recvThread or readMemorySegment() is waiting, then nothing can come around to re-notify, resulting
		//in deadlock. This .notify_all will wake up readMemorySegment().wait() if it's waiting.
		recvCond.notify_all();
		std::unique_lock<std::mutex> um{ recvMutex };
		recvCond.wait(um, [] { return outstandingReads > 0; });
		while (outstandingReads > 0)
		{
#if _WIN64 //windows
			WSAPOLLFD fdarr = { 0 };
			fdarr.fd = dspineSocket;
			fdarr.events = POLLRDNORM;
			WSAPoll(&fdarr, 1, -1);
			int recvLen = recv(dspineSocket, recieveBuffer, recvBufLen, 0);
			if (recvLen == recvBufLen && recieveBuffer[0] == recvBufLen && recieveBuffer[4] == 0)
			{
				outstandingReads--; //very good
				//printf("recvThread dec %d\n", outstandingReads.load());
			}
			else 
			{
				if (recvLen < recvBufLen)
					printf("recv returned less than required buffer length ");
				printf("recv failed exit(5): %d\n", WSAGetLastError());
				exit(5); //could be caused by many things.
			}
#else //assume posix
#error todo...
			//todo:
			//this should poll/select for a recv event
			//then recv of (maximum) length recvBufLen
			//ensure that the length that was recvd was indeed recvBufLen
			//ensure that recieveBuffer[0] == recvBufLen (PINE PROTOCOL)
			//ensure that recieveBuffer[4] == 0 (PINE PROTOCOL)
			//if any "ensures" fail, then we have reached an unrecoverable error,
			//assume that the socket connection is bad and reset and/or close the client.
#endif
		}

	}
}

void readMemorySegment(unsigned int addr, size_t len, char* buf)
{
	//.notify_all() is necessary here because if writeMemorySegment().notify_all() is called and neither
	//recvThread or readMemorySegment() is waiting, then nothing can come around to re-notify, resulting
	//in deadlock. This .notify_all will wake up recvThread().wait() if it's waiting.
	recvCond.notify_all();
	std::unique_lock<std::mutex> um{ recvMutex };
	recvCond.wait(um, [] { return outstandingReads == 0; });
	/*if (outstandingReads != 0)
		printf("BAD");*/
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

#if _WIN64 //windows
		int res = send(dspineSocket, sendBuffer, sendBufLen, 0); //10 = packetSize
		if (res != sendBufLen)
		{
			printf("send() failed exit(6/7)!");
			if (res == SOCKET_ERROR)
				exit(6);
			else
				exit(7); //partial send???
		}
#else //assume posix
#error todo...
		//posix non-blocking send
#endif
	}
	for (size_t i = 0; i < roundedLen; i += 8)
	{
		//recieve section
#if _WIN64 //windows
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
			printf("recv failed exit(8): %d\n", WSAGetLastError());
			exit(8);
		}
		else
		{
			printf("recv() failed exit(9)!");
			exit(9); //could be caused by many things.
		}
#else //assume posix
#error todo...
		//posix poll/select until at least recvBufLen worth of data is ready
		//posix recv a maximum of recvBufLen worth of data
		//ensure the length that was recvd == recvBufLen
		//ensure that recieveBuffer[0] == recvBufLen (PINE PROTOCOL)
		//ensure that recieveBuffer[4] == 0 (PINE PROTOCOL)
		//if any "ensures" fail, then we have reached an unrecoverable error,
		//assume that the socket connection is bad and reset and/or close the client.
#endif
		for (size_t c = 0; c < 8; c++)
			if (i + c < len)
				buf[i + c] = recieveBuffer[c + 5];
	}
}

void writeMemorySegment(unsigned int addr, size_t len, char* buf/*, bool blocking*/)
{
	std::lock_guard<std::mutex> lock{ recvMutex };
	//This macro accounts & compensates for a bug present in duckstation that was fixed in
	//https://github.com/stenzek/duckstation/pull/3230 versions of duckstation older than
	//this will not function with this client without this option set to 1.
	//(However, duckstations with this fix will have no issues with the fix applied).
	//Set to 1 to enable the fix, set to 0 to disable it.
#define applyBufferFix 1
	constexpr unsigned int sendBufLen = 17 + applyBufferFix;
	char sendBuffer[sendBufLen] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	sendBuffer[0] = sendBufLen & 0xFF; //18 = packetSize
	sendBuffer[1] = (sendBufLen >> 8) & 0xFF; //18 = packetSize
	sendBuffer[2] = (sendBufLen >> 16) & 0xFF; //18 = packetSize
	sendBuffer[3] = (sendBufLen >> 24) & 0xFF; //18 = packetSize
	sendBuffer[4] = DSPINEMsgWrite64;
	//char recieveBuffer[recvBufLen];
	size_t whole = len - (len % 8);
	size_t rem = len - whole; //whatever is left over.
	size_t i = 0;
	for (; i < whole; i += 8)
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
		outstandingReads++;
		//printf("write inc %d\n", outstandingReads.load());
#ifdef _WIN64 //windows
		int res = send(dspineSocket, sendBuffer, sendBufLen, 0);
		if (res != sendBufLen)
		{
			printf("send() failed exit(10/11)!");
			if (res == SOCKET_ERROR)
				exit(10);
			else
				exit(11); //partial send???
		}
#else //assume posix
#error todo...
		//posix non-blocking send of size sendBufLen
#endif
	}
	//note: rem is [0-7] inclusive
	unsigned int offsetaddr = addr + whole;
	if ((rem & 4) != 0) //we need a 4
	{
		int sz = 9 + 4 + applyBufferFix;
		sendBuffer[0] = sz & 0xFF;
		sendBuffer[1] = (sz >> 8) & 0xFF;
		sendBuffer[2] = (sz >> 16) & 0xFF;
		sendBuffer[3] = (sz >> 24) & 0xFF;
		sendBuffer[4] = DSPINEMsgWrite32;
		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[9] = buf[i + whole + 0];
		sendBuffer[10] = buf[i + whole + 1];
		sendBuffer[11] = buf[i + whole + 2];
		sendBuffer[12] = buf[i + whole + 3];
		outstandingReads++; //this line must come before send or race condition
		//printf("write inc %d\n", outstandingReads.load());
		offsetaddr += 4;
		i += 4;
#ifdef _WIN64 //windows
		int res = send(dspineSocket, sendBuffer, sz, 0);
		if (res != sz)
		{
			printf("send() failed exit(12/13)!");
			if (res == SOCKET_ERROR)
				exit(12);
			else
				exit(13); //partial send???
		}
#else //assume posix
#error todo...
		//posix non-blocking send of size sz
#endif
	}
	if ((rem & 2) != 0)
	{
		int sz = 9 + 2 + applyBufferFix;
		sendBuffer[0] = sz & 0xFF;
		sendBuffer[1] = (sz >> 8) & 0xFF;
		sendBuffer[2] = (sz >> 16) & 0xFF;
		sendBuffer[3] = (sz >> 24) & 0xFF;
		sendBuffer[4] = DSPINEMsgWrite16;
		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[9] = buf[i + whole + 0];
		sendBuffer[10] = buf[i + whole + 1];
		outstandingReads++; //this line must come before send or race condition
		//printf("write inc %d\n", outstandingReads.load());
		offsetaddr += 2;
		i += 2;
#ifdef _WIN64 //windows
		int res = send(dspineSocket, sendBuffer, sz, 0);
		if (res != sz)
		{
			printf("send() failed exit(14/15)!");
			if (res == SOCKET_ERROR)
				exit(14);
			else
				exit(15); //partial send???
		}
#else //assume posix
#error todo...
		//posix non-blocking send of size sz
#endif
	}
	if ((rem & 1) != 0)
	{
		int sz = 9 + 1 + applyBufferFix;
		sendBuffer[0] = sz & 0xFF;
		sendBuffer[1] = (sz >> 8) & 0xFF;
		sendBuffer[2] = (sz >> 16) & 0xFF;
		sendBuffer[3] = (sz >> 24) & 0xFF;
		sendBuffer[4] = DSPINEMsgWrite8;
		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
		sendBuffer[9] = buf[i + whole + 0];
		outstandingReads++; //this line must come before send or race condition
		//printf("write inc %d\n", outstandingReads.load());
		offsetaddr += 1;
		i += 1;
#ifdef _WIN64 //windows
		int res = send(dspineSocket, sendBuffer, sz, 0);
		if (res != sz)
		{
			printf("send() failed exit(16/17)!");
			if (res == SOCKET_ERROR)
				exit(16);
			else
				exit(17); //partial send???
		}
#else //assume posix
#error todo...
		//posix non-blocking send of size sz
#endif
	}
	recvCond.notify_all();
}

//void ps1mem::writeRaw(unsigned int addr, char val) //this should probably use DSPINEMsgWrite8
//{
//	char buf[sizeof(char)] = { val };
//	writeMemorySegment(addr, sizeof(char), buf);
//}
//
//void ps1mem::writeRaw(unsigned int addr, short val)
//{
//	char buf[sizeof(short)];
//	buf[0] = val & 0xFF; //this might be the wrong endianness
//	buf[1] = (val >> 8) & 0xFF;
//	writeMemorySegment(addr, sizeof(short), buf);
//}