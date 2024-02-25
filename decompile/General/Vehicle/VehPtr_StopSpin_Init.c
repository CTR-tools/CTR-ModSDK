#include <common.h>

void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();
void DECOMP_VehPtr_StopSpin_Animate();

void* PlayerStopSpinFuncTable[0xD] =
{
	0,
	0,
	DECOMP_VehPtr_Crashing_PhysLinear,	// not a mistake, use Crashing
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_Crashing_PhysAngular, // not a mistake, use Crashing
	
	#ifndef REBUILD_PS1
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	DECOMP_VehPtr_StopSpin_Animate,
	VehParticle_DriverMain,
	#endif
};

void DECOMP_VehPtr_StopSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerStopSpinFuncTable[i];
	}
}