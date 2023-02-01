#include <common.h>

void INSTANCE_Death(struct Instance* inst)
{
	JitPool_Remove(
		&sdata->gGT->JitPools.instance,
		inst);
}