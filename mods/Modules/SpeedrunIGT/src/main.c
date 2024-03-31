#include <common.h>

// to do: make header for IGT funcs
void SerializeSplits(char deserialize);
void SaveGameProgressToMemcardBuffer();

#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)

#define HOUR (60 * MINUTE)

#define numLevels 21

#define TimeToString Torch_Subset1

RECT menuWindow = {5, 15, 502, 201};

#if BUILD == JpnTrial
char s_saveSplits[] = "* Edit - No Memcards in Trial Demo";
#else
char s_saveSplits[] = "* Edit [ Save ^ Load";
#endif

// functions dont exist in kiosk demo
#if BUILD != JpnTrial
void SaveSplits()
{
    SerializeSplits(0);
    SaveGameProgressToMemcardBuffer();
    MEMCARD_SetIcon(0);
    RefreshCard_StartMemcardAction(3);
}
#endif

unsigned char trackNamesLNG[] = {

	// 0x2C = Crash Bandicoot (long name)
	// 0x3C = Crash (short name)
	// 0x6E = Dingo Canyon

	0x71, //"Crash Cove",
	0x74, //"Roo's Tubes",
	0x77, //"Mystery Caves",
	0x76, //"Sewer Speedway",
	0x36, //"Ripper Roo",

	0x72, //"Tiger Temple",
	0x7C, //"Coco Park",
	0x73, //"Papu's Pyramid",
	0x6E, //"Dingo Canyon",
	0x35, //"Papu Papu",

	0x70, //"Blizzard Bluff",
	0x6F, //"Dragon Mines",
	0x7A, //"Polar Pass",
	0x7D, //"Tiny Arena",
	0x37, //"Komodo Joe",

	0x79, //"N. Gin Labs",
	0x78, //"Cortex Castle",
	0x75, //"Hot Air Skyway",
	0x7B, //"Oxide Station",
	0x34, //"Pinstripe",

	0x39, //"N. Oxide"
};

char s_totalTime[] = "  00:00.000";
char s_editorTime[] = "  00:00.000";
char s_frozenTime[] = "+  00:00.000";

int splits[numLevels] = {
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR
};

int splitsComparing[numLevels] = {
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR, 10 * HOUR,
    10 * HOUR
};

struct IGT
{
	int totalTime;

	short splitFadeTimer;
	short splitColor;

	char level;
	char stopIncrementing;
	char onMenu;
	char menuRow;

	char selectedRow;
	char framesHoldingUp;
	char framesHoldingDown;
	char isSpeedrunning;

	short podiumRewardID;
};

register struct IGT* igt asm("k1");

void EndOfRace_Hook()
{
    int delta;
    int i;
	int unlockDoors;

	// backup podium
	igt->podiumRewardID = sdata->gGT->podiumRewardID;

	// skip podium
	sdata->gGT->podiumRewardID = 0;

	// unlock doors
	unlockDoors=0;
	if(sdata->advProgress.rewards[2] & 0x40000000) unlockDoors = 0x10;
	if(sdata->advProgress.rewards[2] & 0x80000000) unlockDoors = 0xE0;
	if(sdata->advProgress.rewards[3] & 0x1) unlockDoors = 0x100;
	sdata->advProgress.rewards[3] |= unlockDoors;

    if (!igt->stopIncrementing && !igt->splitFadeTimer)
    {
        splits[igt->level] = igt->totalTime;
        delta = igt->totalTime - splitsComparing[igt->level];
        if (delta > 0)
        {
            TimeToString(&s_frozenTime[1], delta);
            if (delta > HOUR)

			s_frozenTime[0] = '+';
            else
            {
                s_frozenTime[0] = ' ';
                s_frozenTime[2] = '+';
            }
            igt->splitColor = RED;
        }
        else
        {
            delta *= -1;
            TimeToString(&s_frozenTime[1], delta);
            if (delta > HOUR)
                s_frozenTime[0] = '-';
            else
            {
                s_frozenTime[0] = ' ';
                s_frozenTime[2] = '-';
            }
            igt->splitColor = TINY_GREEN;
        }
        igt->splitFadeTimer = 300;
        igt->level++;
        if (igt->level == numLevels)
        {
            // If you PB'd, save splits, otherwise keep old run
            if (splits[numLevels - 1] < splitsComparing[numLevels - 1])
            {
                for (i = 0; i < numLevels; i++)
                    splitsComparing[i] = splits[i];

				// no memcard in kiosk demo
				#if BUILD != JpnTrial
                SaveSplits();
				#endif
            }
            else
            {
                for (i = 0; i < numLevels; i++)
                    splits[i] = splitsComparing[i];
            }
            igt->stopIncrementing = 1;
        }
    }
}

