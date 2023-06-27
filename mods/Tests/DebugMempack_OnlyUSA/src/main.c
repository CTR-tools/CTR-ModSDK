#include <common.h>

// USA Only cause of MEMPACK_Init,
// shouldn't be hard to fix that

// this disables the Torch namespace,
// freeing the memory for whatever we want
void Torch_Main()
{
	return;
}

// Mempack_Init
void MEMPACK_Init_new(int size)
{
  // structure of memory allocation system
  struct Mempack* mp = sdata->PtrMempack;

  // start of memory allocation system
  mp->start = (void*)0x800ba9f0;

  // Set pointer to end of CTR Memory allocation
  // It adds so much so that it becomes 801FF800
  // with the '80' prefix
  mp->lastFreeByte = (void*)(size + 0x7ffff800);
  mp->endOfAllocator = (void*)(size + 0x7ffff800);

  // size of mempack
  // (0x801FF800 - 0x800ba9f0) = (0x200000 - 0xbb1f0)
  mp->packSize = size + -0xbb1f0;

  // set number of bookmarks to zero
  mp->numBookmarks = 0;

  // Set total size of PS1 Memory
  // The game never actually uses this variable
  mp->endOfMemory = (void*)0x80200000;

  // set end of allocation to the start of allocation
  mp->firstFreeByte = mp->start;

  // debug
  printf("MEMPACK_Init: start %08x end %08x\n",mp->start,mp->endOfAllocator);
  printf("              available memory %ld bytes\n",mp->packSize);

  return;
}

// Mempack_AllocMem
void* MEMPACK_AllocMem_new(int size, char* name)

{
  // pointer that will be returned
  void* ret;

  // aligned size of memory allocated
  int sizeAlign;

  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // basically, if there is no room to allocate [size] amount of bytes
  if (mp->lastFreeByte - mp->firstFreeByte < size) {

	// debug
    printf("ERROR: MEMPACK_AllocMem unable to allocate %ld bytes for %s!\n",size);
    printf("       %d bytes left\n", mp->lastFreeByte - mp->firstFreeByte);

	// End the program
	// This function is also called before executing Spyro 2
	// and when the game terminates ( see "case 4" in main(void) )
	CTR_ErrorScreen(0xff,0,0);

	// freeze the game
	do
	{
	} while(1);
  }

  // Save the pointer to the end of currently-allocated memory
  // This will be returned as the pointer where new data will
  // be stored
  ret = mp->firstFreeByte;

  // Align allocation size
  sizeAlign = size + 3U & 0xfffffffc;

  // set the size of memory allocated
  mp->sizeOfPrevAllocation = sizeAlign;

  // Increase address where allocated memory ends,
  // so that used memory can't be overwritten
  mp->firstFreeByte = (void*)((unsigned int)ret + (unsigned int)sizeAlign);

  printf("MEMPACK_AllocMem allocated %ld bytes: %s: %d bytes left\n",
		sizeAlign,
		name,
		(unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte);

  // Return pointer to where memory is free
  return ret;
}

// MEMPACK_AllocHighMem
void* MEMPACK_AllocHighMem_new(int size, char* name)
{
  // This is only called once for "Patch Memory Table",
  // and it is given the amount of free remaining memory

  void* ret;
  int sizeAlign;

  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // basically, if there is no room to allocate [size] amount of bytes
  if (mp->lastFreeByte - mp->firstFreeByte < size)
  {
	// debug
	printf("ERROR: MEMPACK_AllocHighMem unable to allocate %ld bytes for %s!\n",size);
	printf("       %d bytes left\n", mp->lastFreeByte - mp->firstFreeByte);

	// freeze the game
	do
	{
	} while(1);
  }

  // Pointer to the last free byte of memory in the pool
  ret = mp->lastFreeByte;

  // Align allocation size
  sizeAlign = size + 3U & 0xfffffffc;

  // do NOT save size of previous allocation,
  // that's only for Realloc, and using Realloc
  // right after HighMem will break the game

  // decrease the last free byte
  mp->lastFreeByte = ret - sizeAlign;

  // debug
  printf("MEMPACK_AllocHighMem allocated %ld bytes: %s: %d bytes left\n",
			sizeAlign,
			name,
			((unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte)
		);

  return mp->lastFreeByte;
}

// MEMPACK_ReallocMem
void* MEMPACK_ReallocMem_new(int size, char* name)

{
  // pointer to memory managment structure
  void* ret;

  // aligned size of memory allocated
  int sizeAlign;

  // amount of memory to erase
  int sizePrevAlloc;

  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // Save the pointer to the end of currently-allocated memory
  ret = mp->firstFreeByte;

  // Get size of previous allocation
  sizePrevAlloc = mp->sizeOfPrevAllocation;

  // Align allocation size
  sizeAlign = size + 3U & 0xfffffffc;

  // set the size of memory allocated
  mp->sizeOfPrevAllocation = sizeAlign;

  // Change address where allocation ends
  // Decrease by the amount of bytes erased
  // Increase by the amount of bytes allocated
  mp->firstFreeByte = (void*)(((unsigned int)mp->firstFreeByte - (unsigned int)sizePrevAlloc) + sizeAlign);

  printf("MEMPACK_ReallocMem reallocated %d bytes: %d bytes left\n",
				sizeAlign,
				(unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte
		);

  return mp->firstFreeByte;
}

// MEMPACK_PushState
int MEMPACK_PushState_new(void)
{
  int numBookmarks;

  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // get current number of bookmarks
  numBookmarks = mp->numBookmarks;

  // if you have less than 16 bookmarks
  if (numBookmarks < 0x10)
  {
	// set index of bookmark array to the last byte of currently-used memory
    mp->bookmarks[numBookmarks] = mp->firstFreeByte;

	// add one to ptr+0x1c
	mp->numBookmarks = numBookmarks + 1;

    printf("MEMPACK_PushState %d : 0x%08x : %d bytes left\n",
			numBookmarks,
			(unsigned int)mp->firstFreeByte,
            (unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte);
  }

  else
  {
	  printf("ERROR: MEMPACK_PushState out of stack space!\n");
  }

  return numBookmarks;
}

// MEMPACK_PopState
void MEMPACK_PopState_new(void)
{
  int numBookmarks;

  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // check how many bookmarks we have
  numBookmarks = mp->numBookmarks + -1;

  // if there are any bookmarks
  if (0 < mp->numBookmarks)
  {
	// decrease bookmark by one
    mp->numBookmarks = numBookmarks;

	// erase all memory after the bookmark we are going back to
	mp->firstFreeByte = mp->bookmarks[numBookmarks];

	printf("MEMPACK_PopState %d : 0x%08x : %d bytes left\n",
			mp->numBookmarks,
			(unsigned int)mp->firstFreeByte,
			(unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte);
  }
  else
  {
	  printf("ERROR: MEMPACK_PopState has nothing on the stack!\n");
  }
  return;
}

// MEMPACK_PopToState
void MEMPACK_PopToState_new(int bookmarkID)

{
  // pointer to memory managment structure
  struct Mempack* mp = sdata->PtrMempack;

  // set current bookmark
  mp->numBookmarks = bookmarkID;

  // change last byte of currently-used memory
  mp->firstFreeByte = mp->bookmarks[mp->numBookmarks];

  printf("MEMPACK_PopToState %d : 0x%08x : %d bytes left\n",
			mp->numBookmarks,
			(unsigned int)mp->firstFreeByte,
			(unsigned int)mp->lastFreeByte - (unsigned int)mp->firstFreeByte);

  return;
}
