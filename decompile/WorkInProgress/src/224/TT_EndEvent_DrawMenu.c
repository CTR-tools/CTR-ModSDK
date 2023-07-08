#include <common.h>

/*
Ghidra name: FUN_8009fdc8
Status: In-Progress (OVER BUDGET)
Byte budget: 1316/1040
Called in:
  - 224.c
  - MAIN.c
*/

extern struct MenuBox menuBox224_ghost;
extern struct MenuBox menuBox224_basic;

void TT_EndEvent_DrawMenu(void)
{
    int framesSinceRaceEndedCopy;
    struct MenuBox *ptrMenuBox;
    int startX_also_strFlags;   // TODO: Verify type
    short endX;
    short startFrame;
    short pos[2];
    struct GameTracker *gGT = sdata->gGT;

    sdata->flags_timeTrialEndOfRace |= 1;

    // If you just beat N Tropy && N Tropy was beaten on all tracks
    if ((gGT->unknownFlags_1d44 & 0x10000000) && (GAMEPROG_CheckGhostsBeaten(1) & 0xffff))
    {
        sdata->gameProgress.unlocks[0] |= 0x20; // Unlock N Tropy
    }

    if (sdata->framesSinceRaceEnded < 900)
    {
        sdata->framesSinceRaceEnded++;
    }
    else
    {
        if ((gGT->unknownFlags_1d44 & 0x8000000) == 0)
        {
            if ((sdata->framesSinceRaceEnded < 1018) && ((sdata->menuReadyToPass & 0x10) != 0))
            {
                sdata->framesSinceRaceEnded++;
            }
            if (sdata->framesSinceRaceEnded < 1001)
            {
                sdata->framesSinceRaceEnded++;
            }
        }
    }

    // copy the frame counter variable
    framesSinceRaceEndedCopy = sdata->framesSinceRaceEnded;

    if (framesSinceRaceEndedCopy > 900) // 30 seconds
    {
        // start drawing the high score menu that shows the top 5 best times
        gGT->unknownFlags_1d44 |= 2;

        if ((framesSinceRaceEndedCopy < 1017) && ((gGT->unknownFlags_1d44 & 0x8000000) == 0))
        {
            if (framesSinceRaceEndedCopy < 1002)
            {
                startX_also_strFlags = -0x96;
                endX = 0x80;
                startFrame = framesSinceRaceEndedCopy - 901;
            }
            else
            {
                startX_also_strFlags = 0x80;
                endX = -0x96; // NOTE: Overflow if cast to short...
                startFrame = framesSinceRaceEndedCopy - 1001;
            }

            UI_Lerp2D_Linear(&pos[0], startX_also_strFlags, 10, endX, 10, startFrame, 20);

            TT_EndEvent_DrawHighScore(pos[0], pos[1], 0);

            if (framesSinceRaceEndedCopy < 1002)
            {
                startX_also_strFlags = 0x296;
                endX = 0x180;
                startFrame = framesSinceRaceEndedCopy - 0x385;
            }
            else
            {
                startX_also_strFlags = 0x180;
                endX = 0x296;
                startFrame = framesSinceRaceEndedCopy - 0x3e9;
            }

            UI_Lerp2D_Linear(&pos[0], startX_also_strFlags, 0x82, endX, 0x82, startFrame, 20);

            TT_EndEvent_DisplayTime(pos[0], pos[1], sdata->flags_timeTrialEndOfRace);

            // PRESS * TO CONTINUE
            DecalFont_DrawLine(sdata->lngStrings[201], 0x100, 0xbe, 1, 0xffff8000);

            // Cross or Circle, or if timer drags on too long
            if (((sdata->AnyPlayerTap & 0x50) != 0) && (framesSinceRaceEndedCopy < 1002))
            {
                framesSinceRaceEndedCopy = 0x3e9;
                sdata->menuReadyToPass |= 0x10;
            }
        }
        goto showMenuJump;
    }

    if (framesSinceRaceEndedCopy < 91)
    {
        if (framesSinceRaceEndedCopy < 66)
        {
            startX_also_strFlags = 0x14;
        }

        else // ened 66 frames ago or more
        {
            startX_also_strFlags = -0x96;
            startFrame = framesSinceRaceEndedCopy - 65;
        }

        // These next two functions are related to drawing
        // time and "Time Trial" in the top-left corner of screen

        UI_Lerp2D_Linear(&pos[0], 0x14, 8, startX_also_strFlags, 8, startFrame, 20);

        UI_DrawRaceClock(pos[0], pos[1], 0, gGT->drivers[0]);
        goto showMenuJump;
    }

    // If the race ended more than 120 frames ago (4 seconds)
    // Start moving "new high score" onto the screen, if necessary
    if ((framesSinceRaceEndedCopy > 120) &&

        (UI_Lerp2D_Linear(&pos[0], 0x264, 0x7a, 0x100, 0x7a, framesSinceRaceEndedCopy - 120, 20),

         // if there is a new high score
         gGT->newHighScoreIndex > -1))
    {
        // Change color of text every frame to make it blink
        // if current frame is odd: Default orange or new white color
        startX_also_strFlags = (gGT->timer & 1) ? 0xffff8000 : 0xffff8004; // Default orange or new white color

        // "NEW HIGH SCORE!"
        DecalFont_DrawLine(sdata->lngStrings[353], pos[0], pos[1], 1, startX_also_strFlags);

        // Total time should flash
        sdata->flags_timeTrialEndOfRace |= 4;
    }

    // If race ended more than 150 frames ago (5 seconds)
    // Start moving "New Best Lap" onto the screen, if necessary
    if (framesSinceRaceEndedCopy > 150)
    {
        // Fly-in Interpolation
        UI_Lerp2D_Linear(&pos[0], 0xffffff9c, 0x8e, 0x100, 0x8e, framesSinceRaceEndedCopy - 0x96, 20);

        if ((gGT->unknownFlags_1d44 & 0x4000000) != 0)
        {
            // Change color of text every frame to make it blink
            startX_also_strFlags = (gGT->timer & 1) ? 0xffff8000 : 0xffff8004; // Default orange or new white color

            // NEW BEST LAP!
            DecalFont_DrawLine(sdata->lngStrings[370], pos[0], pos[1], 1, startX_also_strFlags);

            // Check which of 3 laps was fastest
            // Make that row flash
            sdata->flags_timeTrialEndOfRace |= (gGT->lapIndexNewBest + 1) * 8;
        }
    }

    // Start moving "You Beat N Tropy" onto the screen, if necessary
    if (framesSinceRaceEndedCopy > 180) // 6 seconds
    {
        UI_Lerp2D_Linear(&pos[0], 0x264, 0xa2, 0x100, 0xa2, framesSinceRaceEndedCopy - 180, 20);

        // Change color of text every frame to make it blink
        startX_also_strFlags = (gGT->timer & 1) ? 0xffff8000 : 0xffff8004; // Default orange or new white color
        char *nTropyString;

        if ((sdata->gGT->unknownFlags_1d44 & 0x8000) == 0)
        {
            // If you did not just beat N Tropy
            if ((sdata->gGT->unknownFlags_1d44 & 0x10000000) == 0)
                goto nTropyNotBeatJump;

            // Only if you just beat N Tropy
            // YOU BEAT N. TROPY!
            nTropyString = sdata->lngStrings[372];
        }
        else
        {
            // N. TROPY OPENED!
            nTropyString = sdata->lngStrings[371];
        }

        // Draw the "N Tropy" related string
        DecalFont_DrawLine(nTropyString, pos[0], pos[1], 1, startX_also_strFlags);
    }

nTropyNotBeatJump:

    UI_Lerp2D_Linear(&pos[0], -0x64, 0x5a, 0x100, 0x5a, framesSinceRaceEndedCopy - 90, 20);

    TT_EndEvent_DisplayTime(pos[0], pos[1], sdata->flags_timeTrialEndOfRace);

    // PRESS * TO CONTINUE
    DecalFont_DrawLine(sdata->lngStrings[201], 0x100, 0xbe, 1, 0xffff8000);

    // If you press Cross or Circle
    if ((sdata->AnyPlayerTap & 0x50) != 0)
    {
        // advance timer, quickly skip to see high scores
        framesSinceRaceEndedCopy = 901; // 30 seconds
    }

showMenuJump:
    if ((!(sdata->menuReadyToPass & 1)) && (1016 < framesSinceRaceEndedCopy))
    {
        // Start drawing high scores
        sdata->menuReadyToPass &= ~(0x10) | 1;

        sdata->flags_timeTrialEndOfRace = 0;

        // If ghost is not too big to save
        if (!sdata->boolGhostTooBigToSave)
        {
            // Show end of race menu with "Save Ghost" option
            ptrMenuBox = &menuBox224_ghost;
        }

        // If ghost is too big to save
        else
        {
            // Show end of race menu without "Save Ghost" option
            ptrMenuBox = &menuBox224_basic
        }

        // Draw end of race menu, see 221 and 222 for more info
        MENUBOX_Show(ptrMenuBox);
    }
    sdata->framesSinceRaceEnded = framesSinceRaceEndedCopy;
}

