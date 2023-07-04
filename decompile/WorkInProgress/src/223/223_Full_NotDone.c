#include <common.h>

// copy/paste from GameProg
#define NO_ADV_BIT(rewards, bitIndex) \
	((rewards[bitIndex>>5] >> (bitIndex & 0x1f)) & 1) != 0

// 8009f700
int str_number;

// 8009f704
int str_x;

// 8009f708 
char str_format[0xC];

// 8009f714
int str_negInt;

// 8009f718
int str_posInt;

// 8009f71c
void RR_EndEvent_UnlockAward()
{
	int i;
	struct Driver* driver;
	struct GameTracker* gGT;
	int raceTime;
	int timeDeduct;
	int bitIndex;
	struct AdvProgress* adv;
	int levelID;
	int relicTime;
	
	gGT = sdata->gGT;
	driver = gGT->drivers[0];
	raceTime = driver->timeElapsedInRace;
	adv = &sdata->advProgress;
	levelID = gGT->levelID;
	
	// 10 seconds for getting all crates
	if(driver->numTimeCrates == gGT->timeCratesInLEV)
		raceTime -= 0x2580;

	for(i = 0; i < 3; i++)
	{
		relicTime = data.RelicTime[levelID * 3 + i];
		
		// if driver did not beat relic time, check next relic
		if(raceTime > relicTime)
			continue;
		
		bitIndex = 0x16 + 0x12*i;
		
		// if relic already unlocked, check next relic
		if(CHECK_ADV_BIT(adv->rewards, bitIndex) != 0)
			continue;
		
		// == beat relic, and unlocked relic ==
		
		// unlock
		UNLOCK_ADV_BIT(adv->rewards, bitIndex);
		
		// relic model
		gGT->podiumRewardID = 0x61;
		
		gGT->unknownFlags_1d44 |= 0x2000000;
		
		// unlocked sapphire
		// do not make this an AND (&&) if statement
		if(i == 0)
		{	
			if(gGT->levelID == TURBO_TRACK)
			{
				// unlock turbo track
				sdata->gameProgress.unlocks[0] |= 2;
			}
			
			continue;
		}
		
		// == Gold or Platinum ==
		
		// store globally... 8008d9b0
		data.relicTime_1min = 	relicTime / 0xe100;
		data.relicTime_10sec =	(relicTime / 0x2580) % 6;
		data.relicTime_1sec =	(relicTime / 0x3c0) % 10;
		data.relicTime_1ms = 	((relicTime * 100) / 0x3c0) % 10; 
		
		// [Not Done]
		data.relicTime_10ms = 0;
	}
}

void RR_EndEvent_DrawHighScore(short startX, int startY, short mode)
{
  // This is different from High Score in Main Menu because Main Menu
  // does not show the rank icons '1', '2', '3', '4', '5'
  struct GameTracker *gGT;
  struct HighScoreEntry *scoreEntry;

  char i;
  char *timeString;
  short nameColor;
  u_int timeColor;
  short pos[2];
  short timebox_X;
  short timebox_Y;
  ushort currRowY;
  RECT box;

  gGT = sdata->gGT;
  timebox_X = startX - 0x1f;
  currRowY = 0;

  // 8008e6f4 is where all high scores are saved
  // 0x49*4 = 0x124, size of each HighScoreTrack
  // 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
  scoreEntry = &sdata->gameProgress->highScoreTracks[gGT->levelID].scoreEntry[mode];

  // interpolate fly-in
  UI_Lerp2D_HUD(&pos, startX, startY, startX, startY, sdata->framesSinceRaceEnded, 0x14);

  // "BEST TIMES"
  DecalFont_DrawLine(sdata->lngStrings[0x171], pos[0], pos[1], 1, 0xffff8000);

  // Draw icon, name, and time of the
  // 5 best times in Time Trial
  for (i = 0; i < 5; i++)
  {
    // default color, not flashing
    timeColor = 0;
    nameColor = scoreEntry->characterID + 5;

    // If this loop index is a new high score
    if (gGT->newHighScoreIndex == i)
    {
      // make name color flash every odd frame
      nameColor = (gGT->timer & 2) ? 4 : scoreEntry->characterID + 5;
      // flash color of time
      timeColor = ((gGT->timer & 2) << 1);
    }

    timebox_Y = startY + 0x11 + currRowY;

    // Make a rank on the high score list ('1', '2', '3', '4', '5')
    // by taking the binary value of the rank (0, 1, 2, 3, 4),
    // and adding the ascii value of '1'
    str_number = (char)i + '1';

    // Draw String for Rank ('1', '2', '3', '4', '5')
    DecalFont_DrawLine(str_number, startX - 0x32, timebox_Y - 1, 2, 4);

    u_int *iconColor = 0x800a0cb4;

    // Draw Character Icon
    MENUBOX_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[data.characterIDs[gGT->drivers[i]->driverID]].iconID],
                        startX - 0x52, timebox_Y,

                        // pointer to PrimMem struct
                        &gGT->backBuffer->primMem,

                        // pointer to OT mem
                        gGT->tileView_UI.ptrOT,
                        iconColor, iconColor, iconColor, iconColor, 1, 0x1000);

    // Draw Name
    DecalFont_DrawLine(scoreEntry->name, timebox_X, timebox_Y, 3, nameColor);

    // Draw time
    DecalFont_DrawLine(MENUBOX_DrawTime(scoreEntry->time), timebox_X, timebox_Y + 0x11, 2, timeColor);

    // If this loop index is a new high score
    if (gGT->newHighScoreIndex == i)
    {
      box.x = startX - 0x56;
      box.y = timebox_Y - 1;
      box.w = 0xab;
      box.h = 0x1a;

      // Draw a rectangle to highlight your time on the "Best Times" list
      CTR_Box_DrawClearBox(&box, &sdata->menuRowHighlight_Normal, 1,
                           // pointer to OT mem
                           gGT->tileView_UI.ptrOT,
                           // pointer to PrimMem struct
                           &gGT->backBuffer->primMem);
    }
    currRowY += 0x1a;
  }

  // If this is Time Trial Mode
  if (mode == 0)
  {
    // "BEST LAP"
    DecalFont_DrawLine(sdata->lngStrings[0x170], startX, startY + 0x95, 1, 0xffff8000);
    // Change the way text flickers
    timeColor = 0xffff8000;
    // If you got a new best lap
    if (((gGT->unknownFlags_1d44 & 0x4000000) != 0) &&
        ((gGT->timer & 2) != 0))
    {
      timeColor = 0xffff8004;
    }
    // make a string for best lap
    timeString = MENUBOX_DrawTime(scoreEntry->time);
  }
  // If this is Relic Mode
  else
  {
    // "YOUR TIME"
    DecalFont_DrawLine(sdata->lngStrings[0xC5], startX, startY + 0x95, 1, 0xffff8000);
    // make a string for your current track time
    timeString = MENUBOX_DrawTime(gGT->drivers[0].timeElapsedInRace);
    // color
    timeColor = 0xffff8000;
  }

  // Print amount of time, for whichever purpose
  DecalFont_DrawLine(timeString, startX, startY + 0xa6, 2, timeColor);

  box.x = pos[0] - 0x60;
  box.y = pos[1] - 4;
  box.w = 0xc0;
  box.h = 0xb4;

  // Draw 2D Menu rectangle background
  MENUBOX_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
}