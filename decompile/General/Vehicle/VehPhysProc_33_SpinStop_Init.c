#include <common.h>

void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();
void DECOMP_VehPhysProc_SpinStop_Animate();

#ifdef USE_60FPS
void Hook60_DriverMain(struct Thread *t, struct Driver *d);
#endif

void* PlayerStopSpinFuncTable[0xD] =
{
	0,
	0,
	DECOMP_VehPhysProc_SlamWall_PhysLinear,	// not a mistake, use Crashing
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehPhysProc_SlamWall_PhysAngular, // not a mistake, use Crashing
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	VehPhysForce_CollideDrivers,
	COLL_StartSearch_Player,
	VehPhysGeneral_JumpAndFriction,
	VehPhysForce_TranslateMatrix,
	DECOMP_VehPhysProc_SpinStop_Animate,

		#ifdef USE_60FPS
		Hook60_DriverMain,
		#else
		VehEmitter_DriverMain
		#endif

	#endif
};

void DECOMP_VehPhysProc_SpinStop_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerStopSpinFuncTable[i];
	}
}