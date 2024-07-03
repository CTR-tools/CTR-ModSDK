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


bool defMemInit();
bool socketValid();
void readMemorySegment(unsigned int addr, size_t len, char* buf);
void writeMemorySegment(unsigned int addr, size_t len, char* buf/*, bool blocking = false*/);
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

/*
* NEW PINE HANDLING:
*
* at program start, initialize the global variable pineSendsCount to 0, and pineRecvsCount to 0.
* asyncronously perform:
*	- every time a PINE api call is made (one or more wrapped calls to tcp send), make the call, make an empty dictionary entry for this
*	call with pineSendsCount as they key, and the increment this variable. 
*	- every time a PINE api call gets returned, go to the dictionary[pineRecvsCount]
*	and fill the entry with this api return value, then increment pineRecvsCount.
*
* requires:
*	- a method to send a PINE api call in the above fashion
*	- a method to query whether or not a previously made PINE api call (with previously provided id) has already been fufilled.
*	- a method to block until a previously made PINE api call is fully complete.
*
* ps1ptr utilizes as:
*	- ctor(false) does not prefetch, but ctor(true) does.
*	- refresh() automatically makes PINE api call and blocks until it's complete and refreshes the represented memory
*		* alternatively refresh(false) makes PINE api call but does not block until it completes, should be matched with wait_refresh() before calling get()
*	- if get() is called while a PINE api call is in progress, then abort
*		* if refresh() was called, this can't happen, if refresh(false) was called, then wait_refresh() unmarks "PINE api call in progress".
*/


//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
template<typename T>
class ps1ptr
{
public:
	typedef std::shared_ptr<T> ptrtype;
private:
	unsigned int address;
	bool volat;
	bool didNotPrefetch;
	char* buf;
	char* originalBuf;
	ptrtype bufferedVal; //implicit dtor will delete this, which deletes the buf and originalBuf
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
	ps1ptr(unsigned int addr, bool doNotPrefetch = false, bool volatileAccess = false) : address(addr), didNotPrefetch(doNotPrefetch), volat(volatileAccess)
	{
		buf = new char[sizeof(T)];
		originalBuf = new char[sizeof(T)];
		if (!doNotPrefetch)
			readMemorySegment(address, sizeof(T), buf);
		else
			memset(buf, 0, sizeof(T));
		memcpy(originalBuf, buf, sizeof(T));
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; delete[] originalBuf; }); //when the shared_ptr dies, free the char* off the heap.
	}
	operator ptrtype() const 
	{
		//this should be an implicit conversion operator between ps1ptr<T> to ptrtype,
		//but for some reason it doesn't usually work (probably because coercion is too weak
		//in most cases). Use .get() instead.
		return bufferedVal;
	}
	/// <summary>
	/// Writes the memory this ps1ptr represents back to ps1 memory.
	/// </summary>
	void commit(/*bool blocking = false*/)
	{
		size_t whole = sizeof(T) - (sizeof(T) % 8);
		size_t rem = sizeof(T) - whole;
		for (size_t i = 0; i < whole; i += 8)
		{
			if (memcmp(buf + i, originalBuf + i, 8) != 0 || didNotPrefetch)
			{
				//TODO: instead of writing the dirty memory,
				//keep looking ahead until the first non-dirty memory OR until the end of the buffer
				//*then* writeMemorySegment() that entire chunk.
				writeMemorySegment(address + i, 8, buf + i/*, blocking*/);
			}
		}
		if (rem != 0 && (memcmp(buf + whole, originalBuf + whole, rem) != 0 || didNotPrefetch))
		{
			writeMemorySegment(address + whole, rem, buf + whole/*, blocking*/);
		}
		memcpy(originalBuf, buf, sizeof(T));
		didNotPrefetch = false; //if it was true, well, we just overwrote *all* the mem this ps1ptr represents,
								//so the copy we have is indeed up-to-date. We can now treat this as though it was
								//prefetched since it's contents are now accurate.
	}
	/// <summary>
	/// Re-fetches the memory this ps1ptr represents from ps1 memory.
	/// </summary>
	void refresh()
	{
		readMemorySegment(address, sizeof(T), buf); //change the underlying data of the shared_ptr
		didNotPrefetch = false;
		memcpy(originalBuf, buf, sizeof(T));
	}
	void partialRefresh(unsigned int offset, size_t length)
	{
		if (offset + length > sizeof(T))
		{
			printf("Trying to partial refresh beyond the buffer length!\n");
			exit_execv(18);
		}
		readMemorySegment(address + offset, length, buf); //change the underlying data of the shared_ptr
		memcpy(originalBuf + offset, buf + offset, length);
	}
	ptrtype get()
	{
		if (volat) //similar in concept to volatile memory, but after your usage you still have to manually commit.
			refresh();
		return bufferedVal;
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
	ps1ptr<T> at(unsigned int addr, bool doNotPrefetch = false, bool volatileAccess = false)
	{
		return ps1ptr<T>(addr + address, doNotPrefetch, volatileAccess);
	}

	//these are useful for unconditional writes.
	//void writeRaw(unsigned int addr, char val);
	//void writeRaw(unsigned int addr, short val);
};

#endif //DEF_MEM