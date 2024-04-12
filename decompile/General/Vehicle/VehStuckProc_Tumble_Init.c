#include <common.h>

void COLL_StartSearch_NearPlayer(struct Thread* thread, struct Driver* driver);
void VehPhysForce_CollideDrivers(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_Player(struct Thread* thread, struct Driver* driver);
void VehPhysForce_TranslateMatrix(struct Thread* thread, struct Driver* driver);
void DECOMP_VehStuckProc_Tumble_Animate(struct Thread* thread, struct Driver* driver);
void VehEmitter_DriverMain(struct Thread* thread, struct Driver* driver);

void* PlayerBlastedFuncTable[0xD] =
{
	(void *)0x0,
	DECOMP_VehStuckProc_Tumble_Update,
	DECOMP_VehStuckProc_Tumble_PhysLinear,
	DECOMP_VehPhysProc_Driving_Audio,
	DECOMP_VehStuckProc_Tumble_PhysAngular,
	DECOMP_VehPhysForce_OnApplyForces,
	
	#ifndef REBUILD_PS1
	COLL_StartSearch_NearPlayer,
	VehPhysForce_CollideDrivers,
	COLL_StartSearch_Player,
	VehPhysGeneral_JumpAndFriction,
	VehPhysForce_TranslateMatrix,
	DECOMP_VehStuckProc_Tumble_Animate,
	VehEmitter_DriverMain
	#endif
};

void DECOMP_VehStuckProc_Tumble_Init(struct Thread *thread, struct Driver *driver)
{
	int i;
	u_int IsOpen_RacingOrBattle;
	int iVar2;
	char bVar3;
	char simpTurnState;
	
	driver->kartState = KS_BLASTED;
	driver->turbo_MeterRoomLeft = 0;
	
	if (
			(DECOMP_LOAD_IsOpen_RacingOrBattle() != 0) && 
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
	{
		DECOMP_RB_Player_ModifyWumpa(driver, -3);
	}
	
	driver->instSelf->animIndex = 0;
	
	iVar2 = FPS_DOUBLE(10);
	#if 0 // 10 =
		VehFrameInst_GetStartFrame(
			
			0, // midpoint
			
			VehFrameInst_GetNumAnimFrames(
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