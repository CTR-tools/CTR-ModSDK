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
#include "Util.h"
#include <atomic>
#include <thread>
#include <semaphore>
#include <condition_variable>
#include <map>
#include <vector>

void recvThread();
typedef unsigned long long internalPineApiID;
internalPineApiID pineSend(DSPINESend sendObj);
void pineRecv();
bool isPineDataPresent(pineApiID id);

#if _WIN64 //windows
SOCKET dspineSocket;
#else //assume posix
#error todo...
//todo:
//declare a variable of whatever type a posix socket is.
#endif
std::thread recvWorker;

std::mutex pineObjsMutex;

/// <summary>
/// Initializes the deferred memory model. Returns false if failed (e.g., TCP socket not connected).
/// If it failed, it needs to be called again until true before the deferred memory model is truly initialized.
/// </summary>
bool defMemInit()
{
#if _WIN64 //windows
	dspineSocket = initSocket();
#else //assume posix
#error todo...
	//todo:
	//call posix version of initSocket() and assign to the posix dspineSocket variable.
#endif
	if (dspineSocket != INVALID_SOCKET)
	{
		recvWorker = std::thread{ recvThread };
		return true;
	}
	else
		return false;
}
bool socketValid()
{
#if _WIN64 //windows
	return dspineSocket != INVALID_SOCKET;
#else //assume posix
#error todo...
#endif
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
	ires = getaddrinfo("127.0.0.1", "28011", &hints, &result); //DS PINE
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
		closesocket(sock);
		WSACleanup();
		return NULL;
	}
	int enable = 1;
	ires = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(int));
	if (ires != 0)
	{
		printf("Unable to enable TCP_NODELAY (disables nagle's algorithm).\n");
		closesocket(sock);
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
	while (true)
	{
		//recvCond.notify_all();
		//std::unique_lock<std::mutex> um{ recvMutex };
		//recvCond.wait(um, [] { return outstandingReads > 0; });
		pineRecv();
	}
}

internalPineApiID pineSendsCount = 0, pineRecvsCount = 0;
/// <summary>
/// Upon a call to pineSend(), an entry in this collection will be made, where the value contains
/// just the "send" portion of the DSPINESendRecvPair if the bool is false, and the value contains
/// both portions of the DSPINESendRecvPair if the bool is true.
/// </summary>
std::map<internalPineApiID, std::pair<DSPINESendRecvPair, bool>> pineObjs{};

internalPineApiID pineSend(DSPINESend sendObj)
{ //could be on another thread, but since tcp send is non-blocking it doesn't really matter.
	//tcp send
	#if _WIN64 //windows
	//critical region (syncronize access pls)
	{
		//need to add it first because the second we send (right after this) the recv thread might try
		//to add it *before* we've even made the entry for it, which would be bad.
		std::lock_guard<std::mutex> um{ pineObjsMutex };
		pineObjs.insert(std::pair<internalPineApiID, std::pair<DSPINESendRecvPair, bool>>{ pineSendsCount, std::pair<DSPINESendRecvPair, bool>{ DSPINESendRecvPair{ sendObj, DSPINERecv{} }, false } });
	}
	//end critical region
	int res = send(dspineSocket, (const char*)&sendObj, sendObj.shared_header.packetSize, 0);
	if (res != sendObj.shared_header.packetSize)
	{
		printf("send() failed!\n");
		if (res == SOCKET_ERROR)
			exit_execv(6);
		else
			exit_execv(7); //partial send???
	}
	#else //assume posix
	#error todo...
	//posix non-blocking send
	#endif
	return pineSendsCount++;
}

std::condition_variable waitPineDataCV;

