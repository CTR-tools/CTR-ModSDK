#include <common.h>

void DECOMP_VehPhysProc_SpinFirst_Init();
void DECOMP_VehStuckProc_Tumble_Init();

int DECOMP_VehPickState_NewState(
	struct Driver* victimDriver, int damageType,
	struct Driver* attackDriver, int reason)
{
	int voice;
	
	int victimState = victimDriver->kartState;
	victimDriver->ChangeState_param2 = 0;
	
	int victimCharacter;
	victimCharacter = data.characterIDs[victimDriver->driverID];
	
	if(victimState == KS_MASK_GRABBED)
		return 0;
	
	if(
		// If player is using mask weapon
		((victimDriver->actionsFlagSet & 0x800000) != 0) ||
		
		(victimDriver->invincibleTimer != 0)
	  )
	{
VictimLaugh:
		Voiceline_RequestPlay(2, victimCharacter, 0x10);
		return 0;
	}
	
	if(victimDriver->instBubbleHold != 0)
	{
		struct Shield* shieldObj =
			victimDriver->instBubbleHold->thread->object;
			
		shieldObj->flags |= 1;
		
		victimDriver->invincibleTimer = 0x2a0;
		
		victimDriver->instBubbleHold = 0;
		
		goto VictimLaugh;
	}
	
	voice = 0;
	
	if(damageType == 0)
		return 1;
	
	// spinning
	else if(damageType == 1)
	{
		// 1.0s
		victimDriver->NoInputTimer = 0x3c0;
		
		if(victimState != 3)
		{
SPINOUT:
			victimDriver->funcPtrs[0] = DECOMP_VehPhysProc_SpinFirst_Init;	
		}
	}
	
	// blasted
	else if(damageType == 2)
	{
		// quit if already blasted
		if(victimState == KS_BLASTED)
			return 0;
		
		// quit if already blasted
		if(victimDriver->funcPtrs[0] == DECOMP_VehStuckProc_Tumble_Init)
			return 0;
		
		victimDriver->funcPtrs[0] = DECOMP_VehStuckProc_Tumble_Init;
		
		// 2.4s
		victimDriver->NoInputTimer = 0x960;
		
		victimDriver->squishTimer = 0;
		
		voice = 1;
	}
	
	// squished
	else if(damageType == 3)
	{
		if(victimState != KS_SPINNING)
		{
			// squish sound
			OtherFX_Play_Echo(
				0x5a, 1, 
				victimDriver->actionsFlagSet & 0x10000
			);
			
			voice = 4;
		}
		
		// 0.25s
		victimDriver->NoInputTimer = 0xf0;
		
		victimDriver->squishTimer = 0xf00;
		
		goto SPINOUT;
	}
	
	// burned
	else if(damageType == 4)
	{
		if(victimDriver->burnTimer == 0)
		{
			OtherFX_Play(0x69, 1);
			
			voice = 1;
		}
		
		// 2.0s
		victimDriver->NoInputTimer = 0x780;
		
		victimDriver->burnTimer = 0xf00;
		
		goto SPINOUT;
	}
	
	// mask grab
	else //if(damageType == 5)
	{
		// 3.36s
		victimDriver->NoInputTimer = 0xd20;
		
		victimDriver->funcPtrs[0] = VehStuckProc_PlantEaten_Init;
		
		voice = 1;
	}
	
	if(voice != 0)
	{
		Voiceline_RequestPlay(voice, victimCharacter, 0x10);
	}
	
	switch(reason)
	{
		// hit by bomb
		case 1:
			victimDriver->numTimesBombHitYou++;
			break;
			
		// hit by motionless potion
		case 2:
			victimDriver->numTimesMotionlessPotionHitYou++;
			break;
		
		default:
			break;
	}
	
	if(attackDriver != 0)
		if(attackDriver != victimDriver)
			switch(reason)
			{
				// hit by bomb
				case 1:
					attackDriver->numTimesBombsHitSomeone++;
					attackDriver->quip4 |= 1;
					break;
				
				// hit by missile
				case 3:
					attackDriver->numTimesMissileHitSomeone++;
					attackDriver->quip4 |= 2;
					break;
					
				// hit by moving potion
				case 4:
					attackDriver->numTimesMovingPotionHitSomeone++;
					attackDriver->quip4 |= 4;
					break;
				
				// squished by turbo
				case 5:
					attackDriver->numTimesSquishedSomeone++;
					break;
				
				// hit by mask weapon
				case 6:
					attackDriver->quip4 |= 8;
					break;
					
				default:
					break;
			}
	
	victimDriver->kartState = KS_NORMAL;
	victimDriver->reserves = 0;
	victimDriver->turbo_outsideTimer = 0;
	victimDriver->matrixArray = 0;
	victimDriver->matrixIndex = 0;
	
	GAMEPAD_ShockFreq(victimDriver, 8, 0);
	GAMEPAD_ShockForce1(victimDriver, 8, 0x7f);
	
	int gameMode1 = sdata->gGT->gameMode1;
	
	if(
		(attackDriver != 0) &&
		((gameMode1 & END_OF_RACE) == 0)
	)
	{
		#ifdef USE_ONLINE
		if(attackDriver->driverID != 0)
			return;
		#endif
		
		struct PushBuffer* pb = 
			&sdata->gGT->pushBuffer[attackDriver->driverID];
		
		short posScreen[2];
		RB_Fruit_GetScreenCoords(pb, attackDriver->instSelf, &posScreen[0]);
		
		// screenPosXY
		attackDriver->BattleHUD.startX = pb->rect.x + posScreen[0];
		attackDriver->BattleHUD.startY = pb->rect.y + posScreen[1];
	
		// if-checked for Battle inside the function
		RB_Player_KillPlayer(attackDriver, victimDriver);
		
		// === Naughty Dog Bug ===
		// original game has unreachable code here for QUIP data
	}
	
	// enable collision (remove flag that prevents collision)
	victimDriver->instSelf->thread->flags &= ~(0x1000);
	
	// make driver visible, if invisible
	victimDriver->instSelf->flags &= ~(0x80);
}