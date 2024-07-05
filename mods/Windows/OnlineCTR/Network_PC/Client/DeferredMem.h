#pragma once
#ifndef DEF_MEM //include guard
#define DEF_MEM

#ifdef _WIN64 //windows
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#else //assume posix
#error todo...
//todo:
//include whatever headers we need for posix socket types.
#endif

#include "DSPINE.h"
#include "Util.h"
#include <memory>
#include <functional>
#include <vector>

//TODO: make as few of these public as possible.

bool defMemInit();
bool socketValid();
//void readMemorySegment(unsigned int addr, size_t len, char* buf);
//void writeMemorySegment(unsigned int addr, size_t len, char* buf/*, bool blocking = false*/);
void recvThread();
#if _WIN64 //windows
SOCKET initSocket();
void uninitSocket(SOCKET* socket);
#else //assume posix
#error todo...
//todo:
//declare functions initSocket() and uninitSocket() using the equivalent posix data type for SOCKET
//Note: the remainder of this file likely shouldn't need to be modified for the sake of posix sockets.
#endif
typedef unsigned long long internalPineApiID;
struct DSPINESendRecvPair
{
	DSPINESend sendData;
	DSPINERecv recvData;
	DSPINESendRecvPair(DSPINESend s, DSPINERecv r) : sendData(s), recvData(r) {}
};
internalPineApiID pineSend(DSPINESend sendObj);
void pineRecv();
typedef unsigned long long pineApiID;
void removeOldPineData(pineApiID id);
void waitUntilPineDataPresent(pineApiID id);
std::vector<DSPINESendRecvPair> getPineDataSegment(pineApiID id);
pineApiID send_readMemorySegment(unsigned int addr, size_t len);
pineApiID send_writeMemorySegment(unsigned int addr, size_t len, char* buf);

