// In Aug 5 prototype, this is
// called MEMPACK_Init,
// param1 is the amount to allocate
void FUN_8003e740(int param_1)

{
  undefined *puVar1;

  // structure of memory allocation system
  puVar1 = PTR_DAT_8008d420;

  // start of memory allocation system
  // 800ba9f0 = (ovr3)0x800ba9f0 + (231)0xEB58 + (align-up)0x4A8,
  // 800ba9f0 = 0x800ab9f0 + 0xF000 (only 0x4A8 can be overwritten)
  *(undefined4 *)(PTR_DAT_8008d420 + 4) = 0x800ba9f0;

  // Set pointer to end of CTR Memory allocation
  // It adds so much so that it becomes 801FF800
  // with the '80' prefix
  *(int *)(puVar1 + 0xc) = param_1 + 0x7ffff800;
  *(int *)(puVar1 + 8) = param_1 + 0x7ffff800;

  // size of mempack
  // (0x801FF800 - 0x800ba9f0) = (0x200000 - 0xbb1f0)
  *(int *)puVar1 = param_1 + -0xbb1f0;

  // set number of bookmarks to zero
  *(undefined4 *)(puVar1 + 0x1c) = 0;

  // Set total size of PS1 Memory
  // The game never actually uses this variable
  *(undefined4 *)(puVar1 + 0x10) = 0x80200000;

  // set end of allocation to the start of allocation
  *(undefined4 *)(puVar1 + 0x14) = *(undefined4 *)(puVar1 + 4);
  return;
}


// MEMPACK_SwapPacks
void FUN_8003e80c(int param_1)
{
  // change pointer of active allocation system,
  // this is pointer incrementation, so param1*0x18
  // is actually param1*0x60 bytes, you can tell by
  // looking at the value 8008d420 as it changes
  PTR_DAT_8008d420 = (undefined *)(&DAT_800990e4 + param_1 * 0x18);
  return;
}

// build a new pack with a new start and end
void FUN_8003e830(int param_1,int param_2)
{
  undefined *puVar1;

  // structure of memory allocation system
  puVar1 = PTR_DAT_8008d420;

  // set start of memory
  *(int *)(PTR_DAT_8008d420 + 4) = param_1;

  // Set lastFreeByte to end of this pack
  *(int *)(puVar1 + 8) = param_1 + param_2;

  // size of pack
  *(int *)puVar1 = param_2;

  // set number of bookmarks to zero
  *(undefined4 *)(puVar1 + 0x1c) = 0;

  // set size of psx memory to size of current CTR memory
  *(int *)(puVar1 + 0x10) = param_1 + param_2;

  // set last byte of allocation to the start of allocation
  *(undefined4 *)(puVar1 + 0x14) = *(undefined4 *)(puVar1 + 4);
  return;
}


// Get amount of free memory
int FUN_8003e85c(void)

{
  // Pointer to end of CTR Memory (0x1FF800) - pointer to end of used memory
  return *(int *)(PTR_DAT_8008d420 + 8) - *(int *)(PTR_DAT_8008d420 + 0x14);
}


// In Aug 5 prototype, this is
// called MEMPACK_AllocMem,
// param1 is amount to allocate
int FUN_8003e874(int param_1)

{
  // pointer to memory managment structure
  undefined *puVar1;

  // pointer that will be returned
  int iVar2;

  // aligned size of memory allocated
  uint uVar3;

  // pointer to memory managment structure
  puVar1 = PTR_DAT_8008d420;

  // if the last byte address of allocated RAM
  // minus the address of RAM being used, is less
  // than the amount of memory you want to allocate

  // PTR_DAT_8008d420 + 8 will be 801FF800 by default
  // PTR_DAT_8008d420 + 0x14 will be a pointer to the last byte in use

  // basically, if there is no room to allocate param_1 amount of bytes
  if (*(int *)(PTR_DAT_8008d420 + 8) - *(int *)(PTR_DAT_8008d420 + 0x14) < param_1) {

	// CTR_ErrorScreen
	FUN_80021c94(0xff,0,0);

	// freeze the game
    do
	{
      trap(0x400);
    } while( true );
  }

  // First free byte
  iVar2 = *(int *)(PTR_DAT_8008d420 + 0x14);

  // Align allocation size
  uVar3 = param_1 + 3U & 0xfffffffc;

  // set the size of memory allocated
  *(uint *)(PTR_DAT_8008d420 + 0x18) = uVar3;

  // Increase address where allocated memory ends,
  // so that used memory can't be overwritten
  *(uint *)(puVar1 + 0x14) = iVar2 + uVar3;

  // Return pointer to where memory is free
  return iVar2;
}

