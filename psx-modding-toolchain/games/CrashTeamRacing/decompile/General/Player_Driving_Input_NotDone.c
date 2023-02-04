#include <common.h>

void GAMEPAD_Vib_4(struct Driver* driver, u_int param_2, int param_3);
void Player_SetHeldItem(struct Driver* driver);
void OtherFX_Play(int sfxID, int flag);
int Player_Steer_ReturnToRest(int param_1, u_int param_2, struct RacingWheelData* param_3);
int Player_GetBaseSpeed(struct Driver* driver);
void Turbo_Increment(struct Driver* driver, int reserves, u_int type, int fireLevel);
int MapToRange(int param_1,int param_2,int param_3,int param_4,int param_5);
int Player_Steer_AbsoluteStrength(int param_1, u_int param_2, struct RacingWheelData* param_3);
int InterpBySpeed(int param_1,int param_2,int param_3);

void Player_Driving_Input(struct Thread* thread, struct Driver* driver)
{
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
	u_int* AxisAnglePointer;
	short sVar13;
	int iVar14;
	u_int buttonsTapped;
	struct RacingWheelData* gamepadRacingWheel;
	u_char trueVectorID;
	u_short driverTimerShort;
	int driverTimer;
	u_int timerHazard;
	int approximateSpeed2;
	u_int actionflags;
	int driverSpeedSmth2;
	struct GamepadBuffer* ptrgamepad;
	u_int cross;
	u_int square;

	int msPerFrame;
	int negativeMsPerFrame;
	int driverValueMinusMsPerFrame;
	u_int driverValueMinusMsPerFrameUnsigned;
	short driverRankItemValue;
	u_short timerHazardSomething;
	u_int itemSound;
	u_int specialFlag;
	u_int buttonHeld;
	u_int vectorID;
	int vectorID2;
	int steeringDirectionOrSmth;
	int driverSpeedOrSmth = 0;
	struct Thread* driverItemThread;
	struct Shield* shield;
	struct TrackerWeapon* bomb;
	u_int superEngineFireLevel;

	// If race timer is not supposed to stop for this racer
	if ((driver->actionsFlagSet & 0x40000) == 0)
	{
		// set racer's timer to the time on the clock
		driver->timeElapsedInRace = sdata->gGT->elapsedEventTime;
	}

	// elapsed milliseconds per frame, ~32
	msPerFrame = sdata->gGT->elapsedTimeMS;

	// negative elapsed milliseconds per frame
	negativeMsPerFrame = -msPerFrame;

	if
	(
		// time on the clock
		(sdata->gGT->elapsedEventTime < 0x8ca00) &&

		// race timer is not frozen for this player
		((driver->actionsFlagSet & 0x40000) == 0)
	)
	{
		// increment timer by (speed * time)
		driver->distanceDriven += (driver->speedApprox * msPerFrame >> 8);
	}

	// Next 7 lines are repetitive, this time for Reserves (0x3e2)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->reserves + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->reserves)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->reserves = driverValueMinusMsPerFrameUnsigned;

		// adds *spent* Reserves to cumulative counter
		driver->timeSpentUsingReserves += msPerFrame;
	}

	// Next 7 lines are repetitive, this time for Outside Turbo Timer (0x3de)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->outsideTurboTimer + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->outsideTurboTimer)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->outsideTurboTimer = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Outside Turbo Sound (0x3e0)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->turboAudioCooldown + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->turboAudioCooldown)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->turboAudioCooldown = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Collision (0x3fe)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->unknownCollision + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->unknownCollision)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->unknownCollision = driverValueMinusMsPerFrameUnsigned;

		// Add elapsed time to a counter for how long you've driven against a wall
		driver->timeSpentAgainstWall += msPerFrame;
	}

	// Next 7 lines are repetitive, this time for Jump Animation (0x3f6)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = driver->jump_ForcedMS + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->jump_ForcedMS)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->jump_ForcedMS = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Unknown (0x3f2)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->jump_CooldownMS + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->jump_CooldownMS)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->jump_CooldownMS = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Unknown (0x3fa)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->unknownJump3 + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->unknownJump3)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->unknownJump3 = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Burnt Effect Timer (0x402)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->burnTimer + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->burnTimer)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->burnTimer = driverValueMinusMsPerFrameUnsigned;

		// increment timer for total frames burnt
		driver->timeSpentBurnt += msPerFrame;
	}

	// Next 7 lines are repetitive, this time for Squished Effect Timer (0x404)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->squishTimer + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->squishTimer)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->squishTimer = driverValueMinusMsPerFrameUnsigned;

		// increment timer for total frames squished
		driver->timeSpentSquished += msPerFrame;
	}

	// Next 7 lines are repetitive, this time for Unknown (0x406)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->StateDriving_0x60 + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->StateDriving_0x60)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->StateDriving_0x60 = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for Unknown (0x408)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->StateDriving_0x280 + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->StateDriving_0x280)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->StateDriving_0x280 = driverValueMinusMsPerFrameUnsigned;
	}

	// If Super Engine Cheat is not enabled
	if (!(sdata->gGT->gameMode2 & 0x10000))
	{
		// Next 7 lines are repetitive, this time for Super Engine Timer (0x38)
		// Make "desired" amount by subtracting elapsed time from "current" amount,
		// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
		// then handle subtraction. In subtraction, make sure desired is not negative,
		// then set current to desired

		driverValueMinusMsPerFrame = (int)driver->superEngineTimer + negativeMsPerFrame;
		driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
		if (0 < (int)driver->superEngineTimer)
		{
			if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
			*(u_short*)&driver->superEngineTimer = driverValueMinusMsPerFrameUnsigned;
		}
	}

	// Next 7 lines are repetitive, this time for Clock Weapon Timer (0xC)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->clockReceive + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->clockReceive)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->clockReceive = driverValueMinusMsPerFrameUnsigned;
	}

	// Next 7 lines are repetitive, this time for "Mashing X makes it big" (0x3c0)
	// Make "desired" amount by subtracting elapsed time from "current" amount,
	// store desired into driverValueMinusMsPerFrame, then copy it into iVar7. If current is more than 0,
	// then handle subtraction. In subtraction, make sure desired is not negative,
	// then set current to desired

	driverValueMinusMsPerFrame = (int)driver->mashingXMakesItBig + negativeMsPerFrame;
	driverValueMinusMsPerFrameUnsigned = (u_short)driverValueMinusMsPerFrame;
	if (0 < (int)driver->mashingXMakesItBig)
	{
		if (driverValueMinusMsPerFrame < 0) driverValueMinusMsPerFrameUnsigned = 0;
		*(u_short*)&driver->mashingXMakesItBig = driverValueMinusMsPerFrameUnsigned;
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
					(sdata->gGT->numPlyrCurrGame == 1)
				) ||
				(
					(
						// If racer is in 6th place
						driverRankItemValue == 5 &&

						// if numPlyrCurrGame is 2
						(sdata->gGT->numPlyrCurrGame == 2)
					)
				)
			) ||
			(
				(
					// if racer is in 4th place
					driverRankItemValue == 3 &&

					// if numPlyrCurrGame is more than 2
					(2 < (u_char)sdata->gGT->numPlyrCurrGame)
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
	if (driver->thCloud != 0) driverRankItemValue = ((struct RainCloud*)driver->thCloud->object)->itemScrollRandom;

	// get approximate speed
	approximateSpeed = (int)driver->speedApprox;

	// Action flags (isRaceOver, isTimeFrozen, etc)
	actionflags = driver->actionsFlagSet;

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
					driverTimer = sdata->gGT->elapsedEventTime,
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
		*(u_short*)&driver->hazardTimer = timerHazardSomething;
	}

	// if you are not impacted by hazard (other than clock)
	else
	{
		driverTimerShort = (u_short)driverTimer;

		// if you are not touching the ground
		if ((actionflags & 1) == 0)
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
		*(u_short*)&driver->hazardTimer = driverTimerUnk;
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
	if (noItemTimer)
	{

		// if Item is about to be gone and Number of Items = 0
		if ((noItemTimer == 1) && (driver->numHeldItems == 0))
		{

			// if numPlyrCurrGame is > 2
			if
			(
				(2 < (u_char)sdata->gGT->numPlyrCurrGame) &&

				// If you're not in Battle Mode
				(
					(
						(
							(sdata->gGT->gameMode1 & 0x20) == 0 &&

							// your weapon is 3 missiles
							(driver->heldItemID == 0xB)
		 				) &&

						// If there are racers that had 3 missiles
						(sdata->gGT->numPlayersWith3Missiles > 0)
					)
				)
			)
			{
				// decrement the number of players that had 3 missiles
				sdata->gGT->numPlayersWith3Missiles--;
			}

			// take away weapon
			*(u_char*)&driver->heldItemID = 0xf;
		}

		driver->noItemTimer = noItemTimer - 1;
	}

	// If Invinsibility effect is active (timer at 0x24)
	// Make "desired" timer by subtracting elapsed time from "current",
	// set "current" to "desired", then set "current" to zero if "desired" is negative

	if
	(
		(driver->invincibleTimer != 0) &&
		(
			driverTimer2 = driver->invincibleTimer - sdata->gGT->elapsedTimeMS,
			driver->invincibleTimer = driverTimer2, driverTimer2 < 0
		)
	)
	{
		driver->invincibleTimer = 0;
	}

	// If Invincibility effect is active (timer at 0x28) and if Cheat Code is Disabled
	// Make "desired" timer by subtracting elapsed time from "current",
	// set "current" to "desired", then set "current" to zero if "desired" is negative

	if
	(
		// if driver is invisible
		(driver->invisibleTimer != 0) &&

		// If Permanent Invisibility Cheat is Disabled
		(!(sdata->gGT->gameMode2 & 0x8000))
	)
	{
		// decrease invisibility timer, can not go below zero
		driverTimer2 = driver->invisibleTimer - sdata->gGT->elapsedTimeMS;
		driver->invisibleTimer = driverTimer2;
		if (driverTimer2 < 0) driver->invisibleTimer = 0;

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

	// Random guess, this next block is probably for making a backup
	// of current position and rotation, to calculate linear + angular
	// velocity by comparing two frames
	
	// action flags
	driver->actionsFlagSetPrevFrame = actionflags;
	
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
	specialFlag = actionflags & 0x7f1f83d5;
	
	if ((sdata->gGT->gameMode2 & 0x4004) != 0) goto setActionsFlagSetToSomething;
	trueVectorID = *(u_char*)&driver->normalVecID + 1;
	
	// what --Super
	if (trueVectorID) trueVectorID = 0;
	
	// get pointer to normalVec, vectorID2 is which vector
	// gotta watch this as well --Super
	AxisAnglePointer = (u_int*)&driver->AxisAngle4_normalVec[trueVectorID];
	
	// if not touching ground
	if ((actionflags & 1) == 0) 
	{
		// AngleAxis2_NormalVec
		*AxisAnglePointer = *(u_int*)&driver->AxisAngle2_normalVec[0];
		*(u_short*)(AxisAnglePointer + 1) = driver->AxisAngle2_normalVec[2];
	}
	
	// if touching ground
	else 
	{
		// AngleAxis1_NormalVec
		*AxisAnglePointer = *(u_int*)&driver->AxisAngle1_normalVec[0];
		*(u_short*)(AxisAnglePointer + 1) = driver->AxisAngle1_normalVec[2];
	}
	
	*(u_char*)&driver->normalVecID = trueVectorID;

	driverItemThread = thread->childThread;

	while (actionflags = specialFlag, driverItemThread != 0)
	{
		// If thread->modelIndex is Aku or Uka
		if ((*(short*)&driverItemThread->modelIndex == 0x3a) || (*(short*)&driverItemThread->modelIndex == 0x39))
		{
			actionflags = specialFlag | 0x800000;
			break;
		}

		// check next player in linked list
		driverItemThread = driverItemThread->siblingThread;
	}

	// pointer to gamepad input of current player (driver)
	ptrgamepad = &sdata->gGamepads->gamepad[(u_int)driver->driverID];

	// by default, hold no buttons
	buttonHeld = 0;

	// If you're not in End-Of-Race menu
	if (!(sdata->gGT->gameMode1 & 0x200000))
	{
		// Get which button is held
		buttonHeld = ptrgamepad->buttonsHeldCurrFrame;
	}

	// by default, tap no buttons
	buttonsTapped = 0;

	// If you're not in End-Of-Race menu
	if ((sdata->gGT->gameMode1 & 0x200000) == 0)
	{
		// Get which button is tapped
		buttonsTapped = ptrgamepad->buttonsTapped;
	}

	// If you hold Cross
	cross = buttonHeld & 0x10;

	// If you hold Square
	square = buttonHeld & 0x20;

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
							(heldItemID != 0xF) && (heldItemID != 0x10)
						) &&
						(
							(driver->noItemTimer == 0 &&
								(
									(driverRankItemValue != 1 && (driver->clockReceive == 0))
								)
							)
						)
					)
					{
						// This driver wants to fire a weapon
						actionflags = actionflags | 0x8000;

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
								goto YouUsedTheSpring;
							}
						}
						else
						{
							jumpCooldown = sdata->gGT->gameMode2 & 0x400c00;
							YouUsedTheSpring:
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
			((buttonHeld & 0xc00) != 0) &&
			(driverRankItemValue != 3)
		)
		{
			if ((actionflags & 4) == 0)
			{
				// 10 frame jump buffer
				driver->jump_TenBuffer = 10;
			}
			goto LAB_8006222c;
		}
		actionflags = actionflags & 0xfffffffb;
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
			actionflags = actionflags | 4;
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
	steeringDirectionOrSmth = 0x80;

	// If you're not in End-Of-Race menu
	if ((sdata->gGT->gameMode1 & 0x200000) == 0)
	{
		// gamepadBuffer -> stickRY (for gas or reverse)
		steeringDirectionOrSmth = (int)ptrgamepad->stickRY;
	}

	if
	(
		// If Reserves are not zero
		(driver->reserves != 0) ||

		(driverRankItemValue == 6)
	)
	{
		if
		(
			// If you are not holding Cross
			(cross == 0) &&

			(driverTimer = Player_Steer_ReturnToRest(steeringDirectionOrSmth, 0x80, 0), driverTimer > -1)
		)
		{
			actionflags |= 0x400000;
		}


		if
		(
			// If are holding Square
			(square != 0) &&

			(approximateSpeed > 0x300)
		)
		{
			actionflags |= 0x800;
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
	if ((sdata->gGT->gameMode1 & 0x200000) == 0) driverTimer = (int)ptrgamepad->stickLY;

	if
	(
		(driver->simpTurnState < 0) ||
		(actionflags &= 0xdfffffff, driver->simpTurnState < 1)
	)
	{
		actionflags = actionflags & 0xbfffffff;
	}
	approximateSpeed2 = (int)driver->speedApprox;
	if (approximateSpeed2 < 0)
	{
		approximateSpeed2 = -approximateSpeed2;
	}
	if (approximateSpeed2 < 0x300)
	{
		actionflags = actionflags & 0x9fffffff;
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
			actionflags = actionflags & 0xfffdffff;
			goto LAB_80062548;
		}

		// if you are not holding cross, or have no Reserves...
		//driverSpeedSmth2 is replaced

		// Player_Steer_ReturnToRest
		driverSpeedSmth2 = Player_Steer_ReturnToRest(steeringDirectionOrSmth, 0x80, 0);

		driverSpeedOrSmth = -driverSpeedSmth2;
		if (driverSpeedSmth2 < 1)
		{
			if
			(	
				(driverSpeedOrSmth == 0) &&
				(
					(
						driverTimer = Player_Steer_ReturnToRest(driverTimer, 0x80, 0), driverTimer > 99 ||

						(
							(driverTimer > 0 && ((actionflags & 0x20000) != 0))
						)
					)
				)
			)
			{
				// driver is steering?
				actionflags |= 0x20000;
		
				driverSpeedSmth2 = -(int)driver->const_BackwardSpeed;
				goto LAB_80062548;
			}
			driverSpeedOrSmth = driverBaseSpeed * driverSpeedOrSmth;
			driverSpeedSmth2 = driverSpeedOrSmth >> 7;
			if (driverSpeedOrSmth < 0) driverSpeedSmth2 = driverSpeedOrSmth + 0x7f >> 7;
			goto LAB_8006253c;
		}
		if ((driver->speedApprox < 0x301) && ((actionflags & 0x60000000) == 0))
		{
			driverSpeedOrSmth = driver->const_BackwardSpeed * driverSpeedOrSmth;
			if (driverSpeedOrSmth < 0) driverSpeedOrSmth = driverSpeedOrSmth + 0x7f;
			approximateSpeed2 = driverSpeedOrSmth >> 7;
			buttonsTapped = 0x20000;
			LAB_800625c4:
			buttonHeld = actionflags | buttonsTapped;
		}
		else
		{
			buttonHeld = actionflags | 8;
			if (0 < driver->simpTurnState) buttonHeld = actionflags | 0x40000008;
			if (driver->simpTurnState < 0)
			{
				buttonsTapped = 0x20000000;
				actionflags = buttonHeld;
				goto LAB_800625c4;
			}
		}
	}
	// If you are holding Square
	else
	{
		driverTimer = Player_Steer_ReturnToRest(driverTimer, 0x80, 0);

		if ((driverTimer < 100) && ((driverTimer < 1 || ((actionflags & 0x20000) == 0))))
		{
			// if you are not holding cross, and you have no Reserves
			if (cross == 0)
			{
				// Player_Steer_ReturnToRest
				driverSpeedOrSmth = Player_Steer_ReturnToRest(driverSpeedOrSmth, 0x80, 0);

				driverSpeedSmth2 = driverBaseSpeed * -driverSpeedOrSmth;
				if (driverSpeedOrSmth < 0)
				{
					if (driverSpeedSmth2 < 0) driverSpeedSmth2 = driverSpeedSmth2 + 0xff;
					driverSpeedSmth2 = driverSpeedSmth2 >> 8;
					actionflags = actionflags | 0x20;
					goto LAB_80062548;
				}
				if (0 < driverSpeedOrSmth)
				{
					driverSpeedOrSmth = (int)driver->const_BackwardSpeed * -driverSpeedOrSmth;
					driverSpeedSmth2 = driverSpeedOrSmth >> 8;
					if (driverSpeedOrSmth < 0) driverSpeedSmth2 = driverSpeedOrSmth + 0xff >> 8;
					goto LAB_8006248c;
				}
				actionflags = actionflags | 8;
				driverSpeedSmth2 = approximateSpeed2;
			}
			// If you are holding cross, or you have Reserves
			else
			{
				actionflags = actionflags | 0x20;
				driverSpeedSmth2 = driverBaseSpeed / 2;
			}
			goto LAB_8006253c;
		}
		driverSpeedOrSmth = (int)driver->const_BackwardSpeed * -3;
		driverSpeedSmth2 = driverSpeedOrSmth >> 2;
		if (driverSpeedOrSmth < 0) 	driverSpeedSmth2 = driverSpeedOrSmth + 3 >> 2;
		LAB_8006248c:
		actionflags = actionflags | 0x20020;
		LAB_80062548:
		buttonHeld = actionflags & 0x9fffffff;
		approximateSpeed2 = driverSpeedSmth2;
	}
	if ((buttonHeld & 0x20000) == 0)
	{
		actionflags = buttonHeld & 8;
		if (driver->superEngineTimer != 0)
		{
			// if Racer is moving
			if (0 < approximateSpeed2)
			{
				actionflags = buttonHeld & 8;
				if ((buttonHeld & 0x400020) != 0) goto LAB_80062648;

				// if you have less than 10 wumpa
				superEngineFireLevel = 0x80;

				driver->actionsFlagSet = buttonHeld;

				// if number of wumpa > 9
				// if wumpa is 10
				if (driver->numWumpas > 9) superEngineFireLevel = 0x100;

				// Turbo_Increment
				// add 0.12s reserves
				Turbo_Increment(driver, 0x78, 0x14, superEngineFireLevel);

				buttonHeld = driver->actionsFlagSet;
			}
			goto code_r0x80062644;
		}
	}

	else
	{
		driver->timeSpentReversing += msPerFrame;
		
code_r0x80062644:
		actionflags = buttonHeld & 8;
	}

	LAB_80062648:
	if (actionflags != 0)
	{
		driverSpeedOrSmth = (int)driver->speedApprox;
		if (driverSpeedOrSmth < 0) driverSpeedOrSmth = -driverSpeedOrSmth;
		
		if (driverSpeedOrSmth > 0x300) 
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
	if ((buttonHeld & 0x800020) == 0)
	{
		driverSpeedOrSmth = *(int*)(&driver->terrainMeta2 + 8);
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
	if ((sdata->gGT->gameMode1 & 0x200000) == 0)
	{
		// gamepadBuffer -> stickLX
		driverSpeedOrSmth = (int)ptrgamepad->stickLX;
	}

	iVar14 = (u_int)driver->const_TurnRate + ((int)driver->turnConst << 1) / 5;
	if ((driver->mashXUnknown < 7) || (approximateSpeed > 0x25ff))
	{
		if (driver->unknownCollision == 0)
		{
			if ((buttonHeld & 0x28) != 0)
			{
				// if you are not holding cross
				if (cross == 0)
				{
					iVar14 = 0x40;
				}

				// if you are holding cross
				else
				{
					// get speed
					driverTimer = (int)driver->speed;

					// set speed to absolute value
					if (driverTimer < 0) driverTimer = -driverTimer;

					// Map value from [oldMin, oldMax] to [newMin, newMax]
					// inverting newMin and newMax will give an inverse range mapping
					iVar14 = MapToRange(driverTimer,0x300,(int)((u_int)driver->const_Speed_ClassStat << 0x10) >> 0x11,0x40,iVar14);
				}
			}
		}
		else
		{
			iVar14 = 0x30;
		}
	}
	else
	{
		iVar14 = 0x5a;
	}

	// Steer
	iVar14 = Player_Steer_AbsoluteStrength(driverSpeedOrSmth, iVar14, ptrgamepad->rwd);

	if (-iVar14 == 0) *(u_short*)&driver->numFramesSpentSteering = 10000;
	else
	{
		if ((iVar14 < 1) || (driver->simpTurnState < 0))
		{
			if ((-1 < iVar14) || (0 < driver->simpTurnState)) goto LAB_800628b0;
			buttonHeld = buttonHeld | 0x10;
		}
		else buttonHeld = buttonHeld & 0xffffffef;
		driver->numFramesSpentSteering = 0;
	}
	LAB_800628b0:
	*(u_char*)&driver->simpTurnState = (char)-iVar14;

	// Steer
	driverSpeedOrSmth = Player_Steer_AbsoluteStrength(driverSpeedOrSmth, 0x40, ptrgamepad->rwd);

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
		//Jittery number 1
		*(u_int*)&driver->tireColor = 0x2e606061;
	}
	else
	{
		//jittery number 2
		*(u_int*)&driver->tireColor = 0x2e808080;
	}
	setActionsFlagSetToSomething:
	driver->actionsFlagSet = specialFlag;
	return;
}