#include <common.h>

void DECOMP_PROC_DestroySelf(struct Thread* t)
{
	// thread must exist
	if(t == 0) return;
	
	// this is usuallly PROC_DestroyInstance
	if(t->funcThDestroy != 0)
		t->funcThDestroy(t);
	
	// used by RB_Follower
	t->timesDestroyed++;
	
	// destroy object attached,
	// guaranteed all threads have one
	DECOMP_PROC_DestroyObject(t->object, t->flags);
	
	// recycle thread
	DECOMP_LIST_AddFront(&sdata->gGT->JitPools.thread.free, (struct Item*)t);
}