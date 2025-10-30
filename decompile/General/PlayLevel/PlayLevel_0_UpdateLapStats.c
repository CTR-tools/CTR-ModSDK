#include <common.h>

#ifdef USE_ONLINE

// online can be fragmented
#define HANDLE_NULL_DRIVER continue

#else

// unmodded wont be fragmented
#define HANDLE_NULL_DRIVER break

#endif

void DECOMP_PlayLevel_UpdateLapStats(void)
{
	int driverID_closestToFinish;
	u_char lapCounter;
	short lapIndex;
	short prevLapIndex;
	struct Driver *firstRank;
	struct Driver *currDriver;
	int distToFinish_prev;
	int distToFinish_curr;
	int minDistance;
	char i;
	int numDriversFinished;
	int currRank;
	struct GameTracker *gGT = sdata->gGT;

	prevLapIndex = 0;
	numDriversFinished = 0;
	currRank = 0;
	
	// driver pointer,
	// unlike other "rank" index variables
	firstRank = NULL;

	// find farthest-ahead human
	for (i= 0; i < 8; i++)
	{
		currDriver = gGT->driversInRaceOrder[i];

		if ((currDriver != NULL) && ((currDriver->actionsFlagSet & 0x100000) == 0))
		{
			firstRank = currDriver;
			break;
		}
	}

	#ifdef USE_ONLINE
	firstRank = gGT->drivers[0];
	#endif

	for(i = 0; i < 8; i++)
	{
		gGT->driversInRaceOrder[i] = NULL;

		// iVar6 = driver struct
		currDriver = gGT->drivers[i];

		if (currDriver == NULL)
			HANDLE_NULL_DRIVER;

		// before and after
		distToFinish_prev = currDriver->distanceToFinish_curr;
		VehLap_UpdateProgress(currDriver);
		distToFinish_curr = currDriver->distanceToFinish_curr;

		int drivenBackwards = currDriver->distanceDrivenBackwards + (distToFinish_curr - distToFinish_prev);

		// clamp minimum
		if (drivenBackwards < 0)
			drivenBackwards = 0;

		// clamp to max
		else if (drivenBackwards > 1000)
			drivenBackwards = 1000;

		// update distance driven backwards
		currDriver->distanceDrivenBackwards = drivenBackwards;

		// === Natty Video ===
		// https://www.youtube.com/watch?v=lDaT2rY6GKI

		// Part A: Start-line -> 32000 distToFinish
		// Part B: 32000 distToFinish -> 1200 distToFinish
		// Part C: 1200 distToFinish -> Finish-line

		if (
				// crossed finishline (forwards)
				(distToFinish_prev < 1200) &&
				(distToFinish_curr > 32000)
			)
		{
			// Set racer's distance driven backwards to zero
			currDriver->distanceDrivenBackwards = 0;

			// if driving behind startline, now not
			if ((currDriver->actionsFlagSet & 0x1000000) != 0)
			{
				currDriver->actionsFlagSet &= ~(0x1000000);

				// skip next 46 lines of code
				goto LAB_800418b4;
			}

			// update checkpoint with distToFinish
			currDriver->distanceToFinish_checkpoint = distToFinish_curr;

			#ifdef USE_ONLINE
			if (i == 0)
			{
				int currLapSaveIndex = currDriver->lapIndex % 2;
				currDriver->currLapTime = gGT->elapsedEventTime - currDriver->lapTime;
				if (currDriver->currLapTime < currDriver->bestLapTime)
				{
					currDriver->bestLapTime = currDriver->currLapTime;
				}
			}
			#endif

			// If finished last lap, clamp
			if (gGT->numLaps < (currDriver->lapIndex + 1))
			{
				lapCounter = currDriver->lapIndex;
			}

			// if this is not final lap
			else
			{
				#ifndef USE_ONLINE
				if (
		
						((gGT->gameMode1 & (ARCADE_MODE | ADVENTURE_MODE | TIME_TRIAL)) != 0) &&

						//player of any kind
						(currDriver->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
					)
				{
					DECOMP_UI_SaveLapTime(
						currDriver->lapIndex,
						gGT->elapsedEventTime - currDriver->lapTime,
						currDriver->driverID);


					gGT->lapTime[currDriver->lapIndex] =
						gGT->elapsedEventTime - currDriver->lapTime;
				}
				#endif

				// time on the clock
				currDriver->lapTime = gGT->elapsedEventTime;

				// lap counter = lap counter + 1
				currDriver->lapIndex++;

				// if farthest-ahead human
				if (currDriver == firstRank)
				{
					OtherFX_Play(0x66, 1);
					Voiceline_ClearTimeStamp();
				}

				lapCounter = currDriver->lapIndex;

				// If Final Lap
				if (lapCounter == (gGT->numLaps - 1))
				{
					// if this is human and not AI
					if ((currDriver->actionsFlagSet & 0x100000) == 0)
					{
						#ifdef USE_ONLINE
						if(currDriver->driverID == 0)
						#endif

							// frames, so the animation lasts 3 seconds
							sdata->finalLapTextTimer[i] = FPS_DOUBLE(90);
					}
				}
			}

			// If did not just finish race
			if (lapCounter != gGT->numLaps)
				goto LAB_800418b4;

			// === If did just finish race ===

			// if racer hadn't finished the race
			if ((currDriver->actionsFlagSet & 0x2000000) == 0)
			{
				// this one racer has now finished the race
				currDriver->actionsFlagSet |= 0x2000000;

				// === Run on first frame that race ends ===

				// if total event hasn't finished (gGT->gameMode1)
				if ((gGT->gameMode1 & END_OF_RACE) == 0)
				{
					// set driver placement rank, based on
					// how many drivers have finished the race
					currDriver->driverRank = sdata->numPlayersFinishedRace;
					sdata->numPlayersFinishedRace++;
				}

				// you have no weapon
				currDriver->heldItemID = 0xf;

				#ifdef USE_ONLINE
				if(currDriver->driverID == 0)
				#endif

				// If this is human and not AI
				if ((currDriver->actionsFlagSet & 0x100000) == 0)
				{
					// If this racer is in first place
					if (currDriver->driverRank == 0)
					{
						// amount of confetti particles
						gGT->confetti.numParticles_max = 250;
						gGT->confetti.unk2 = 250;

						// one person won,
						// one person gets confetti
						gGT->numWinners = 1;

						char driverID = currDriver->driverID;

						// add driver ID to array of confetti winners
						gGT->winnerIndex[0] = driverID;

						// edit window variables for confetti
						gGT->pushBuffer[driverID].fadeFromBlack_currentValue = 0x1fff;
						gGT->pushBuffer[driverID].fadeFromBlack_desiredResult = 0x1000;
						gGT->pushBuffer[driverID].fade_step = 0xff78;
					}
					if (currDriver->noItemTimer != 0)
					{
						currDriver->noItemTimer = 0;
						currDriver->heldItemID = 0xf;
					}

					// turn driver into robotcar
					BOTS_Driver_Convert(currDriver);
				}
				goto LAB_800418b4;
			}
		}

		// if player did not just finish a lap (correctly)
		else
		{
			if (
					// crossed startline backwards
					(distToFinish_curr < 1200) &&
					(distToFinish_prev > 32000)
				)
			{
				// automatic backwards penalty
				currDriver->distanceDrivenBackwards = 600;
				currDriver->actionsFlagSet |= 0x1000000;
			}

			// if player did not JUST cross finish backwards
			else
			{
				unsigned int trackLen =
					gGT->level1->ptr_restart_points[0].distToFinish;

				if (
					// if player did not EVER cross finish backwards
					((currDriver->actionsFlagSet & 0x1000000) == 0) &&

					(
						// if distance driven this frame is less than...
						(currDriver->distanceToFinish_checkpoint - distToFinish_curr) <=

						// level's distance to finish
						((trackLen >> 2) << 3)
					)
				   )
				{
					// save distance for next frame
					currDriver->distanceToFinish_checkpoint = distToFinish_curr;
				}
			}

		LAB_800418b4:
			// if racer hasn't finished the race
			if ((currDriver->actionsFlagSet & 0x2000000) == 0)
			{
				// set rank to "unsorted"
				currDriver->driverRank = -1;

				// skip next 5 lines of code
				continue;
			}
		}

		// === Driver Finished Race ===

		if (currDriver->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
		{
			// count humans to finish race
			numDriversFinished++;
		}

		// increase your rank in the race, someone passed you
		char newRank = currDriver->driverRank + 1;

		// get human in last
		if (currRank < newRank)
		{
			currRank = newRank;
		}
	}

	#ifdef USE_ONLINE
	int numDead1 = 0;
	int numSpawn = 0;
	#endif

	// sort all drivers that have NOT finished race
	for (currRank; currRank < 8; currRank++)
	{
		#ifdef USE_ONLINE
		if(gGT->drivers[currRank] == NULL)
			numDead1++;
		#endif

		if(gGT->drivers[currRank] == NULL)
			HANDLE_NULL_DRIVER;

		// set "min" distance to max
		minDistance = 0x3fffffff;

		// set "highest" lap to min
		driverID_closestToFinish = -1;

		// lap index
		prevLapIndex = -10;

		// look for "next" farthest driver,
		// out of all unsorted drivers remaining
		for (i = 0; i < 8; i++)
		{
			// get current driver
			currDriver = gGT->drivers[i];

			if(currDriver == NULL)
				HANDLE_NULL_DRIVER;

			if(currDriver->driverRank != -1)
				continue;

			// driver lap index
			lapIndex = currDriver->lapIndex;

			// if drive backwards behind startline
			if((currDriver->actionsFlagSet & 0x1000000) != 0)
				lapIndex -= 1;

			if (
					// new highest lap
					(lapIndex > prevLapIndex) ||

					// OR

					(
						// same lap
						(prevLapIndex == lapIndex) &&

						// AND

						// new lowest distance (max progress)
						(currDriver->distanceToFinish_curr < (unsigned int)minDistance)
					)
				)
			{
				// set new min distToFinish (max progress)
				minDistance = currDriver->distanceToFinish_curr;

				// highest lap
				prevLapIndex = lapIndex;

				// index of driver closest to finish
				driverID_closestToFinish = i;
			}
		}

		if (driverID_closestToFinish != -1)
		{
			// If traffic lights run out
			if (gGT->trafficLightsTimer <= SECONDS(0))
			{
				gGT->drivers[driverID_closestToFinish]->driverRank = currRank;

				#ifdef USE_ONLINE
				gGT->drivers[driverID_closestToFinish]->driverRank -= numDead1;
				#endif
			}

			// if traffic lights >= 1
			else
			{
				#ifdef USE_ONLINE

				// This is broken, sometimes a hole will appear between
				// the icons at the startline, if someone disconnects,
				// nobody knows why, but screw it
				gGT->drivers[driverID_closestToFinish]->driverRank = numSpawn;
				gGT->humanPlayerPositions[driverID_closestToFinish-numDead1] = numSpawn;
				numSpawn++;

				#else

				// set every driver position rank,
				// to the order that they spawn on the starting line
				gGT->drivers[driverID_closestToFinish]->driverRank = sdata->kartSpawnOrderArray[driverID_closestToFinish];
				gGT->humanPlayerPositions[driverID_closestToFinish] = sdata->kartSpawnOrderArray[driverID_closestToFinish];

				#endif
			}
		}
	}

	for (i = 0; i < 8; i++)
	{
		// get pointer to each player structure
		currDriver = gGT->drivers[i];

		if(currDriver == NULL)
			HANDLE_NULL_DRIVER;

		// should be impossible to be -1 here
		if(currDriver->driverRank > -1)
		{
			gGT->driversInRaceOrder[currDriver->driverRank] = currDriver;
		}
	}

	for (i = 0; i < gGT->numPlyrCurrGame; i++)
	{
		// pointer to each player structure
		currDriver = gGT->drivers[i];

		if (currDriver == NULL)
			HANDLE_NULL_DRIVER;

		int currRank = currDriver->driverRank;

		if (
				(-1 < currRank) &&
				(0x4b00 < gGT->elapsedEventTime) &&
				(gGT->humanPlayerPositions[i] < currRank)
			)
		{
			int characterID =
				data.characterIDs[gGT->driversInRaceOrder[currRank-1]->driverID];

			// Make driver talk
			Voiceline_RequestPlay(8, characterID, 0x10);
		}
		gGT->humanPlayerPositions[i] = currRank;
	}

	// If already finished race
	if ((gGT->gameMode1 & END_OF_RACE) != 0)
		return;

	#ifdef USE_ONLINE
	if((gGT->drivers[0]->actionsFlagSet & 0x2000000) != 0)
	{
		MainGameEnd_Initialize();
	}
	return;
	#else

	int numPlyr = gGT->numPlyrCurrGame;

	// Check if race should end
	if (
		(
			// 1P game, with 1 human finished
			(numPlyr == 1) &&
			(numDriversFinished > 0)

		) ||

		(
			// Multiplayer VS, all finished except one
			(numPlyr > 1) &&
			((gGT->gameMode1 & ARCADE_MODE) == 0) &&
			(numDriversFinished >= (numPlyr - 1))
		) ||

		(
			// Arcade mode, all humans finished
			((gGT->gameMode1 & ARCADE_MODE) != 0) &&
			(numPlyr <= numDriversFinished)
		)
	   )
	{
		// End race for all drivers
		for (currRank = 0; currRank < 8; currRank++)
		{
			// Get address of each player structure
			currDriver = gGT->drivers[currRank];

			if(currDriver == NULL)
				HANDLE_NULL_DRIVER;

			// if driver already finished race
			if((currDriver->actionsFlagSet & 0x2000000) != 0)
				continue;

			// End the race for this player
			currDriver->actionsFlagSet |= 0x2000000;

			// remove weapon
			currDriver->heldItemID = 0xf;

			// skip AIs
			if ((currDriver->actionsFlagSet & 0x100000) != 0)
				continue;

			// === VS Mode ===

			// Make the player Blasted
			VehPickState_NewState(currDriver, 2, currDriver, 0);

			// Reduce counters for AttackingPlayer and AttackedByPlayer
			currDriver->numTimesAttackedByPlayer[currDriver->driverID]--;
			currDriver->numTimesAttackingPlayer[currDriver->driverID]--;

		}

		MainGameEnd_Initialize();
	}
	#endif
}
