#include <common.h>

void DECOMP_INSTANCE_Death(struct Instance* inst)
{
	JitPool_Remove(
		&sdata->gGT->JitPools.instance,
		inst);
}