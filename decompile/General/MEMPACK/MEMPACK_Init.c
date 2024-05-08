#include <common.h>

#ifdef REBUILD_PC
// 32mb RAM, so that PrimMem can fill the entirety 
// of 24-bit address space (16mb max) and have enough
// RAM left over for the rest of the game (16mb more)
char memory[32*1024*1024];
#endif

void RB_EndOfFile();
void CS_EndOfFile();
extern char RB_NewEndFile[4];
void OVR_Region3();

void DECOMP_MEMPACK_Init(int ramSize)
{
	struct Mempack* ptrMempack;

	// Get the pointer to the memory allocation system
	ptrMempack = sdata->PtrMempack;

#ifdef REBUILD_PC

	// must be a 24-bit address
	// Visual Studio -> Properties -> Linker -> Advanced -> 
	// Base Address, Randomized Base Address, Fixed Base Address
	ptrMempack->start = &memory[0];
	printf(
		"[CTR] Where does memory starts? (%s) %08x\n",
		(ptrMempack->start < 0x01000000 ? "GOOD" : "BAD"),
		ptrMempack->start
	);
	
	memset(memory, 0, 32*1024*1024);
	ptrMempack->endOfAllocator = &memory[32*1024*1024 - 4];
	ptrMempack->lastFreeByte = &memory[32*1024*1024 - 4];

#else
	
	// Defragmentation requires a lower overlay size in bigfile,
	// which we dont have for 231, so we cheat by setting size
	// manually in MainMain after call to DECOMP_LOAD_ReadDirectory
	
	// RB_EndOfFile		800ba548	30 sectors (original game, deprecated by decomp)
	// (defragged 231)	800b8c78	28 sectors
	// CS_EndOfFile		800b97fc	28 sectors (original game, current largest size)
	
	u_int Aligned231 = 28*0x800;
	//u_int Size231 = (u_int)RB_NewEndFile - (u_int)OVR_Region3;
	//u_int Aligned231 = ((Size231 + 0x7ff) & ~(0x7ff));
	//printf("\nMEMPACK_Init: %d sectors in 231\n\n", Aligned231/0x800);
	
	// Original game allocated 0x800 to stack,
	// but now Stack is relocated to kernel memory
	ptrMempack->start = (u_int)OVR_Region3 + Aligned231;
	ptrMempack->endOfAllocator = (void *)(ramSize + 0x80000000);
	ptrMempack->lastFreeByte = (void *)(ramSize + 0x80000000);
#endif

	ptrMempack->numBookmarks = 0;
	ptrMempack->firstFreeByte = ptrMempack->start;
	//printf("%08x\n", ptrMempack->firstFreeByte);
}