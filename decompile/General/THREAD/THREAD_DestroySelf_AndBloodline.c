#include <common.h>

void DECOMP_THREAD_DestroySelf(struct Thread* t)
{
	// thread must exist
	if(t == 0) return;
	
	// this is usuallly THREAD_DestroyInstance
	if(t->funcThDestroy != 0)
		t->funcThDestroy(t);
	
	// useless?
	t->timesDestroyed++;
	
	// destroy object attached,
	// guaranteed all threads have one
	DECOMP_THREAD_DestroyObject(t->object, t->flags);
	
	// recycle thread
	DECOMP_LIST_AddFront(&sdata->gGT->JitPools.thread.free, t);
}

// must be here, too large for original slot
void DECOMP_THREAD_DestroyBloodline(struct Thread* t)
{	
	while(t != 0)
	{
		// recursively find all children
		if(t->childThread != 0)
			DECOMP_THREAD_DestroyBloodline(t->childThread);
		
		DECOMP_THREAD_DestroySelf(t);
		t = t->siblingThread;
	}
}