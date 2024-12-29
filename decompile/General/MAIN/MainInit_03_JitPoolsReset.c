#include <common.h>

void DECOMP_MainInit_JitPoolsReset(struct GameTracker* gGT)
{
	DECOMP_JitPool_Clear(&gGT->JitPools.thread);
	DECOMP_JitPool_Clear(&gGT->JitPools.instance);
	DECOMP_JitPool_Clear(&gGT->JitPools.smallStack);
	DECOMP_JitPool_Clear(&gGT->JitPools.mediumStack);
	DECOMP_JitPool_Clear(&gGT->JitPools.largeStack);
	DECOMP_JitPool_Clear(&gGT->JitPools.particle);
	DECOMP_JitPool_Clear(&gGT->JitPools.oscillator);
	DECOMP_JitPool_Clear(&gGT->JitPools.rain);
}