struct Instance* INSTANCE_Birth_Hook()
{
	register struct Instance* i asm("v0");
	struct Model* m = i->model;

    if ((m->id == -1) && (m->numHeaders > 1))
    {
        m->headers[0].maxDistanceLOD = 0;
        m->headers[1].maxDistanceLOD = 0;
    }

	return i;
}

void IncrementIGT()
{
    igt->totalTime += sdata->gGT->elapsedTimeMS;
    TimeToString(s_totalTime, igt->totalTime);
}

void ResetIGT()
{
    int i;
    igt->totalTime = 0;
    igt->isSpeedrunning = 0;
    igt->level = 0;
    igt->splitFadeTimer = 0;
    igt->stopIncrementing = 0;
    for (i = 0; i < numLevels; i++)
        splits[i] = splitsComparing[i];
    TimeToString(s_totalTime, igt->totalTime);
}

void DrawIGT()
{
  struct GameTracker* gGT;
  void* backupOT;

  // dont need to be this strict,
  // just a design choice
  if (sdata->Loading.stage >= 1) return;

  gGT = sdata->gGT;
  backupOT = gGT->pushBuffer_UI.ptrOT;
  gGT->pushBuffer_UI.ptrOT = gGT->otSwapchainDB[gGT->swapchainIndex];

  if (igt->splitFadeTimer > 0)
  {
      if (s_frozenTime[0] == ' ')
          DecalFont_DrawLine(&s_frozenTime[2], 256, 17, FONT_SMALL, igt->splitColor | JUSTIFY_CENTER);
      else
          DecalFont_DrawLine(s_frozenTime, 256, 17, FONT_SMALL, igt->splitColor | JUSTIFY_CENTER);
      igt->splitFadeTimer--;
  }
  if (s_totalTime[0] == ' ')
      DecalFont_DrawLine(&s_totalTime[2], 256, 8, FONT_SMALL, ORANGE | JUSTIFY_CENTER);
  else
      DecalFont_DrawLine(s_totalTime, 256, 8, FONT_SMALL, ORANGE | JUSTIFY_CENTER);

  // restore OT
  gGT->pushBuffer_UI.ptrOT = backupOT;
}

void SerializeSplits(char deserialize)
{
    int i;
    int j;
    int * buffer;
    int k = 0;

    for (i = 0; i < 6; i++)
    {
        buffer = (int *) &sdata->gameProgress.highScoreTracks[i].scoreEntry[6];
        for (j = 0; j < 4; j++)
        {
            if (deserialize)
                splits[k] = buffer[j];
            else
                buffer[j] = splits[k];
            k++;
            if (k == numLevels)
                break;
        }
    }
}

void SaveGameProgressToMemcardBuffer()
{
    int * progressBuffer;
    int * memoryCardBuffer;

    progressBuffer = &sdata->gameProgress.unknown;
    memoryCardBuffer = (int *)(&sdata->memcardBytes[0] + 0x144);

    while (progressBuffer != (int *) &sdata->advProgress)
        *(memoryCardBuffer++) = *(progressBuffer++);
}