void pineRecv()
{ //on another thread
	DSPINERecv recvData{};
	#if _WIN64 //windows
	WSAPOLLFD fdarr = { 0 };
	fdarr.fd = dspineSocket;
	fdarr.events = POLLRDNORM;
	WSAPoll(&fdarr, 1, -1); //block until something is waiting in tcp buffer.
	int recvLen = recv(dspineSocket, (char*)&recvData, sizeof(DSPINERecv::SharedHeader), 0);
	if (recvLen == sizeof(DSPINERecv::SharedHeader) &&
		//recvData.shared_header.packetSize == /*whatever size this recv is meant to be*/ &&
		recvData.shared_header.DSPINEMsgReplyCode == 0)
	{ //very good
	}
	else
	{
		if (recvLen < sizeof(DSPINERecv::SharedHeader)) //todo: make consumer buffer for this
			printf("recv returned less than required buffer length (?packet fragmentation?) "); //partial recv could be solved by coroutine
		printf("recv failed: %d\n", WSAGetLastError());
		exit_execv(5); //could be caused by many things.
	}
	unsigned int remainingSize = recvData.shared_header.packetSize - sizeof(DSPINERecv::SharedHeader);
	if (remainingSize != 0)
	{
		//no need to poll bc the first 5 bytes of this packet (which have already been parsed) and whatever remains
		//(regardless of packet size) should never have been fragmented (hopefully!)
		recvLen = recv(dspineSocket, ((char*)&recvData) + sizeof(DSPINERecv::SharedHeader), remainingSize, 0);
		if (recvLen == remainingSize)
		{ //very good
		}
		else
		{
			if (recvLen < remainingSize) //todo: make consumer buffer for this
				printf("recv returned less than required buffer length (?packet fragmentation?) "); //partial recv could be solved by coroutine
			else
				printf("recv returned ?*MORE*? than the required buffer length (corrupted stack)??? ");
			printf("recv failed: %d\n", WSAGetLastError());
			exit_execv(5); //could be caused by many things.
		}
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
	//critical region (syncronize access pls)
	{
		std::lock_guard<std::mutex> um{ pineObjsMutex };
		auto& e = pineObjs.at(pineRecvsCount);
		e.first.recvData = recvData;
		e.second = true;
		pineRecvsCount++;
		waitPineDataCV.notify_all();
	}
	//end critical region
}

pineApiID pineApiRequestCount = 0;
/// <summary>
/// A single "pineApiID" correlates to a group of "internalPineApiID". If the boolean is true,
/// then the entry is active, if it's false, then it's marked for the garbage collector.
/// </summary>
std::map<pineApiID, std::pair<std::vector<internalPineApiID>, bool>> pineApiRequests{};

void markPineDataForGC(pineApiID id)
{
	auto& dat = pineApiRequests.at(id).second = false;
}

void GCDeadPineData()
{
	std::vector<pineApiID> toRemove{};
	std::vector<internalPineApiID> intToRemove{};
	for (auto& e : pineApiRequests)
	{
		if (!e.second.second && isPineDataPresent(e.first))
		{
			toRemove.push_back(e.first);
			for (auto& iid : e.second.first)
			{
				intToRemove.push_back(iid);
			}
		}
	}
	//remove eligible data.
	for (auto& id : toRemove)
	{
		pineApiRequests.erase(id);
	}
	//critical region (syncronize access pls)
	std::lock_guard<std::mutex> um{ pineObjsMutex };
	{
		for (auto& iid : intToRemove)
		{
			pineObjs.erase(iid);
		}
	}
	//end critical region
}

/// <summary>
/// Checks if all the data correlated with a single pineApiID has been fully recieved.
///
/// !!!WARNING!!! Callers of this function must acquire the "pineObjsMutex" before calling.
/// This function is internal, and should not be called outside the API.
/// </summary>
bool isPineDataPresent(pineApiID id)
{
	bool isAllPresent = true;
	auto& dat = pineApiRequests.at(id).first;
	//critical region (syncronize access pls)
	{
		//CALLERS MUST ACQUIRE THIS MUTEX BEFORE CALLING!
		//std::lock_guard<std::mutex> um{ pineObjsMutex };
		for (size_t i = 0; i < dat.size(); i++)
		{
			isAllPresent &= pineObjs.at(dat[i]).second; //this bool is only true when it's been recvd
		}
	}
	//end critical region
	return isAllPresent;
}

void waitUntilPineDataPresent(pineApiID id)
{
	std::unique_lock<std::mutex> ul{ pineObjsMutex };
	//its possible that after we've acquired the mutex, the data arrives, but it arrives
	//BEFORE the .wait call, (i.e., waitPineDataCV.notify_all() gets called before .wait()), leading to deadlock.
	if (!isPineDataPresent(id))
		waitPineDataCV.wait(ul, [id] { return isPineDataPresent(id); });
}

std::vector<DSPINESendRecvPair> getPineDataSegment(pineApiID id)
{
	std::vector<DSPINESendRecvPair> segment{};
	auto& dat = pineApiRequests.at(id).first;
	//critical region (syncronize access pls)
	{
		std::lock_guard<std::mutex> um{ pineObjsMutex };
		for (size_t i = 0; i < dat.size(); i++)
		{
			DSPINESendRecvPair obj = pineObjs.at(dat[i]).first;
			segment.push_back(obj);
		}
	}
	//end critical region
	return segment;
}

pineApiID send_readMemorySegment(unsigned int addr, size_t len)
{
	if (len == 0)
		exit_execv(10); //this function only works if you attempt to read a non-zero length of memory.
	std::vector<internalPineApiID> iids{};
	//size_t roundedUpLen = len + ((len % 8 != 0) ? (8 - (len % 8)) : 0);
	size_t roundedUpLen = ((len & 0x7) != 0) ? (len & ~0x7) + 8 : len; //should be identical to above
	for (size_t i = 0; i < roundedUpLen; i += 8)
	{
		DSPINESend sendObj{};
		//TODO: verify that this assigns members like packetsize etc. correctly automatically.
		sendObj.read64 = DSPINERead64Send{};
		sendObj.read64.address = addr + i;
		iids.push_back(pineSend(sendObj));
	}
	pineApiRequests.insert(std::pair<pineApiID, std::pair<std::vector<internalPineApiID>, bool>>{pineApiRequestCount, std::pair<std::vector<internalPineApiID>, bool>{ iids, true }});
	return pineApiRequestCount++;
}

pineApiID send_writeMemorySegment(unsigned int addr, size_t len, char* buf, char* originalBuf)
{
	if (len == 0)
		exit_execv(11); //this function only works if you attempt to write a non-zero length of memory.
	std::vector<internalPineApiID> iids{};
	auto dispatchContig = [&iids](unsigned int address, size_t length, char* buffer)
	{
		pineApiID firstSendID = 0;
		size_t sendCount = 0; //may not necessarily result in whole / 8
		size_t whole = length - (length % 8);
		size_t rem = length - whole; //whatever is left over.
		//size_t i = 0;
		for (size_t i = 0; i < whole; i += 8)
		{
			DSPINESend sendObj{};
			//TODO: verify that this assigns members like packetsize etc. correctly automatically.
			sendObj.write64 = DSPINEWrite64Send{};
			sendObj.write64.address = address + i;
			memcpy(sendObj.write64.data.bytes, buffer + i, 8);
			iids.push_back(pineSend(sendObj));
		}
		//note: rem is [0-7] inclusive
		//unsigned int offsetaddr = addr + whole;
		unsigned int offset = 0;
		if ((rem & 4) != 0) //we need a 4
		{
			DSPINESend sendObj{};
			sendObj.write32 = DSPINEWrite32Send{};
			sendObj.write32.address = address + whole + offset;
			memcpy(sendObj.write32.data.bytes, buffer + whole + offset, 4);
			iids.push_back(pineSend(sendObj));
			offset += 4;
		}
		if ((rem & 2) != 0) //we need a 2
		{
			DSPINESend sendObj{};
			sendObj.write16 = DSPINEWrite16Send{};
			sendObj.write16.address = address + whole + offset;
			memcpy(sendObj.write16.data.bytes, buffer + whole + offset, 2);
			iids.push_back(pineSend(sendObj));
			offset += 2;
		}
		if ((rem & 1) != 0) //we need a 2
		{
			DSPINESend sendObj{};
			sendObj.write8 = DSPINEWrite8Send{};
			sendObj.write8.address = address + whole + offset;
			memcpy(sendObj.write8.data.bytes, buffer + whole + offset, 1);
			iids.push_back(pineSend(sendObj));
			offset += 1;
		}
	};
	if (originalBuf == nullptr)
	{
		dispatchContig(addr, len, buf);
	}
	else
	{
		pineApiID firstSendID = 0;
		size_t sendCount = 0;
		long mismatchStart = -1, mismatchLength = 1;
		for (size_t i = 0; i < len; i++)
		{
			if (mismatchStart != -1 && buf[i] != originalBuf[i])
				mismatchLength++; //we already have a mismatch, make it longer
			if (mismatchStart == -1 && buf[i] != originalBuf[i])
				mismatchStart = i; //start a new mismatch
			if (mismatchStart != -1 && buf[i] == originalBuf[i])
			{ //end of the mismatch, now dispatch
				dispatchContig(addr + mismatchStart, mismatchLength, buf + mismatchStart);

				mismatchStart = -1; mismatchLength = 1; //at the very end
			}
		}
		if (mismatchStart != -1)
			dispatchContig(addr + mismatchStart, mismatchLength, buf + mismatchStart);
	}
	pineApiRequests.insert(std::pair<pineApiID, std::pair<std::vector<internalPineApiID>, bool>>{pineApiRequestCount, std::pair<std::vector<internalPineApiID>, bool>{ iids, true }});
	return pineApiRequestCount++;
}