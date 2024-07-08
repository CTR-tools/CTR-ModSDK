#include <common.h>

// budget: 4624
// curr: 4380

// see the bottom of this file
extern short PhysLinear_DriverOffsets[14];

void DECOMP_VehPhysProc_Driving_PhysLinear(struct Thread* thread, struct Driver* driver)
{
	struct GameTracker* gGT;
	int gameMode2;

	char kartState;
	char heldItemID;
	short noItemTimer;
	char isNumWumpas10;
	u_short driverTimerNegativeFinal;
	u_short driverBaseSpeedUshort;
	int approxTrig;
	int driverBaseSpeed;
	short approximateSpeed;
	short sVar13;
	int iVar14;
	u_int buttonsTapped;
	u_short driverTimerNegativePrelim;
	short driverTimer;
	short timerHazard;
	short approximateSpeed2;
	u_int actionsFlagSetCopy;
	short driverSpeedSmth2;
	struct GamepadBuffer* ptrgamepad;
	u_int cross;
	u_int square;

	short* normSrc;
	short* normDst;
	short* val;
	int i;
	int msPerFrame;
	short driverRankItemValue;
	u_int itemSound;
	u_int uVar20;
	int stickLY;
	int stickRY;
	int driverSpeedOrSmth = 0;
	struct Thread* driverItemThread;
	struct Shield* shield;
	struct TrackerWeapon* bomb;
	u_int superEngineFireLevel;
	int unk0x80;
	short driverSpeedCopy;

	gGT = sdata->gGT;
	gameMode2 = gGT->gameMode2;

	// If race timer is not supposed to stop for this racer
	if ((driver->actionsFlagSet & 0x40000) == 0)
	{
		// set racer's timer to the time on the clock
		driver->timeElapsedInRace = gGT->elapsedEventTime;
	}


	// === Count Timers ===


	// elapsed milliseconds per frame, ~32
	msPerFrame = gGT->elapsedTimeMS;

	if
	(
		// time on the clock
		(gGT->elapsedEventTime < 10 * MINUTE) &&

		// race timer is not frozen for this player
		((driver->actionsFlagSet & 0x40000) == 0)
	)
	{
		// increment timer by (speed * time)
		driver->distanceDriven += (driver->speedApprox * msPerFrame) >> 8;
	}

	for(i = 0; i < 14; i++)
	{
		short* val = (short*)((int)driver + (int)PhysLinear_DriverOffsets[i]);
		#ifdef USE_ONLINE
		if (i == 0)
		{
			if (driver->reserves == 0) { driver->uncappedReserves = 0; }

			if (driver->uncappedReserves > 0) { driver->uncappedReserves = max(driver->uncappedReserves - msPerFrame, 0); }
			else if (driver->reserves > 0) { driver->reserves = max(driver->reserves - msPerFrame, 0); }
		}
		else if (*val > 0)
		{
			*val -= msPerFrame;
			if(*val < 0) *val = 0;
		}
		#else
		if(*val > 0)
		{
			*val -= msPerFrame;
			if(*val < 0) *val = 0;
		}
		#endif
	}

	if(driver->reserves > 0) driver->timeSpentUsingReserves += msPerFrame;
	if(driver->set_0xF0_OnWallRub > 0) driver->timeSpentAgainstWall += msPerFrame;
	if(driver->burnTimer > 0) driver->timeSpentBurnt += msPerFrame;
	if(driver->squishTimer > 0) driver->timeSpentSquished += msPerFrame;

	// If Super Engine Cheat is not enabled
	if (!(gameMode2 & CHEAT_ENGINE))
	{
		driver->superEngineTimer -= msPerFrame;
		if(driver->superEngineTimer < 0) driver->superEngineTimer = 0;
	}

	// If invisible, without Permanent Invisibility cheat,
	// dont remove invisibleTimer check, or an invalid
	// instFlagsBackup overwrites instFlags
	if
	(
		(driver->invisibleTimer != 0) &&
		((gameMode2 & CHEAT_INVISIBLE) == 0)
	)
	{
		driver->invisibleTimer -= msPerFrame;

		// if newly visible
		if(driver->invisibleTimer <= 0)
		{
			driver->invisibleTimer = 0;
			driver->instSelf->flags = driver->instFlagsBackup;
			driver->instSelf->alphaScale = 0;
			DECOMP_OtherFX_Play(0x62, 1);
		}
	}

	if (0 < driver->jump_TenBuffer) driver->jump_TenBuffer--;
	if (9 < driver->numWumpas) driver->timeSpentInTenWumpa += msPerFrame;
	if (driver->currentTerrain == 0xE) driver->timeSpentInMud += msPerFrame;


	// === Check Last Place ===


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


	// === Determine Hazard ===


	driverRankItemValue = 4;

	// if you have a raincloud over your head from potion
	if (driver->thCloud != 0)
		driverRankItemValue =
			((struct RainCloud*)driver->thCloud->object)->boolScrollItem;

	// get approximate speed
	approximateSpeed = driver->speedApprox;

	// Action flags (isRaceOver, isTimeFrozen, etc)
	actionsFlagSetCopy = driver->actionsFlagSet;

	// driver->clockReceive
	driverTimer = driver->clockReceive;

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
				driverTimer = driver->squishTimer,

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
		timerHazard = driver->hazardTimer;

		// hazard timer will not go down unless you keep moving
		// is this for the raincloud from red beakers?

		// if you have high speed
		if (approximateSpeed > 0x100)
		{
			// decrease hazard by elapsed time
			timerHazard -= msPerFrame;
		}

		timerHazard = timerHazard & 0xfffe;
		if (timerHazard > -1) timerHazard = -2;

		driver->hazardTimer = timerHazard;
	}

	// if you are not impacted by hazard (other than clock)
	else
	{
		driverTimerNegativePrelim = driverTimer;

		// if you are not touching the ground
		if ((actionsFlagSetCopy & 1) == 0)
		{
			// if speed is low
			if (approximateSpeed < 0x101) goto speedIsLow;

			// if speed is high...

			// absolute value of clock hazard
			if (driverTimer < 0)
			{
				driverTimerNegativePrelim = -driverTimerNegativePrelim;
			}

			turndriverTimerNegative:
			driverTimerNegativeFinal = -driverTimerNegativePrelim | 1;
		}

		// if you are touching the ground
		else
		{
			// if speed is low
			if (approximateSpeed < 0x101)
			{
				speedIsLow:
				driverTimerNegativePrelim = *(u_short*)&driver->hazardTimer;
				driverTimerNegativeFinal = driverTimerNegativePrelim | 1;
				if ((short)driverTimerNegativePrelim > 0) goto turndriverTimerNegative;
			}

			// if speed is high
			else
			{
				// absolute value of clock hazard
				if (driverTimer < 0)
				{
					driverTimerNegativePrelim = -driverTimerNegativePrelim;
				}

				// Use trigonometry with speed and
				// clock timer to make the car waddle

				driverTimer = driver->clockReceive >> 6;
				if (driverTimer > 0x40) driverTimer = 0x40;

				timerHazard = driver->clockReceive << 4;

				// approximate trigonometry
				approxTrig = *(int*)&data.trigApprox[(timerHazard & 0x3ff)];

				if ((timerHazard & 0x400) == 0) approxTrig = approxTrig << 0x10;
				approxTrig = approxTrig >> 0x10;

				if ((timerHazard & 0x800) != 0) approxTrig = -approxTrig;
				approximateSpeed2 = approximateSpeed >> 8;

				if (approximateSpeed2 > 0x20) approximateSpeed2 = 0x20;

#ifndef REBUILD_PS1
				// gamepad vibration
				GAMEPAD_ShockForce1(driver, 4, driverTimer + (approxTrig >> 5) + approximateSpeed2 + 0x18);
#endif

				driverTimerNegativeFinal = driverTimerNegativePrelim | 1;
			}
		}
		driver->hazardTimer = driverTimerNegativeFinal;
	}


	// === Item Roll ===


	// if Held Item = None (rolling)
	if (driver->heldItemID == 0x10)
	{

		//if Item roll is done
		if (driver->itemRollTimer == 0)
		{
			// Select a random weapon for driver
			DECOMP_VehPhysGeneral_SetHeldItem(driver);

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

			// sound of getting weapon
			DECOMP_OtherFX_Play(itemSound, isNumWumpas10);
		}

		//if Item roll is not done
		else driver->itemRollTimer--;
	}


	// === Item Used By Player ===


	// Make Item fade away from icon
	if (driver->noItemTimer > 0) driver->noItemTimer--;

	// if Item is about to be gone and Number of Items = 0
	if ((driver->noItemTimer == 1) && (driver->numHeldItems == 0))
	{
		if
		(
			// multiplayer game, not battle, weapon was 3 missiles
			(2 < (u_char)gGT->numPlyrCurrGame) &&
			((gGT->gameMode1 & BATTLE_MODE) == 0) &&
			(driver->heldItemID == 0xB) &&
			(gGT->numPlayersWith3Missiles > 0)
		)
		{
			// keep count
			gGT->numPlayersWith3Missiles--;
		}

		// take away weapon
		*(u_char*)&driver->heldItemID = 0xf;
	}


	// === Normal Vector ===


	// action flags
	driver->actionsFlagSetPrevFrame = actionsFlagSetCopy;

	// backup rotation
	*(u_int*)&driver->rotPrev.x = *(u_int*)&driver->rotCurr.x;
	driver->rotPrev.z = driver->rotCurr.z;

	// backup position
	driver->posPrev.x = driver->posCurr.x;
	driver->posPrev.y = driver->posCurr.y;
	driver->posPrev.z = driver->posCurr.z;

	// unknown
	driver->jumpHeightPrev = driver->jumpHeightCurr;
	driver->turnAnglePrev = driver->turnAngleCurr;

	// ??? --Super
	uVar20 = actionsFlagSetCopy & 0x7f1f83d5;

	// disable input if opening adv hub door with key
	if ((gameMode2 & 0x4004) != 0)
	{
		driver->actionsFlagSet = uVar20;
		return;
	}

	// destination
	normDst = &driver->AxisAngle4_normalVec[0];
	if(driver->normalVecID == -1) normDst = &driver->AxisAngle3_normalVec[0];
	driver->normalVecID = 0;

	// source
	normSrc = &driver->AxisAngle2_normalVec[0];
	if ((actionsFlagSetCopy & 1) != 0) normSrc = &driver->AxisAngle1_normalVec.x;

	// copy
	*(u_int*)&normDst[0] = *(u_int*)&normSrc[0];
	normDst[2] = normSrc[2];



	// === Check Mask Weapon ===


	actionsFlagSetCopy = uVar20;
	driverItemThread = thread->childThread;
	while (driverItemThread != 0)
	{
		// If thread->modelIndex is Aku or Uka
		if
		(
			(*(short*)&driverItemThread->modelIndex == 0x3a) ||
			(*(short*)&driverItemThread->modelIndex == 0x39)
		)
		{
			// driver is using mask weapon
			actionsFlagSetCopy = uVar20 | 0x800000;
			break;
		}

		// check next player in linked list
		driverItemThread = driverItemThread->siblingThread;
	}


	// === Check Buttons ===


	// pointer to gamepad input of current player (driver)
	ptrgamepad = &sdata->gGamepads->gamepad[(u_int)driver->driverID];

	// no hold, no tap
	uVar20 = 0;
	buttonsTapped = 0;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & END_OF_RACE) == 0)
	{
		uVar20 = ptrgamepad->buttonsHeldCurrFrame;
		buttonsTapped = ptrgamepad->buttonsTapped;
	}

	cross = uVar20 & BTN_CROSS;
	square = uVar20 & BTN_SQUARE;

	// state of kart
	kartState = driver->kartState;


	// === Check Weapons ===


	if
	(
		(
			((buttonsTapped & BTN_CIRCLE) != 0) &&

			(
				(kartState == KS_NORMAL) ||
				(kartState == KS_DRIFTING) ||
				(kartState == KS_ANTIVSHIFT)
			)
		) &&

		// if there is no tnt on your head
		(driver->instTntRecv == 0)
	)
	{
		// If there is a Bomb Pointer
		if (driver->instBombThrow != 0)
		{
			// Detonate the bomb
			bomb = (struct TrackerWeapon*)driver->instBombThrow->thread->object;
			bomb->flags |= 2;
			driver->instBombThrow = 0;
			goto CheckJumpButtons;
		}

		// If there is a Bubble Pointer
		if (driver->instBubbleHold != 0)
		{
			// Shoot the bubble
			shield = (struct Shield*)driver->instBubbleHold->thread->object;
			shield->flags |= 2;
			driver->instBubbleHold = 0;
			goto CheckJumpButtons;
		}

		// item is rolling
		if (driver->itemRollTimer != 0)
		{
			// circle button ends timer, if
			// less than 70 frames (2.3s) remain
			if (driver->itemRollTimer < FPS_DOUBLE(70))
				driver->itemRollTimer = 0;

			// skip weapon firing check
			goto CheckJumpButtons;
		}

		// === Item Roll finished before PhysLinear ===

		// If you dont have "roulette" weapon (0x10), and if you dont have "no weapon" (0xf)
		// and if you did not have a weapon last frame (0x3c->0),
		// and if (unknown driverRankItemValue related to 0x4a0),
		// and if you are not being effected by Clock Weapon
		heldItemID = driver->heldItemID;
		if
		(
			(heldItemID != 0xF) &&
			(heldItemID != 0x10) &&
			(driver->noItemTimer == 0) &&
			(driverRankItemValue != 1) &&
			(driver->clockReceive == 0)
		)
		{
			// This driver wants to fire a weapon
			actionsFlagSetCopy |= 0x8000;

			// if numHeldItems == 0
			// wait a full second before next weapon
			driver->noItemTimer = FPS_DOUBLE(0x1e);

			// If "held item quantity" is zero
			if (driver->numHeldItems != 0)
			{
				// if numHeldItems > 0,
				// wait 5 frames before next weapon use
				driver->noItemTimer = FPS_DOUBLE(5);

				// not spring weapon
				if (heldItemID != 5)
				{
					// only reduce numHeldItem if not using item cheats
					if ((gameMode2 & (CHEAT_BOMBS | CHEAT_TURBO | CHEAT_MASK)) == 0) driver->numHeldItems--;
				}

				// no spring in final game
				#if 0

				// If you have the Spring weapon
				else
				{
					if (
						(driver->jump_CoyoteTimerMS != 0) &&
						(driver->jump_CooldownMS == 0)
					   )
					{
						driver->numHeldItems--;
					}
				}

				#endif
			}
		}
	}


	// === Drift Section ===


