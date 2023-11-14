#include <common.h>

void DECOMP_INSTANCE_Death(struct Instance* inst)
{
	DECOMP_JitPool_Remove(
		&sdata->gGT->JitPools.instance,
		inst);
}