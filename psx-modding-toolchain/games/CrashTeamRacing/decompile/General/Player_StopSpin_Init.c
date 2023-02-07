#include <common.h>

void Player_StopSpin_Update();
void Player_StopSpin_PhysLinear();
void Player_Driving_Audio();
void Player_StopSpin_PhysAngular();
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void OnCollide_Drivers();
void COLL_StartSearch_Player();
void Player_JumpAndFriction();
void OnRender();
void Player_StopSpin_Animate();
void SpawnParticle_DriverMain();

void* PlayerStopSpinFuncTable[0xD] =
{
	0,
	Player_StopSpin_Update,
	Player_StopSpin_PhysLinear,
	Player_Driving_Audio,
	Player_StopSpin_PhysAngular,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	Player_StopSpin_Animate,
	SpawnParticle_DriverMain,
};

void DECOMP_Player_StopSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerStopSpinFuncTable[i];
	}
}