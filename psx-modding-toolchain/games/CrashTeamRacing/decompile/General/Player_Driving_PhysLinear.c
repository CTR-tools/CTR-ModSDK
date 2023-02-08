#include <common.h>

void GAMEPAD_Vib_4(struct Driver* driver, u_int param_2, int param_3);
void Player_SetHeldItem(struct Driver* driver);
void OtherFX_Play(int sfxID, int flag);
int Player_StickReturnToRest(int param_1, u_int param_2, struct RacingWheelData* param_3);
int Player_GetBaseSpeed(struct Driver* driver);
void Turbo_Increment(struct Driver* driver, int reserves, u_int type, int fireLevel);
int MapToRange(int param_1,int param_2,int param_3,int param_4,int param_5);
int Player_StickGetStrengthAbsolute(int param_1, u_int param_2, struct RacingWheelData* param_3);
int InterpBySpeed(int param_1,int param_2,int param_3);

extern short PhysLinear_DriverOffsets[14];

void DECOMP_Player_Driving_PhysLinear(struct Thread* thread, struct Driver* driver)
{
	struct GameTracker* gGT;
	char kartState;
	char heldItemID;
	short noItemTimer;
	char isNumWumpas10;
	u_short driverTimerUnk;
	u_short driverBaseSpeedUshort;
	int driverTimer2;
	u_int jumpCooldown;
	int driverBaseSpeed;
	int approximateSpeed;
	char* AxisAnglePointer;
	short sVar13;
	int iVar14;
	u_int buttonsTapped;
	struct RacingWheelData* gamepadRacingWheel;
	u_short driverTimerShort;
	int driverTimer;
	u_int timerHazard;
	int approximateSpeed2;
	u_int uVar22;
	int driverSpeedSmth2;
	struct GamepadBuffer* ptrgamepad;
	u_int cross;
	u_int square;

	short* val;
	int i;
	int msPerFrame;
	int negativeMsPerFrame;
	int driverValueMinusMsPerFrame;
	u_int driverValueMinusMsPerFrameUnsigned;
	short driverRankItemValue;
	u_short timerHazardSomething;
	u_int itemSound;
	u_int uVar20;
	u_int vectorID;
	int vectorID2;
	int joystickStrength;
	int driverSpeedOrSmth = 0;
	struct Thread* driverItemThread;
	struct Shield* shield;
	struct TrackerWeapon* bomb;
	u_int superEngineFireLevel;
	
	gGT = sdata->gGT;

	// If race timer is not supposed to stop for this racer
	if ((driver->actionsFlagSet & 0x40000) == 0)
	{
		// set racer's timer to the time on the clock
		driver->timeElapsedInRace = gGT->elapsedEventTime;
	}

	// elapsed milliseconds per frame, ~32
	msPerFrame = gGT->elapsedTimeMS;

	// negative elapsed milliseconds per frame
	negativeMsPerFrame = -msPerFrame;

	if
	(
		// time on the clock
		(gGT->elapsedEventTime < 10 * MINUTE) &&

		// race timer is not frozen for this player
		((driver->actionsFlagSet & 0x40000) == 0)
	)
	{
		// increment timer by (speed * time)
		driver->distanceDriven += (driver->speedApprox * gGT->elapsedTimeMS >> 8);
	}

	for(i = 0; i < 14; i++)
	{
		short* val = (short*)((int)driver + (int)PhysLinear_DriverOffsets[i]);
		*val -= msPerFrame;
		if(*val < 0) *val = 0;
	}
	
	if(driver->reserves > 0) driver->timeSpentUsingReserves += msPerFrame;
	if(driver->set_0xF0_OnWallRub > 0) driver->timeSpentAgainstWall += msPerFrame;
	if(driver->burnTimer > 0) driver->timeSpentBurnt += msPerFrame;
	if(driver->squishTimer > 0) driver->timeSpentSquished += msPerFrame;	

	// If Super Engine Cheat is not enabled
	if (!(gGT->gameMode2 & 0x10000))
	{
		// [Same repetition]
		driverValueMinusMsPerFrame = (int)driver->superEngineTimer + negativeMsPerFrame;
		driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
		if (0 < (int)driver->superEngineTimer)
		{
			if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
			*(u_short*)&driver->superEngineTimer = driverValueMinusMsPerFrameUnsigned;
		}
	}

	// If invisible, and not using perm cheat
	if
	(
		// must check this first, otherwise
		// instFlagsBackup is invalid
		(driver->invisibleTimer != 0) &&

		// If Permanent Invisibility Cheat is Disabled
		(!(gGT->gameMode2 & 0x8000))
	)
	{		
		// [Same repetition]
		driverValueMinusMsPerFrame = (int)driver->invisibleTimer + negativeMsPerFrame;
		driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
		if (0 < (int)driver->invisibleTimer)
		{
			if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
			*(u_short*)&driver->invisibleTimer = driverValueMinusMsPerFrameUnsigned;
		}

		// If the timer expires, make yourself visible
		if (driver->invisibleTimer == 0)
		{
			// restore backup of instance flags
			driver->instSelf->flags = driver->instFlagsBackup;

			// set instance transparency to zero
			driver->instSelf->alphaScale = 0;

			OtherFX_Play(0x62, 1);
		}
	}

	// This one is a frame timer, not a millisecond timer,
	// Decrease one frame from Jump Buffering as long as timer is more than zero
	if (0 < driver->jump_TenBuffer) driver->jump_TenBuffer--;

	//keep track of time spent with full wumpa
	if (9 < driver->numWumpas) driver->timeSpentInTenWumpa += msPerFrame;

	//keep track of time spent in mud
	if (driver->currentTerrain == 0xE) driver->timeSpentInMud += msPerFrame;

	// Get placement of racer (1st place, 2nd, 3rd, etc)
	driverRankItemValue = driver->driverRank;

	// Basically, if racer is in last place in any possible race scenario
	if
	(
		(
			(
				(
					// If racer is in 8th place
					(driverRankItemValue == 7) &&

					// If numPlyrCurrGame is 1
					(gGT->numPlyrCurrGame == 1)
				) ||
				(
					(
						// If racer is in 6th place
						driverRankItemValue == 5 &&

						// if numPlyrCurrGame is 2
						(gGT->numPlyrCurrGame == 2)
					)
				)
			) ||
			(
				(
					// if racer is in 4th place
					driverRankItemValue == 3 &&

					// if numPlyrCurrGame is more than 2
					(2 < (u_char)gGT->numPlyrCurrGame)
				)
			)
		) &&
		(
			// race timer is not frozen for this player
			(driver->actionsFlagSet & 0x40000) == 0
		)
	)
	{
		// Increase the time racer has been in last place by elapsed milliseconds
		driver->timeSpentInLastPlace += msPerFrame;
	}

	driverRankItemValue = 4;

	// if you have a raincloud over your head from potion
	if (driver->thCloud != 0) 
		driverRankItemValue = 
			((struct RainCloud*)driver->thCloud->object)->itemScrollRandom;

	// get approximate speed
	approximateSpeed = (int)driver->speedApprox;

	// Action flags (isRaceOver, isTimeFrozen, etc)
	uVar22 = driver->actionsFlagSet;

	// driver->clockReceive
	driverTimer = (int)driver->clockReceive;

	driver->driverRankItemValue = driverRankItemValue;

	// absolute value of speed
	if (approximateSpeed < 0) approximateSpeed = -approximateSpeed;

	if
	(
		(
			// if you are not impacted by clock weapon
			(driverTimer == 0) &&
			(
				// get squished timer
				driverTimer = (int)driver->squishTimer,

				// if you are not squished
				driverTimer == 0
			)
		) &&
		(
			(
				driverRankItemValue != 0 ||
				(
					// if time on the clock is zero
					driverTimer = gGT->elapsedEventTime,
					driverTimer == 0
				)
			)
		)
	)
	{
		// timerHazard = Hazard Timer (sign extended 2 to 4 bytes)
		// keep a close eye on this one --Super
		timerHazard = (u_int)driver->hazardTimer;

		// hazard timer will not go
		// down unless you keep moving,
		// is this for red potion raincloud?

		// if you have high speed
		if (approximateSpeed > 0x100)
		{
			// decrease hazard by elapsed time
			timerHazard += negativeMsPerFrame;
		}

		timerHazardSomething = (u_short)(timerHazard & 0xfffffffe);
		if ((int)(timerHazard & 0xfffffffe) > -1)
		{
			timerHazardSomething = 0xfffe;
		}

		// Hazard Timer = timerHazardSomething
		driver->hazardTimer = timerHazardSomething;
	}

	// if you are not impacted by hazard (other than clock)
	else
	{
		driverTimerShort = (u_short)driverTimer;

		// if you are not touching the ground
		if ((uVar22 & 1) == 0)
		{
			// if speed is low
			if (approximateSpeed < 0x101) goto speedIsLow;

			// if speed is high...

			// absolute value of clock hazard
			if (driverTimer < 0)
			{
				driverTimerShort = -driverTimerShort;
			}

			turnDriverTimerNegative:
			driverTimerUnk = -driverTimerShort | 1;
		}

		// if you are touching the ground
		else
		{
			// if speed is low
			if (approximateSpeed < 0x101)
			{
				speedIsLow:
				driverTimerShort = *(u_short*)&driver->hazardTimer;
				driverTimerUnk = driverTimerShort | 1;
				if (0 < (short)driverTimerShort) goto turnDriverTimerNegative;
			}

			// if speed is high
			else
			{
				// absolute value of clock hazard
				if (driverTimer < 0)
				{
					driverTimerShort = -driverTimerShort;
				}

				// Use trigonometry with speed and
				// clock timer to make the car waddle

				// driverTimer2 = Clock Item (Receive) Timer << 0x10
				driverTimer2 = (u_int)driver->clockReceive << 0x10;

				driverTimer = driverTimer2 >> 0x16;
				if (driverTimer > 0x40) driverTimer = 0x40;

				timerHazard = (driverTimer2 >> 0x10) << 4;

				// approximate trigonometry
				driverTimer2 = data.trigApprox[(timerHazard & 0x3ff)];

				if ((timerHazard & 0x400) == 0) driverTimer2 = driverTimer2 << 0x10;
				driverTimer2 = driverTimer2 >> 0x10;

				if ((timerHazard & 0x800) != 0) driverTimer2 = -driverTimer2;
				approximateSpeed2 = approximateSpeed >> 8;

				if (approximateSpeed2 > 0x20) approximateSpeed2 = 0x20;

				// gamepad vibration
				GAMEPAD_Vib_4(driver, 4, driverTimer + (driverTimer2 >> 5) + approximateSpeed2 + 0x18);

				driverTimerUnk = driverTimerShort | 1;
			}
		}
		driver->hazardTimer = driverTimerUnk;
	}

	//trigger Item roll / selection
	//if Held Item = None
	if (driver->heldItemID == 0x10)
	{

		//if Item roll is done
		if (driver->itemRollTimer == 0)
		{
			// Select a random weapon for driver
			Player_SetHeldItem(driver);

			// if 9 < number of wumpa
			// if wumpa is 10
			isNumWumpas10 = driver->numWumpas > 9;

			// if you have less than 10 wumpa

			// "ding" sound
			itemSound = 0x5e;

			// if you have 10 wumpa
			if (isNumWumpas10)
			{
				// "ka-ching" sound
				itemSound = 0x41;
			}

			// OtherFX_Play of getting weapon
			OtherFX_Play(itemSound, (u_int)isNumWumpas10);
		}

		//if Item roll is not done
		else driver->itemRollTimer--;
	}

	noItemTimer = driver->noItemTimer;

	//if Item is going away
	if (noItemTimer != 0)
	{

		// if Item is about to be gone and Number of Items = 0
		if ((noItemTimer == 1) && (driver->numHeldItems == 0))
		{

			// if numPlyrCurrGame is > 2
			if
			(
				(2 < (u_char)gGT->numPlyrCurrGame) &&

				// If you're not in Battle Mode
				(
					(
						(
							(gGT->gameMode1 & 0x20) == 0 &&

							// your weapon is 3 missiles
							(driver->heldItemID == 0xB)
		 				) &&

						// If there are racers that had 3 missiles
						(gGT->numPlayersWith3Missiles > 0)
					)
				)
			)
			{
				// decrement the number of players that had 3 missiles
				gGT->numPlayersWith3Missiles--;
			}

			// take away weapon
			*(u_char*)&driver->heldItemID = 0xf;
		}

		driver->noItemTimer = noItemTimer - 1;
	}
	
	// action flags
	driver->actionsFlagSetPrevFrame = uVar22;
	
	// backup rotation
	*(u_int*)&driver->rotPrev.x = *(u_int*)&driver->rotCurr.x;
	driver->rotPrev.z = driver->rotCurr.z;
	
	// backup position
	driver->posPrev[0] = driver->posCurr[0];
	driver->posPrev[1] = driver->posCurr[1];
	driver->posPrev[2] = driver->posCurr[2];
	
	// unknown
	driver->unknownDimensionPrev = driver->unknownDimensionCurr;
	driver->unknownDimension2Prev = driver->unknownDimension2Curr;

	// ??? --Super
	uVar20 = uVar22 & 0x7f1f83d5;
	
	// disable input if opening adv hub door with key
	if ((gGT->gameMode2 & 0x4004) != 0)
	{
		driver->actionsFlagSet = uVar20;
		return;
	}
	
	// if not touching ground
	if ((uVar22 & 1) == 0) 
	{
		// AngleAxis2_NormalVec
		*(u_int*)&driver->AxisAngle4_normalVec[0] = *(u_int*)&driver->AxisAngle2_normalVec[0];
		driver->AxisAngle4_normalVec[2] = driver->AxisAngle2_normalVec[2];
	}
	
	// if touching ground
	else 
	{
		// AngleAxis1_NormalVec
		*(u_int*)&driver->AxisAngle4_normalVec[0] = *(u_int*)&driver->AxisAngle1_normalVec[0];
		driver->AxisAngle4_normalVec[2] = driver->AxisAngle1_normalVec[2];
	}
	
	driver->normalVecID = 0;

	driverItemThread = thread->childThread;

	uVar22 = uVar20;

	while (driverItemThread != 0)
	{
		// If thread->modelIndex is Aku or Uka
		if ((*(short*)&driverItemThread->modelIndex == 0x3a) || (*(short*)&driverItemThread->modelIndex == 0x39))
		{
			uVar22 = uVar20 | 0x800000;
			break;
		}

		// check next player in linked list
		driverItemThread = driverItemThread->siblingThread;
	}

	// pointer to gamepad input of current player (driver)
	ptrgamepad = &sdata->gGamepads->gamepad[(u_int)driver->driverID];

	// by default, hold no buttons
	uVar20 = 0;

	// If you're not in End-Of-Race menu
	if (!(gGT->gameMode1 & 0x200000))
	{
		// Get which button is held
		uVar20 = ptrgamepad->buttonsHeldCurrFrame;
	}

	// by default, tap no buttons
	buttonsTapped = 0;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & 0x200000) == 0)
	{
		// Get which button is tapped
		buttonsTapped = ptrgamepad->buttonsTapped;
	}

	// If you hold Cross
	cross = uVar20 & 0x10;

	// If you hold Square
	square = uVar20 & 0x20;

	// state of kart
	kartState = driver->kartState;

	if
	(
		(
			// If you press circle
			((buttonsTapped & 0x40) != 0) &&

			(
				// if neutral driving
				((kartState == 0 ||

				// or sliding
				(kartState == 2)) ||

				// or ???
				(kartState == 9))
			)
		) &&

		// if there is no tnt on your head
		(driver->instTntRecv == 0)
	)
	{
		// If there is no Bomb pointer
		if (driver->instBombThrow == 0)
		{

			// If there is no Bubble pointer
			if (driver->instBubbleHold == 0)
			{

				// If there is no "weapon roulette" animation
				noItemTimer = driver->itemRollTimer;
				if (noItemTimer == 0)
				{

					// If you dont have "roulette" weapon (0x10), and if you dont have "no weapon" (0xf)
					// and if you did not have a weapon last frame (0x3c->0),
					// and if (unknown driverRankItemValue related to 0x4a0),
					// and if you are not being effected by Clock Weapon
					heldItemID = driver->heldItemID;
					if
					(
						(
							(heldItemID != 0xF) && 
							(heldItemID != 0x10) &&
							(driver->noItemTimer == 0) &&
							(driverRankItemValue != 1) &&
							(driver->clockReceive == 0)
							
						)
					)
					{
						// This driver wants to fire a weapon
						uVar22 = uVar22 | 0x8000;

						// If "held item quantity" is zero
						if (driver->numHeldItems == 0)
						{
							driver->noItemTimer = 0x1e;
							goto CheckButtons;
						}

						// If you have the Spring weapon
						// probably removed in later builds --Super
						if (heldItemID == 5)
						{
							if (driver->jump_CoyoteTimerMS != 0)
							{
								// sext.... --Super
								jumpCooldown = (u_int)driver->jump_CooldownMS;
								goto ReduceCount;
							}
						}
						else
						{
							// only reduce numHeldItem if not using cheats
							jumpCooldown = gGT->gameMode2 & 0x400c00;
							
							ReduceCount:
							if (jumpCooldown == 0) driver->numHeldItems--;
						}
						driver->noItemTimer = 5;
						goto CheckButtons;
					}
					noItemTimer = driver->itemRollTimer;
				}

				// if there are less than 70 frames (2.3 sec remaining)
				if (noItemTimer < 0x46)
				{
					// skip to the end of the countdown
					driver->itemRollTimer = 0;
				}
			}

			// If there is a Bubble Pointer
			else
			{
				// Shoot the bubble

				// We can see the bubble pointer (driver + 0x14)

				// instance -> thread -> object
				shield = (struct Shield*)driver->instBubbleHold->thread->object;

				shield->shieldshot |= 2;

				// Reset to nullptr
				driver->instBubbleHold = 0;
			}
		}

		// If there is a Bomb Pointer
		else
		{
			// Detonate the bomb

			// We can see the bomb pointer (driver + 0x10)

			// instance -> thread -> object
			bomb = (struct TrackerWeapon*)driver->instBombThrow->thread->object;

			// always face camera
			bomb->flags |= 2;

			// Reset to nullptr
			driver->instBombThrow = 0;
		}
	}
	CheckButtons:

	// Check for Tapping L1 and R1
	buttonsTapped = buttonsTapped & 0xc00;

	if
	(
		//if you're not pressing L1 or R1
		(buttonsTapped == 0) ||
		// or you are sliding
		(driver->kartState == 2)
	)
	{
		if
		(
			// If you are holding L1 or R1 and
			((uVar20 & 0xc00) != 0) &&
			(driverRankItemValue != 3)
		)
		{
			if ((uVar22 & 4) == 0)
			{
				// 10 frame jump buffer
				driver->jump_TenBuffer = 10;
			}
			goto LAB_8006222c;
		}
		uVar22 = uVar22 & 0xfffffffb;
		if (driver->jump_TenBuffer > 0) driver->jump_TenBuffer = 0;
	}

	//if you're pressing jump buttons and not sliding
	else
	{
		//if L1 and R1 were being tapped at once
		if (buttonsTapped == 0xc00)
		{
			//set Last Jump button pressed to R1
			driver->buttonUsedToStartDrift = 0x400;
		}

		//if you're not tapping L1 and R1 at once
		else
		{
			//Last Jump button pressed = buttonsTapped
			driver->buttonUsedToStartDrift = (short)buttonsTapped;
		}

		if (driverRankItemValue != 3)
		{
			driver->jump_TenBuffer = 10;
			LAB_8006222c:
			uVar22 = uVar22 | 4;
		}
	}

	if
	(
		// If you are holding Square
		(square != 0) &&

		// if you're not on any turbo pad
		((driver->stepFlagSet & 3) == 0)
	)
	{
		// Set Reserves to zero
		driver->reserves = 0;
	}

	// assume normal gas pedal
	joystickStrength = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & 0x200000) == 0)
	{
		// gamepadBuffer -> stickRY (for gas or reverse)
		joystickStrength = (int)ptrgamepad->stickRY;
	}

	if
	(
		// If Reserves are not zero
		(driver->reserves != 0) ||

		(driverRankItemValue == 6)
	)
	{
		// If you are not holding Cross
		if(cross == 0)
		{
			driverTimer = Player_StickReturnToRest(joystickStrength, 0x80, 0); 
			
			if(driverTimer > -1)
			{
				uVar22 |= 0x400000;
			}
		}


		if
		(
			// If are holding Square
			(square != 0) &&

			(approximateSpeed > 0x300)
		)
		{
			uVar22 |= 0x800;
		}

		// if you're on any turbo pad
		if ((driver->stepFlagSet & 3) != 0)
		{
			// assume not holding square until boost is over
			square = 0;
		}

		// Assume you're holding Cross, because
		// you have Reserves and you aren't slowing down
		cross = 0x10;
	}

	driverTimer = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & 0x200000) == 0) 
	{
		driverTimer = (int)ptrgamepad->stickLY;
	}
	
	if
	(
		(driver->simpTurnState < 0) ||
		(uVar22 &= 0xdfffffff, driver->simpTurnState < 1)
	)
	{
		uVar22 = uVar22 & 0xbfffffff;
	}
	approximateSpeed2 = (int)driver->speedApprox;
	if (approximateSpeed2 < 0)
	{
		approximateSpeed2 = -approximateSpeed2;
	}
	if (approximateSpeed2 < 0x300)
	{
		uVar22 = uVar22 & 0x9fffffff;
	}
	approximateSpeed2 = 0;
	// Racer's Base Speed (4s)
	driverBaseSpeed = Player_GetBaseSpeed(driver);
	// Racer's Base Speed (2u)
	driverBaseSpeedUshort = (u_short)driverBaseSpeed;

	// If you are not holding Square
	if (square == 0)
	{
		//driverSpeedSmth2 = Racer's Base Speed
		driverSpeedSmth2 = driverBaseSpeed;

		// If you are holding Cross, or if you have Reserves
		if (cross != 0)
		{
			LAB_8006253c:
			uVar22 = uVar22 & 0xfffdffff;
			goto LAB_80062548;
		}

		// if you are not holding cross, or have no Reserves...
		//driverSpeedSmth2 is replaced

		// Player_StickReturnToRest
		driverSpeedSmth2 = Player_StickReturnToRest(joystickStrength, 0x80, 0);

		driverSpeedOrSmth = -driverSpeedSmth2;
		if (driverSpeedSmth2 < 1)
		{
			if
			(	
				(driverSpeedOrSmth == 0) &&
				(
					(
						driverTimer = Player_StickReturnToRest(driverTimer, 0x80, 0), driverTimer > 99 ||

						(
							(driverTimer > 0 && ((uVar22 & 0x20000) != 0))
						)
					)
				)
			)
			{
				// driver is steering?
				uVar22 |= 0x20000;
		
				driverSpeedSmth2 = -(int)driver->const_BackwardSpeed;
				goto LAB_80062548;
			}
			driverSpeedOrSmth = driverBaseSpeed * driverSpeedOrSmth;
			driverSpeedSmth2 = driverSpeedOrSmth >> 7;
			if (driverSpeedOrSmth < 0) driverSpeedSmth2 = driverSpeedOrSmth + 0x7f >> 7;
			goto LAB_8006253c;
		}
		if ((driver->speedApprox < 0x301) && ((uVar22 & 0x60000000) == 0))
		{
			driverSpeedOrSmth = driver->const_BackwardSpeed * driverSpeedOrSmth;
			if (driverSpeedOrSmth < 0) driverSpeedOrSmth = driverSpeedOrSmth + 0x7f;
			approximateSpeed2 = driverSpeedOrSmth >> 7;
			buttonsTapped = 0x20000;
			LAB_800625c4:
			uVar20 = uVar22 | buttonsTapped;
		}
		else
		{
			uVar20 = uVar22 | 8;
			if (0 < driver->simpTurnState) uVar20 = uVar22 | 0x40000008;
			if (driver->simpTurnState < 0)
			{
				buttonsTapped = 0x20000000;
				uVar22 = uVar20;
				goto LAB_800625c4;
			}
		}
	}
	// If you are holding Square
	else
	{
		driverTimer = Player_StickReturnToRest(driverTimer, 0x80, 0);

		if ((driverTimer < 100) && ((driverTimer < 1 || ((uVar22 & 0x20000) == 0))))
		{
			// if you are not holding cross, and you have no Reserves
			if (cross == 0)
			{
				// Player_StickReturnToRest
				driverSpeedOrSmth = Player_StickReturnToRest(joystickStrength, 0x80, 0);

				driverSpeedSmth2 = driverBaseSpeed * -driverSpeedOrSmth;
				if (driverSpeedOrSmth < 0)
				{
					if (driverSpeedSmth2 < 0) driverSpeedSmth2 = driverSpeedSmth2 + 0xff;
					driverSpeedSmth2 = driverSpeedSmth2 >> 8;
					uVar22 = uVar22 | 0x20;
					goto LAB_80062548;
				}
				if (0 < driverSpeedOrSmth)
				{
					driverSpeedOrSmth = (int)driver->const_BackwardSpeed * -driverSpeedOrSmth;
					driverSpeedSmth2 = driverSpeedOrSmth >> 8;
					if (driverSpeedOrSmth < 0) driverSpeedSmth2 = driverSpeedOrSmth + 0xff >> 8;
					goto LAB_8006248c;
				}
				uVar22 = uVar22 | 8;
				driverSpeedSmth2 = approximateSpeed2;
			}
			// If you are holding cross, or you have Reserves
			else
			{
				uVar22 = uVar22 | 0x20;
				driverSpeedSmth2 = driverBaseSpeed / 2;
			}
			goto LAB_8006253c;
		}
		driverSpeedOrSmth = (int)driver->const_BackwardSpeed * -3;
		driverSpeedSmth2 = driverSpeedOrSmth >> 2;
		if (driverSpeedOrSmth < 0) 	driverSpeedSmth2 = driverSpeedOrSmth + 3 >> 2;
		LAB_8006248c:
		uVar22 = uVar22 | 0x20020;
		LAB_80062548:
		uVar20 = uVar22 & 0x9fffffff;
		approximateSpeed2 = driverSpeedSmth2;
	}

	// not driving backwards
	if ((uVar20 & 0x20000) == 0)
	{
		if (driver->superEngineTimer != 0)
		{
			// if Racer is moving
			if (0 < approximateSpeed2)
			{
				// not holding breaks
				if ((uVar20 & 0x400020) == 0) 
				{
					// if you have less than 10 wumpa
					superEngineFireLevel = 0x80;

					driver->actionsFlagSet = uVar20;

					// if number of wumpa > 9
					// if wumpa is 10
					if (driver->numWumpas > 9) superEngineFireLevel = 0x100;

					// Turbo_Increment
					// add 0.12s reserves
					Turbo_Increment(driver, 0x78, 0x14, superEngineFireLevel);

					uVar20 = driver->actionsFlagSet;
				}
			}
		}
	}
	
	// driving backwards
	else
	{
		driver->timeSpentReversing += gGT->elapsedTimeMS;
	}

	uVar22 = uVar20 & 8;

	if (uVar22 != 0)
	{		
		// high speed
		if (
				(driver->speedApprox > 0x300) || 
				(driver->speedApprox < -0x300)
			) 
		{
			// record amount of time with high speed
			driver->timeSpentWithHighSpeed += msPerFrame;
		}
	}

	if
	(
		(driver->mashingXMakesItBig == 0) ||

		// kart state not 0, and kart state not 9
		((driver->kartState != 0 && (driver->kartState != 9)))
	)
	{
		driver->mashXUnknown = 0;
	}

	if (driver->fireSpeed < 1)
	{
		//if Racer is moving, skip next 4 lines of code
		if (approximateSpeed2 > 0) goto LAB_800626d4;
		LAB_800626fc:
		//Racer struct + 0x39E = Racer's Base Speed
		*(u_short*)&driver->fireSpeed = (short)approximateSpeed2;
	}
	else
	{
		//if Racer is not moving
		if (approximateSpeed2 < 1)
		{
			LAB_800626d4:
			if (driver->mashingXMakesItBig != 0) driver->mashXUnknown++;
			driver->mashingXMakesItBig = 0x100;
			goto LAB_800626fc;
		}
		//Racer struct + 0x39E = Racer's Base Speed
		*(u_short*)&driver->fireSpeed = (short)approximateSpeed2;
	}
	if ((uVar20 & 0x800020) == 0)
	{
		driverSpeedOrSmth = driver->terrainMeta2->unk_0x8;
		//if racer is out of normal driving conditions?
		//for example, 0x35C[0x8] is 0xB4 when in water at Cove
		//and the value of 0x39C fits the result perfectly
		if (driverSpeedOrSmth != 0x100)
		{
			//Base Speed = 0xB4 (at Cove water) * Base Speed >> 8
			approximateSpeed2 = driverSpeedOrSmth * approximateSpeed2 >> 8;
			driverBaseSpeedUshort = (u_short)((u_int)(driverSpeedOrSmth * driverBaseSpeed) >> 8);
		}
	}
	*(u_short*)&driver->unknowndriverBaseSpeed = driverBaseSpeedUshort;
	*(u_short*)&driver->baseSpeed = (short)approximateSpeed2;

	// assume neutral steer (drive straight)
	driverSpeedOrSmth = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & 0x200000) == 0)
	{
		// gamepadBuffer -> stickLX
		driverSpeedOrSmth = (int)ptrgamepad->stickLX;
	}

	// default steer strength from class stats
	iVar14 = (u_int)driver->const_TurnRate + ((int)driver->turnConst << 1) / 5;
	
	// if mashing X button
	if ((driver->mashXUnknown > 6) && (approximateSpeed < 0x2600))
	{
		// sharp turn
		iVar14 = 0x5a;
		goto UseTurnRate;
	}
	
	// rubbing on wall now, or recently
	if (driver->set_0xF0_OnWallRub != 0)
	{
		// restrict turn
		iVar14 = 0x30;
		goto UseTurnRate;
	}
	
	// === not rubbing on wall now, or recently ===

	// if not holding Square (& 0x8)
	// or holding Square + Cross (& 0x20)
	if ((uVar20 & 0x28) == 0)
	{
		// use const_TurnRate + turnConst<<1/5
		goto UseTurnRate;
	}
	
	// if only holding Square
	if (cross == 0)
	{
		// turn rate
		iVar14 = 0x40;
		goto UseTurnRate;
	}

	// === if holding Square + Cross ===
	
	// absolute value driver speed
	driverTimer = (int)driver->speed;
	if (driverTimer < 0) driverTimer = -driverTimer;

	// As speed increases, turn rate decreases
	iVar14 = MapToRange(
				driverTimer,0x300,
				(int)((u_int)driver->const_Speed_ClassStat << 0x10) >> 0x11,0x40,
				iVar14);
	
