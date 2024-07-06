#include <common.h>

// this goes to footer
static int str_number = 0x20; // " \0"

extern struct RectMenu menu224;
extern struct MenuRow rowsWithSave[6];
extern struct MenuRow rowsNoSave[5];

void DECOMP_TT_EndEvent_DisplayTime(int paramX, short paramY, u_int UI_DrawRaceClockFlags);

void DECOMP_TT_EndEvent_DrawMenu(void)
{
    int framesSinceRaceEnded;
    int startX_also_strFlags;
    short endX;
    short pos[2];
	char** lngStrings;
	u_int unknownFlags_1d44;
    struct GameTracker *gGT;

	gGT = sdata->gGT;
	lngStrings = sdata->lngStrings;
	unknownFlags_1d44 = gGT->unknownFlags_1d44;

    sdata->flags_timeTrialEndOfRace |= 1;

    // If you just beat N Tropy && N Tropy was beaten on all tracks
    if (
			((unknownFlags_1d44 & 0x10000000) != 0) &&
			((GAMEPROG_CheckGhostsBeaten(1) & 0xffff) != 0)
		)
    {
        sdata->gameProgress.unlocks[0] |= 0x20; // Unlock N Tropy
    }

    // copy the frame counter variable
    framesSinceRaceEnded = sdata->framesSinceRaceEnded;

    if (framesSinceRaceEnded < FPS_DOUBLE(900))
    {
AddStuff:
        framesSinceRaceEnded++;
    }
    else
    {
		// if dont need to show high scores,
		// then dont increment framesSinceRaceEnded,
		// and then the later "if > 900" wont happen
        if ((unknownFlags_1d44 & 0x8000000) == 0)
        {
			// between 1001 and 1018, frame counter is paused until &0x10,
			// that's 15 frames between lerp high score off-screen, and showing Menu
            if ((framesSinceRaceEnded < FPS_DOUBLE(1018)) && ((sdata->menuReadyToPass & 0x10) != 0)) goto AddStuff;
            if (framesSinceRaceEnded < FPS_DOUBLE(1001)) goto AddStuff;
        }
    }

    // copy "back" the frame counter variable
    sdata->framesSinceRaceEnded = framesSinceRaceEnded;

	if (framesSinceRaceEnded < FPS_DOUBLE(91))
    {
		// no lerp, just sit on-screen
        startX_also_strFlags = 0x14;

        if (framesSinceRaceEnded > FPS_DOUBLE(65))
        {
            startX_also_strFlags = -0x96;
            framesSinceRaceEnded -= FPS_DOUBLE(65);
        }

		// draw race clock in top-left corner
        DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			0x14, 8,
			startX_also_strFlags, 8,
			framesSinceRaceEnded, FPS_DOUBLE(0x14));

		DECOMP_UI_DrawRaceClock(
			(int)pos[0], (int)pos[1], 0, gGT->drivers[0]);

		return;
    }

	// between 91 and 900 frames (3-30)
	if (framesSinceRaceEnded <= FPS_DOUBLE(900))
	{
		// first transition is race clock
		framesSinceRaceEnded -= FPS_DOUBLE(90);

		// race time
		DECOMP_UI_Lerp2D_Linear(
			&pos[0],
			-0x64, 90,
			0x100, 90,
			framesSinceRaceEnded, FPS_DOUBLE(0x14));

		DECOMP_TT_EndEvent_DisplayTime(
			(int)pos[0], pos[1], sdata->flags_timeTrialEndOfRace);

		// Blink Orange/White
		startX_also_strFlags = (gGT->timer & FPS_DOUBLE(1)) ? 0xffff8000 : 0xffff8004;



		// "new high score" 1 second later
		framesSinceRaceEnded -= FPS_DOUBLE(30);

		if ((framesSinceRaceEnded > 0) &&

			// if there is a new high score
			gGT->newHighScoreIndex > -1)
		{
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				0x264, 122,
				0x100, 122,
				framesSinceRaceEnded, FPS_DOUBLE(0x14));

			// "NEW HIGH SCORE!"
			DecalFont_DrawLine(
				lngStrings[353],
				(int)pos[0], (int)pos[1],
				1, startX_also_strFlags);

			// Total time should flash
			sdata->flags_timeTrialEndOfRace |= (1<<2);
		}



		// "new best lap" 1 second later
		framesSinceRaceEnded -= FPS_DOUBLE(30);

		if ((framesSinceRaceEnded > 0) &&

			// if got new best lap
			((unknownFlags_1d44 & 0x4000000) != 0))
		{
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				-0x64, 142,
				0x100, 142,
				framesSinceRaceEnded, FPS_DOUBLE(0x14));

			// NEW BEST LAP!
			DecalFont_DrawLine(
				lngStrings[370],
				(int)pos[0], (int)pos[1],
				1, startX_also_strFlags);

			// make the best row start flashing
			sdata->flags_timeTrialEndOfRace |= 1 << (3 + gGT->lapIndexNewBest);
		}



		// "n tropy" 1 second later
		framesSinceRaceEnded -= FPS_DOUBLE(30);

		if ((framesSinceRaceEnded > 0) &&

			// if just open, or beat, n tropy
			((unknownFlags_1d44 & 0x10008000) != 0))
		{
			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				0x264, 162,
				0x100, 162,
				framesSinceRaceEnded, FPS_DOUBLE(0x14));

			char *nTropyString;

			// default, N Tropy Opened
			nTropyString = lngStrings[371];

			// search "18000000"
			// if just beat n tropy, YOU BEAT N. TROPY!
			if ((unknownFlags_1d44 & 0x10000000) != 0)
				nTropyString = lngStrings[372];

			// Draw the "N Tropy" related string
			DecalFont_DrawLine(
				nTropyString,
				(int)pos[0], (int)pos[1],
				1, startX_also_strFlags);
		}

		// PRESS * TO CONTINUE
		DecalFont_DrawLine(lngStrings[201], 0x100, 0xbe, 1, 0xffff8000);

		// If you press Cross or Circle
		if ((sdata->AnyPlayerTap & 0x50) != 0)
		{
			// advance timer, quickly skip to see high scores
			sdata->framesSinceRaceEnded = FPS_DOUBLE(901); // 30 seconds
		}

		return;
	}

	// 901 or more (30 secs)
    if (framesSinceRaceEnded < FPS_DOUBLE(1017))
    {
        // start drawing the high score menu that shows the top 5 best times
        gGT->unknownFlags_1d44 |= 2;

		if ((unknownFlags_1d44 & 0x8000000) == 0)
		{

			// ====== Draw High Score ===========

			// 900-1002
			if (framesSinceRaceEnded < FPS_DOUBLE(1002))
			{
				framesSinceRaceEnded -= FPS_DOUBLE(901);

				startX_also_strFlags = -0x96;
				endX = 0x80;
			}

			// 1002-1017
			else
			{
				framesSinceRaceEnded -= FPS_DOUBLE(1001);

				startX_also_strFlags = 0x80;
				endX = -0x96;
			}

			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				startX_also_strFlags, 10,
				endX, 10,
				framesSinceRaceEnded, FPS_DOUBLE(0x14));

			DECOMP_TT_EndEvent_DrawHighScore(pos[0], (int)pos[1]);


			// ====== Draw Your Time ===========


			// 900-1002,
			// sneaky IF to save instructions
			if (endX == 0x80)
			{
				startX_also_strFlags = 0x296;
				endX = 0x180;
			}

			// 1002-1017
			else
			{
				startX_also_strFlags = 0x180;
				endX = 0x296;
			}

			DECOMP_UI_Lerp2D_Linear(
				&pos[0],
				startX_also_strFlags, 0x82,
				endX, 0x82,
				framesSinceRaceEnded, FPS_DOUBLE(0x14));

			DECOMP_TT_EndEvent_DisplayTime(
				(int)pos[0], pos[1],
				sdata->flags_timeTrialEndOfRace);

			// PRESS * TO CONTINUE
			DecalFont_DrawLine(
				lngStrings[201],
				0x100, 0xbe,
				1, 0xffff8000);

			// ==== Pause Timer until Press X =======
			// Cross or Circle, or if timer drags on too long
			if (((sdata->AnyPlayerTap & 0x50) != 0) && (sdata->framesSinceRaceEnded < FPS_DOUBLE(1002)))
			{
				sdata->framesSinceRaceEnded = FPS_DOUBLE(1001);

				// unpause frame counter,
				// which then counts up to 1018 for transition-out
				sdata->menuReadyToPass |= 0x10;
			}
		}

		return;
	}

	// if not showing menu yet
	if ((sdata->menuReadyToPass & 1) == 0)
	{
		// start showing menu
		sdata->menuReadyToPass = sdata->menuReadyToPass & 0xffffffef | 1;

		sdata->flags_timeTrialEndOfRace = 0;

		if (sdata->boolGhostTooBigToSave)
			menu224.rows = rowsNoSave;

		RECTMENU_Show(&menu224);
	}

    return;
}

