#include <common.h>

void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
	
	#ifdef REBUILD_PC
	size = size*8;
	#else
		#ifdef USE_60FPS
		// This is needed cause of LOD upgrading in 60fps,
		// which is needed cause LOD[1] can't double-lerp
		// animations
		
		// Without this, game crashes if you load
		// Adventure->HotAirSkyway, then tap X+LEFT at startline
		
		// Should fit with all memory optimizations
		size += 0x800;
		#endif
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

void DECOMP_MainDB_OTMem(struct OTMem* otMem, u_int size)
{
	void* pvVar1;
	
	pvVar1 = DECOMP_MEMPACK_AllocMem(size);
	otMem->size = size;
	otMem->curr = pvVar1;
	otMem->start = pvVar1;
	
	// skip alignment by & 0xfffffffc,
	// all possible size inputs are already aligned
	otMem->end = (void*)((int)pvVar1 + size);
	
	return;
}