#include <common.h>
#include <inttypes.h>

#ifdef REBUILD_PC
// with 8mb expansion, we have bonus PrimMem
char memory[8*1024*1024];
#endif

void RB_EndOfFile();
void CS_EndOfFile();
void RB_NewEndFile(); // only in decomp
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
		"[CTR] Where does memory starts? (%s) %" PRIu32 "\n",
		(ptrMempack->start < 0x01000000 ? "GOOD" : "BAD"),
		ptrMempack->start
	);
	memset(memory, 0, 8*1024*1024);
	
	ptrMempack->endOfAllocator = &memory[8*1024*1024 - 4];
	ptrMempack->lastFreeByte = &memory[8*1024*1024 - 4];

#else
	
	// === Not Ready === Can't relocate RB_Teeth
	// Defragmentation requires a lower overlay size in bigfile,
	// which we dont have for 231, so we cheat by setting size
	// manually in MainMain after call to DECOMP_LOAD_ReadDirectory
	
	// RB_EndOfFile		800ba548	30 sectors (original game, deprecated by decomp)
	// RB_NewEndFile	800b86e0	26 sectors (decomp, 4:3 30fps)
	// RB_NewEndFile	800b87c8	26 sectors (decomp, 16:9 60fps)
	// CS_EndOfFile		800b97fc	28 sectors (original game, current largest size)

	// Use current largest
	#define END231 RB_EndOfFile
	
	u_int Aligned231 = (((u_int)(END231-OVR_Region3) + 0x7ff) & ~(0x7ff));
	//printf("\nMEMPACK_Init: %d sectors in 231\n\n", Aligned231/0x800);
	
	ptrMempack->start = (u_int)OVR_Region3 + Aligned231;
	ptrMempack->endOfAllocator = (void *)(ramSize + 0x80000000 - 0x800);
	ptrMempack->lastFreeByte = (void *)(ramSize + 0x80000000 - 0x800);
#endif

	ptrMempack->numBookmarks = 0;
	ptrMempack->firstFreeByte = ptrMempack->start;
}