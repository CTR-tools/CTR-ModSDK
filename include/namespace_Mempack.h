// each mempack is 0x18*4 (0x60) bytes large
struct Mempack
{
	// 0x0
	int packSize;			  // end - start, 0x144E10

	// 0x4
	void* start;			  // 0x800ba9f0

	// 0x8
	void* lastFreeByte; 	  // where you can put new data on High-End,

	// 0xC
	void* endOfAllocator;  	  // always 0x801FF800

	// 0x10
	void* endOfMemory;   	  // 0x80200000 (2mb) (never used)

	// 0x14
	void* firstFreeByte;	  // where you can put new data on Low-End

	// 0x18
	int sizeOfPrevAllocation; // self-explanatory

	// 0x1C
	int numBookmarks;		  // amount of bookmarks used

	// 0x20
	void* bookmarks[0x10];	  // address of each bookmark

	// 0x60 -- size of struct
};

_Static_assert(sizeof(struct Mempack) == 0x60);