// In Aug 5 prototype, this is
// called MEMPACK_AllocHighMem,
// param1 is amount to allocate,
int FUN_8003e8e8(int param_1)
{
  // This is only called once for "Patch Memory Table",
  // and it is given the amount of free remaining memory

  int iVar1;
  undefined *puVar2;
  uint uVar3;

  // pointer to memory managment structure
  puVar2 = PTR_DAT_8008d420;

  // basically, if there is no room to allocate param_1 amount of bytes
  if (*(int *)(PTR_DAT_8008d420 + 8) - *(int *)(PTR_DAT_8008d420 + 0x14) < param_1)
  {
	// Freeze the game
    do
	{
      trap(0x400);
    } while( true );
  }

  // lastFreeByte
  iVar1 = *(int *)(PTR_DAT_8008d420 + 8);

  // Align allocation size
  uVar3 = param_1 + 3U & 0xfffffffc;

  // set the size of memory allocated
  *(uint *)(PTR_DAT_8008d420 + 0x18) = uVar3;

  // decrease the last free byte
  *(uint *)(puVar2 + 8) = iVar1 - uVar3;

  // return pointer to memory
  return (iVar1 - uVar3);
}

// MEMPACK_ClearHighMem
void FUN_8003e938(void)

{
  // lastFreeByte = endOfAllocator
  *(undefined4 *)(PTR_DAT_8008d420 + 8) = *(undefined4 *)(PTR_DAT_8008d420 + 0xc);
  return;
}

// In Aug 5 prototype, this is
// called MEMPACK_ReallocMem,
// param1 is the amount to allocate
void FUN_8003e94c(int param_1)

{
  // pointer to memory managment structure
  int iVar1;

  // pointer that will be returned
  undefined *puVar2;

  // aligned size of memory allocated
  uint uVar3;

  // amount of memory to erase
  int iVar4;

  // pointer to memory managment structure
  puVar2 = PTR_DAT_8008d420;

  // firstFreeByte
  iVar1 = *(int *)(PTR_DAT_8008d420 + 0x14);

  // Get size of previous allocation
  iVar4 = *(int *)(PTR_DAT_8008d420 + 0x18);

  // Align allocation size
  uVar3 = param_1 + 3U & 0xfffffffc;

  // set the size of memory allocated
  *(uint *)(PTR_DAT_8008d420 + 0x18) = uVar3;

  // Change address where allocation ends
  // Decrease by the amount of bytes erased
  // Increase by the amount of bytes allocated
  *(uint *)(puVar2 + 0x14) = (iVar1 - iVar4) + uVar3;

  // return pointer
  return (iVar1 - iVar4);
}


// In Aug 5 prototype, this is
// called MEMPACK_PushState,
// add a bookmark
void FUN_8003e978(void)

{
  undefined *puVar1;
  int iVar2;

  // pointer to memory allocation system
  puVar1 = PTR_DAT_8008d420;

  // get current number of bookmarks
  iVar2 = *(int *)(PTR_DAT_8008d420 + 0x1c);

  // if you have less than 16 bookmarks
  if (iVar2 < 0x10)
  {
	// set member of bookmark array
    *(undefined4 *)(PTR_DAT_8008d420 + iVar2 * 4 + 0x20) =

		// firstFreeByte
		*(undefined4 *)(PTR_DAT_8008d420 + 0x14);

	// increment number of bookmarks
	*(int *)(puVar1 + 0x1c) = iVar2 + 1;
  }

  return;
}


// MEMPACK_ClearLowMem
void FUN_8003e9b8(void)
{
  undefined4 *puVar1;
  undefined *puVar2;

  // pointer to memory allocation structure
  puVar2 = PTR_DAT_8008d420;

  // get first byte of memory allocation
  puVar1 = (undefined4 *)(PTR_DAT_8008d420 + 4);

  // set number of bookmarks to zero
  *(undefined4 *)(PTR_DAT_8008d420 + 0x1c) = 0;

  // set firstFreeByte to mempack start
  *(undefined4 *)(puVar2 + 0x14) = *puVar1;
  return;
}

// In Aug 5 prototype, this is
// called MEMPACK_PopState,
// erase all memory after the last bookmark
void FUN_8003e9d0(void)
{
  undefined *puVar1;
  int iVar2;

  // get pointer to memory allocation system
  puVar1 = PTR_DAT_8008d420;

  // check how many bookmarks we have
  iVar2 = *(int *)(PTR_DAT_8008d420 + 0x1c) + -1;

  // if there are any bookmarks
  if (0 < *(int *)(PTR_DAT_8008d420 + 0x1c))
  {
	// decrease bookmark by one
    *(int *)(PTR_DAT_8008d420 + 0x1c) = iVar2;

	// erase all memory after the bookmark we are going back to
    *(undefined4 *)(puVar1 + 0x14) = *(undefined4 *)(puVar1 + iVar2 * 4 + 0x20);
  }
  return;
}

// In Aug 5 prototype, this is
// called MEMPACK_PopToState,
// erase all memory after this bookmark
// param1 is the bookmark ID
void FUN_8003ea08(int param_1)

{
  undefined *puVar1;

  // get structure to memory managment system
  puVar1 = PTR_DAT_8008d420;

  // set current bookmark
  *(int *)(PTR_DAT_8008d420 + 0x1c) = param_1;

  // change last byte of currently-used memory
  *(undefined4 *)(puVar1 + 0x14) = *(undefined4 *)(puVar1 + param_1 * 4 + 0x20);
  return;
}
