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
void markPineDataForGC(pineApiID id);
void GCDeadPineData();
bool isPineDataPresent(pineApiID id);
void waitUntilPineDataPresent(pineApiID id);
std::vector<DSPINESendRecvPair> getPineDataSegment(pineApiID id);
pineApiID send_readMemorySegment(unsigned int addr, size_t len);
pineApiID send_writeMemorySegment(unsigned int addr, size_t len, char* buf, char* originalBuf = nullptr);

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
	template<typename U> friend class ps1ptr;
public:
	typedef std::shared_ptr<T> ptrtype;
private:

	unsigned int address;
	/*bool volat;*/
	bool didPrefetch;
	char* buf;
	char* originalBuf;
	std::shared_ptr<void> parentIfPresent;
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
	/// <param name="prefetch">If false, this ps1ptr will not prefetch the contents of that memory upon construction.
	/// This is useful if you plan on completely overwriting this portion of memory, saving latency.
	/// However, an object in this state will always commit it's entire buffer to ps1 memory every
	/// time it is commited, so make sure *all* of the memory this ps1ptr represents is set as you intend.</param>
	/// <param name="volatileAccess">If true, will automatically refresh() for you upon every call to get()</param>
	ps1ptr(unsigned int addr, bool prefetch = true/*, bool volatileAccess = false*/) : address(addr), didPrefetch(prefetch)/*, volat(volatileAccess)*/
	{
		buf = new char[sizeof(T)];
		originalBuf = new char[sizeof(T)];
		parentIfPresent = nullptr;
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; delete[] originalBuf; }); //when the shared_ptr dies, free the char* off the heap.
		if (prefetch)
			blockingRead();
		else
		{
			memset(buf, 0, sizeof(T));
			memcpy(originalBuf, buf, sizeof(T));
		}
	}
	//TODO: this needs work
	/// <summary>
	/// This ctor is for if you want to make a ps1ptr that represents just a portion of an existing ps1ptr.
	/// e.g., if you intend to have very high usage of a submember of some other ps1ptr like octr, this can lighten the
	/// load on TCP/PINE. (See example in FrameStall in CL_main.cpp)
	/// </summary>
	template<typename U>
	ps1ptr(ps1ptr<U> parentPtr, size_t offset)
	{
		buf = parentPtr.buf + offset;
		originalBuf = parentPtr.originalBuf + offset;
		parentIfPresent = parentPtr.bufferedVal; //this is only saved for the sake of strong reference counting.
		bufferedVal = std::shared_ptr<T>((T*)&buf[0], [=](T* val) { /* do nothing, underlying mem is destroyed with parent */ });
		address = parentPtr.address + offset;
		didPrefetch = true; //functionally desirable in this case
	}
	//TODO: this needs work
	template<typename U>
	ps1ptr<U> createSubmemberPtr(size_t offset)
	{
		return ps1ptr<U>{*this, offset};
	}
	void blockingRead()
	{
		startRead();
		waitRead();
	}
	void startRead()
	{
		if (pState == reading)
			waitRead();
		else if (pState == writing)
			waitWrite();
		//if (pState != none)
		//	exit_execv(69); //todo abort bad
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

		markPineDataForGC(outstandingAPIID);
		memcpy(originalBuf, buf, sizeof(T));
		didPrefetch = true; //if we've read, we can treat this object (from this point on) as if it was prefetched.
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
		if (pState == reading)
			waitRead();
		else if (pState == writing)
			waitWrite();
		//if (pState != none)
		//	exit_execv(69); //todo abort bad
		outstandingAPIID = send_writeMemorySegment(address, sizeof(T), buf, didPrefetch ? originalBuf : nullptr);
		didPrefetch = true; //if we've written, we can treat this object (from this point on) as if it was prefetched, because it now *is* the canonical memory state
		pState = writing;
	}
	void waitWrite()
	{
		if (pState != writing)
			exit_execv(69); //todo abort bad
		waitUntilPineDataPresent(outstandingAPIID);

		//currently nothing needs to be done with pineData
		//std::vector<DSPINESendRecvPair> pineData = getPineDataSegment(outstandingAPIID);

		markPineDataForGC(outstandingAPIID); //integrity & proper sizes are verified by the api functions
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
	unsigned int get_address()
	{
		return address;
	}

	~ps1ptr()
	{
		if (pState != none)
			markPineDataForGC(outstandingAPIID);
	}
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
	ps1ptr<T> at(unsigned int addr, bool prefetch = true/*, bool volatileAccess = false*/)
	{
		return ps1ptr<T>(addr + address, prefetch/*, volatileAccess*/);
	}
};

#endif //DEF_MEM