#include <common.h>

void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();
void DECOMP_VehPtr_Crashing_Animate();

// budget, 0x120 bytes, 288 bytes

void* PlayerCrashingFuncTable[13] =
{
	0,
	0,
	DECOMP_VehPtr_Crashing_PhysLinear,
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_Crashing_PhysAngular,
	
	#ifndef REBUILD_PS1
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	DECOMP_VehPtr_Crashing_Animate,
	VehParticle_DriverMain,
	#endif
};

void DECOMP_VehPtr_Crashing_Init(struct Thread* t, struct Driver* d)
{
	int i;
	struct Instance* inst;
	inst = d->instSelf;
	
	// it doesn't set 2? does that change anyway?
	inst->scale[0] = 0xccc;
	inst->scale[1] = 0xccc;
	
	d->kartState = KS_CRASHING;
	
	d->numFramesSpentSteering = 1000;
	
	d->Screen_OffsetY = 0;
	d->ampTurnState = 0;
	d->unk36E = 0;
	d->speed = 0;
	d->speedApprox = 0;
	d->baseSpeed = 0;
	d->fireSpeed = 0;
	d->rotationSpinRate = 0;
	d->unk_LerpToForwards = 0;
	d->unk3D4[0] = 0;
	d->unk3D4[1] = 0;
	d->unk3D4[2] = 0;
	d->turbo_MeterRoomLeft = 0;
	d->turbo_outsideTimer = 0;
	d->turbo_audioCooldown = 0;
	d->reserves = 0;
	d->distanceFromGround = 0;
	d->jumpSquishStretch = 0;
	d->unk40E = 0;
	d->jumpSquishStretch2 = 0;
	
	// all ints set to zero
	d->xSpeed = 0;
	d->ySpeed = 0;
	d->zSpeed = 0;
	d->velocityXYZ[0] = 0;
	d->velocityXYZ[1] = 0;
	d->velocityXYZ[2] = 0;
	
	for(i = 0; i < 13; i++)
	{
		d->funcPtrs[i] = PlayerCrashingFuncTable[i];
	}
}