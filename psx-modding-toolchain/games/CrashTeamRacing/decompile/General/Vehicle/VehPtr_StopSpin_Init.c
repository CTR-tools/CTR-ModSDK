#include <common.h>

void DECOMP_VehPtr_Crashing_PhysLinear(); // not a mistake, use Crashing
void VehPtr_Driving_Audio();
void DECOMP_VehPtr_Crashing_PhysAngular(); // not a mistake, use Crashing
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void OnCollide_Drivers();
void COLL_StartSearch_Player();
void Player_JumpAndFriction();
void OnRender();
void DECOMP_VehPtr_StopSpin_Animate();
void VehParticle_DriverMain();

void* PlayerStopSpinFuncTable[0xD] =
{
	0,
	0,
	DECOMP_VehPtr_Crashing_PhysLinear,	// not a mistake, use Crashing
	VehPtr_Driving_Audio,
	DECOMP_VehPtr_Crashing_PhysAngular, // not a mistake, use Crashing
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	DECOMP_VehPtr_StopSpin_Animate,
	VehParticle_DriverMain,
};

void DECOMP_VehPtr_StopSpin_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerStopSpinFuncTable[i];
	}
}