CheckJumpButtons:

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
			if ((actionsFlagSetCopy & 4) == 0)
			{
				// 10 frame jump buffer
				driver->jump_TenBuffer = FPS_DOUBLE(10);
			}
			goto LAB_8006222c;
		}
		actionsFlagSetCopy &= 0xfffffffb;
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
			driver->buttonUsedToStartDrift = buttonsTapped;
		}

		if (driverRankItemValue != 3)
		{
			driver->jump_TenBuffer = FPS_DOUBLE(10);
			LAB_8006222c:
			actionsFlagSetCopy |= 4;
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
	stickRY = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & END_OF_RACE) == 0)
	{
		// gamepadBuffer -> stickRY (for gas or reverse)
		stickRY = (int)ptrgamepad->stickRY;
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
			unk0x80 = DECOMP_VehPhysJoystick_ReturnToRest(stickRY, 0x80, 0);

			if(unk0x80 > -1)
			{
				actionsFlagSetCopy |= 0x400000;
			}
		}

		// If holding Square while moving fast
		if((square != 0) && (approximateSpeed > 0x300))
		{
			// back wheel skids
			actionsFlagSetCopy |= 0x800;
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


	// === Gas/Brake section ===


	stickLY = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & END_OF_RACE) == 0)
	{
		stickLY = ptrgamepad->stickLY;
	}

	if
	(
		(driver->simpTurnState < 0) ||
		(actionsFlagSetCopy &= 0xdfffffff, driver->simpTurnState < 1)
	)
	{
		actionsFlagSetCopy &= 0xbfffffff;
	}
	approximateSpeed2 = driver->speedApprox;
	if (approximateSpeed2 < 0)
	{
		approximateSpeed2 = -approximateSpeed2;
	}
	if (approximateSpeed2 < 0x300)
	{
		actionsFlagSetCopy &= 0x9fffffff;
	}
	approximateSpeed2 = 0;

	// with zero wumpa, should be const_Speed_ClassStat (13140 for Crash Bandicoot)
	// this works for both decomp and original

	// with one wumpa, (25600 in rewrite, 13169 in original)

	#ifdef REBUILD_PC
	// buggy, experimental
	//driverBaseSpeed = DECOMP_VehPhysGeneral_GetBaseSpeed(driver);
	driverBaseSpeed = driver->const_Speed_ClassStat;
	#else
	// original, for decomp
	driverBaseSpeed = VehPhysGeneral_GetBaseSpeed(driver);
	#endif

	driverBaseSpeedUshort = driverBaseSpeed;

	// If you are not holding Square
	if (square == 0)
	{
		//driverSpeedSmth2 = Racer's Base Speed
		driverSpeedSmth2 = driverBaseSpeed;

		// If you are holding Cross, or if you have Reserves
		if (cross != 0)
		{
			LAB_8006253c:
			actionsFlagSetCopy &= 0xfffdffff;
			goto LAB_80062548;
		}

		// if you are not holding cross, or have no Reserves...
		// driverSpeedSmth2 is replaced

		driverSpeedSmth2 = DECOMP_VehPhysJoystick_ReturnToRest(stickRY, 0x80, 0);

		driverSpeedOrSmth = -driverSpeedSmth2;
		if (driverSpeedSmth2 < 1)
		{
			if
			(
				(driverSpeedOrSmth == 0) &&
				(
					(
						unk0x80 = DECOMP_VehPhysJoystick_ReturnToRest(stickLY, 0x80, 0),

						(unk0x80 > 99) ||

						(
							(unk0x80 > 0) &&
							((actionsFlagSetCopy & 0x20000) != 0)
						)
					)
				)
			)
			{
				// driver is steering?
				actionsFlagSetCopy |= 0x20000;

				driverSpeedSmth2 = -driver->const_BackwardSpeed;
				goto LAB_80062548;
			}

			driverSpeedOrSmth = driverBaseSpeed * driverSpeedOrSmth;
			driverSpeedSmth2 = driverSpeedOrSmth >> 7;
			if (driverSpeedOrSmth < 0) driverSpeedSmth2 = (driverSpeedOrSmth + 0x7f) >> 7;

			// remove flag for reversing
			goto LAB_8006253c;
		}
		if ((driver->speedApprox < 0x301) && ((actionsFlagSetCopy & 0x60000000) == 0))
		{
			driverSpeedOrSmth = driver->const_BackwardSpeed * driverSpeedOrSmth;
			if (driverSpeedOrSmth < 0) driverSpeedOrSmth = driverSpeedOrSmth + 0x7f;
			approximateSpeed2 = driverSpeedOrSmth >> 7;
			buttonsTapped = 0x20000;
			LAB_800625c4:
			uVar20 = actionsFlagSetCopy | buttonsTapped;
		}
		else
		{
			uVar20 = actionsFlagSetCopy | 8;
			if (0 < driver->simpTurnState) uVar20 = actionsFlagSetCopy | 0x40000008;
			if (driver->simpTurnState < 0)
			{
				buttonsTapped = 0x20000000;
				actionsFlagSetCopy = uVar20;
				goto LAB_800625c4;
			}
		}
	}
	// If you are holding Square
	else
	{
		unk0x80 = DECOMP_VehPhysJoystick_ReturnToRest(stickLY, 0x80, 0);

		if ((unk0x80 < 100) && ((unk0x80 < 1 || ((actionsFlagSetCopy & 0x20000) == 0))))
		{
			// if you are not holding cross, and you have no Reserves
			if (cross == 0)
			{
				driverSpeedOrSmth = DECOMP_VehPhysJoystick_ReturnToRest(stickRY, 0x80, 0);

				if (driverSpeedOrSmth < 0)
				{
					driverSpeedOrSmth = driverBaseSpeed * -driverSpeedOrSmth;
					if (driverSpeedOrSmth < 0) driverSpeedOrSmth += 0xff;
					driverSpeedSmth2 = driverSpeedOrSmth >> 8;

					// gas and brake together
					actionsFlagSetCopy |= 0x20;

					goto LAB_80062548;
				}

				if (0 < driverSpeedOrSmth)
				{
					driverSpeedOrSmth = driver->const_BackwardSpeed * -driverSpeedOrSmth;
					if (driverSpeedOrSmth < 0) driverSpeedOrSmth += 0xff;
					driverSpeedSmth2 = driverSpeedOrSmth >> 8;

					// reversing, and gas+brake
					goto LAB_8006248c;
				}

				// driverSpeedOrSmth == 0,
				// no gas, only brake

				// using the brake
				actionsFlagSetCopy |= 8;

				driverSpeedSmth2 = approximateSpeed2;
			}
			// If you are holding cross, or you have Reserves
			else
			{
				// gas and brake together
				actionsFlagSetCopy |= 0x20;

				driverSpeedSmth2 = driverBaseSpeed / 2;
			}
			goto LAB_8006253c;
		}
		driverSpeedOrSmth = driver->const_BackwardSpeed * -3;
		driverSpeedSmth2 = driverSpeedOrSmth >> 2;
		if (driverSpeedOrSmth < 0) 	driverSpeedSmth2 = (driverSpeedOrSmth + 3) >> 2;

		LAB_8006248c:
		// reversing engine, and brakes
		actionsFlagSetCopy |= 0x20020;

		LAB_80062548:
		uVar20 = actionsFlagSetCopy & 0x9fffffff;
		approximateSpeed2 = driverSpeedSmth2;
	}

	// driving backwards
	if ((uVar20 & 0x20000) != 0)
	{
		driver->timeSpentReversing += gGT->elapsedTimeMS;
	}

	// not driving backwards
	else
	{
		if (driver->superEngineTimer != 0)
		{
			// if Racer is moving
			if (0 < approximateSpeed2)
			{
				// not holding brake
				if ((uVar20 & 0x400020) == 0)
				{
					driver->actionsFlagSet = uVar20;

					// fire level, depending on numWumpa
					superEngineFireLevel = 0x80;
					if (driver->numWumpas > 9)
						superEngineFireLevel = 0x100;

					// add 0.12s reserves
					DECOMP_VehFire_Increment(driver, 120, (TURBO_PAD | SUPER_ENGINE), superEngineFireLevel);

					uVar20 = driver->actionsFlagSet;
				}
			}
		}
	}

	// if accel prevention (hold square)
	actionsFlagSetCopy = uVar20 & 8;
	if (actionsFlagSetCopy != 0)
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

		(
			(driver->kartState != KS_NORMAL) &&
			(driver->kartState != KS_ANTIVSHIFT)
		)
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
		*(u_short*)&driver->fireSpeed = approximateSpeed2;
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
		*(u_short*)&driver->fireSpeed = approximateSpeed2;
	}

	// brakes
	if ((uVar20 & 0x800020) == 0)
	{
#ifdef REBUILD_PC
		// no collision, no "found" quadblock, no "known"
		// terrain, so for now, assume asphalt
		driver->terrainMeta1 = &data.MetaDataTerrain[0];
		driver->terrainMeta2 = &data.MetaDataTerrain[0];
#endif

		driverSpeedOrSmth = driver->terrainMeta2->unk_0x8;

		if (driverSpeedOrSmth != 0x100)
		{
			//Base Speed = 0xB4 (at Cove water) * Base Speed >> 8
			approximateSpeed2 = 	(driverSpeedOrSmth * approximateSpeed2) >> 8;
			driverBaseSpeedUshort = (driverSpeedOrSmth * driverBaseSpeed) >> 8;
		}
	}
	*(u_short*)&driver->unknowndriverBaseSpeed = driverBaseSpeedUshort;
	*(u_short*)&driver->baseSpeed = approximateSpeed2;


	// === Steering Section ===


	// assume neutral steer (drive straight)
	driverSpeedOrSmth = 0x80;

	// If you're not in End-Of-Race menu
	if ((gGT->gameMode1 & END_OF_RACE) == 0)
	{
		// gamepadBuffer -> stickLX
		driverSpeedOrSmth = (int)ptrgamepad->stickLX;
	}

	// default steer strength from class stats
	iVar14 = driver->const_TurnRate + (driver->turnConst << 1) / 5;

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
	// or not using brakes (& 0x20)
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
	driverSpeedCopy = driver->speed;
	if (driverSpeedCopy < 0) driverSpeedCopy = -driverSpeedCopy;

	// As speed increases, turn rate decreases
	iVar14 = DECOMP_VehCalc_MapToRange
	(
		driverSpeedCopy,
		0x300,	driver->const_Speed_ClassStat / 2,
		0x40,	iVar14
	);

