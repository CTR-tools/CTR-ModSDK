#include <common.h>

void Player_LastSpin_Update();
void Player_LastSpin_Input();
void Player_Driving_Audio();
void Player_LastSpin_Interpolate();
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void OnCollide_Drivers();
void COLL_StartSearch_Player();
void Player_JumpAndFriction();
void OnRender();
void OnAnimate_LastSpin();
void SpawnParticle_DriverMain();

void* PlayerLastSpinFuncTable[0xD] =
{
	0,
	Player_LastSpin_Update,
	Player_LastSpin_Input,
	Player_Driving_Audio,
	Player_LastSpin_Interpolate,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_LastSpin,
	SpawnParticle_DriverMain,
};

void DECOMP_Player_LastSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerLastSpinFuncTable[i];
	}
}