UseTurnRate:

	// Steer, based on strength, and LeftStickX
	iVar14 = Player_StickGetStrengthAbsolute(driverSpeedOrSmth, iVar14, ptrgamepad->rwd);

	if (-iVar14 == 0) *(u_short*)&driver->numFramesSpentSteering = 10000;
	else
	{
		if ((iVar14 < 1) || (driver->simpTurnState < 0))
		{
			if ((-1 < iVar14) || (0 < driver->simpTurnState)) goto LAB_800628b0;
			uVar20 = uVar20 | 0x10;
		}
		else uVar20 = uVar20 & 0xffffffef;
		driver->numFramesSpentSteering = 0;
	}
	LAB_800628b0:
	*(u_char*)&driver->simpTurnState = (char)-iVar14;

	// Steer
	driverSpeedOrSmth = Player_StickGetStrengthAbsolute(driverSpeedOrSmth, 0x40, ptrgamepad->rwd);

	// Interpolate rotation by speed
	driverBaseSpeedUshort = InterpBySpeed((int)driver->wheelRotation, 0x18, -driverSpeedOrSmth);

	driverSpeedOrSmth = (int)driver->fireSpeed;
	*(u_short*)&driver->wheelRotation = driverBaseSpeedUshort;
	if (driverSpeedOrSmth < 0) driverSpeedOrSmth = -driverSpeedOrSmth;

	if (((driver->actionsFlagSetPrevFrame & 1) == 0) || (kartState == 2))
	{
		driverSpeedOrSmth = driverSpeedOrSmth + 0xf00;
	}
	else
	{
		driverSpeedOrSmth = driverSpeedOrSmth + approximateSpeed >> 1;
	}

	sVar13 = (short)((driverSpeedOrSmth * 0x89 + (int)driver->unkSpeedValue2 * 0x177) * 8 >> 0xc);
	driver->unkSpeedValue2 = sVar13;

	if ((driver->actionsFlagSetPrevFrame & 8) == 0)
	{
		//prevent Basic Speed from being negative
		if (approximateSpeed2 < 0) approximateSpeed2 = -approximateSpeed2;

		//if Base Speed > 0x200 or approximateSpeed = 0x200 (?)
		if ((approximateSpeed2 > 0x200) || (approximateSpeed > 0x200))
		{
			driver->unkSpeedValue1 -= sVar13;
		}
	}
	
	//if 0x3BC <= 0 and last bit of jittery number 2 is off and
	if
	(
		(
			(driver->unkSpeedValue1 < 1) && ((driver->tireColor & 1) == 0)
		) &&
		(kartState != 4)
	)
	{
		//reset 0x3BC
		driver->unkSpeedValue1 = 0x1e00;
		
		driver->tireColor = 0x2e606061;
	}
	else
	{
		driver->tireColor = 0x2e808080;
	}
	
	driver->actionsFlagSet = uVar20;
	return;
}

#define OFFSETOF(TYPE, ELEMENT) (short)((unsigned int)&(((TYPE *)0)->ELEMENT))
short PhysLinear_DriverOffsets[14] =
{
	OFFSETOF(struct Driver, reserves),
	OFFSETOF(struct Driver, set_0xF0_OnWallRub),
	OFFSETOF(struct Driver, burnTimer),
	OFFSETOF(struct Driver, squishTimer),
	OFFSETOF(struct Driver, outsideTurboTimer),
	OFFSETOF(struct Driver, turboAudioCooldown),
	OFFSETOF(struct Driver, jump_ForcedMS),
	OFFSETOF(struct Driver, jump_CooldownMS),
	OFFSETOF(struct Driver, jump_unknown),
	OFFSETOF(struct Driver, StartDriving_0x60),
	OFFSETOF(struct Driver, StartRollback_0x280),
	OFFSETOF(struct Driver, clockReceive),
	OFFSETOF(struct Driver, mashingXMakesItBig),
	OFFSETOF(struct Driver, invincibleTimer)
};