UseTurnRate:

	// Steer, based on strength, and LeftStickX
	iVar14 = DECOMP_VehPhysJoystick_GetStrengthAbsolute(driverSpeedOrSmth, iVar14, ptrgamepad->rwd);

	// no desired steer
	if (-iVar14 == 0)
	{
		driver->numFramesSpentSteering = 10000;
	}

	// desired steer
	else
	{
		// desired steer left, or active steer left
		if ((iVar14 < 1) || (driver->simpTurnState < 0))
		{
			// desired steer right, or active steer right
			if ((-1 < iVar14) || (0 < driver->simpTurnState))
			{
				// active steer has not changed
				goto SkipSetSteer;
			}

			// active steer left
			uVar20 = uVar20 | 0x10;
		}

		else
		{
			// active steer right
			uVar20 = uVar20 & 0xffffffef;
		}
		driver->numFramesSpentSteering = 0;
	}

SkipSetSteer:

	*(u_char*)&driver->simpTurnState = (char)-iVar14;

	// Change wheel rotation based on StickLX
	driverSpeedOrSmth = DECOMP_VehPhysJoystick_GetStrengthAbsolute(driverSpeedOrSmth, 0x40, ptrgamepad->rwd);
	driverBaseSpeedUshort = DECOMP_VehCalc_InterpBySpeed((int)driver->wheelRotation, FPS_HALF(0x18), -driverSpeedOrSmth);
	*(u_short*)&driver->wheelRotation = driverBaseSpeedUshort;

	driverSpeedOrSmth = (int)driver->fireSpeed;
	if (driverSpeedOrSmth < 0) driverSpeedOrSmth = -driverSpeedOrSmth;

	if (((driver->actionsFlagSetPrevFrame & 1) == 0) || (kartState == KS_DRIFTING))
	{
		driverSpeedOrSmth = driverSpeedOrSmth + 0xf00;
	}
	else
	{
		driverSpeedOrSmth = driverSpeedOrSmth + approximateSpeed >> 1;
	}

	sVar13 = ((driverSpeedOrSmth * 0x89 + driver->unkSpeedValue2 * 0x177) * 8) >> 0xc;
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

	// alternate tire colors each frame,
	// if 2e808080 is detected (&1==0),
	// if not RevEngine, and if unkSpeedVal
	if
	(
		(driver->unkSpeedValue1 < 1) &&
		((driver->tireColor & 1) == 0) &&
		(kartState != KS_ENGINE_REVVING)
	)
	{
		//reset 0x3BC
		driver->unkSpeedValue1 = 0x1e00;

		driver->tireColor = 0x2e606061;
	}

	// default tire color
	else
	{
		driver->tireColor = 0x2e808080;
	}

	driver->actionsFlagSet = uVar20;
	return;
}