void DECOMP_TT_EndEvent_DisplayTime(int paramX, short paramY, u_int UI_DrawRaceClockFlags)
{
	struct GameTracker* gGT;
	struct Driver* d;
	short textWidth;
	short pos[2];
	RECT rectangle;

	gGT = sdata->gGT;
	d = gGT->drivers[0];

	// "TOTAL"
	textWidth = DECOMP_DecalFont_GetLineWidth(sdata->lngStrings[0xc4], 1);

	// === Naughty Dog Bug ===
	// Start and End is the same

	// Fly-in Interpolation
	DECOMP_UI_Lerp2D_Linear(
		&pos[0],
		(paramX - (0x88 - textWidth) / 2), paramY,
		(paramX - (0x88 - textWidth) / 2), paramY,
		sdata->framesSinceRaceEnded, FPS_DOUBLE(0x14));

	// "YOUR TIME"
	DecalFont_DrawLine(sdata->lngStrings[197], paramX, ((u_int)pos[1] - 0x4c), FONT_BIG, (JUSTIFY_CENTER | ORANGE));

	DECOMP_UI_DrawRaceClock(pos[0], pos[1], UI_DrawRaceClockFlags, d);

	rectangle.x = (pos[0] - textWidth) - 6;
	rectangle.y = pos[1] - 0x50;

	rectangle.w = textWidth + 0x94;
	rectangle.h = 99;

	// Draw 2D Menu rectangle background
	RECTMENU_DrawInnerRect(&rectangle, 4, gGT->backBuffer->otMem.startPlusFour);

	return;
}

