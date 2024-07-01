#include <common.h>

void DECOMP_UI_CupStandings_InputAndDraw(void)
{
  // Too many variables, many reused registers
  // same variable names used for different purposes
  struct GameTracker * gGT;
  short sVar1;
  u_short uVar2;
  short sVar5;
  int i;
  int framesPassed;
  int local_90;
  int local_30;
  int local_38;
  u_int uVar6;
  short sVar7;
  u_int uVar8;
  short uVar9;
  int iVar10;
  int iVar12;
  int * ranks;
  short uVar14;
  int iVar15;
  int numDrivers;
  short sVar18;

  u_short local_58[2];

  gGT = sdata->gGT;

  numDrivers = gGT->numPlyrCurrGame + gGT->numBotsNextGame;

  // Multiplayer Cup Game
  if (gGT->numPlyrCurrGame != 1)
  {
	if(
		((gGT->gameMode2 & CUP_ANY_KIND) != 0) &&
		(DECOMP_RaceFlag_IsFullyOffScreen())
	  )
	{
		DECOMP_RaceFlag_BeginTransition(1);
	}

	if(!DECOMP_RaceFlag_IsFullyOnScreen())
		return;

	// Assume FullyOnScreen
	DECOMP_RaceFlag_SetCanDraw(1);

    // disable loading screen,
    // set amount of confetti to zero
    gGT -> confetti.numParticles_max = 0;
    gGT -> confetti.unk2 = 0;
    gGT -> renderFlags &= 0x1000;
  }

  // Conditions to increment frame counter
  if (
		(sdata->framesSinceRaceEnded < 0xf0) ||
		(
			(sdata->framesSinceRaceEnded < 400) &&
			((sdata->menuReadyToPass & 8) != 0)
		)
	)
  {
    sdata->framesSinceRaceEnded++;
  }

  if (
		(sdata->framesSinceRaceEnded < 60) &&

		// If you press Cross or Circle
		((sdata->AnyPlayerTap & 0x50) != 0)
	)
  {
    sdata->framesSinceRaceEnded = 60;
    sdata->numIconsEOR = numDrivers;
    DECOMP_RECTMENU_ClearInput();
  }

  if ((sdata->menuReadyToPass & 4) == 0)
  {
    local_38 = -0x32;
    local_30 = 0x1e;
  }

  else
  {
    local_38 = 0x1e;
    local_30 = -0x32;
  }

  if (sdata->framesSinceRaceEnded <= 0xf0)
  {
    uVar9 = 0xffffff6a;
    uVar14 = 0x100;
    local_90 = 0x1e;
    iVar12 = (int) local_38;
    framesPassed = sdata->framesSinceRaceEnded;
  }

  else
  {
    uVar9 = 0x100;
    iVar12 = 0x1e;
    uVar14 = 0x296;
    local_90 = (int) local_30;
    framesPassed = sdata->framesSinceRaceEnded - 0xf0;
  }

  DECOMP_UI_Lerp2D_Linear(
	&local_58[0], uVar9, iVar12,
	uVar14, local_90, framesPassed, 0x14);

  // "FINAL"
  int index = 0x22E;
  int cupID = gGT->cup.cupID;

  if ((sdata->menuReadyToPass & 4) == 0)
  {
    // Level ID
    index = data.metaDataLEV[gGT->levelID].name_LNG;
  }

  else if (gGT->cup.trackIndex != 3)
  {
  	// If not in Arcade or VS cup
  	if ((gGT->gameMode2 & 0x10) == 0)
  	{
  		index = data.AdvCups[cupID].lngIndex_CupName;
  	}

  	// If Arcade or VS cup
  	else
  	{
  		index = data.ArcadeCups[cupID].lngIndex_CupName;
  	}
  }

  // title text
  DECOMP_DecalFont_DrawLine(
	sdata->lngStrings[index],
	local_58[0], local_58[1]-0x11,
	1, 0xffff8000);

  // STANDINGS
  DECOMP_DecalFont_DrawLine(
	sdata->lngStrings[0xCA],
	local_58[0], local_58[1],
	1, 0xffff8000);

  // 24 characters, in case of other
  // languages with longer text
  char text[24];

  // TRACK 1/4, 2/4, 3/4, 4/4
  sprintf(text, "%s %ld/4",

    // TRACK
    sdata->lngStrings[0x175],

    // Track Index (0, 1, 2, 3) + 1
    gGT->cup.trackIndex + 1);

  DECOMP_DecalFont_DrawLine(
	text,
	local_58[0], local_58[1]+0x11,
	2, 0xffff8000);

  if (
		(sdata->framesSinceRaceEnded == (sdata->framesSinceRaceEnded / 10) * 10)
		&& (sdata->numIconsEOR < numDrivers)
	)
  {
    sdata->numIconsEOR++;
  }

  // OPTIMIZATION, replace all pushBuffer RECT values
  //struct PushBuffer* pb = &gGT->pushBuffer[0];
  int rectX = 0;
  int rectW = 0x200;

  // OPTIMIZATION,
  // better way of dealing with points

  // Race with no AIs (9,6,3,1)
  int* points = &data.cupPointsPerPosition[0];

  // If VS cup (not purple gem, or adv/arcade)
  if (numDrivers <= 4)
  {
  	// 3,2,1,0
  	points = &points[4+(4-numDrivers)];
  }

    sVar18 = 0;
    for (i = 0; i < sdata->numIconsEOR;i++)
    {
      sVar5 = (short)i;
      // If you are in Purple Gem Cup
      if (gGT->cup.cupID == 4) {
        if (i < 5) {
          uVar9 = 0x60;
          sVar7 = rectX;
          sVar5 = (short)((rectW + -0x20) / 5) * sVar5 + 0x10;
          goto LAB_800568d4;
        }
        sVar7 = 0;
        uVar9 = 0;
      }

      // If this is not Purple Gem Cup
      else {

        // Basically, if you're in 2P Arcade
        if (numDrivers == 6)
		{
          uVar9 = 0x42;

		  if (i < 3) {
            sVar7 = rectX;
            sVar5 = 0x60 * sVar5 + 0x20;
          }

		  else {
            sVar5 = sVar5 + -2;

			LAB_800568b8:
              uVar9 = 0x79;

            sVar7 = rectX;
            sVar5 = 0x60 * sVar5 + 0x60;
          }
        }

        // If you are not in 2P Arcade
        else {

          // If VS cup of any kind
          if (gGT->numBotsNextGame == 0)
		  {
            uVar9 = 0x6c;
            sVar7 = rectX + (short)((rectW - (numDrivers * 0x5a) + 0xc) / 2) + sVar18;
            goto LAB_800568d8;
          }

		  uVar9 = 0x42;
          if (3 < i) {
            sVar1 = rectW;
            sVar5 = sVar5 + -4;
            goto LAB_800568b8;
          }

		  sVar7 = rectX;
          sVar5 = 0x60 * sVar5 + 0x20;
        }

		LAB_800568d4:
          sVar7 = sVar7 + sVar5;
      }

	  LAB_800568d8:

	  if (sdata->framesSinceRaceEnded <= 0xf0)
	  {
        iVar10 = 0x296;
        iVar15 = (int) sVar7;
        framesPassed = sdata->framesSinceRaceEnded - (i*10);
      }

	  else {
        iVar10 = (int) sVar7;
        iVar15 = -0x96;
        framesPassed = sdata->framesSinceRaceEnded + -0xf0;
      }

      // Interpolate fly-in variables over 0x14 frames
      DECOMP_UI_Lerp2D_Linear(
		&local_58[0],
		iVar10, uVar9,
		iVar15, uVar9,
		framesPassed, 0x14);

      // %d
      sprintf(text, &sdata->s_int, i + 1);

      DecalFont_DrawLine(
		text,
		local_58[0] + 0x20,
		local_58[1] - 1,
		2, 3);

	  struct Driver* d;

      // If this is the first screen of cup standings,
      // where you see just amount of points added
      if ((sdata->menuReadyToPass & 4) == 0) {
        // get driver in order of race rank (for one track)
        d = gGT->driversInRaceOrder[i];
      }

      // if this is not the first page,
      // so now you see total points of drivers
      else {
        // get driver in order of cup rank (for collection of tracks)
        d = gGT->drivers[data.cupPositionPerPlayer[i]];
      }

      // Draw character icon
      DECOMP_UI_DrawDriverIcon(
        gGT->ptrIcons[
          data.MetaDataCharacters[
			data.characterIDs[
				d->driverID
			]
		  ].iconID
		],

		MakePoint(local_58[0], local_58[1]),

        gGT->pushBuffer_UI.ptrOT,
        1, 0x1000, MakeColor(0x80, 0x80, 0x80));

      // If this is the first screen of cup standings,
      // where you see just amount of points added
      if ((sdata->menuReadyToPass & 4) == 0)
	  {
        iVar12 = 0;

		if(i < 4)
			iVar12 = points[i];

        *(int*)&text[0] = '+' + (('0' + iVar12)<<8);
      }

      // if this is not the first page,
      // so now you see total points of drivers
      else
	  {
        // The amount of points that each player has, in a cup
        sprintf(
			text, &sdata->s_longInt[0],
			gGT->cup.points[data.cupPositionPerPlayer[i]]);
      }

      sVar18 = sVar18 + 0x5a;

      // draw string for number of points
      DecalFont_DrawLine(
		text,
		local_58[0] + 0x2d,
		local_58[1] + 6,
		1, 1);
    }

  // If this is the first screen of cup standings,
  // where you see just amount of points added
  if ((sdata->menuReadyToPass & 4) == 0)
  {
    // fly-in interpolation
    DECOMP_UI_Lerp2D_Linear(
		&local_58[0],
		-10, (int)local_38,
		-10, 9,
		sdata->framesSinceRaceEnded, 0x14);
  }

  // if it's not...
  else {
    if (sdata->framesSinceRaceEnded <= 0xf0)
	{
      local_58[0] = -10;
      local_58[1] = 9;
    }

	else
	{
      // fly-in interpolation
      DECOMP_UI_Lerp2D_Linear(
		&local_58[0],
		-10, 9,
		-10, (int)local_30,
		sdata->framesSinceRaceEnded + -0xf0, 0x14);
    }
  }

  RECT r;
  r.x = local_58[0];
  r.y = local_58[1];
  r.w = 0x214;
  r.h = 0x32;

  // Draw 2D Menu rectangle background
  RECTMENU_DrawInnerRect(&r, 4, gGT->backBuffer->otMem.startPlusFour);

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
        // PRESS * TO CONTINUE
        DecalFont_DrawLine(sdata->lngStrings[0xC9], 0x100, 0xbe, 1, 0xffff8000),

        // If you press Cross or Circle
        (sdata->AnyPlayerTap & 0x50) != 0)
    ) {
      // Timer
      sdata->framesSinceRaceEnded = 0xf0;

      // Proceed from Track standings to overall Cup standings,
      // where you see how many points each driver has overall
      sdata->menuReadyToPass = sdata->menuReadyToPass | 8;

      // clear gamepad input (for menus)
      RECTMENU_ClearInput();
    }
  }

  else
  {
    sdata->numIconsEOR = 1;
    sdata->framesSinceRaceEnded = 0;
    uVar6 = sdata->menuReadyToPass & 0xfffffff6;
    uVar8 = sdata->menuReadyToPass & 4;

    // Proceed from end-of-race menu to Track Standings,
    // where you see how many points are added just for this race
    sdata->menuReadyToPass = uVar6 | 4;

    // If the "4" flag was not enabled till just now,
    // If this is the first frame of Track Standings
    if (uVar8 == 0)
	{
	  if(numDrivers > 4)
		  numDrivers = 4;

      for (i = 0; i < numDrivers; i++)
	  {
        // the amount of points this player has in the cup
        gGT->cup.points[gGT->driversInRaceOrder[i]->driverID] +=

          // Incremented by
          // The amount of points that should be awarded to each position
          points[i];
      }

      // update cup rank of all drivers
      UI_CupStandings_UpdateCupRanks();
    }

    // If this is not the first frame of track standings
    else
	{
      sdata->menuReadyToPass = uVar6;

      // enable drawing HUD
      gGT->hudFlags |= 1;

      // Disable types of HUD that are not needed for gameplay,
      // This includes Cup rankings, which is a flag in this byte
      gGT->hudFlags &= 0xfb;

      sdata->menuReadyToPass = sdata->menuReadyToPass & 0xfffffffb;

      // Increment Track Number by 1 (0-3 in the cup)
	  gGT->cup.trackIndex++;

      int cupTrack = gGT->cup.trackIndex;

      // If this is not the last race in the cup
      if (cupTrack < 4)
	  {
		// If not in Arcade or VS cup
		if ((gGT->gameMode2 & 0x10) == 0)
		{
			index = data.advCupTrackIDs[(4*cupID)+cupTrack];
		}

		// If Arcade or VS cup
		else
		{
			index = data.ArcadeCups[cupID].CupTrack[cupTrack].trackID;
		}

		MainRaceTrack_RequestLoad(index);
      }

      // If this was the last race in the cup
      // If the cup is over
      else
	  {
		if ((gGT->gameMode2 & 0x10) != 0)
			UI_CupStandings_FinalizeCupRanks();

        gGT->cup.trackIndex = 0;

        // Array with the final ranking of each player
        ranks = &data.cupPositionPerPlayer[0];
        for (i = 0; i < 8; i++)
		{
		  struct Driver* d;
		  d = gGT->drivers[ranks[i]];

          // If driver is not nullptr
          if (d != 0)
		  {
            // Set final ranking of each player
            d->driverRank = (short) i;
          }

          // set driver's cup score to zero
          gGT->cup.points[i] = 0;
        }

        Podium_InitModels(gGT);

		i = gGT->cup.cupID;

        // If this is an Adventure Cup
        if ((gGT->gameMode2 & 0x10) == 0)
		{
          // Array with the ranking of each player
          gGT->levelID = i + 100;

          // when loading is done,
          // remove flag for adventure cup
          sdata->Loading.OnBegin.RemBitsConfig0 |= 0x10000000;

          // If player 1 won the cup
          if (data.cupPositionPerPlayer[0] == gGT->drivers[0]->driverID)
		  {
            int bitIndex = 0x6a + i;
			int* rewardsSet = &sdata->advProgress.rewards[0];

            if (CHECK_ADV_BIT(rewardsSet, bitIndex) == 0)
			{
			  UNLOCK_ADV_BIT(rewardsSet, bitIndex);

			  // unlock Roo, Papu, Joe, Pinstripe, FCrash
			  bitIndex = 7 + i;
			  rewardsSet = &sdata->gameProgress.unlocks[0];
			  UNLOCK_ADV_BIT(rewardsSet, bitIndex);

              // Set podium reward model to Gem
              gGT->podiumRewardID = 0x5f;
            }

            // reset counter for number of times you lost cup, to zero
            sdata->advProgress.timesLostCupRace[i] = 0;
          }

          // If player 1 did not win the cup
          else
		  {
            if (sdata->advProgress.timesLostCupRace[i] < 10)
				sdata->advProgress.timesLostCupRace[i]++;
          }
        }

        // If this is not an Adventure Cup
        else
		{
		  // === Naughty Dog Bug ===
		  // If driver[1] is an AI in a 1P cup,
		  // then you still get completion credit

          // If Player 1 or Player 2 won the cup
          if (((gGT->drivers[0]->driverRank) == 0) ||
            (((gGT->drivers[1]->driverRank) == 0)) &&

            // If you're in Arcade Mode
            ((gGT->gameMode1 & ARCADE_MODE) != 0))
		  {
			int difficulty = (gGT->arcadeDifficulty/0x50)-1;
			if(difficulty > 2) difficulty = 2;

			int* rewardsSet =
				&sdata->gameProgress.unlocks[0];

			int baseIndex =
				sdata->UnlockBitIndex.CupCompletion_prev[difficulty];

			// if track was not unlocked "previously",
			// this writes when TakeCupProgress is saved
			int bitIndex = baseIndex + gGT->cup.cupID;
            if (CHECK_ADV_BIT(rewardsSet, bitIndex) == 0)
			{
              // lets 233 know to prompt the Save Game box
              gGT->gameMode2 |= 0x1000;

			  baseIndex =
				sdata->UnlockBitIndex.CupCompletion_curr[difficulty];

			  bitIndex = baseIndex + gGT->cup.cupID;
			  UNLOCK_ADV_BIT(rewardsSet, bitIndex);

			  int boolUnlockMap = 1;
              for (i = 0; i < 4; i++)
			  {
                // if any of four cups on this difficulty was not won
				bitIndex = baseIndex + i;
                if (CHECK_ADV_BIT(rewardsSet, bitIndex) == 0)
				{
                  // you dont deserve to unlock a battle map
                  boolUnlockMap = 0;
                  break;
                }
              }

              // If new Battle unlocked
              if (boolUnlockMap)
			  {
				bitIndex = sdata->UnlockBitIndex.UnlockBattleMap[difficulty];
				UNLOCK_ADV_BIT(rewardsSet, bitIndex);

                // battle map is now unlocked (233 overlay)
                gGT->gameMode2 |= 0x2000;
              }
            }
          }

          // Set podium's reward model to "Empty"
          gGT->podiumRewardID = 0x38;
        }

        // Level ID for Gemstone Valley (podiums)
        MainRaceTrack_RequestLoad(0x19);
      }
    }
  }
}

#include "../AltMods/Mods8.c"

void __attribute__ ((section (".end"))) Mods8_EndOfFile()
{
	// leave empty
}