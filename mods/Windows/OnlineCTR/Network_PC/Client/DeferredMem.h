#pragma once
#include <WinSock2.h>
#include "DSPINE.h"
#include <memory>
#include <functional>
//#include <memory>

SOCKET dspineSocket;
void init();
SOCKET getSocket();
void closeSocket(SOCKET* socket);
void readMemorySegment(unsigned int addr, size_t len, char* buf);
void writeMemorySegment(unsigned int addr, size_t len, char* buf);

//template<typename T>
//T* read

//class mem
//{
//
//} ps1mem;
//
//template<typename T>
//class ps1pointer
//{
//	unsigned int address;
//
//	//suppose you have a variable named "ptr" of type "ps1pointer"
//	//in order to transparently treat this as though it is actually ps1 mem
//	//we need to overload the following operators:
//	//ptr->
//	//*ptr
//	//*ptr =
//	//ptr = (rval of type unsigned int, gets automatically turned into ps1pointer)
//	//ptr[x]         //just *(ptr + (x))
//
//public:
//	ps1pointer(unsigned int addr) : address(addr) {}
//
//	T& operator*() const
//	{
//		char buf[sizeof(T)];
//		readMemorySegment(address, sizeof(T), buf);
//		return ((T)&buf[0]);
//	}
//};

void init()
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
	ires = getaddrinfo("localhost", "28011", &hints, &result); //DS PINE
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
	return sock;
}

void closeSocket(SOCKET* socket) //should be preceded by a call to getSocket
{
	if (*socket != INVALID_SOCKET)
		closeSocket(socket);
	WSACleanup();
}

void readMemorySegment(unsigned int addr, size_t len, char* buf)
{
	//sendBuffer is 10 instead of 9 bc of this bug in ds, can revert when fixed.
	//https://github.com/stenzek/duckstation/pull/3230

	char sendBuffer[10] = { 0,0,0,0,0,0,0,0,0 }; //10 = packetSize
	sendBuffer[0] = 10 & 0xFF; //10 = packetSize
	sendBuffer[1] = (10 >> 8) & 0xFF; //10 = packetSize
	sendBuffer[2] = (10 >> 16) & 0xFF; //10 = packetSize
	sendBuffer[3] = (10 >> 24) & 0xFF; //10 = packetSize
	sendBuffer[4] = DSPINEMsgRead64;
	char recieveBuffer[13];
	size_t roundedLen = len + ((len % 8 != 0) ? (8 - (len % 8)) : 0);
	for (size_t i = 0; i < roundedLen; i += 8)
	{ //8 byte transfer(s)
		unsigned int offsetaddr = addr + i;

		sendBuffer[5] = offsetaddr & 0xFF;
		sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
		sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
		sendBuffer[8] = (offsetaddr >> 24) & 0xFF;

		send(dspineSocket, sendBuffer, 10, 0); //10 = packetSize
		int recvLen = recv(dspineSocket, recieveBuffer, 13, 0);
		if (recvLen == 13 && recieveBuffer[0] == 13)
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
	char sendBuffer[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; //18 = packetSize
	sendBuffer[0] = 18 & 0xFF; //18 = packetSize
	sendBuffer[1] = (18 >> 8) & 0xFF; //18 = packetSize
	sendBuffer[2] = (18 >> 16) & 0xFF; //18 = packetSize
	sendBuffer[3] = (18 >> 24) & 0xFF; //18 = packetSize
	sendBuffer[4] = DSPINEMsgWrite64;
	char recieveBuffer[100]; //idk
	size_t whole = len - (len % 8);
	for (size_t i = 0; i < whole; i += 8)
	{ //8 byte transfer(s)
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

		send(dspineSocket, sendBuffer, 18, 0); //18 = packetSize
		int recvLen = recv(dspineSocket, recieveBuffer, 100, 0);
		if (recvLen == 5 && recieveBuffer[0] == 5)
			; //very good
		else if (recvLen == SOCKET_ERROR)
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
		else
			exit(-69420); //could be caused by many things.
	}
	size_t rem = (len % 8 == 0) ? 0 : (8 - (len % 8));
	unsigned int offsetaddr = addr + whole;
	readMemorySegment(offsetaddr, 8, &buf[9]);
	sendBuffer[5] = offsetaddr & 0xFF;
	sendBuffer[6] = (offsetaddr >> 8) & 0xFF;
	sendBuffer[7] = (offsetaddr >> 16) & 0xFF;
	sendBuffer[8] = (offsetaddr >> 24) & 0xFF;
	send(dspineSocket, sendBuffer, 18, 0); //18 = packetSize
	int recvLen = recv(dspineSocket, recieveBuffer, 100, 0);
	if (recvLen == 5 && recieveBuffer[0] == 5)
		; //very good
	else if (recvLen == SOCKET_ERROR)
	{
		printf("recv failed: %d\n", WSAGetLastError());
	}
	else
		exit(-69420); //could be caused by many things.
}

/// <summary>
/// Reads the specified address from PS1 (emulator RAM) and casts it as a unique pointer.
///
/// The object itself is only a copy of emulator RAM, so to commit changes, use writeObject
/// </summary>
template<typename T>
std::unique_ptr<T, std::function<void(T*)>> readObject(unsigned int addr)
{
	char buf[] = new char[sizeof(T)]/*()*/; //not necessary since we overwrite it with readMemorySegment
	readMemorySegment(addr, sizeof(T), buf);
	return std::unique_ptr<T, std::function<void(T*)>>((T*)&buf[0], [](T* val) { delete[] buf; });
}