// same in TT and RR, but not the same in Main Menu
void DECOMP_TT_EndEvent_DrawHighScore(short startX, int startY)
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
	u_short currRowY;
	RECT box;

	gGT = sdata->gGT;
	timebox_X = startX - 0x1f;
	currRowY = 0;

	// 12 entries per track, 6 for Time Trial and 6 for Relic Race
	scoreEntry = &sdata->gameProgress.highScoreTracks[gGT->levelID].scoreEntry[0];

	// === Naughty Dog Bug ===
	// Start and End is the same

	// interpolate fly-in
	DECOMP_UI_Lerp2D_Linear(
		&pos[0],
		startX, startY,
		startX, startY,
		sdata->framesSinceRaceEnded, FPS_DOUBLE(0x14));

	// "BEST TIMES"
	DecalFont_DrawLine(
		sdata->lngStrings[0x171],
		pos[0], pos[1],
		1, 0xffff8000);

	// Draw icon, name, and time of the
	// 5 best times in Time Trial
	for (i = 0; i < 5; i++)
	{
		// default color, not flashing
		timeColor = 0;
		nameColor = scoreEntry[i+1].characterID + 5;

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			// make name color flash every odd frame
			nameColor = (gGT->timer & FPS_DOUBLE(2)) ? 4 : nameColor;

			// flash color of time
			timeColor = ((gGT->timer & FPS_DOUBLE(2)) << FPS_LEFTSHIFT(1));
		}

		timebox_Y = startY + 0x11 + currRowY;

		// Make a rank on the high score list ('1', '2', '3', '4', '5')
		// by taking the binary value of the rank (0, 1, 2, 3, 4),
		// and adding the ascii value of '1'
		str_number = (char)i + '1';

		// Draw String for Rank ('1', '2', '3', '4', '5')
		DecalFont_DrawLine(&str_number, startX - 0x32, timebox_Y - 1, 2, 4);

		u_int iconColor = 0x808080;

		// Draw Character Icon
		RECTMENU_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[scoreEntry[i+1].characterID].iconID],
							startX - 0x52, timebox_Y,

							// pointer to PrimMem struct
							&gGT->backBuffer->primMem,

							// pointer to OT mem
							gGT->pushBuffer_UI.ptrOT,

							// color of each corner
							iconColor, iconColor,
							iconColor, iconColor,

							1, 0x1000);

		// Draw Name
		DecalFont_DrawLine(scoreEntry[i+1].name, timebox_X, timebox_Y, 3, nameColor);

		// Draw time
		DecalFont_DrawLine(RECTMENU_DrawTime(scoreEntry[i+1].time), timebox_X, timebox_Y + 0x11, 2, timeColor);

		// If this loop index is a new high score
		if (gGT->newHighScoreIndex == i)
		{
			box.x = startX - 0x56;
			box.y = timebox_Y - 1;
			box.w = 0xab;
			box.h = 0x1a;

			// Draw a rectangle to highlight your time on the "Best Times" list
			Color color;
			color.self = sdata->menuRowHighlight_Normal;
			DECOMP_CTR_Box_DrawClearBox(&box, color, TRANS_50_DECAL,
								 // pointer to OT mem
								 gGT->pushBuffer_UI.ptrOT);
		}
		currRowY += 0x1a;
	}

	// IF TT
	{
		// Change the way text flickers
		timeColor = 0xffff8000;

		// "BEST LAP"
		DecalFont_DrawLine(sdata->lngStrings[0x170], startX, startY + 0x95, 1, timeColor);

		// If you got a new best lap
		if (((gGT->unknownFlags_1d44 & 0x4000000) != 0) &&
			((gGT->timer & FPS_DOUBLE(2)) != 0))
		{
			timeColor = 0xffff8004;
		}
		// make a string for best lap
		timeString = RECTMENU_DrawTime(scoreEntry[0].time);
	}

	// Print amount of time, for whichever purpose
	DecalFont_DrawLine(timeString, startX, startY + 0xa6, 2, timeColor);

	box.x = pos[0] - 0x60;
	box.y = pos[1] - 4;
	box.w = 0xc0;
	box.h = 0xb4;

	// Draw 2D Menu rectangle background
	RECTMENU_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
}

