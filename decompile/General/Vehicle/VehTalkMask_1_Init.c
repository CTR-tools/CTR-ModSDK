#include <common.h>

void DECOMP_VehTalkMask_ThTick(struct Thread* t);

struct Instance* DECOMP_VehTalkMask_Init()
{
	struct Instance* mhInst =
		DECOMP_INSTANCE_BirthWithThread(
			0x39, 0, SMALL, AKUAKU,
			DECOMP_VehTalkMask_ThTick,
			sizeof(struct MaskHint), 0);
			
	struct Thread* mhTh = mhInst->thread;
	mhTh->funcThDestroy = DECOMP_PROC_DestroyInstance;
	
	((struct MaskHint*)mhTh->object)->scale = 0;
	
	return mhInst;
}