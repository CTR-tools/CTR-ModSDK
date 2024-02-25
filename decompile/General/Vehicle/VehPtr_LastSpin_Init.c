#include <common.h>

void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	DECOMP_VehPtr_LastSpin_Update,
	DECOMP_VehPtr_LastSpin_PhysLinear,
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_LastSpin_PhysAngular,
	
	#ifndef REBUILD_PS1
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_LastSpin,
	VehParticle_DriverMain,
	#endif
};

void DECOMP_VehPtr_LastSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerLastSpinFuncTable[i];
	}
}