#include <common.h>

void DECOMP_VehFire_Increment(struct Driver* driver, int reserves, u_int type, int fireLevel)
{
	char kartState;
	u_char count;
	
	int newFireSpeedCap;
	int newFireSize;
	int oldOTT;
	
	u_int addFlags;
	struct Turbo* turboObj;
	struct Thread* turboThread;
	struct Instance* turboInst1;
	struct Instance* turboInst2;
	
	struct GameTracker* gGT = sdata->gGT;

    u_char isPlayer = (driver->instSelf->thread->modelIndex == DYNAMIC_PLAYER);

	if
	(
		// if this is a turbo pad
		(type & 4) &&
		
		// racer is in accel prevention (holding square)
		((driver->actionsFlagSet & 8) != 0)
	)
	{
		// do nothing
		return;
	}

    // Player / AI structure + 0x4a shows driver index (0-7)

	// If this is the first driver (P1) and
	if
	((driver->driverID == 0) &&

		// if modelIndex == "player" of any kind
		(isPlayer)
	)
	{
		// Add Reserves to ghost buffer
		GhostTape_WriteBoosts(reserves, (u_char)type, fireLevel);
	}

	kartState = driver->kartState;

	if (kartState == KS_SPINNING) return;
	if (kartState == KS_MASK_GRABBED) return;
	if (kartState == KS_BLASTED) return;

	//turn off 8th flag, turn on 22nd flag of actions flag set
	//means ? (!(8)) and racer just got an outside turbo (22)
	driver->actionsFlagSet = driver->actionsFlagSet & 0xffffff7f | 0x200000;

	// turbo thread bucket
	turboThread = gGT->threadBuckets[TURBO].thread;

	// check all turbo threads
	while(turboThread != 0)
	{	
		// if this turbo thread is owned by this driver
		if (((struct Turbo*)turboThread->object)->driver == driver)
		{
			// quit, turboThread is now this driver's turbo thread
			break;
		}

		// next turbo thread in bucket
		turboThread = turboThread->siblingThread;
	}
	
	// if no turbo exists, create one
	if(turboThread == 0)
	{
		#if BUILD < JpnRetail

		driver->numTurbos = 1;

		#else

		// some sort of variable related to drifting? check + 0x3be in japanese output
		if (driver->japanTurboUnknown == 0)
		{
			driver->numTurbos = 1;
			if ((driver->numTurbosHighScore < 1) && ((gGT->gameMode1 & END_OF_RACE) == 0))
			{
				driver->numTurbosHighScore = 1;
			}
		}
		else
		{
			driver->numTurbos++;
			if ((driver->numTurbosHighScore < driver->numTurbos) && ((gGT->gameMode1 & END_OF_RACE) == 0))
			{
				driver->numTurbosHighScore = driver->numTurbos;
			}
		}

		#endif
		
		turboInst1 = INSTANCE_BirthWithThread(
			STATIC_TURBO_EFFECT, 				// modelID
			&sdata->s_turbo1[0],	// name
			SMALL, 				// SmallStackPool
			TURBO, 				// ThreadBucket
			VehTurbo_ThTick,	// func
			0x10, 				// object size
			0					// no parent thread
		);
	
		turboObj = NULL;
	
		if (turboInst1 != 0)
		{
			// get thread, ignore all collisions
			turboThread = turboInst1->thread;
			turboThread->flags |= 0x1000;
			turboThread->funcThDestroy = VehTurbo_ThDestroy;
			
			// turbo #2
			turboInst2 = INSTANCE_Birth3D(
				gGT->modelPtr[STATIC_TURBO_EFFECT], 	// model
				&sdata->s_turbo2[0], 		// name
				turboThread					// parent thread
			);
			
			// get object, set essentials
			turboObj = turboThread->object;
			turboObj->inst = turboInst2;
			turboObj->driver = driver;
			turboObj->fireAnimIndex = 0;
			turboObj->fireVisibilityCooldown = 0x60;
			
			// make flame disappear after
			// 	- powerslide: two frames (quick death)
			//	- all others: 255 frames (slowly die out)
			if (type & 2)	count = 2;
			else					count = 0xff;
			turboObj->fireDisappearCountdown = count;
	
			// if modelIndex == "player" of any kind
			if (isPlayer)
			{
				turboObj->fireAudioDistort = 0;
				
				if(driver->kartState != KS_CRASHING)
				{
					VehFire_Audio(driver, fireLevel);
				}
			}
	
			// 2P 3P 4P flags
			addFlags = 0;
	
			// 1P flags
			if (gGT->numPlyrCurrGame == 1)
			{
				addFlags = 0x2000000;
			}
	
			// make turbos invisible, and transparent.
			// why does numPlyrCurrGame alter pause-menu invisible toggle?
			turboInst1->flags = turboInst1->flags | addFlags | 0x1040080;
			turboInst2->flags = turboInst2->flags | addFlags | 0x1040080;
		}
	}

	// if turbo exists, modify it
	else
	{
		// get the turbo's object
		turboObj = turboThread->object;
	
		// get the turbo's instances
		turboInst1 = turboThread->inst;
		turboInst2 = turboObj->inst;
	
		// remove "dead thread" flag
		turboThread->flags &= 0xfffff7ff;
	
		// turbo pad
		if (type & 4)
		{
			// only increase counter on the first frame of turbo pad
			
			if ((driver->actionsFlagSetPrevFrame & 0x200000) == 0)
			{
				driver->numTurbos++;
				
				#if BUILD == JpnRetail
				// the japanese version of the game keeps track of your highest turbo chain in a race
				if (driver->numTurbosHighScore < driver->numTurbos && (gGT->gameMode1 & END_OF_RACE) == 0) driver->numTurbosHighScore = driver->numTurbos;
				#endif
			}
		}
	
		// all other boosts
		else
		{
			// make fire invisible for the sake of the visibility cooldown as explained in common.h
			turboInst1->flags |= 0x1000080;
			turboInst2->flags |= 0x1000080;
	
			turboObj->fireVisibilityCooldown = 0x60;
			driver->numTurbos++;
			#if BUILD == JpnRetail
			// the japanese version of the game keeps track of your highest turbo chain in a race
			if (driver->numTurbosHighScore < driver->numTurbos && (gGT->gameMode1 & END_OF_RACE) == 0) driver->numTurbosHighScore = driver->numTurbos;
			#endif
		}
	
		turboObj->fireDisappearCountdown = 0xff;
		turboInst1->alphaScale = 0;
		turboInst2->alphaScale = 0;
	
		// driver -> instance -> thread -> modelIndex == "player" of any kind
		if(isPlayer)
		{
			if
			(
				// if racer is not getting an Outside turbo (turbo pad or powerup), 
				// this prevents audio-spam from multiple boosts  
				((driver->actionsFlagSet & 0x200000) == 0) ||
				((driver->actionsFlagSetPrevFrame & 0x200000) == 0)
			)
			
			{
				turboObj->fireAudioDistort = 0;
				VehFire_Audio(driver, fireLevel);
			}
		}
	}

	newFireSpeedCap = 
	
		driver->const_SingleTurboSpeed +
		
		// fireLevel * 8
		(
			fireLevel * 
			
			// this can all be simplified to: 8
			(driver->const_SacredFireSpeed - driver->const_SingleTurboSpeed) >> 8
		);

	if
	(
		// any gain in boost,
		// resize to gain boost
		(
			// Reserves are equal to zero
			// OR
			// speed cap has been raised
			(driver->reserves == 0) ||
			(driver->fireSpeedCap < (short)newFireSpeedCap)
		) ||

		// OR

		// you have USF, and boosted on a non-STP,
		// resize fire to lose size
		(
			// Current speed cap is at USF
			// AND
			// You are not on a super turbo pad
			(0x6400 <= driver->fireSpeedCap) &&
			((driver->stepFlagSet & 2) == 0)
		)
	)
	
	{
		driver->fireSpeedCap = (short)newFireSpeedCap;

		if (turboObj != 0)
		{
			// modify, cap, and save the size of the fire
			newFireSize = (fireLevel >> 6) + 5;
			if (newFireSize > 8) newFireSize = 8;
			turboObj->fireSize = (short)newFireSize;
		}
	}

	// boost powerup
	if (type & 8)
	{
		//turn on 14th bit of Actions Flag set (means racer is driving against a wall)
		driver->actionsFlagSet |= 0x200;
	}

	// super engine
	if (type & 0x10)
	{
		// set reserves to reserves parameter instead of incrementing
		if (driver->reserves < reserves)
		{
			driver->reserves = reserves;
		}
	}

	// startline, hang time, powerslide
	else if (!(type & 1))
	{
		// increase reserves BY param2
		driver->reserves += reserves;
	}
	
	// turbo pad, boost powerup
	else
	{
		// this adds reserves on the first frame you touch the turbo pad,
		// then prevent reserves from decreasing until the first frame 
		// you leave the turbo pad
		
		oldOTT = driver->turbo_outsideTimer;
		
		if (oldOTT < reserves)
		{
			driver->turbo_outsideTimer += 	(reserves - oldOTT);
			driver->reserves += 			(reserves - oldOTT);
		}
	}

	// if modelIndex == "player" of any kind
	if (!isPlayer) return;
	
    // CameraDC flag
    gGT->cameraDC[driver->driverID].flags |= 0x80;

    // gamepad vibration
    GAMEPAD_ShockForce1(driver, 8, 127);
	
}
