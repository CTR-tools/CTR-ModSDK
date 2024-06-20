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

template<typename T>
class ps1ptr
{
	/// <summary>
	/// Note to future maintainers:
	///
	/// The largest element of latency when communicating with emulator RAM is probably read/writeMemorySegment.
	///
	/// Each of these calls actually just splits up the memory into 8-byte chuncks and read/writes them via PINE
	/// (8 bytes is the largest size the API supports I believe).
	///
	/// *if* when you readMemorySegment in the ctor/refresh, you made an additional "reference copy" of the data,
	/// when it comes time to commit(), you can walk through the data and only make calls for the data that *actually*
	/// changed.
	///
	/// If you're working with a large data structure (e.g., CTROnline = 228 bytes), and only a *single* byte was changed,
	/// You can reduce the number of API calls within writeMemorySegment() from approximately 228/8 to 1.
	///
	/// However, these benefits disappear e.g., if many "scattered" changes were made throughout the data structure, and that
	/// many locations were changed such that for every block of 8 bytes within the structure, at least 1 byte within that
	/// segment was changed. In this case, the number of API calls is the same as if you just committed the whole structure.
	/// (which is no worse then what is currently being done).
	/// </summary>

public:
	typedef std::shared_ptr<T> ptrtype;
private:
	unsigned int address;
	char* buf;
	ptrtype bufferedVal; //implicit dtor will delete this, which deletes the buf
public:
	/// <summary>
	/// Reads the specified address from PS1 (emulator RAM), copies it, and creates a shared_ptr.
	///
	/// The object itself is only a copy of emulator RAM, so to commit changes, use commit().
	/// If changes have been made to emulator RAM, use refresh() to re-fetch the underlying memory.
	///
	/// When this object falls out of scope, any changes made will *not* be automatically committed.
	/// Do it yourself.
	/// </summary>
	ps1ptr(unsigned int addr) : address(addr)
	{
		buf = new char[sizeof(T)]/*()*/; //not necessary since we overwrite it with readMemorySegment
		readMemorySegment(address, sizeof(T), buf);
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; });
	}
	operator ptrtype() const
	{
		return bufferedVal;
	}
	/// <summary>
	/// Writes the memory this ps1ptr represents back to ps1 memory.
	/// </summary>
	void commit()
	{
		writeMemorySegment(address, sizeof(T), buf);
	}
	/// <summary>
	/// Re-fetches the memory this ps1ptr represents from ps1 memory.
	/// </summary>
	void refresh()
	{
		readMemorySegment(address, sizeof(T), buf);
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; });
	}
	ptrtype get()
	{
		return bufferedVal;
	}
};

class ps1mem
{
private:
	unsigned int address;
public:
	ps1mem(unsigned int addr) : address(addr) { }

	/// <summary>
	/// Creates a ps1ptr of the specified address, offset by the address of this ps1mem.
	/// </summary>
	template<typename T>
	ps1ptr<T> at(unsigned int addr)
	{
		return ps1ptr<T>(addr + address);
	}
};