#define DriverPhysLinear_OFFSETOF(TYPE, ELEMENT) (short)((unsigned int)&(((TYPE *)0)->ELEMENT))
short PhysLinear_DriverOffsets[14] =
{
	DriverPhysLinear_OFFSETOF(struct Driver, reserves),
	DriverPhysLinear_OFFSETOF(struct Driver, set_0xF0_OnWallRub),
	DriverPhysLinear_OFFSETOF(struct Driver, burnTimer),
	DriverPhysLinear_OFFSETOF(struct Driver, squishTimer),
	DriverPhysLinear_OFFSETOF(struct Driver, turbo_outsideTimer),
	DriverPhysLinear_OFFSETOF(struct Driver, VehFire_AudioCooldown),
	DriverPhysLinear_OFFSETOF(struct Driver, jump_ForcedMS),
	DriverPhysLinear_OFFSETOF(struct Driver, jump_CooldownMS),
	DriverPhysLinear_OFFSETOF(struct Driver, jump_unknown),
	DriverPhysLinear_OFFSETOF(struct Driver, StartDriving_0x60),
	DriverPhysLinear_OFFSETOF(struct Driver, StartRollback_0x280),
	DriverPhysLinear_OFFSETOF(struct Driver, clockReceive),
	DriverPhysLinear_OFFSETOF(struct Driver, mashingXMakesItBig),
	DriverPhysLinear_OFFSETOF(struct Driver, invincibleTimer)
};