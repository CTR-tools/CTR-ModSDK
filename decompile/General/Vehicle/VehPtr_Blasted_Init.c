#include <common.h>

int LOAD_IsOpen_RacingOrBattle();
void RB_Player_ModifyWumpa(struct Driver* driver, int wumpaDelta);

void OnApplyForces(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_NearPlayer(struct Thread* thread, struct Driver* driver);
void OnCollide_Drivers(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_Player(struct Thread* thread, struct Driver* driver);
void OnRender(struct Thread* thread, struct Driver* driver);
void DECOMP_VehPtr_Blasted_Animate(struct Thread* thread, struct Driver* driver);
void VehParticle_DriverMain(struct Thread* thread, struct Driver* driver);

void* PlayerBlastedFuncTable[0xD] =
{
	(void *)0x0,
	DECOMP_VehPtr_Blasted_Update,
	DECOMP_VehPtr_Blasted_PhysLinear,
	DECOMP_VehPtr_Driving_Audio,
	DECOMP_VehPtr_Blasted_PhysAngular,
	
	#ifndef REBUILD_PS1
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	DECOMP_VehPtr_Blasted_Animate,
	VehParticle_DriverMain
	#endif
};

void DECOMP_VehPtr_Blasted_Init(struct Thread *thread, struct Driver *driver)
{
	int i;
	u_int IsOpen_RacingOrBattle;
	int iVar2;
	char bVar3;
	char simpTurnState;
	
	driver->kartState = KS_BLASTED;
	driver->turbo_MeterRoomLeft = 0;
	
#ifndef REBUILD_PS1
	if (
			(LOAD_IsOpen_RacingOrBattle() != 0) && 
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
	{
		RB_Player_ModifyWumpa(driver, -3);
	}
#endif
	
	driver->instSelf->animIndex = 0;
	
	iVar2 = 10;
	#if 0 // 10 =
		VehAnim_Instance_GetStartFrame(
			
			0, // midpoint
			
			VehAnim_Instance_GetNumAnimFrames(
				driver->instSelf, 	// driver instance
				0					// anim #0, steer
			)
		);
	#endif
	
	driver->instSelf->animFrame = (short)iVar2;
	
	iVar2 = DECOMP_MixRNG_Scramble();
	driver->KartStates.Blasted.boolPlayBackwards = iVar2 & 4;
	
	simpTurnState = driver->simpTurnState;
	if (simpTurnState < 1)
	{
		bVar3 = 0x19;
	}
	else
	{
		bVar3 = 0x29;
	}
	
	for(i = 0; i < 0xD; i++)
	{
		driver->funcPtrs[i] = PlayerBlastedFuncTable[i];
	}
	
#ifndef REBUILD_PS1
	GAMEPAD_JogCon1(driver, bVar3, 0x60);
#endif
}