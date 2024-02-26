#include <common.h>

void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();

void* PlayerSpinningFuncTable[0xD] =
{
	DECOMP_VehPtr_Spinning_InitSetUpdate,
	0,
	DECOMP_VehPtr_Spinning_PhysLinear,
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_Spinning_PhysAngular,
	DECOMP_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_Spinning,
	VehParticle_DriverMain,
	#endif
};

void DECOMP_VehPtr_Spinning_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	d->kartState = KS_SPINNING;
	
	d->unk_LerpToForwards = 0;
	d->turbo_MeterRoomLeft = 0;
	
#ifndef REBUILD_PS1
	if(LOAD_IsOpen_RacingOrBattle())
	{
		RB_Player_ModifyWumpa(d, -1);
	}
	
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
// and then DECOMP_VehPtr_Spinning_Update should happen after that,
// otherwise driver wont spin out if hitting armadillo while driver is motionless
void DECOMP_VehPtr_Spinning_InitSetUpdate(struct Thread* t, struct Driver* d)
{
	d->funcPtrs[0] = 0;
	d->funcPtrs[1] = DECOMP_VehPtr_Spinning_Update;
}