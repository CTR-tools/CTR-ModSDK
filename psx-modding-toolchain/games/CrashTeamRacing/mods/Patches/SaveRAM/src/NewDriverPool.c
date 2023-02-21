#include <common.h>

// Mem_AddExtraThreads.c
void ClearThreadPool(struct JitPool* p);

void ClearDriverPool(struct JitPool* p)
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
void New_MainInit_JitPoolsReset(struct GameTracker* gGT)

{
  // erase everything in all pools
  ClearThreadPool(&gGT->JitPools.thread); 		// Thread Pool
  JitPool_Clear(&gGT->JitPools.instance); 		// Instance Pool
  JitPool_Clear(&gGT->JitPools.smallStack); 	// Small Stack Pool
  JitPool_Clear(&gGT->JitPools.mediumStack); 	// Medium Stack Pool
  ClearDriverPool(&gGT->JitPools.largeStack); 	// Large Stack Pool (drivers)
  JitPool_Clear(&gGT->JitPools.particle); 		// Particle Pool
  JitPool_Clear(&gGT->JitPools.oscillator); 	// Oscillator Pool
  JitPool_Clear(&gGT->JitPools.rain); 			// Rain Pools
  return;
}