#include <common.h>

void DECOMP_VehPhysProc_SlamWall_PhysLinear(struct Thread* t, struct Driver* d)
{
	DECOMP_VehPhysProc_Driving_PhysLinear(t, d);

	// baseSpeed and fireSpeed
	// set both "shorts" in one "int"
	*(int*)&d->baseSpeed = 0;
}