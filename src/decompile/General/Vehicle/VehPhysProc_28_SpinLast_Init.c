#include <common.h>

void COLL_MOVED_PlayerSearch();
void COLL_FIXED_PlayerSearch();

#ifdef USE_60FPS
void Hook60_DriverMain(struct Thread *t, struct Driver *d);
#endif

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	DECOMP_VehPhysProc_SpinLast_Update,
	DECOMP_VehPhysProc_SpinLast_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehPhysProc_SpinLast_PhysAngular,
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_MOVED_PlayerSearch,
	VehPhysForce_CollideDrivers,
	COLL_FIXED_PlayerSearch,
	VehPhysGeneral_JumpAndFriction,
	VehPhysForce_TranslateMatrix,
	VehFrameProc_LastSpin,

		#ifdef USE_60FPS
		Hook60_DriverMain,
		#else
		VehEmitter_DriverMain
		#endif

	#endif
};

void DECOMP_VehPhysProc_SpinLast_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerLastSpinFuncTable[i];
	}
}