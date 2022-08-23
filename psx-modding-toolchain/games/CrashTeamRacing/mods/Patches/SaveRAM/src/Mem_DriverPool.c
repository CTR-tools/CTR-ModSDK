#include <common.h>

// To do: add header
void AllocPool_Clear(struct AllocPool* ap);
void LIST_Clear(struct LinkedList* L);
void LIST_AddFront(struct LinkedList* L, void* item);

// Mem_AddExtraThreads.c
void ClearThreadPool(struct AllocPool* p);

void ClearDriverPool(struct AllocPool* p)
{
	int loop;
	LIST_Clear(&p->free);
	LIST_Clear(&p->taken);

	for(loop = 0; loop < 4*0x660; loop+=0x660)
	{
		LIST_AddFront(&p->free, (void*)(0x8000A000+loop));

		// add 0x400 from what I originally wanted, fixes Unirom
		LIST_AddFront(&p->free, (void*)(0x8000C400+loop));

		// last byte of last driver, in 8000A, is 0x8000B980
		// last byte of last driver, in 8000C, is 0x8000DD80
	}
}

// original is now free to overwrite
void New_ClearAllMemPools(struct GameTracker* gGT)

{
  // erase everything in all pools
  ClearThreadPool(&gGT->AllocPools.thread); 		// Thread Pool
  AllocPool_Clear(&gGT->AllocPools.instance); 		// Instance Pool
  AllocPool_Clear(&gGT->AllocPools.smallStack); 	// Small Stack Pool
  AllocPool_Clear(&gGT->AllocPools.mediumStack); 	// Medium Stack Pool
  ClearDriverPool(&gGT->AllocPools.largeStack); 	// Large Stack Pool (drivers)
  AllocPool_Clear(&gGT->AllocPools.particle); 		// Particle Pool
  AllocPool_Clear(&gGT->AllocPools.oscillator); 	// Oscillator Pool
  AllocPool_Clear(&gGT->AllocPools.rain); 			// Rain Pools
  return;
}