struct MenuRow rowsWithSave[6] =
{
	// Retry
	{
		.stringIndex = 4,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},

	// Change Level
	{
		.stringIndex = 6,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},

	// Change Character
	{
		.stringIndex = 5,
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},

	// Save Ghost
	{
		.stringIndex = 9,
		.rowOnPressUp = 2,
		.rowOnPressDown = 4,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},

	// Quit
	{
		.stringIndex = 3,
		.rowOnPressUp = 3,
		.rowOnPressDown = 4,
		.rowOnPressLeft = 4,
		.rowOnPressRight = 4,
	},

	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

struct MenuRow rowsNoSave[5] =
{
	// Retry
	{
		.stringIndex = 4,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},

	// Change Level
	{
		.stringIndex = 6,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},

	// Change Character
	{
		.stringIndex = 5,
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},

	// Quit
	{
		.stringIndex = 3,
		.rowOnPressUp = 2,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},

	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

struct RectMenu menu224 =
{
	.stringIndexTitle = 0xFFFF,
	.posX_curr = 0x100,
	.posY_curr = 0xA0,

	.unk1 = 0,

	.state = 0xC83,
	.rows = rowsWithSave,
	.funcPtr = DECOMP_UI_RaceEnd_MenuProc,
	.drawStyle = 4,

	// rest of variables all default zero
};