#include <common.h>

void DECOMP_MainInit_JitPoolsReset(struct GameTracker* gGT)
{
	JitPool_Clear(&gGT->JitPools.thread);
	JitPool_Clear(&gGT->JitPools.instance);
	JitPool_Clear(&gGT->JitPools.smallStack);
	JitPool_Clear(&gGT->JitPools.mediumStack);
	JitPool_Clear(&gGT->JitPools.largeStack);
	JitPool_Clear(&gGT->JitPools.particle);
	JitPool_Clear(&gGT->JitPools.oscillator);
	JitPool_Clear(&gGT->JitPools.rain);
}