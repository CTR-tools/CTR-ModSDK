// PlayLevel_UpdateLapStats
void FUN_800414f4(void)
{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined *puVar12;
  int iVar13;

  //puVar7 = 0x96B20
  puVar7 = PTR_DAT_8008d2ac;
  iVar11 = 0;
  iVar13 = 0;

  // loop counter
  iVar9 = 0;

  //puVar5 = 0x96B20
  puVar5 = PTR_DAT_8008d2ac;

  // get the highest-ranked player,
  // store that in puVar5 (pointer)

  // for (iVar9 = 0; iVar9 < 8; iVar9++)
  do
  {
    //iVar2 = (iVar9 + 1)th's place racer struct pointer
    iVar2 = *(int *)(puVar5 + 0x250c);

	// If this driver pointer is not nullptr
	// If this is a human and not AI
    if ((iVar2 != 0) && ((*(uint *)(iVar2 + 0x2c8) & 0x100000) == 0))	{
			break;
		}

    // increment loop counter
    iVar9 = iVar9 + 1;

    //move on to next racer
    puVar5 = puVar5 + 4;

	// clear pointer
    iVar2 = 0;

  } while (iVar9 < 8);

  // counter for loop iteration
  iVar10 = 0;

  // variable is used for multple things,
  // at beginning and end of the loop
  // it is 4 * iVar10
  iVar9 = 0;

  do
  {
    //iVar6 = driver struct
    iVar6 = *(int *)(puVar7 + iVar9 + 0x24ec);

    //set 1st place racer to no one
    *(undefined4 *)(puVar7 + iVar9 + 0x250c) = 0;

	//if driver exists
    if (iVar6 != 0)
	{
      // iVar8 = distance to finish
      iVar8 = *(int *)(iVar6 + 0x488);

      // VehLap_UpdateProgress (driver)
      FUN_8005ca24(iVar6);

      // iVar9 = distance driven backwards + (distToFinish_curr - distToFinish_prev)
      iVar9 = *(int *)(iVar6 + 0x490) + (*(int *)(iVar6 + 0x488) - iVar8);

      // update distance driven backwards
      *(int *)(iVar6 + 0x490) = iVar9;

      // If racer's distance driven backwards is negative
      // (means racer is driving forwards)
      if (iVar9 < 0)
	  {
		// Set racer's distance driven backwards to zero, so it's not negative
        *(undefined4 *)(iVar6 + 0x490) = 0;
      }

      // if racer has distance driven backwards
      else
      {
        // If racer's distance driven backwards > 1000 units
        if (1000 < iVar9)
        {
		      // This prevents racer from going having negative laps
		      // Set maximum drive backwards value to 1000
          *(undefined4 *)(iVar6 + 0x490) = 1000;
        }
      }

	  // === Natty Video ===
	  // https://www.youtube.com/watch?v=lDaT2rY6GKI
	  
	  // Part A: Start-line -> 32000 distToFinish
	  // Part B: 32000 distToFinish -> 1200 distToFinish
	  // Part C: 1200 distToFinish -> Finish-line

	  // if player just finished lap
      if (
	       // if distance to finish was low last frame
			(iVar8 < 1200) &&

			// now suddenly high
			(32000 < *(int *)(iVar6 + 0x488))
		 )
      {
		// Set racer's distance driven backwards to zero
        *(undefined4 *)(iVar6 + 0x490) = 0;

        //if racer was driving behind the finish lap
        if ((*(uint *)(iVar6 + 0x2c8) & 0x1000000) != 0)
		    {
          //turn off 25th flag of actions flag set (means player crossed the start line backwards)
          //racer is not driving backwards through the start line anymore
          *(uint *)(iVar6 + 0x2c8) = *(uint *)(iVar6 + 0x2c8) & 0xfeffffff;
          //skip next 46 lines of code
          goto LAB_800418b4;
        }

        // update checkpoint with distToFinish
        *(undefined4 *)(iVar6 + 0x48c) = *(undefined4 *)(iVar6 + 0x488);

		// puVar7 is 8008d2ac
		// if numLaps < lapIndex+1
		// If this is final lap
        if ((int)(char)puVar7[0x1d33] < (int)((uint)*(byte *)(iVar6 + 0x44) + 1)) {
LAB_80041720:
          // uVar3 = lap counter
          uVar3 = (uint)*(byte *)(iVar6 + 0x44);
        }

		// if this is not final lap
        else
		{
          if (
				// Compare !=
				// puVar7 is 8008d2ac
				// If you're in Arcade, or
				// If you're in Adventure, or
				// If you're in Time Trial
				((*(uint *)puVar7 & 0x4a0000) != 0) &&

				// AND

				// driver -> instance -> thread -> modelIndex == "player" of any kind
				(*(short *)(*(int *)(*(int *)(iVar6 + 0x1c) + 0x6c) + 0x44) == 0x18)
			)
		  {
			// Save Lap Time
            FUN_8004c55c(
							// Lap Counter
							(uint)*(byte *)(iVar6 + 0x44),

							// puVar7 is 8008d2ac

							// time on clock - lap time
							*(int *)(puVar7 + 0x1d10) - *(int *)(iVar6 + 0x40),

							// Player / AI structure + 0x4a shows driver index (0-7)
							(uint)*(byte *)(iVar6 + 0x4a)
						);

			// Keep track of each lap time for time trial or relic race

											// lap counter
            *(int *)(puVar7 + (uint)*(byte *)(iVar6 + 0x44) * 4 + 0x1d14) =

				// time on clock - lap time
                 *(int *)(puVar7 + 0x1d10) - *(int *)(iVar6 + 0x40);
          }

											// time on the clock
          *(undefined4 *)(iVar6 + 0x40) = *(undefined4 *)(puVar7 + 0x1d10);

		  // lap counter = lap counter + 1
          *(char *)(iVar6 + 0x44) = *(char *)(iVar6 + 0x44) + '\x01';

		  // if player is highest ranked player
          if (iVar6 == iVar2)
		  {
			// OtherFX_Play for finishing lap
            FUN_80028468(0x66,1);

			// Voiceline_ClearTimeStamp
            FUN_8002caa8();
          }

          // uVar3 = lap counter
          uVar3 = (uint)*(byte *)(iVar6 + 0x44);

		  // if driver lap == last lap of race
		  if (uVar3 == (int)(char)PTR_DAT_8008d2ac[0x1d33] - 1U)
		  {
            // if this is human and not AI
            if ((*(uint *)(iVar6 + 0x2c8) & 0x100000) == 0)
			{
			  // set "Final Lap" timer to 0x5a (90)
			  // frames, so the animation lasts 3 seconds
              (&DAT_8008d2a0)[iVar10] = 0x5a;
            }
            goto LAB_80041720;
          }
        }

		// if driver lap is not equal to numLaps
		//		this is true any time finish line is crossed,
		//		except for crossing finish at end of final lap
        if (uVar3 != (int)(char)puVar7[0x1d33]) goto LAB_800418b4;

        //if racer hadn't finished the race
        if ((*(uint *)(iVar6 + 0x2c8) & 0x2000000) == 0)
        {
          // this one racer has now finished the race
          *(uint *)(iVar6 + 0x2c8) = *(uint *)(iVar6 + 0x2c8) | 0x2000000;
		  
		  // === Run on first frame that race ends ===
		  
		  // if total event hasn't finished (gGT->gameMode1)
          if ((*(uint *)puVar7 & 0x200000) == 0)
		  {
			// set driver placement rank, based on
			// how many drivers have finished the race
            *(short *)(iVar6 + 0x482) = DAT_8008d2aa;
            DAT_8008d2aa = DAT_8008d2aa + 1;
          }

		  // you have no weapon
          *(undefined *)(iVar6 + 0x36) = 0xf;

		  // If this is human and not AI
          if ((*(uint *)(iVar6 + 0x2c8) & 0x100000) == 0)
		  {
			// If this racer is in first place
            if (*(short *)(iVar6 + 0x482) == 0)
			{
			  // amount of confetti particles
              *(undefined2 *)(puVar7 + 0x1b04) = 0xfa;
              *(undefined2 *)(puVar7 + 0x1b06) = 0xfa;

			  // Player / AI structure + 0x4a shows driver index (0-7)
              bVar1 = *(byte *)(iVar6 + 0x4a);

			  // add driver ID to array of confetti winners
              *(uint *)(puVar7 + 0x2558) = (uint)bVar1;

			  // one person won,
			  // one person gets confetti
              *(undefined4 *)(puVar7 + 0x2568) = 1;

			  // edit window variables for confetti
			  *(undefined2 *)(puVar7 + (uint)bVar1 * 0x110 + 0x17a) = 0x1fff;
              *(undefined2 *)(puVar7 + *(int *)(puVar7 + 0x2558) * 0x110 + 0x17c) = 0x1000;
              *(undefined2 *)(puVar7 + *(int *)(puVar7 + 0x2558) * 0x110 + 0x17e) = 0xff78;
            }
            if (*(short *)(iVar6 + 0x3c) != 0) {
              *(undefined2 *)(iVar6 + 0x3c) = 0;
              *(undefined *)(iVar6 + 0x36) = 0xf;
            }

			// turn driver into robotcar
            FUN_80017318(iVar6);
          }
          goto LAB_800418b4;
        }
      }

      // if player did not just finish a lap (correctly)
      else
	  {
		// if player crossed finish line backwards
        if (
				// if distToFinish_curr is low
				(*(int *)(iVar6 + 0x488) < 0x4b0) &&

				// if distToFinish_prev is high
				(32000 < iVar8)
			)
		{
		  // automatic backwards penalty
          *(undefined4 *)(iVar6 + 0x490) = 600;

          //turn on 25th bit of Actions Flag set (means racer crossed start line backwards)
          *(uint *)(iVar6 + 0x2c8) = *(uint *)(iVar6 + 0x2c8) | 0x1000000;
        }

        // if player did not JUST cross finish backwards
        else {

          // if player did not EVER cross finish backwards
          if (((*(uint *)(iVar6 + 0x2c8) & 0x1000000) == 0) &&

			// if distance driven this frame is less than...
			((uint)(*(int *)(iVar6 + 0x48c) - *(int *)(iVar6 + 0x488)) <=

										//puVar7 is 8008d2ac (0x96B20)
            (uint)(*(ushort *)(*(int *)(*(int *)(puVar7 + 0x160) + 0x14c) + 6) >> 2) << 3))
		  {
			// save distance for next frame
            *(int *)(iVar6 + 0x48c) = *(int *)(iVar6 + 0x488);
          }
        }
LAB_800418b4:
        //if racer hasn't finished the race
        if ((*(uint *)(iVar6 + 0x2c8) & 0x2000000) == 0)
        {
          //set racer's place in race to -1
          *(undefined2 *)(iVar6 + 0x482) = 0xffff;

          //skip next 5 lines of code
          goto LAB_80041910;
        }
      }

	  // driver -> instance -> thread -> modelIndex == "player" of any kind
      if (*(short *)(*(int *)(*(int *)(iVar6 + 0x1c) + 0x6c) + 0x44) == 0x18)
	  {
        iVar13 = iVar13 + 1;
      }

	  // increase your rank in the race, someone passed you
      iVar9 = (int)*(short *)(iVar6 + 0x482) + 1;

	  if (iVar11 < iVar9)
	  {
        iVar11 = iVar9;
      }
    }
LAB_80041910:

	// increment loop iteration counter
    iVar10 = iVar10 + 1;

	// pointer incrementation
    iVar9 = iVar10 * 4;

	// if you're done looping from 0 - 7
	// for all 8 drivers on the track

    if (7 < iVar10) {

	  while (iVar11 < 8)
	  {
		// set "min" distance to max
        iVar6 = 0x3fffffff;

		// index of driver closest to finish line
        iVar2 = -1;

        iVar9 = -10;

		// loop counter
        iVar10 = 0;

		// puVar7 is 8008d2ac
        puVar5 = puVar7;

		// for iVar10 = 0; iVar10 < 8; iVar10++
        do
		{
		  // get current driver
          iVar8 = *(int *)(puVar5 + 0x24ec);

          if (
				(
					// Compare !=
					(iVar8 != 0) &&

					// AND

					// Compare ==
					(*(short *)(iVar8 + 0x482) == -1)
				) &&

				// AND

				(
					(
						// Assignment
						iVar4 = (uint)*(byte *)(iVar8 + 0x44) - ((uint)*(byte *)(iVar8 + 0x2cb) & 1),

						// Compare <
						iVar9 < iVar4 ||

						// OR

						(
							(
								// Compare ==
								iVar4 == iVar9 &&

								// AND

								// Compare distToFinish < min
								(*(int *)(iVar8 + 0x488) < iVar6)
							)
						)
					)
			    )
			  )
		  {
			// set new min distToFinish
            iVar6 = *(int *)(iVar8 + 0x488);

            iVar9 = iVar4;

			// index of driver closest to finish
            iVar2 = iVar10;
          }

		  // increment loop counter
          iVar10 = iVar10 + 1;

          puVar5 = puVar5 + 4;
        } while (iVar10 < 8);

        if (iVar2 != -1)
		{
		  // puVar7 is 8008d2ac
		  // If traffic lights run out
          if (*(int *)(puVar7 + 0x1d0c) < 1)
		  {
            *(undefined2 *)(*(int *)(puVar7 + iVar2 * 4 + 0x24ec) + 0x482) = (short)iVar11;
          }

		  // if traffic lights >= 1
          else
		  {
			// set every driver position rank,
			// to the order that they spawn on the starting line
            *(ushort *)(*(int *)(puVar7 + iVar2 * 4 + 0x24ec) + 0x482) =
                 (ushort)(byte)(&DAT_8008d69c)[iVar2];
            puVar7[iVar2 + 0x257a] = (&DAT_8008d69c)[iVar2];
          }
        }
        iVar11 = iVar11 + 1;
      }

	  // loop iteration counter
      iVar11 = 0;

	  // set puVar5 to ptr-8d2ac
      puVar5 = puVar7;

	  // for iVar11 = 0; iVar11 < 8; iVar11++
      do
	  {
		// get pointer to each player structure
        iVar9 = *(int *)(puVar5 + 0x24ec);

		if (
				// Compare !=
				(iVar9 != 0) &&

				// AND

				// Compare <
				(-1 < (int)*(short *)(iVar9 + 0x482))
			)
		{
		  // puVar7 is 8008d2ac
          *(int *)(puVar7 + (int)*(short *)(iVar9 + 0x482) * 4 + 0x250c) = iVar9;
        }

		// increment loop counter
        iVar11 = iVar11 + 1;

		// increment pointer
        puVar5 = puVar5 + 4;

      } while (iVar11 < 8);

	  // iteration counter
      iVar11 = 0;

	  // reset both variables to ptr_8d2ac
      puVar5 = puVar7;
      puVar12 = puVar7;

	  // if numPlyrCurrGame is not zero
      if (PTR_DAT_8008d2ac[0x1ca8] != '\0') {

		// for(int iVar11 = 0; iVar11 < numPlyrCurrGame; iVar11++)
        do
		{
		  // pointer to each player structure
          iVar9 = *(int *)(puVar12 + 0x24ec);

		  // if player structure is not nullptr
          if (iVar9 != 0)
		  {
            iVar2 = (int)*(short *)(iVar9 + 0x482);

            if (
					(
						// Compare <
						(-1 < iVar2) &&


						// puVar7 is 8008d2ac

						// if time on the clock is not low
						(0x4b00 < *(int *)(puVar7 + 0x1d10))
					) &&

					// AND

					// Compare <
					((char)puVar5[0x257a] < iVar2))
			{
			  // Make driver talk
              FUN_8002cbe8(8,(int)(short)(&DAT_80086e84)
                                         [*(byte *)(*(int *)(PTR_DAT_8008d2ac +
                                                            (iVar2 + -1) * 4 + 0x250c) + 0x4a)],0x10);
            }
            puVar5[0x257a] = *(undefined *)(iVar9 + 0x482);
          }

		  // increment loop counter
          iVar11 = iVar11 + 1;

          puVar5 = puVar5 + 1;

		  // increment pointer
          puVar12 = puVar12 + 4;

							// numPlyrCurrGame
        } while (iVar11 < (int)(uint)(byte)PTR_DAT_8008d2ac[0x1ca8]);
      }

	  // puVar7 is 8008d2ac
	  // If not in end-of-race menu
      if ((*(uint *)puVar7 & 0x200000) == 0)
	  {
		// numPlyrCurrGame
        bVar1 = puVar7[0x1ca8];

		// Basically "if race should end",
		// then trigger end-of-race menu
        if (
				(
					(
						// If there is one screen
						(bVar1 == 1) &&

						// AND

						// Compare <
						(0 < iVar13)
					) ||

					// OR

					(
						(
							// Compare <=
							(int)((uint)bVar1 - 1) <= iVar13 &&

							// AND

							(
								(
									// If more than 1 player
									1 < bVar1 &&

									// AND

									// If you're not in Arcade Mode
									// puVar7 is 8008d2ac
									((*(uint *)puVar7 & 0x400000) == 0)
								)
							)
						)
					)
				) ||
				(
					(
						// puVar7 is 8008d2ac
						// If you're in Arcade Mode
						(*(uint *)puVar7 & 0x400000) != 0 &&

						// AND

						// Compare <=
						// puVar7 is 8008d2ac
						((int)(uint)(byte)puVar7[0x1ca8] <= iVar13)
					)
				)
		   )
		{
		  // loop iteration counter
          iVar11 = 0;

		  // =================
		  // end race for all drivers
		  // =================

		  // for iVar11 = 0; iVar11 < 8; iVar11++
          do
		  {
			// get address of each player structure
            iVar9 = *(int *)(puVar7 + 0x24ec);

            if (
					// if player structure is not nullptr
					(iVar9 != 0) &&

					//if racer hadn't finished the race
					((*(uint *)(iVar9 + 0x2c8) & 0x2000000) == 0))
            {
              // end the race for this player
              *(uint *)(iVar9 + 0x2c8) = *(uint *)(iVar9 + 0x2c8) | 0x2000000;

			  // This block executes one time

			  // you have no weapon
              *(undefined *)(iVar9 + 0x36) = 0xf;

			  // If this is human and not AI
              if ((*(uint *)(iVar9 + 0x2c8) & 0x100000) == 0)
			  {
				// Player / AI structure + 0x4a shows driver index (0-7)

				// In VS mode, this is what blows up the player in last place

				// Make the player Blasted
				// VehPickState_NewState
                FUN_80064568(iVar9,2,iVar9,0);

				// reduce counter for AttackingPlayer on yourself, 
				// and AttackedByPlayer, on yourself, following ChangeState Blasted
                iVar13 = iVar9 + (uint)*(byte *)(iVar9 + 0x4a);
                *(char *)(iVar13 + 0x560) = *(char *)(iVar13 + 0x560) + -1;
                iVar9 = iVar9 + (uint)*(byte *)(iVar9 + 0x4a);
                *(char *)(iVar9 + 0x50c) = *(char *)(iVar9 + 0x50c) + -1;
              }
            }

			// increment loop counter
            iVar11 = iVar11 + 1;

			// increment pointer
            puVar7 = puVar7 + 4;

          } while (iVar11 < 8);

		  // MainGameEnd_Initialize
          FUN_8003a3fc();
        }
      }
      return;
    }
  } while( true );
}
