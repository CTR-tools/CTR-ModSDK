#include <common.h>

u_int TitleFlag_IsFullyOffScreen();

void DECOMP_UI_CupStandings_UpdateCupRanks(void)
{
  // Too many variables, many reused registers
  // same variable names used for different purposes
  struct GameTracker * gGT;
  char wonCup;
  short sVar1;
  u_short uVar2;
  short sVar5;
  short byteIndex;
  int i;
  int titleFlag;
  int framesPassed;
  int cupOffset;
  int addPts;
  int cupTrack;
  int difficulty;
  int local_90;
  u_int uVar6;
  short sVar7;
  u_int uVar8;
  short uVar9;
  int iVar10;
  char * format;
  short puvar11;
  int iVar12;
  int * points;
  int * ranks;
  short uVar14;
  int iVar15;
  short * puVar16;
  int numDrivers;
  short sVar18;
  u_short local_80;
  u_short local_7e;
  short local_7c;
  short local_7a;
  char acStack120[8];
  char acStack112[24];
  u_short local_58;
  u_short local_56;
  short local_50;
  short local_4c;
  short local_48;
  short local_44;
  short local_40;
  short local_3c;
  short local_38;
  short local_30;

  gGT = sdata->gGT;

  numDrivers = gGT->numPlyrCurrGame + gGT->numBotsCurrGame;
  
  titleFlag = TitleFlag_IsFullyOffScreen();

    // if numPlyrCurrGame is not 1
      // if this is a multiplayer game
  if (gGT -> numPlyrCurrGame != 1

    // title checkered flag is not on screen
    &&
    titleFlag == 1) {
    // If you are in Arcade or VS cup
    if (gGT -> gameMode2 & 0x10) {
      // checkered flag, begin transition on-screen
      TitleFlag_BeginTransition(1);
    }
    // enable checkered flag
    TitleFlag_SetCanDraw(1);
  }

  if (
    // if fully on screen
    (titleFlag == 0) ||

    // If numPlyrCurrGame is 1
    (gGT -> numPlyrCurrGame == 1)
  ) {
    // if flag is fully on screen, and this is multiplayer
    if (gGT -> numPlyrCurrGame != 1) {
      // disable loading screen,
      // set amount of confetti to zero
      gGT -> confetti.numParticles_max = 0;
      gGT -> confetti.unk2 = 0;
      gGT -> renderFlags &= 0x1000;
    }

    if ((sdata -> framesSinceRaceEnded < 0xf0) || (((sdata -> menuReadyToPass & 8) != 0 && (sdata -> framesSinceRaceEnded < 400)))) {
      sdata -> framesSinceRaceEnded++;
    }
  }

  if ((sdata->framesSinceRaceEnded < 0x3c) &&

    // If you press Cross or Circle
    ((sdata->AnyPlayerTap & 0x50) != 0)
  ) {
    sdata->framesSinceRaceEnded = 0x3c;

    // Save the number of drivers
    sdata->numIconsEOR = gGT->numPlyrCurrGame + gGT->numBotsCurrGame;

    // clear gamepad input (for menus)
    MenuBox_ClearInput();
  }
  if ((sdata->menuReadyToPass & 4) == 0) {
    local_38 = -0x32;
    local_30 = 0x1e;
  } else {
    local_38 = 0x1e;
    local_30 = -0x32;
  }
  if (sdata->framesSinceRaceEnded < 0xf1) {
    uVar9 = 0xffffff6a;
    uVar14 = 0x100;
    local_90 = 0x1e;
    iVar12 = (int) local_38;
    framesPassed = sdata->framesSinceRaceEnded;
  } else {
    uVar9 = 0x100;
    iVar12 = 0x1e;
    uVar14 = 0x296;
    local_90 = (int) local_30;
    framesPassed = sdata->framesSinceRaceEnded + -0xf0;
  }

  // Interpolate variables from the previous "if-statement"
  UI_Lerp2D_Linear(&local_58, uVar9, iVar12, uVar14, local_90, framesPassed, 0x14);

  if ((sdata->menuReadyToPass & 4) == 0) {
    // Level ID
    sVar18 = (data.metaDataLEV[gGT->levelID].name_LNG);
  } else {
    // If this is the last track in a cup
    if (gGT->cup.trackIndex == 3) {
      // FINAL
      uVar9 = (sdata->lngStrings[0x8b8]);
      goto LAB_80056678;
    }

    // If you are not in Arcade or VS cup
    if ((gGT->gameMode2 & 0x10) == 0) {
      // adv cup name LNG index
      puvar11 = &data.AdvCups[0].lngIndex_CupName;

      // each is 8 bytes apart
      cupOffset = gGT->cup.cupID << 3;
    }

    // If you are not in Arcade or VS cup
    else {
      // arcade cup name LNG index
      puvar11 = &data.AdvCups[0].lngIndex_CupName;

      // each is 0x12 (18) bytes apart
      cupOffset = gGT->cup.cupID * 0x12;
    }

    // get final lang index
    sVar18 = (puvar11[cupOffset]);
  }

  // get pointer to name from lng
  uVar9 = (int)sdata->lngStrings[sVar18];

  LAB_80056678:

    // title text
    DecalFont_DrawLine(uVar9, (int)(short) local_58, (int)((u_int) local_56 - 0x11), 1,
      0xffff8000);

  // sdata->lngStrings[0x328
  // STANDINGS
  DecalFont_DrawLine((sdata->lngStrings[0x328]), (int)(short) local_58, (int)(short) local_56, 1,
    0xffff8000);

  // TRACK 1/4, 2/4, 3/4, 4/4
  sprintf(acStack112, "%s %ld/4",

    // sdata->lngStrings[0x5d4
    // TRACK
    (sdata->lngStrings[0x5d4]),

    // Track Index (0, 1, 2, 3) + 1
    (gGT->cup.trackIndex + 1));

  DecalFont_DrawLine(acStack112, (int)(short) local_58, (int)((u_int) local_56 + 0x11), 2, 0xffff8000);

  if ((sdata->framesSinceRaceEnded == (sdata->framesSinceRaceEnded / 10) * 10) 
  && (sdata->numIconsEOR < numDrivers)) {
    sdata->numIconsEOR++;
  }

  if (0 < sdata->numIconsEOR) {
    sVar18 = 0;
    for (i = 0; i < sdata->numIconsEOR;i++)
    {
      sVar5 = (short)i;
      // If you are in Purple Gem Cup
      if (gGT->cup.cupID == 4) {
        if (i < 5) {
          uVar9 = 0x60;
          sVar7 = gGT->tileView->rect.x;
          sVar5 = (short)(((int) gGT->tileView->rect.w + -0x20) / 5) * sVar5 + 0x10;
          goto LAB_800568d4;
        }
        sVar7 = 0;
        uVar9 = 0;
      }

      // If this is not Purple Gem Cup
      else {

        // Basically, if you're in 2P Arcade
        if (numDrivers == 6) {
          uVar9 = 0x42;
          if (i < 3) {
            sVar7 = gGT->tileView->rect.x;
            sVar5 = (short)((int) gGT->tileView->rect.w + -0x80 >> 2) * sVar5 + 0x20;
          } else {
            sVar1 = gGT->tileView->rect.w;
            sVar5 = sVar5 + -2;
            LAB_800568b8:
              uVar9 = 0x79;
            sVar7 = gGT->tileView->rect.x;
            sVar5 = (short)((int) sVar1 + -0x80 >> 2) * sVar5 + 0x60;
          }
        }

        // If you are not in 2P Arcade
        else {

          // If number of AIs is zero
          if (gGT->numBotsCurrGame == 0) {
            uVar9 = 0x6c;
            sVar7 = gGT->tileView->rect.x + (short)(((int) gGT->tileView->rect.w + var1 * -0x5a + 0xc) / 2) + sVar18;
            goto LAB_800568d8;
          }
          uVar9 = 0x42;
          if (3 < i) {
            sVar1 = gGT->tileView->rect.w;
            sVar5 = sVar5 + -4;
            goto LAB_800568b8;
          }
          sVar7 = gGT->tileView->rect.x;
          sVar5 = (short)((int) gGT->tileView->rect.w + -0x80 >> 2) * sVar5 + 0x20;
        }
        LAB_800568d4:
          sVar7 = sVar7 + sVar5;
      }
      LAB_800568d8:
        if (sdata->framesSinceRaceEnded < 0xf1) {
          iVar10 = 0x296;
          iVar15 = (int) sVar7;
          framesPassed = sdata->framesSinceRaceEnded + (i + var2) * -2;
        }
      else {
        iVar10 = (int) sVar7;
        iVar15 = -0x96;
        framesPassed = sdata->framesSinceRaceEnded + -0xf0;
      }

      // Interpolate fly-in variables over 0x14 frames
      UI_Lerp2D_Linear(& local_58, iVar10, uVar9, iVar15, uVar9, iVar12, 0x14);

      // %d
      sprintf(acStack120, & sdata->s_int, titleFlag + 1);

      DecalFont_DrawLine(acStack120, (int)((u_int) local_58 + 0x20), (int)((u_int) local_56 - 1), 2, 3);

      // If this is the first screen of cup standings,
      // where you see just amount of points added
      if ((sdata->menuReadyToPass & 4) == 0) {
        // get driver in order of race rank (for one track)
        iVar12 = gGT->driversInRaceOrder[i];
      }

      // if this is not the first page,
      // so now you see total points of drivers
      else {
        // get driver in order of cup rank (for collection of tracks)
        iVar12 = (gGT->drivers[(int) data.cupPositionPerPlayer[i]]);
      }

      // Draw character icon
      UI_DrawDriverIcon(
        (gGT +
          ((int)((u_int)
            ( & data.MetaDataCharacters->iconID +

              // Player / AI structure + 0x4a shows driver index (0-7)

              // character ID
              (int)(short) data.characterIDs[(iVar12 + 0x4a)] * 0x10) <<
            0x10) >> 0xe) + 0x1eec), (int)(short) local_58, (int)(short) local_56,

        // pointer to PrimMem struct
        &
        gGT->backBuffer->primMem,

        // pointer to OT memory
        gGT->tileView->ptrOT,

        1, 0x1000, 0x808080);

      // If this is the first screen of cup standings,
      // where you see just amount of points added
      if ((sdata->menuReadyToPass & 4) == 0) {
        // If number of AIs is zero
        if (gGT->numBotsCurrGame == 0) {

          // amount of points to add is based on how
          // many players are in the race, and race position
          // numPlyrCurrGame - [unknown]
          iVar12 = gGT->numPlyrCurrGame - (titleFlag + 1);
        }

        // if there are AIs
        else {
          // amount of points to add is based on array
          // 9, 6, 3, 1, 0, 0, 0, 0
          iVar12 = data.cupPointsPerPosition[i];
        }
        format = & sdata->s_additionInt;
      }

      // if this is not the first page,
      // so now you see total points of drivers
      else {
        // The amount of points that each player has, in a cup
        iVar12 = (gGT->cup.points[data.cupPositionPerPlayer[i]]);

        // "%ld"
        format = & sdata->s_longInt;
      }
      // make a string to draw, based on above variables
      sprintf(acStack120, format, iVar12);

      sVar18 = sVar18 + 0x5a;

      // draw string for number of points
      DecalFont_DrawLine(acStack120, (int)((u_int) local_58 + 0x2d),
        (int)((u_int) local_56 + 6), 1, 1);
    }
  }

  // If this is the first screen of cup standings,
  // where you see just amount of points added
  if ((sdata->menuReadyToPass & 4) == 0) {
    // fly-in interpolation
    UI_Lerp2D_Linear(&local_58, 0xfffffff6, (int) local_38, 0xfffffff6, 9, sdata->framesSinceRaceEnded, 0x14);
  }

  // if it's not...
  else {
    if (sdata->framesSinceRaceEnded < 0xf1) {
      local_58 = 0xfff6;
      local_56 = 9;
    } else {
      // fly-in interpolation
      UI_Lerp2D_Linear(&local_58, 0xfffffff6, 9, 0xfffffff6, (int) local_30, sdata->framesSinceRaceEnded + -0xf0, 0x14);
    }
  }
  local_7c = 0x214;
  local_7a = 0x32;
  local_80 = local_58;
  local_7e = local_56;

  // Draw 2D Menu rectangle background
  FUN_800457b0(&local_80, 4, gGT->backBuffer->otMem.startPlusFour);

  // Timer
  if (sdata->framesSinceRaceEnded < 0x10f) {
    if (
      (
        // Timer
        (0x3b < sdata->framesSinceRaceEnded) &&

        // If you are not in overall Cup standings
        ((sdata->menuReadyToPass & 8) == 0)
      ) &&
      (
        // sdata->lngStrings[0x324
        // PRESS * TO CONTINUE
        DecalFont_DrawLine(sdata->lngStrings[0x324], 0x100, 0xbe, 1, 0xffff8000),

        // If you press Cross or Circle
        (sdata->AnyPlayerTap & 0x50) != 0)
    ) {
      // Timer
      sdata->framesSinceRaceEnded = 0xf0;

      // Proceed from Track standings to overall Cup standings,
      // where you see how many points each driver has overall
      sdata->menuReadyToPass = sdata->menuReadyToPass | 8;

      // clear gamepad input (for menus)
      MenuBox_ClearInput();
    }
  } else {
    sdata->numIconsEOR = 1;
    sdata->framesSinceRaceEnded = 0;
    uVar6 = sdata->menuReadyToPass & 0xfffffff6;
    uVar8 = sdata->menuReadyToPass & 4;

    // Proceed from end-of-race menu to Track Standings,
    // where you see how many points are added just for this race
    sdata->menuReadyToPass = uVar6 | 4;

    // If the "4" flag was not enabled till just now,
    // If this is the first frame of Track Standings
    if (uVar8 == 0) {
      // Add points awarded from Track Standings to Cup Standings

      // If number of AIs is zero (VS cup)
      if (gGT->numBotsCurrGame == 0) {

        // if numPlyrCurrGame != 0
        if (gGT->numPlyrCurrGame != 0) {
          titleFlag = 0;

          for (i = 0; i < gGT->numPlyrCurrGame; i++) {

            // the amount of points this player has in the cup
            gGT->cup.points[gGT->driversInRaceOrder[i]->driverID] =
              gGT->cup.points[gGT->driversInRaceOrder[i]->driverID] +

              // Incremented by
              // numPlyrCurrGame - rank
              gGT->numPlyrCurrGame - i;

          }
        }
      }

      // If there are AIs (Arcade cup)
      else {

        // Array of ints that holds the amount of
        // points that should be awarded for each position
        // {9, 6, 3, 1, 0, 0, 0, 0}
        points = &data.cupPointsPerPosition;

        // wont break when you have 6 drivers
        // in 2P Arcade Cup

        for (i = 0; i < 8; i++) {
          // get value at this array index
          addPts = points[i];

          // the amount of points this player has in the cup
          gGT->cup.points[gGT->driversInRaceOrder[i]->driverID] =
            gGT->cup.points[gGT->driversInRaceOrder[i]->driverID] +

            // Incremented by
            // The amount of points that should be awarded to each position
            addPts;

        }

      }

      // update cup rank of all drivers
      UI_CupStandings_UpdateCupRanks();
    }

    // If this is not the first frame of track standings
    else {
      sdata->menuReadyToPass = uVar6;

      // enable drawing HUD
      gGT->hudFlags |= 1;

      // Disable types of HUD that are not needed for gameplay,
      // This includes Cup rankings, which is a flag in this byte
      gGT->hudFlags &= 0xfb;

      sdata->menuReadyToPass = sdata->menuReadyToPass & 0xfffffffb;

      // Increment Track Number by 1 (0-3 in the cup)
      cupTrack = gGT->cup.trackIndex + 1;

      // If this is not the last race in the cup
      if (cupTrack < 4) {
        // If this is an Adventure Cup
        if ((gGT->gameMode2 & 0x10) == 0) {
          // Load the next LEV, given cup ID (0-3) and track index of cup (0-3)
          MainRaceTrack_RequestLoad((int)(data.advCupTrackIDs + numDrivers * 4 + gGT->cup.cupID * 0x10));
        }

        // If this is not an Adventure Cup
        else {
          // Load the next LEV, given cup ID (0-3) and track index of cup (0-3)
          MainRaceTrack_RequestLoad((int)(data.ArcadeCups->CupTrack->trackID + numDrivers * 4 + gGT->cup.cupID * 0x12));
        }
      }

      // If this was the last race in the cup
      // If the cup is over
      else {
        cupTrack = 0;

        // If this is an Adventure Cup
        if ((gGT->gameMode2 & 0x10) == 0) {
          // Array with the ranking of each player
          ranks = & data.cupPositionPerPlayer; // Set Level ID
          gGT->levelID = gGT->cup.cupID + 100;

          // Set Track Index of Cup to 0, for the start of the next cup
          gGT->cup.trackIndex = 0;

          // when loading is done,
          // remove flag for adventure cup
          sdata->Loading.OnBegin.RemBitsConfig0 |= 0x10000000;

          // Loop through 8 drivers, clear all data for next cup

          for (i = 0; i < 8; i++) {
            // If driver is not nullptr
            if (gGT->drivers[ranks[i]] != 0) {
              // Set final ranking of each player
              gGT->drivers[ranks[i]]->driverRank = (short) i;
            }

            // set driver's cup score to zero
            gGT->cup.points[i] = 0;
          }
          Tawna_Init(gGT);

          // If player 1 won the cup
          if (data.cupPositionPerPlayer[0] == gGT->drivers[0]->driverID) {
            // bit offst 0x6a is where the gems start in the bits of Adventure Progress

            // If this cup has never been beaten before (if you dont have the gem)
            // 0x8fba4 is where the adventure profile (currently loaded) begins
            if (((u_int) sdata->advProgress.rewards[(int)(gGT->cup.cupID + 0x6aU) >> 5] >>
                (gGT->cup.cupID + 0x6aU & 0x1f) & 1) == 0) {
              // Set podium reward model to Gem
              gGT->podiumRewardID = 0x5f;

              // bit offset of non-adventure progress to unlock character,
              // plus cupID
              uVar6 = gGT->cup.cupID + 7;

              // get index of integer array for this bit
              numDrivers = (int) uVar6 >> 5;

              // 4 bytes of rewards (characters + tracks)
              // This unlocks Roo, Papu, Joe, Pinstripe, or Fake Crash
              sdata->gameProgress.unlocks[i] |= 1 << (uVar6 & 0x1f);

              // bit offset of adventure progress to unlock gem
              // plus cupID
              uVar6 = gGT->cup.cupID + 0x6a;

              // 0x8fba4 is where the adventure profile (currently loaded) begins
              // Unlocks one of the gems
              sdata->advProgress.rewards[(int) uVar6 >> 5] =
                sdata->advProgress.rewards[(int) uVar6 >> 5] | 1 << (uVar6 & 0x1f);
            }

            // track index 0,1,2,3
            // reset counter for number of times you lost cup, to zero
            sdata->advProgress.timesLostCupRace[gGT->cup.trackIndex] = 0;
          }

          // If player 1 did not win the cup
          else {
            // track index 0,1,2,3
            numDrivers = gGT->cup.trackIndex;

            // if you lost the cup less than 10 times
            if ((char) sdata->advProgress.timesLostCupRace[i] < 10) {
              // increase number of times you lost the cup
              sdata->advProgress.timesLostCupRace[i]++;
            }
          }

          // Level ID for Gemstone Valley (podiums)
          MainRaceTrack_RequestLoad(0x19);
        }

        // If this is not an Adventure Cup
        else {
          // Set Track Index of Cup to 0, for the start of the next cup
          gGT->cup.trackIndex = 0;

          UI_CupStandings_FinalizeCupRanks();

          // Array with the final ranking of each player
          ranks = &data.cupPositionPerPlayer;
          for (i = 0; i < 8; i++) {
            // If driver is not nullptr
            if ((gGT->drivers[ranks[i]]) != 0) {
              // Set final ranking of each player
              ((gGT->drivers[ranks[i]])->driverRank) = (short) i;
            }

            // set driver's cup score to zero
            gGT->cup.points[i] = 0;
          }

          // Tawna_Init
          Tawna_Init(gGT);

          // If Player 1 or Player 2 won the cup
          if (((gGT->drivers[0]->driverRank) == 0) ||
            (((gGT->drivers[1]->driverRank) == 0)) &&

            // If you're in Arcade Mode
            ((gGT->gameMode1 & ARCADE_MODE) != 0)) {
            // If P1 or P2 lost the cup, or if this was VS mode,
            // then nothing would unlock

            // You deserve to have something unlocked.
            wonCup = true;

            // If Arcade difficulty is "Easy"
            if (gGT->arcadeDifficulty == 0x50) {
              difficulty = 0;
            }

            // if difficulty is not easy
            else {
              // If Arcade difficulty is "Hard"
              difficulty = 2;

              // If Arcade difficulty is "Medium"
              if (gGT->arcadeDifficulty == 0xa0) {
                difficulty = 1;
              }
            }

            // Bit index of cup completion (curr),
            // one index per difficulty
            // [0] (easy) = 0xC
            // [1] (medium) = 0x10
            // [2] (hard) = 0x14
            local_50 = sdata->UnlockBitIndex.CupCompletion_curr[0];
            local_4c = sdata->UnlockBitIndex.CupCompletion_curr[2];

            // Bit index of cup completion (prev),
            // one index per difficulty
            // [0] (easy) = 0xC
            // [1] (medium) = 0x10
            // [2] (hard) = 0x14
            local_48 = sdata->UnlockBitIndex.CupCompletion_prev[0];
            local_44 = sdata->UnlockBitIndex.CupCompletion_prev[2];

            // Bit index of Battle Track Unlock
            // [0] (easy) = 0xC
            // [1] (medium) = 0x10
            // [2] (hard) = 0x14
            local_40 = sdata->UnlockBitIndex.UnlockBattleMap[0];
            local_3c = sdata->UnlockBitIndex.CupCompletion_curr[2];

            // get base index
            puVar16 = ((int) & local_50 + difficulty * 2);

            // add cupID to bit
            uVar6 = (int)puVar16[gGT->cup.cupID];

            // byte index
            byteIndex = (int) uVar6 >> 5;

            // Save record that this cup, on this difficulty, was won
            sdata->gameProgress.unlocks[byteIndex] |= 1 << uVar6;

            // bit index of cup completion on this difficulty (prior to now)
            uVar6 = (int)((int) & local_48 + difficulty * 2) + gGT->cup.cupID;

            // If this cup was not previuosly beaten on this difficulty,
            // and this is the first time the cup was won
            if ((sdata->gameProgress.unlocks[byteIndex] >> uVar6 & 1) == 0) {

              // gGT->0x8 | 0x1000,
              // lets 233 know to prompt the Save Game box
              gGT->gameMode2 |= 0x1000;

              // bit index of cup completion (curr)
              uVar8 = SEXT24(puVar16);
              uVar6 = uVar8;

              // loop through all 4 cups to see if they've all
              // been beaten on the current cup difficulty

              for (i = 0; i < 4; i++) {

                // if any of four cups on this difficulty was not won
                if ((sdata->gameProgress.unlocks[uVar6 >> 5] >> uVar6 & 1) == 0) {
                  // you dont deserve to unlock a battle map
                  wonCup = false;
                  break;
                }
                uVar6 = uVar8 + i;
              }
              while (i < 4);

              // If P1 or P2 won an Arcade Cup, and if you haven't unlocked
              // a battle map for this difficulty, and if you've beaten all
              // four Arcade cups on this difficulty
              if (wonCup) {
                // Get bit index of battle map unlock
                uVar2 = ((int) & local_40 + difficulty * 2);
                difficulty = (int)((u_int) uVar2 << 0x10) >> 0x15;

                // Unlock a Battle Map (Parking Lot, North Bowl, Parking Lot)
                sdata->gameProgress.unlocks[difficulty] = sdata->gameProgress.unlocks[difficulty] | 1 << (uVar2 & 0x1f);

                // gGT->0x8 | 0x2000
                // battle map is now unlocked (233 overlay)
                gGT->gameMode2 |= 0x2000;
              }
            }
          }

          // Set podium's reward model to "Empty"
          gGT->podiumRewardID = 0x38;

          // Level ID for Gemstone Valley (podiums)
          MainRaceTrack_RequestLoad(0x19);
        }
      }
    }
  }
  return;
}