void DrawMenu()
{
    int i;
    short rowColor;
    char bufferCopyDone;

	// japan builds
	#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
	// if main menu
	if(sdata->gGT->levelID == MAIN_MENU_LEVEL)
	{
		// disable checkered flag
		sdata->gGT->renderFlags &= 0xffffefff;
	}
	#endif

    if (igt->rowSelected)
    {
        if (igt->framesHoldingUp < 10)
        {
            if (sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame & (BTN_UP | BTN_RIGHT))
                igt->framesHoldingUp++;
            else
                igt->framesHoldingUp = 0;

            if (sdata->gGamepads->gamepad[0].buttonsTapped & (BTN_UP | BTN_RIGHT))
                splits[igt->menuRow] += 1;
        }
        else
        {
            if (sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame & (BTN_UP | BTN_RIGHT))
                splits[igt->menuRow] += 10;
            else
                igt->framesHoldingUp = 0;
        }

        if (igt->framesHoldingDown < 10)
        {
            if (sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame & (BTN_DOWN | BTN_LEFT))
                igt->framesHoldingDown++;
            else
                igt->framesHoldingDown = 0;

            if (sdata->gGamepads->gamepad[0].buttonsTapped & (BTN_DOWN | BTN_LEFT))
                splits[igt->menuRow] -= 1;
        }
        else
        {
            if (sdata->gGamepads->gamepad[0].buttonsHeldCurrFrame & (BTN_DOWN | BTN_LEFT))
                splits[igt->menuRow] -= 10;
            else
                igt->framesHoldingDown = 0;
        }

		if (splits[igt->menuRow] < 0) splits[igt->menuRow] = 0;
    }
    else
    {
        if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_UP)
        {
            igt->menuRow--;
            if (igt->menuRow == -1)
                igt->menuRow = numLevels - 1;
        }

        if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_DOWN)
            igt->menuRow = (igt->menuRow + 1) % numLevels;
    }

    if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_CROSS)
        igt->rowSelected ^= 1;


	// no save/load support in japan kiosk trial
	#if BUILD != JpnTrial
    if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SQUARE)
    {
        SaveSplits();
        igt->onMenu = 0;
        sdata->gGamepads->gamepad[0].buttonsTapped = 0;
        return;
    }

    if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_TRIANGLE)
        SerializeSplits(1);
	#endif

    sdata->gGamepads->gamepad[0].buttonsTapped = 0;

    for (i = 0; i < numLevels; i++)
    {
		// if !=
		rowColor = ORANGE;

		// if ==
        if (i == igt->menuRow)
        {
			// if selectedRow
			rowColor = PERIWINKLE;

			// if !selectedRow
            if (!igt->rowSelected)
            {
                if (sdata->gGT->timer & 1)
                    rowColor = ORANGE;
            }
        }

        DecalFont_DrawLine(sdata->lngStrings[trackNamesLNG[i]], 20, 18 + 9 * i, FONT_SMALL, rowColor);
        TimeToString(s_editorTime, splits[i]);
        if (s_editorTime[0] == ' ')
            DecalFont_DrawLine(&s_editorTime[2], 390, 18 + 9 * i, FONT_SMALL, rowColor);
        else
            DecalFont_DrawLine(s_editorTime, 370, 18 + 9 * i, FONT_SMALL, rowColor);
    }
    DecalFont_DrawLine(s_saveSplits, 254, 207, FONT_SMALL, ORANGE | JUSTIFY_CENTER);
    RECTMENU_DrawInnerRect(&menuWindow, 1, sdata->gGT->backBuffer->otMem.startPlusFour);
}

