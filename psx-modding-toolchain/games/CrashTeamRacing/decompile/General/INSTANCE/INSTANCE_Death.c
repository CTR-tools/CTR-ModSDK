#include <common.h>

void INSTANCE_Death(struct Instance* inst)
{
	AllocPool_Remove(
		&sdata->gGT->AllocPools.instance,
		inst);
}