#include <common.h>

void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();

#ifdef USE_60FPS
void Hook60_DriverMain(struct Thread *t, struct Driver *d);
#endif

void* PlayerSpinningFuncTable[0xD] =
{
	DECOMP_VehPhysProc_SpinFirst_InitSetUpdate,
	0,
	DECOMP_VehPhysProc_SpinFirst_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehPhysProc_SpinFirst_PhysAngular,
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	VehPhysForce_CollideDrivers,
	COLL_StartSearch_Player,
	VehPhysGeneral_JumpAndFriction,
	VehPhysForce_TranslateMatrix,
	VehFrameProc_Spinning,

		#ifdef USE_60FPS
		Hook60_DriverMain,
		#else
		VehEmitter_DriverMain
		#endif

	#endif
};

void DECOMP_VehPhysProc_SpinFirst_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	d->kartState = KS_SPINNING;
	
	d->unk_LerpToForwards = 0;
	d->turbo_MeterRoomLeft = 0;
	
	if(DECOMP_LOAD_IsOpen_RacingOrBattle())
	{
		DECOMP_RB_Player_ModifyWumpa(d, -1);
	}

	#ifdef USE_ONLINE
	if(d->driverID == 0)
	#endif

		#ifndef REBUILD_PS1	
		Voiceline_RequestPlay(3, data.characterIDs[d->driverID], 0x10);
		#endif
	
	// if spinning left
	d->KartStates.Spinning.spinDir = 1;
	d->KartStates.Spinning.driftSpinRate = FPS_HALF(300);
	
	if(d->ampTurnState < 0)
	{
		// if spinning right
		d->KartStates.Spinning.spinDir = -1;
		d->KartStates.Spinning.driftSpinRate = FPS_HALF(-300);
	}
	
	if(d->simpTurnState < 1)
	{
		i = 0x19;
	}
	
	else
	{
		i = 0x29;
	}
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerSpinningFuncTable[i];
	}
	
#ifndef REBUILD_PS1
	GAMEPAD_JogCon1(d, i, 0x60);
#endif
}

// all other Spinning functions should execute for one frame,
// and then DECOMP_VehPhysProc_SpinFirst_Update should happen after that,
// otherwise driver wont spin out if hitting armadillo while driver is motionless
void DECOMP_VehPhysProc_SpinFirst_InitSetUpdate(struct Thread* t, struct Driver* d)
{
	d->funcPtrs[0] = 0;
	d->funcPtrs[1] = DECOMP_VehPhysProc_SpinFirst_Update;
}