// Our mod begins here
void RunUpdateHook()
{
    char kartState;
    int i;
	int gameMode1;

	gameMode1 = sdata->gGT->gameMode1;

	if (sdata->gGT->trafficLightsTimer > 0)
	{
		// needed?
		// sdata->gGT->cameraDC[0].flags |= 9;

		// skip race intros
		sdata->gGT->gameMode1 &= ~START_OF_RACE;
		sdata->gGT->hudFlags |= 0x21;
	}

    if (igt->isSpeedrunning)
    {
        // if you went back to the main menu
        if (sdata->gGT->levelID == MAIN_MENU_LEVEL)
            ResetIGT();

        kartState = sdata->gGT->drivers[0]->kartState;
        // if you're not loading, end of race, race countdown, adv mask speech or adv warping
        if ((!igt->stopIncrementing) && (!((gameMode1 & (LOADING | END_OF_RACE)) || (kartState == 4) || (kartState == 10) || (kartState == 11))))
            IncrementIGT();
    }
    else
    {
        // if you accessed hub 1
        if (sdata->gGT->levelID == N_SANITY_BEACH)
        {
            for (i = 0; i < numLevels; i++)
                splitsComparing[i] = splits[i];


            igt->isSpeedrunning = 1;
            igt->onMenu = 0;
        }

    }

    // if you're not on the naughty dog box screen and you're not running
    if ((sdata->gGT->levelID != NAUGHTY_DOG_CRATE) && (!(igt->isSpeedrunning && !igt->stopIncrementing)))
        if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SELECT)
        {
            igt->onMenu ^= 1;
            igt->menuRow = 0;
            igt->rowSelected = 0;
            igt->framesHoldingDown = 0;
            igt->framesHoldingUp = 0;

			// japan builds
			#if (BUILD == JpnTrial) || (BUILD == JpnRetail)
			// if in main menu, turn checkered flag "back" on,
			// it will be disabled in DrawMenu
			if(sdata->gGT->levelID == MAIN_MENU_LEVEL)
			{
				// enable flag by default
				sdata->gGT->renderFlags |= 0x1000;
			}
			#endif
        }

	// if game is not loading
    if (!(gameMode1 & LOADING))
    {
		// that check ^^ is useless because
		// the hook doesn't run during loading.
		// However, the hook will change later

        if (igt->onMenu)
            DrawMenu();
    }

	#if 0
	// temporary debug
	if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_UP)
	{
		sdata->gGT->drivers[0]->lapIndex = 2;
		sdata->gGT->drivers[0]->actionsFlagSet &= 0xfeffffff;
	}
	#endif
}

void AA_EndEvent_DisplayTime();

void AllocDriversHook_BeforeTeleport()
{
	// restore the reward, so TeleportSelf knows
	// where to put the driver
	sdata->gGT->podiumRewardID = igt->podiumRewardID;

	// clear
	igt->podiumRewardID = 0;
}

void TeleportSelfHook_AfterTeleport()
{
	// clear reward
	sdata->gGT->podiumRewardID = 0;
}

// happens halfway through the end-of-race menu
void AA_DisplayTime_Hook()
{
	// fake the passing of time
	sdata->framesSinceRaceEnded = 900;

	// fake a gamepad tap
	sdata->AnyPlayerTap = 0x50;
}

// currently hooks threadbuckets
void RunInitHook()
{
    int i;
	int* ptr;
	int size222;

	// Skip flag that doesn't let you move when teleporting to a hub door
	sdata->gGT->gameMode2 &= 0xffffbfff;

	// if bottom of AA_EndEvent_DrawMenu is JR RA,
	// (also, if this is the right overlay)
	if(*(unsigned int*)(AA_EndEvent_DisplayTime-8) == 0x03E00008)
	{
		*(unsigned int*)(AA_EndEvent_DisplayTime-8) = JMP(EndOfRace_Hook);

		// I was going to make this less hard-coded, but screw it
		#if BUILD == SepReview
		#define AA_DisplayTime_JRRA 0x8009f528
		#elif BUILD == UsaRetail
		#define AA_DisplayTime_JRRA 0x800A0B30
		#elif BUILD == JpnTrial
		#define AA_DisplayTime_JRRA 0x8009fae4
		#elif BUILD == EurRetail
		#define AA_DisplayTime_JRRA 0x800a0f74
		#elif BUILD == JpnRetail
		#define AA_DisplayTime_JRRA 0x800a4110
		#else
		#error unsupported builds
		#endif

		*(unsigned int*)(AA_DisplayTime_JRRA) = JMP(AA_DisplayTime_Hook);
	}

	// this part should happen on boot,
	// if function is not jr ra
	if(igt != (struct IGT*)0x8000FF80)
	{
		igt = (struct IGT*)0x8000FF80;

		// patch out AI particles, also 3P4P particles
		for(ptr = (int*)&data.emSet_Exhaust_Low[0]; ptr < (int*)&data.emSet_GroundSparks[0]; ptr++)
		{
			*ptr = 0;
		}
	}
}
