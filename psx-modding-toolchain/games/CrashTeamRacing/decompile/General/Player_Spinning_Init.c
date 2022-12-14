#include <common.h>

void DECOMP_Player_Spinning_Update();
void DECOMP_Player_Spinning_Input();
void Player_Driving_Audio();
void DECOMP_Player_Spinning_Interpolate();
void OnApplyForces();
void COLL_StartSearch_NearPlayer();
void OnCollide_Drivers();
void COLL_StartSearch_Player();
void Player_JumpAndFriction();
void OnRender();
void OnAnimate_Spinning();
void SpawnParticle_DriverMain();

void* PlayerSpinningFuncTable[0xD] =
{
	0,
	DECOMP_Player_Spinning_Update,
	DECOMP_Player_Spinning_Input,
	Player_Driving_Audio,
	DECOMP_Player_Spinning_Interpolate,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	OnAnimate_Spinning,
	SpawnParticle_DriverMain,
};

void DECOMP_Player_Spinning_Init(struct Thread* t, struct Driver* d)
{
	int i;
	
	// spinning
	d->kartState = 3;
	
	d->unk_LerpToForwards = 0;
	d->turboMeterLeft = 0;
	
	if(LOAD_IsOpen_RacingOrBattle())
	{
		RB_Player_ModifyWumpa(d, -1);
	}
	
	Voiceline_RequestPlay(3, data.characterIDs[d->driverID], 0x10);
	
	// if spinning left
	d->KartStates.Spinning.spinDir = 1;
	d->KartStates.Spinning.driftSpinRate = 300;
	
	if(d->ampTurnState < 0)
	{
		// if spinning right
		d->KartStates.Spinning.spinDir = -1;
		d->KartStates.Spinning.driftSpinRate = -300;
	}
	
	if(d->simpTurnState < 1)
	{
		i = 0x19;
	}
	
	else
	{
		i = 0x29;
	}
	
	GAMEPAD_Vib_1(d, i, 0x60);
	
	for(i = 0; i < 0xD; i++)
	{
		d->funcPtrs[i] = PlayerSpinningFuncTable[i];
	}
}