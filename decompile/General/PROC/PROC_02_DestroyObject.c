#include <common.h>

void DECOMP_PROC_DestroyObject(void* object, int threadFlags)
{
	struct JitPool* allPools; 
	struct JitPool* myPool;
	int index;
	
	// TODO: need an array and enum for this
	allPools = &sdata->gGT->JitPools.thread;
	
	// 0x100 - largeStackPool	(0x1970) [4]
	// 0x200 - medStackPool		(0x1948) [3]
	// 0x300 - smallStackPool	(0x1920) [2]
	
	// index is now 1,2,3
	index = (threadFlags>>8)&3;
	
	// index is now 4,3,2
	index = 5 - index;
	
	// small, med, large
	myPool = &allPools[index];
	
	// in allocation, "next" and "prev" are abstracted
	// with obj+=8, so not all structs need "next" and "prev",
	// now subtract 8 bytes to access those two pointers
	object = (void*)((unsigned int)object - 8);
	
	// add object back to free list
	DECOMP_LIST_AddFront(&myPool->free, object);
}