/* NOTE: We could save space by just using one MenuBox 
and switch the MenuRows programatically */

void UI_RaceEnd_MenuBoxFuncPtr(struct MenuBox *);

struct MenuRow menuRows224_ghost[6] =
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

struct MenuBox menuBox224_ghost =
    {
        .stringIndexTitle = 0xFFFF,
        .posX_curr = 256,
        .posY_curr = 160,
        .unk1 = 0,
        .state = (0x800 | EXECUTE_FUNCPTR | USE_SMALL_FONT | CENTER_ON_COORDS), // 0xC83
        .rows = menuRows224_ghost,
        .funcPtr = UI_RaceEnd_MenuBoxFuncPtr,
        .drawStyle = 4,
        // rest of variables all default zero
};

struct MenuRow menuRows224_basic[5] =
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

struct MenuBox menuBox224_basic =
    {
        .stringIndexTitle = 0xFFFF,
        .posX_curr = 256,
        .posY_curr = 160,
        .unk1 = 0,
        .state = (0x800 | EXECUTE_FUNCPTR | USE_SMALL_FONT | CENTER_ON_COORDS), // 0xC83
        .rows = menuRows224_basic,
        .funcPtr = UI_RaceEnd_MenuBoxFuncPtr,
        .drawStyle = 4,
        // rest of variables all default zero
};