#include <common.h>

void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	DECOMP_VehPhysProc_SpinLast_Update,
	DECOMP_VehPhysProc_SpinLast_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehPhysProc_SpinLast_PhysAngular,
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	VehPhysForce_CollideDrivers,
	COLL_StartSearch_Player,
	VehPhysGeneral_JumpAndFriction,
	VehPhysForce_TranslateMatrix,
	VehFrameProc_LastSpin,
	VehEmitter_DriverMain,
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