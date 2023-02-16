#include <common.h>

u_int LOAD_IsOpen_RacingOrBattle();
void RB_Player_ModifyWumpa(struct Driver* driver, int wumpaDelta);
int Instance_GetNumAnimFrames(struct Driver* driver, int param_2);
int Instance_GetStartFrame(int midpoint, int numFrames);
int RNG_Scramble();
void Player_Blasted_Update(struct Thread* thread, struct Driver* driver);
void Player_Blasted_PhysLinear(struct Thread* thread, struct Driver* driver);
void Player_Driving_Audio(struct Thread* thread, struct Driver* driver);
void Player_Blasted_PhysAngular(struct Thread* thread, struct Driver* driver);
void OnApplyForces(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_NearPlayer(struct Thread* thread, struct Driver* driver);
void OnCollide_Drivers(struct Thread* thread, struct Driver* driver);
void COLL_StartSearch_Player(struct Thread* thread, struct Driver* driver);
void Player_JumpAndFriction(struct Thread* thread, struct Driver* driver);
void OnRender(struct Thread* thread, struct Driver* driver);
void Player_Blasted_Animate(struct Thread* thread, struct Driver* driver);
void SpawnParticle_DriverMain(struct Thread* thread, struct Driver* driver);
void GAMEPAD_Vib_1(struct Driver* driver, char param_2, u_short param_3);

void Player_Blasted_Init(struct Thread *thread, struct Driver *driver)
{
	u_int IsOpen_RacingOrBattle;
	int iVar2;
	byte bVar3;
	char simpTurnState;
	
	driver->kartState = '\x06';
	driver->turbo_MeterRoomLeft = 0;
	IsOpen_RacingOrBattle = LOAD_IsOpen_RacingOrBattle();
	if ((IsOpen_RacingOrBattle) && ((sdata->gGT->gameMode1 & 0x100000U) == 0))
	{
		RB_Player_ModifyWumpa(driver, -3);
	}
	*(u_char *)&driver->instSelf->animIndex = 0;
	iVar2 = Instance_GetNumAnimFrames(driver->instSelf, 0);
	iVar2 = Instance_GetStartFrame(0, iVar2);
	driver->instSelf->vertSplit = (short)iVar2;
	iVar2 = RNG_Scramble();
	driver->KartStates = iVar2 & 4;
	driver->funcPtrs[1] = Player_Blasted_Update;
	driver->funcPtrs[2] = Player_Blasted_PhysLinear;
	driver->funcPtrs[3] = Player_Driving_Audio;
	driver->funcPtrs[4] = Player_Blasted_PhysAngular;
	driver->funcPtrs[5] = OnApplyForces;
	driver->funcPtrs[6] = COLL_StartSearch_NearPlayer;
	driver->funcPtrs[7] = OnCollide_Drivers;
	driver->funcPtrs[8] = COLL_StartSearch_Player;
	driver->funcPtrs[9] = Player_JumpAndFriction;
	driver->funcPtrs[10] = OnRender;
	driver->funcPtrs[0xb] = Player_Blasted_Animate;
	simpTurnState = driver->simpTurnState;
	driver->funcPtrs[0] = (void *)0x0;
	driver->funcPtrs[0xc] = SpawnParticle_DriverMain;
	if (simpTurnState < 1)
	{
		bVar3 = 0x19;
	}
	else
	{
		bVar3 = 0x29;
	}
	GAMEPAD_Vib_1(driver, bVar3, 0x60);
	return;
}