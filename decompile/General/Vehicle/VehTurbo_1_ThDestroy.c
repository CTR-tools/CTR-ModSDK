#include <common.h>

void DECOMP_VehTurbo_ThDestroy(struct Thread* t)
{
	struct Turbo* turboObj;
	turboObj = t->object;
	
	struct Driver* d = turboObj->driver;
	d->actionsFlagSet &= 0xfffffdff;
	
	DECOMP_INSTANCE_Death(t->inst);
	DECOMP_INSTANCE_Death(turboObj->inst);
}