#include <common.h>

struct Instance* INSTANCE_Birth3D(
	struct Model* model, char* name, struct Thread* th)
{
	struct Instance* inst =
		JitPool_Add(&sdata->gGT->JitPools.instance);

	if(inst != 0)
	{
		INSTANCE_Birth(inst, model, name, th, 0xf);
	}
	
	return inst;
}