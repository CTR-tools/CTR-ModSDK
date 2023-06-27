#include <common.h>

void DECOMP_VehPtr_LastSpin_Update();
void DECOMP_VehPtr_LastSpin_PhysLinear();
void DECOMP_VehPtr_LastSpin_PhysAngular();
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void COLL_StartSearch_Player();

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	DECOMP_VehPtr_LastSpin_Update,
	DECOMP_VehPtr_LastSpin_PhysLinear,
	VehPtr_Driving_Audio,
	DECOMP_VehPtr_LastSpin_PhysAngular,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_LastSpin,
	VehParticle_DriverMain,
};

void DECOMP_VehPtr_LastSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerLastSpinFuncTable[i];
	}
}