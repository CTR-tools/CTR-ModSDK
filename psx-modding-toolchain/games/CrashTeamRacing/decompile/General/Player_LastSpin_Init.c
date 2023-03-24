#include <common.h>

void DECOMP_Player_LastSpin_Update();
void DECOMP_Player_LastSpin_PhysLinear();
void Player_Driving_Audio();
void DECOMP_Player_LastSpin_PhysAngular();
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void OnCollide_Drivers();
void COLL_StartSearch_Player();
void Player_JumpAndFriction();
void OnRender();
void OnAnimate_LastSpin();
void VehParticle_DriverMain();

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	DECOMP_Player_LastSpin_Update,
	DECOMP_Player_LastSpin_PhysLinear,
	Player_Driving_Audio,
	DECOMP_Player_LastSpin_PhysAngular,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_LastSpin,
	VehParticle_DriverMain,
};

void DECOMP_Player_LastSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerLastSpinFuncTable[i];
	}
}