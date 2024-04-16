#include <common.h>

void DECOMP_MainDB_PrimMem(struct PrimMem* primMem, u_int size)
{
	void* pvVar1;
	
	#ifdef REBUILD_PC
	size = size*8;
	#endif
	
	#ifdef USE_60FPS
	// RenderBucketInstance is moved to rdata_free,
	// which saves 0x400 to 0x1000 bytes, so increase
	// by 0x200 bytes, which happens twice
	
	// This is needed cause of LOD upgrading in 60fps,
	// which is needed cause LOD[1] can't double-lerp
	// animations
	
	// Without this, game crashes if you load
	// 1P Arcade N Tropy Crash Cove,
	// then startline boost while holding R2
	size += 0x200;
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