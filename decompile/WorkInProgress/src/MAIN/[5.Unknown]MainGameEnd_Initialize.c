#include <common.h>

void MainGameEnd_Initialize(void)
{
  char *pbVar1;
  int *piVar2;
  int iVar3;
  short sVar5;
  int iVar6;
  u_int *puVar7;
  int iVar8;
  u_int gameMode1;
  int iVar11;
  int iVar12;
  u_int uVar14;
  int rank;
  u_int teamIndex;
  u_int uVar17;
  int i;
  u_int local_38;
  u_int local_34;
  struct Driver* player;
  struct Driver* driver;
  struct Thread* t;

  struct GameTracker *gGT = sdata->gGT;

  player = gGT->drivers[0];

  gameMode1 = gGT->gameMode1;

  // If you're not in End-Of-Race menu,
  // then enable End-Of-Race menu
  if ((gameMode1 & END_OF_RACE) == 0)
  {
    for (i = 0; i < 8; i++)
    {
      driver = gGT->drivers[i];
      // pointer to address of all 8 player structures,
      // if each structure is not nullptr
      if (driver != NULL)
      {
        // spawn player in position of next race, depending on
        // rank in current race (1st place, 2nd place, etc)
        sdata->kartSpawnOrderArray[i] = driver->driverRank;
      }
    }

    gGT->newHighScoreIndex = 0xff;

    // If you're drawing Weapon Roulette (randomizing)
    if ((gameMode1 & ROLLING_ITEM) != 0)
    {
      // stop weapon shuffle sound
      OtherFX_Stop2(0x5d);

      // disable randomizing effect in HUD
      gGT->gameMode1 &= ~(ROLLING_ITEM);
    }
    // Trophy, CTR Challenge, Crystal, Boss

    // If not in Adventure cup and not in Relic,
    // but you are in Adventure Mode
    if ((gameMode1 & (ADVENTURE_CUP | RELIC_RACE | ADVENTURE_MODE)) == ADVENTURE_MODE)
    {

      // If player is in 1st place
      if (player->driverRank == 0)
      {
        // If this is boss race
        if ((int)gameMode1 < 0)
        {
          sdata->advProgress.timesLostBossRace[gGT->bossID] = 0;
        }

        // if this is not boss race
        else
        {
          // Level ID
          sdata->advProgress.timesLostRacePerLev[gGT->levelID] = 0;
        }
      }

      // if player is not in 1st place
      else
      {
        // if this is boss race
        if ((int)gameMode1 < 0)
        {
          i = gGT->bossID + 0x17;
        }

        // if this is not boss race
        else
        {
          // Level ID
          i = gGT->levelID;
        }

        // if number of times lost is less than 10
        if (sdata->advProgress.timesLostRacePerLev[i] < 10)
        {
          // increment number of times lost
          sdata->advProgress.timesLostRacePerLev[i]++;
        }
      }
    }

    // Enable End-Of-Race menu
    gameMode1 = gGT->gameMode1;

    gGT->gameMode1 |= END_OF_RACE;

    gGT->unknownFlags_1d44 = gameMode1 & 0x3e0020 | END_OF_RACE;

    // If you are not in Battle Mode
    if ((gameMode1 & BATTLE_MODE) == 0)
    {
      // if not zero screens
      if (gGT->numPlyrCurrGame != 0)
      {
        for (i = 0; i < gGT->numPlyrCurrGame; i++)
        {
          driver = gGT->drivers[i];
          // if racer is in the top 3 positions of the race (1st, 2nd, 3rd)
          if (driver->driverRank < 3)
          {
            // all this, is just to increment one value by 1

            // The code here in Versus Standings looks
            // like the code use in Battle Standings

            // Get the rank that the player finished in VS (1st, 2nd, 3rd)
            // Then get the number of times this player has finished in this rank,
            // then increment that number
            gGT->standingsPoints[i * driver->driverRank]
          }
        }
      }
      // if in battle mode
      else
      {
        // if not point limit
        if ((gameMode1 & POINT_LIMIT) == 0)
        {
          // if time limit
          if ((gameMode1 & TIME_LIMIT) != 0)
          {
            local_38 = sdata->unk_RaceWheelConfig[1];
            local_34 = sdata->unk_RaceWheelConfig[2];

            for (i = 0; i < 4; i++)
            {
              sVar5 = -400;
              driver = gGT->drivers[i];
              for (teamIndex = 4; teamIndex > 0; teamIndex--)
              {
                // pointer to each player structure, plus offset
                if (driver->BattleHUD.numLives != 0)
                {
                  // pointer to each player structure, plus offset
                  if ((driver->BattleHUD.numLives == sVar5) &&
                      (((uVar17 & 0xff) >> (teamIndex & 1) == 0)))
                  {
                    *(short *)((int)&local_38 + ((iVar12 + 1) >> 2)) = teamIndex;
                    uVar17 |= 1 << teamIndex;
                  }
                  else
                  {
                    // pointer to each player structure, plus offset
                    if ((sVar5 <= driver->BattleHUD.numLives) &&
                        (((uVar17 & 0xff) >> teamIndex & 1) == 0))
                    {
                      // pointer to each player structure, plus offset
                      sVar5 = driver->BattleHUD.numLives;
                      iVar12++;
                      puVar7 = &local_38;
                      if (0 < iVar12)
                      {
                        for (iVar11 = 0 ; iVar11 < iVar12; iVar11++)
                        {
                          if (puVar7[0] != 0xffffffff)
                          {
                            uVar17 &= ~(1 << puVar7[0]);
                          }
                          puVar7 = (u_int *)((int)puVar7 + 2);
                        } while (iVar11 < iVar12);
                      }
                      iVar12 = 0;

                      // Battle Team that the player is on
                      uVar17 |= 1 << (gGT->drivers[i]->BattleHUD.teamID & 0x1f);

                      // Battle Team that the player is on
                      local_38 &= 0xffff0000 | gGT->drivers[i]->BattleHUD.teamID;
                    }
                  }
                }
              } 

              sVar5 = (short)iVar12;
              if (((short)local_38 != -1) && (iVar12 = 0, 0 < (int)sVar5 + 1))
              {
                puVar7 = &local_38;
                do
                {
                  // based on battle team, increment gGT Standing Points by 1,
                  // determine how many times driver finished with each rank (1st 2nd 3rd 4th)
                  *(int *)(gGT + i * 4 + *(int *)(*(int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec) + 0x4e8) * 0xc + standingsPoints) =
                      *(int *)(gGT + i * 4 + *(int *)(*(int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec) + 0x4e8) * 0xc + standingsPoints) + 1;

                  if (
                      (i == 0) &&

                      // address of each player structure
                      (*(int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec) != 0))
                  {
                    // set next winner index in the array of winners, this ID will get confetti
                    *(u_int *)(gGT + gGT->numWinners * 4 + winnerIndex) =

                        // address of each player structure
                        (u_int) * (char *)(*(int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec) + 0x4a);

                    // Edit gGT offsets 0x17a, 0x17c, 0x17e
                    // = PushBuffer offsets 0x12, 0x14, 0x16

                    // current fade = flash white
                    *(undefined2 *)(gGT +
                                    *(int *)(gGT + gGT->numWinners * 4 + winnerIndex) * 0x110 + 0x17a) =
                        0x1fff;

                    // desired fade = neutral
                    *(undefined2 *)(gGT +
                                    *(int *)(gGT + gGT->numWinners * 4 + winnerIndex) * 0x110 + 0x17c) =
                        0x1000;

                    // fade step is negative, to move downward
                    *(undefined2 *)(gGT +
                                    *(int *)(gGT + gGT->numWinners * 4 + winnerIndex) * 0x110 + 0x17e) =
                        0xff78;

                    // turn driver into Robotcar
                    BOTS_Driver_Convert(*(u_int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec));

                    // increment number of winners,
                    // more people get confetti
                    gGT->numWinners++;
                  }

                  // amount of confetti particles
                  gGT->numParticles = 0xfa;
                  gGT->confetti.unk2 = 0xfa;

                  // save the rank that the driver (or team) finished this event
                  *(int *)(gGT + (int)*(short *)puVar7 * 4 + 0x1da8) = i;

                  // numPlyrCurrGame
                  pbVar1 = gGT + 0x1ca8;

                  // loop iteration counter
                  uVar14 = 0;

                  // if numPlyrCurrGame is not zero
                  if (*pbVar1 != 0)
                  {
                    // address of each player structure
                    piVar2 = (int *)(gGT + (int)*(short *)puVar7 * 4 + 0x24ec);

                    // for uVar14 = 0; uVar14 < numPlyrCurrGame; uVar14++
                    do
                    {
                      // If two players are on the same team
                      if (*(int *)(*(int *)(gGT + 0x24ec) + 0x4e8) == *(int *)(*piVar2 + 0x4e8))
                      {
                        gameMode1 = gameMode1 | 1 << (uVar14 & 0x1f);
                      }

                      // increment loop iteration counter
                      uVar14 = uVar14 + 1;

                      // increment pointer
                      gGT = gGT + 4;

                    } while ((int)uVar14 < (int)(u_int)*pbVar1);
                  }
                  iVar12 = iVar12 + 1;
                  puVar7 = (u_int *)((int)puVar7 + 2);
                } while (iVar12 < (int)sVar5 + 1);
              }
              local_38 = CONCAT22(local_38._2_2_, 0xffff);
              i = i + sVar5 + 1;
            }
          }
        }
        // if point limit
        else
        {
          local_38 = sdata->unk_RaceWheelConfig[1];
          local_34 = sdata->unk_RaceWheelConfig[2];
          for (i = 0; i < 4; i++)
          {
            sVar5 = -400;
            iVar12 = 0;
            for (teamIndex = 4; teamIndex > 0;teamIndex--)
            {
              // if points on battle team == highest num points
              if ((gGT->battleSetup.pointsPerTeam[teamIndex] == sVar5) &&
                  (((uVar17 & 0xff) >> (teamIndex & 0x1f) & 1U) == 0))
              {
                // there is a tie
                iVar12++;
                *(short *)((int)&local_38 + (iVar12 >> 1)) = teamIndex;

              LAB_8003a71c:
                uVar17 |= 1 << (teamIndex & 0x1f);
              }
              // if not equal
              else
              {
                // points on team is more than highest score
                if (sVar5 <= (gGT->battleSetup.pointsPerTeam[teamIndex]) &&
                    (((uVar17 & 0xff) >> teamIndex & 1U) == 0))
                {
                  // set new highest score
                  sVar5 = gGT->battleSetup.pointsPerTeam[teamIndex] ;

                  // set number of winners (more than 1 if a tie)
                  iVar12++;

                  // clear previous list of winners,
                  // since we have someone with higher scores
                  puVar7 = &local_38;

                  // no Winners;
                  if (0 < iVar12)
                  {
                    for (iVar11 = 0; iVar11 < iVar12; iVar11++)
                    {
                      if (puVar7[0] != 0xffffffff)
                      {
                        uVar17 &= ~(1 << (puVar7[0] & 0x1fU));
                      }
                      puVar7 = (u_int *)((int)puVar7 + 2);
                    } 
                  }

                  // reset counter
                  iVar12 = 0;

                  // new list of winners
                  local_38 &= 0xffff0000 | teamIndex & 0xffff;

                  goto LAB_8003a71c;
                }
              }
            }

            if ((short)local_38 != -1)
            {
              iVar11 = iVar12 + 1;
              puVar7 = &local_38;
              if (0 < iVar11)
              {
                for (iVar8; iVar8 < iVar11; iVar8++)
                {
                  // save the rank that the player (or team) finished in this event
                  gGT->battleSetup.finishedRankOfEachTeam[puVar7[0]] = i;
                  puVar7 = (u_int *)((int)puVar7 + 2);
                } while (iVar8 < iVar11);
              }
            }
            local_38 = CONCAT22(local_38._2_2_, 0xffff);
          } 

          for (i = 0; i < 4; i++)
          {
            // If you are not in last place
            if (gGT->finishedRankOfEachTeam[i] != 3)
            {
              // Get Battle Team, then get rank of battle team (1st, 2nd, 3rd),
              // then get number of times this team has gotten this rank

              // Increment the number of times this team has finished in this rank

              // In "Battle Standings" You'll see "1st - xx" "2nd - xx", etc.
              // This is incrementing the "xx"

              gGT->standingsPoints[i * gGT->finishedRankOfEachTeam[i]]++;
            }

            driver = gGT->drivers[i];

            if (
                // if player structure is not nullptr
                (driver != 0) &&

                // If this player is on a team that won the battle (0 for 1st place, 1 for 2nd, etc)
                gGT->finishedRankOfEachTeam[driver->BattleHUD.teamID] == 0)
            {
              // set next winner index in the array of winners, this ID will get confetti
              gGT->winnerIndex[gGT->numWinners] =

                  // Player / AI structure + 0x4a shows driver index (0-7)
                  driver->driverID;

              gGT->pushBuffer[gGT->winnerIndex[gGT->numWinners]].fadeFromBlack_currentValue = 0x1fff;
              gGT->pushBuffer[gGT->winnerIndex[gGT->numWinners]].fadeFromBlack_desiredResult = 0x1000;
              gGT->pushBuffer[gGT->winnerIndex[gGT->numWinners]].fade_step = 0xff78;

              // turn driver into Robotcar
              BOTS_Driver_Convert(*(u_int *)(gGT + 0x24ec));

              // increment number of winners,
              // more people get confetti
              gGT->numWinners++;
            }
            // amount of confetti particles
            gGT->numParticles = 0xfa;
            gGT->confetti.unk2 = 0xfa;

          } 
        }
      }

      for (i = 0; i < 4; i++)
      {
        for (rank = 0; rank < 3; rank++)
        {
          iVar8 += gGT->standingsPoints[i * rank] * (3 - rank);
        } 
        gGT->unk_afterTeams[i] = iVar8;
      } 

      // no idea what this section is for
      for (i = 0; i < 4; i++)
      {
        sVar5 = 0;
        uVar14 = 0xffffffff;
        for (teamIndex = 4; 0 < teamIndex; teamIndex--)
        {
          if (((sVar5 <= gGT->unk_afterTeams[teamIndex]) &&

               (((uVar17 & 0xff) >> teamIndex & 1) == 0)) &&

              // if team exists
              (((gGT->battleSetup.teamFlags & 1 << teamIndex) != 0 ||

              // not in battle mode
              ((gameMode1 & BATTLE_MODE) == 0))))
          {
            sVar5 = gGT->unk_afterTeams[teamIndex];
            if (uVar14 != 0xffffffff)
            {
              uVar17  &= ~(1 << uVar14);
            }
            uVar17 |= 1 << teamIndex;
            uVar14 = teamIndex;
          }
        }
        gGT->unk1dc8[i] = uVar14;
      } 

      // pointer to first Player thread
      t = gGT->threadBuckets[PLAYER]->thread;

      // end race clock for all human players

      // if thread is valid
      while (t != NULL)
      {
        UI_RaceEnd_GetDriverClock((struct Driver*)(t->object));

        // go to next thread
        t = t->siblingThread
      }

      UI_VsQuipAssignAll();

      DECOMP_SubmitName_RestoreName(2);

      // if you are in Relic Race or Time Trial
      if ((gameMode1 & (RELIC_RACE | TIME_TRIAL)) != 0)
      {
        MainGameEnd_SoloRaceGetReward(1);

        // If you're not in a Relic Race
        if ((gameMode1 & RELIC_RACE) == 0)
        {
          if (

              // if you are not showing a ghost during a race
              (sdata->boolReplayHumanGhost == 0) ||
              ((
                  // if ghost is not too big
                  sdata->boolGhostTooBigToSave == 0 &&

                  (player->timeElapsedInRace < sdata->ptrGhostTapePlaying->timeElapsedInRace))))
          {
            GhostTape_End();

            gGT->unknownFlags_1d44 |= 1;
          }
        }
        // If you are in Relic Race
        else
        {
          RR_EndEvent_UnlockAward();
        }
      }
    }
    Podium_InitModels(gGT);
  }
}