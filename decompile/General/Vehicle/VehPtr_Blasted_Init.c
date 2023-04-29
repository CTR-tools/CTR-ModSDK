#include <common.h>

int LOAD_IsOpen_RacingOrBattle();
void RB_Player_ModifyWumpa(struct Driver* driver, int wumpaDelta);
int Instance_GetNumAnimFrames(struct Driver* driver, int param_2);
int Instance_GetStartFrame(int midpoint, int numFrames);
int MixRNG_Scramble();
void DECOMP_VehPtr_Blasted_Update(struct Thread* thread, struct Driver* driver);
void DECOMP_VehPtr_Blasted_PhysLinear(struct Thread* thread, struct Driver* driver);
void VehPtr_Driving_Audio(struct Thread* thread, struct Driver* driver);
void DECOMP_VehPtr_Blasted_PhysAngular(struct Thread* thread, struct Driver* driver);
void OnApplyForces(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_NearPlayer(struct Thread* thread, struct Driver* driver);
void OnCollide_Drivers(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_Player(struct Thread* thread, struct Driver* driver);
void Player_JumpAndFriction(struct Thread* thread, struct Driver* driver);
void OnRender(struct Thread* thread, struct Driver* driver);
void DECOMP_VehPtr_Blasted_Animate(struct Thread* thread, struct Driver* driver);
void VehParticle_DriverMain(struct Thread* thread, struct Driver* driver);
void GAMEPAD_Vib_1(struct Driver* driver, char param_2, u_short param_3);

void* PlayerBlastedFuncTable[0xD] =
{
	(void *)0x0,
	DECOMP_VehPtr_Blasted_Update,
	DECOMP_VehPtr_Blasted_PhysLinear,
	VehPtr_Driving_Audio,
	DECOMP_VehPtr_Blasted_PhysAngular,
	OnApplyForces,
	COLL_StartSearch_NearPlayer,
	OnCollide_Drivers,
	COLL_StartSearch_Player,
	Player_JumpAndFriction,
	OnRender,
	DECOMP_VehPtr_Blasted_Animate,
	VehParticle_DriverMain
};

void VehPtr_Blasted_Init(struct Thread *thread, struct Driver *driver)
{
	int i;
	u_int IsOpen_RacingOrBattle;
	int iVar2;
	char bVar3;
	char simpTurnState;
	
	driver->kartState = '\x06';
	driver->turbo_MeterRoomLeft = 0;
	
	if (
			(LOAD_IsOpen_RacingOrBattle() != 0) && 
			((sdata->gGT->gameMode1 & ADVENTURE_ARENA) == 0)
		)
	{
		RB_Player_ModifyWumpa(driver, -3);
	}
	
	*(u_char *)&driver->instSelf->animIndex = 0;
	iVar2 = Instance_GetNumAnimFrames(driver->instSelf, 0);
	iVar2 = Instance_GetStartFrame(0, iVar2);
	driver->instSelf->vertSplit = (short)iVar2;
	iVar2 = MixRNG_Scramble();
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
	GAMEPAD_Vib_1(driver, bVar3, 0x60);
	
	for(i = 0; i < 0xD; i++)
	{
		driver->funcPtrs[i] = PlayerBlastedFuncTable[i];
	}
	
	return;
}