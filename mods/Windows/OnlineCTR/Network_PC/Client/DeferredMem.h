#pragma once
#include <WinSock2.h>
#include "DSPINE.h"
#include <memory>
#include <functional>


extern void defMemInit();
extern SOCKET getSocket();
extern void closeSocket(SOCKET* socket);
extern void readMemorySegment(unsigned int addr, size_t len, char* buf);
extern void writeMemorySegment(unsigned int addr, size_t len, char* buf);

//https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
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
	///
	/// If it's possible to enable a nagle-esq algorithm on the sockets, that might be benifical (keep in mind traffic is
	/// from CLIENT.EXE -> localhost, so latency should be sub-millisecond probably).
	/// </summary>

public:
	typedef std::shared_ptr<T> ptrtype;
private:
	unsigned int address;
	bool volat;
	char* buf;
	char* originalBuf;
	ptrtype bufferedVal; //implicit dtor will delete this, which deletes the buf
public:
	ps1ptr() { } //for static init only, do not actually use this.
	/// <summary>
	/// Reads the specified address from PS1 (emulator RAM), copies it, and creates a shared_ptr.
	///
	/// The object itself is only a copy of emulator RAM, so to commit changes, use commit().
	/// If changes have been made to emulator RAM, use refresh() to re-fetch the underlying memory.
	///
	/// When this object falls out of scope, any changes made will *not* be automatically committed.
	/// Do it yourself.
	/// </summary>
	ps1ptr(unsigned int addr, bool volatileAccess = false) : address(addr), volat(volatileAccess)
	{
		buf = new char[sizeof(T)]/*()*/; //not necessary since we overwrite it with readMemorySegment
		readMemorySegment(address, sizeof(T), buf);
		originalBuf = new char[sizeof(T)];
		memcpy(originalBuf, buf, sizeof(T));
		bufferedVal = ptrtype((T*)&buf[0], [=](T* val) { delete[] buf; delete[] originalBuf; }); //when the shared_ptr dies, free the char* off the heap.
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
		if (memcmp(buf, originalBuf, sizeof(T)) == 0)
			printf("Commit() called but nothing was changed!");
		else
			writeMemorySegment(address, sizeof(T), buf);
	}
	/// <summary>
	/// Re-fetches the memory this ps1ptr represents from ps1 memory.
	/// </summary>
	void refresh()
	{
		readMemorySegment(address, sizeof(T), buf); //change the underlying data of the shared_ptr
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
	ps1ptr<T> at(unsigned int addr)
	{
		return ps1ptr<T>(addr + address);
	}

	//these are useful for unconditional writes.

	void writeRaw(unsigned int addr, char val);

	void writeRaw(unsigned int addr, short val);
};