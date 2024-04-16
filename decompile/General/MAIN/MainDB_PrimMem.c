#include <common.h>

void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
	
	#ifdef REBUILD_PC
	size = size*8;
	#endif
	
	#ifdef USE_60FPS
	// This is needed cause of LOD upgrading in 60fps,
	// which is needed cause LOD[1] can't double-lerp
	// animations
	
	// Without this, game crashes if you load
	// Adventure->HotAirSkyway, then tap X+LEFT at startline
	
	// half of 0x400 (this runs twice)
	// at least 0x400 saved from RenderBucketInstance->RDATA_FREE
	size += 0x200;
	
	// half of 0x200 (this runs twice)
	// 0x200 bytes saved from moving $sp in MEMPACK_Init
	size += 0x100;
	#endif
	
	pvVar1 = DECOMP_MEMPACK_AllocMem(size);
	primMem->size = size;
	primMem->unk2 = (int)pvVar1;
	primMem->curr = pvVar1;
	primMem->start = pvVar1;
	
	// skip alignment by & 0xfffffffc,
	// all possible size inputs are already aligned
	pvVar1 = (void*)((int)pvVar1 + size);
	primMem->end = pvVar1;
	primMem->endMin100 = (void*)((int)pvVar1 - 0x100);
	
	return;
}