//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
template<typename T>
class ps1ptr
{
private:
	enum pineState
	{
		none,
		reading,
		writing,
	};
public:
	typedef std::shared_ptr<T> ptrtype;
private:
	unsigned int address;
	/*bool volat;
	bool didNotPrefetch;*/
	char* buf;
	//char* originalBuf;
	ptrtype bufferedVal; //implicit dtor will delete this, which deletes the buf and originalBuf
	pineState pState = none;
	pineApiID outstandingAPIID;
public:
	//for static initialization only, do not actually ever call this.
	ps1ptr() { }
	/// <summary>
	/// Reads the specified address from PS1 (emulator RAM), copies it, and creates a shared_ptr.
	///
	/// The object itself is only a copy of emulator RAM, so to commit changes, use commit().
	/// If changes have been made to emulator RAM, use refresh() to re-fetch the underlying memory.
	///
	/// When this object falls out of scope, any changes made will *not* be automatically committed.
	/// Do it yourself.
	/// </summary>
	/// <param name="addr">The address of PS1 memory to represent</param>
	/// <param name="doNotPrefetch">If true, this ps1ptr will not prefetch the contents of that memory.
	/// This is useful if you plan on completely overwriting this portion of memory, saving latency.
	/// However, an object in this state will always commit it's entire buffer to ps1 memory every
	/// time it is commited, so make sure *all* of the memory this ps1ptr represents is set as you intend.</param>
	/// <param name="volatileAccess">If true, will automatically refresh() for you upon every call to get()</param>
	ps1ptr(unsigned int addr, bool doNotPrefetch = false/*, bool volatileAccess = false*/) : address(addr)/*, didNotPrefetch(doNotPrefetch), volat(volatileAccess)*/
	{
		buf = new char[sizeof(T)];
		//originalBuf = new char[sizeof(T)];
		memset(buf, 0, sizeof(T));
		//memcpy(originalBuf, buf, sizeof(T));
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; /*delete[] originalBuf;*/ }); //when the shared_ptr dies, free the char* off the heap.
		if (!doNotPrefetch)
			blockingRead();
	}
	void blockingRead()
	{
		startRead();
		waitRead();
	}
	void startRead()
	{
		//This allows for waitWrite() to not need to be called before a read.
		if (pState == writing)
		{
			//TODO: since writes cause canonical state immediately, this can be optimized to not wait, and instead just mark this as
			//not needed. waitWrite is currently needed to clean up the old pine data (prevent mem leak).
			waitWrite();
		}
		if (pState != none)
			exit_execv(69); //todo abort bad
		outstandingAPIID = send_readMemorySegment(address, sizeof(T));
		pState = reading;
	}
	void waitRead()
	{
		if (pState != reading)
			exit_execv(69); //todo abort bad
		waitUntilPineDataPresent(outstandingAPIID);
		std::vector<DSPINESendRecvPair> pineData = getPineDataSegment(outstandingAPIID);
		//reads should be of the form: 8? 8? 8? 8? ... (excess is ignored if not a multiple of 8)
		for (size_t i = 0; i < pineData.size(); i++)
		{
			DSPINESendRecvPair dat = pineData.at(i);
			size_t bufInd = dat.sendData.shared_header.address - address;
			size_t len = ((sizeof(T) - bufInd) >= 8) ? 8 : sizeof(T) - bufInd;
			memcpy(buf + bufInd, dat.recvData.read64.data.bytes, len);
		}
		removeOldPineData(outstandingAPIID);
		//at the very end
		pState = none;
	}
	void blockingWrite()
	{
		startWrite();
		waitWrite();
	}
	void startWrite()
	{
		if (pState != none)
			exit_execv(69); //todo abort bad
		outstandingAPIID = send_writeMemorySegment(address, sizeof(T), buf);
		pState = writing;
	}
	void waitWrite()
	{
		if (pState != writing)
			exit_execv(69); //todo abort bad
		waitUntilPineDataPresent(outstandingAPIID);
		//std::vector<DSPINESendRecvPair> pineData = getPineDataSegment(outstandingAPIID);
		//currently nothing needs to be done with pineData
		removeOldPineData(outstandingAPIID); //integrity & proper sizes are verified by the api functions
		//at the very end
		pState = none;
	}
	ptrtype get()
	{
		//This allows for waitWrite() to not need to be called before get().
		if (pState == writing)
		{
			//TODO: since writes cause canonical state immediately, this can be optimized to not wait, and instead just mark this as
			//not needed. waitWrite is currently needed to clean up the old pine data (prevent mem leak).
			waitWrite();
		}
		if (pState != none)
			exit_execv(69); //todo abort bad
		return bufferedVal;
	}
	~ps1ptr()
	{
		//TODO: instead of blocking & waiting, just removeOldPineData in a way
		//that tells the API you don't care about the pending results.
		if (pState == reading)
			waitRead();
		else if (pState == writing)
			waitWrite();
	}
	/// <summary>
	/// Writes the memory this ps1ptr represents back to ps1 memory.
	/// </summary>
	//void commit(/*bool blocking = false*/)
	//{
	//	size_t whole = sizeof(T) - (sizeof(T) % 8);
	//	size_t rem = sizeof(T) - whole;
	//	for (size_t i = 0; i < whole; i += 8)
	//	{
	//		if (memcmp(buf + i, originalBuf + i, 8) != 0 || didNotPrefetch)
	//		{
	//			//TODO: instead of writing the dirty memory,
	//			//keep looking ahead until the first non-dirty memory OR until the end of the buffer
	//			//*then* writeMemorySegment() that entire chunk.
	//			writeMemorySegment(address + i, 8, buf + i/*, blocking*/);
	//		}
	//	}
	//	if (rem != 0 && (memcmp(buf + whole, originalBuf + whole, rem) != 0 || didNotPrefetch))
	//	{
	//		writeMemorySegment(address + whole, rem, buf + whole/*, blocking*/);
	//	}
	//	memcpy(originalBuf, buf, sizeof(T));
	//	didNotPrefetch = false; //if it was true, well, we just overwrote *all* the mem this ps1ptr represents,
	//							//so the copy we have is indeed up-to-date. We can now treat this as though it was
	//							//prefetched since it's contents are now accurate.
	//}
	/// <summary>
	/// Re-fetches the memory this ps1ptr represents from ps1 memory.
	/// </summary>
	//void refresh()
	//{
	//	readMemorySegment(address, sizeof(T), buf); //change the underlying data of the shared_ptr
	//	didNotPrefetch = false;
	//	memcpy(originalBuf, buf, sizeof(T));
	//}
	//void partialRefresh(unsigned int offset, size_t length)
	//{
	//	if (offset + length > sizeof(T))
	//	{
	//		printf("Trying to partial refresh beyond the buffer length!\n");
	//		exit_execv(18);
	//	}
	//	readMemorySegment(address + offset, length, buf); //change the underlying data of the shared_ptr
	//	memcpy(originalBuf + offset, buf + offset, length);
	//}
	//ptrtype get()
	//{
	//	if (volat) //similar in concept to volatile memory, but after your usage you still have to manually commit.
	//		refresh();
	//	return bufferedVal;
	//}
};

class ps1mem
{
private:
	unsigned int address;
public:
	ps1mem() { } //for static init only, do not actually use this.
	ps1mem(unsigned int addr) : address(addr) { }

	/// <summary>
	/// Creates a ps1ptr of the specified address, offset by the address of this ps1mem.
	/// </summary>
	template<typename T>
	ps1ptr<T> at(unsigned int addr, bool doNotPrefetch = false/*, bool volatileAccess = false*/)
	{
		return ps1ptr<T>(addr + address, doNotPrefetch/*, volatileAccess*/);
	}

	//these are useful for unconditional writes.
	//void writeRaw(unsigned int addr, char val);
	//void writeRaw(unsigned int addr, short val);
};

#endif //DEF_MEM