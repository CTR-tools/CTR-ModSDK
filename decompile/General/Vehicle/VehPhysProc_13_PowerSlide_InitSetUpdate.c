#include <common.h>

void DECOMP_VehPhysProc_PowerSlide_InitSetUpdate(struct Thread* t, struct Driver* d)
{
	// This is so the update function
	// is not called on the first frame,
	// just like spinning

	d->funcPtrs[0] = 0;
	d->funcPtrs[1] = DECOMP_VehPhysProc_PowerSlide_Update;
}