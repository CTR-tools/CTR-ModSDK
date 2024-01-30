#include <common.h>

void DECOMP_StartLine_Update(void)
{
	char i;
	u_char bVar1;
	int iVar2;
	u_char lapCounter;
	int iVar4;
	struct Driver *firstRank;
	struct Driver *currDriver;
	int distToFinish_prev;
	int distToFinish_curr;
	int minDistance;
	int iVar9;
	int iVar10;
	int currRank;
	int iVar13;
	struct GameTracker *gGT = sdata->gGT;

	currRank = 0;
	iVar13 = 0;

	// get the highest-ranked player,
	// store that in puVar5 (pointer)

	for (i = 0; i < 8; i++)
	{
		firstRank = gGT->driversInRaceOrder[i];

		// If this driver pointer is not nullptr
		// If this is a human and not AI
		if ((firstRank != 0) && ((firstRank->actionsFlagSet & 0x100000) == 0))
			break;
	}

	// counter for loop iteration
	i = 0;

	// variable is used for multple things,
	// at beginning and end of the loop
	// it is 4 * iVar10
	iVar9 = 0;

	do
	{
		// iVar6 = driver struct
		currDriver = gGT->drivers[i];

		// set 1st place racer to no one
		gGT->driversInRaceOrder[i] = NULL;

		// if driver exists
		if (currDriver != NULL)
		{
			distToFinish_prev = currDriver->distanceToFinish_curr;

			Driver_UpdateLapProgress(currDriver);

			distToFinish_curr = currDriver->distanceToFinish_curr;

			int drivenBackwards = currDriver->distanceDrivenBackwards + (distToFinish_curr - distToFinish_prev);

			// If racer's distance driven backwards is negative
			// (means racer is driving forwards)
			if (drivenBackwards < 0)
			{
				// Set racer's distance driven backwards to zero, so it's not negative
				drivenBackwards = 0;
			}
			// if racer has distance driven backwards > 1000 units
			else if (1000 < drivenBackwards)
			{
				// This prevents racer from going having negative laps
				// Set maximum drive backwards value to 1000
				drivenBackwards = 1000;
			}

			// update distance driven backwards
			currDriver->distanceDrivenBackwards = drivenBackwards;

			// if player just finished lap

			// if distance to finish was low last frame
			if ((distToFinish_prev < 1200) &&

				// now suddenly high
				(32000 < distToFinish_curr))
			{
				// Set racer's distance driven backwards to zero
				currDriver->distanceDrivenBackwards = 0;

				// if racer was driving behind the finish lap
				if ((currDriver->actionsFlagSet & 0x1000000) != 0)
				{
					// turn off 25th flag of actions flag set (means player crossed the start line backwards)
					// racer is not driving backwards through the start line anymore
					currDriver->actionsFlagSet &= (0x1000000);
					// skip next 46 lines of code
					goto LAB_800418b4;
				}

				// update checkpoint with distToFinish
				currDriver->distanceToFinish_checkpoint = distToFinish_curr;

				// if numLaps < lapIndex+1
				// If this is final lap
				if (gGT->numLaps < (currDriver->lapIndex + 1))
				{
				setLapCounter:
					lapCounter = currDriver->lapIndex;
				}

				// if this is not final lap
				else
				{
					// If you're in Arcade, or
					// If you're in Adventure, or
					// If you're in Time Trial
					if (((gGT->gameMode1 & 0x4a0000) != 0) &&

						// AND

						// driver -> instance -> thread -> modelIndex == "player" of any kind
						(currDriver->instSelf->thread->modelIndex == DYNAMIC_PLAYER))
					{
						// Save Lap Time
						UI_SaveLapTime(
							// Lap Counter
							currDriver->lapIndex,

							// time on clock - lap time
							gGT->elapsedEventTime - currDriver->lapTime,

							// Player / AI structure + 0x4a shows driver index (0-7)
							currDriver->driverID);

						// Keep track of each lap time for time trial or relic race

						// lap counter
						gGT->lapTime[currDriver->lapIndex] =

							// time on clock - lap time
							gGT->elapsedEventTime - currDriver->lapTime;
					}

					// time on the clock
					currDriver->lapTime = gGT->elapsedEventTime;

					// lap counter = lap counter + 1
					currDriver->lapIndex++;

					// if player is highest ranked player
					if (currDriver == firstRank)
					{
						OtherFX_Play(0x66, 1);
						Voiceline_ClearTimeStamp();
					}

					lapCounter = currDriver->lapIndex;

					// if driver lap == last lap of race
					if (lapCounter == (gGT->numLaps - 1))
					{
						// if this is human and not AI
						if ((currDriver->actionsFlagSet & 0x100000) == 0)
						{
							// frames, so the animation lasts 3 seconds
							sdata->finalLapTextTimer[i] = FPS_DOUBLE(90);
						}
						goto setLapCounter;
					}
				}

				// if driver lap is not equal to numLaps
				// this is true any time finish line is crossed,
				// except for crossing finish at end of final lap
				if (lapCounter != gGT->numLaps)
					goto LAB_800418b4;

				// if racer hadn't finished the race
				if ((currDriver->actionsFlagSet & 0x2000000) == 0)
				{
					// this one racer has now finished the race
					currDriver->actionsFlagSet |= 0x2000000;

					// === Run on first frame that race ends ===

					// if total event hasn't finished (gGT->gameMode1)
					if ((gGT->gameMode1 & 0x200000) == 0)
					{
						// set driver placement rank, based on
						// how many drivers have finished the race
						currDriver->driverRank = sdata->numPlayersFinishedRace;
						sdata->numPlayersFinishedRace++;
					}

					// you have no weapon
					currDriver->heldItemID = 0xf;

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
							gGT->tileView[driverID].fadeFromBlack_currentValue = 0x1fff;
							gGT->tileView[driverID].fadeFromBlack_desiredResult = 0x1000;
							gGT->tileView[driverID].fade_step = 0xff78;
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
				// if player crossed finish line backwards

				// if distToFinish_curr is low
				if ((distToFinish_curr < 1200) &&

					// if distToFinish_prev is high
					(32000 < distToFinish_prev))
				{
					// automatic backwards penalty
					currDriver->distanceDrivenBackwards = 600;

					// turn on 25th bit of Actions Flag set (means racer crossed start line backwards)
					currDriver->actionsFlagSet |= 0x1000000;
				}

				// if player did not JUST cross finish backwards
				else
				{

					// if player did not EVER cross finish backwards
					if (((currDriver->actionsFlagSet & 0x1000000) == 0) &&

						// if distance driven this frame is less than...
						((currDriver->distanceToFinish_checkpoint - distToFinish_curr) <=

						// level's distant to finish
						(gGT->level1->ptr_restart_points->distToFinish >> 2) << 3))
					{
						// save distance for next frame
						currDriver->distanceToFinish_checkpoint = distToFinish_curr;
					}
				}
			LAB_800418b4:
				// if racer hasn't finished the race
				if ((currDriver->actionsFlagSet & 0x2000000) == 0)
				{
					// set racer's place in race to -1
					currDriver->driverRank = -1;

					// skip next 5 lines of code
					goto LAB_80041910;
				}
			}

			if (currDriver->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
			{
				iVar13 = iVar13 + 1;
			}

			// increase your rank in the race, someone passed you
			char newRank = currDriver->driverRank + 1;

			if (currRank < newRank)
			{
				currRank = newRank;
			}
		}

	LAB_80041910:

		// if you're done looping from 0 - 7
		// for all 8 drivers on the track

		if (7 < iVar10)
		{
			for (currRank; currRank < 8; currRank++)
			{
				// set "min" distance to max
				minDistance = 0x3fffffff;

				// index of driver closest to finish line
				iVar2 = -1;

				iVar9 = -10;

				for (iVar10 = 0; iVar10 < 8; iVar10++)
				{
					// get current driver
					currDriver = gGT->drivers[iVar10];

					if (((currDriver != 0) &&

						 // AND

						 (currDriver->driverRank == -1)) &&

						// AND

						((iVar4 = currDriver->lapIndex - (currDriver->actionsFlagSet & 0x1000000),

						  iVar9 < iVar4 ||

							  // OR

							  ((iVar4 == iVar9 &&

								// AND

								// Compare distToFinish < min
								(currDriver->distanceToFinish_curr < minDistance))))))
					{
						// set new min distToFinish
						currDriver = currDriver->distanceToFinish_curr;

						iVar9 = iVar4;

						// index of driver closest to finish
						iVar2 = iVar10;
					}
				}

				if (iVar2 != -1)
				{
					// If traffic lights run out
					if (gGT->trafficLightsTimer < 1)
					{
						gGT->drivers[iVar2]->driverRank = currRank;
					}

					// if traffic lights >= 1
					else
					{
						// set every driver position rank,
						// to the order that they spawn on the starting line
						gGT->drivers[iVar2]->driverRank = sdata->kartSpawnOrderArray[iVar2];
						gGT->humanPlayerPositions[iVar2] = sdata->kartSpawnOrderArray[iVar2];
					}
				}
			}

			for (currRank = 0; currRank < 8; currRank++)
			{
				// get pointer to each player structure
				currDriver = gGT->drivers[currRank];

				if ((currDriver != 0) &&

					// AND

					(-1 < currDriver->driverRank))
				{
					gGT->driversInRaceOrder[currDriver->driverRank] = currDriver;
				}
			}

			u_char numPlyr = gGT->numPlyrCurrGame;

			// if numPlyrCurrGame is not zero
			if (numPlyr != 0)
			{

				for (currRank = 0; currRank < numPlyr; currRank++)
				{
					// pointer to each player structure
					currDriver = gGT->drivers[currRank];

					// if player structure is not nullptr
					if (currDriver != NULL)
					{
						u_char currRank = currDriver->driverRank;

						if (((-1 < currRank) &&

							 // AND

							 // if time on the clock is not low
							 (0x4b00 < gGT->elapsedEventTime)) &&

							// AND

							// Compare <
							(gGT->humanPlayerPositions[0] < currRank))
						{
							// Make driver talk
							Voiceline_RequestPlay(8, data.characterIDs[currDriver->driverID], 0x10);
						}
						gGT->humanPlayerPositions[0] = currRank;
					}
				}
			}

			// If not in end-of-race menu
			if ((gGT->gameMode1 & END_OF_RACE) == 0)
			{
				// Check if race should end
				if (((numPlyr == 1 && 0 < iVar13) || (((numPlyr - 1) <= iVar13) &&
					
					(1 < numPlyr && (gGT->gameMode1 & ARCADE_MODE) == 0))) ||

					((gGT->gameMode1 & ARCADE_MODE) != 0 && numPlyr <= iVar13))
				{

					// End race for all drivers
					for (currRank = 0; currRank < 8; currRank++)
					{
						// Get address of each player structure
						currDriver = gGT->drivers[currRank];

						// If player structure is not nullptr and racer hadn't finished the race
						if (currDriver != NULL && (currDriver->actionsFlagSet & 0x2000000) == 0)
						{
							// End the race for this player
							currDriver->actionsFlagSet |= 0x2000000;

							// This block executes one time

							// Set weapon to none
							currDriver->heldItemID = 0xf;

							// If this is a human and not AI
							if ((currDriver->actionsFlagSet & 0x100000) == 0)
							{
								// In VS mode, this is what blows up the player in last place

								// Make the player Blasted
								Player_ChangeState(currDriver, 2, currDriver, 0);

								// Reduce counters for AttackingPlayer and AttackedByPlayer
								currDriver->numTimesAttackedByPlayer--;
								currDriver->numTimesAttackingPlayer--;
							}
						}
					}
					MainGameEnd_Initialize();
				}
			}
			return;
		}
	} while (true);
}
