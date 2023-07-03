#include <common.h>

/*
Ghidra name: FUN_8009f8c0
Status: Needs Review
Byte budget: 1052/ 1228
Called in:
  - 224.c
*/

void TT_EndEvent_DrawHighScore(short paramX, int paramY, short mode)

{
    // This is different from High Score in Main Menu because Main Menu
    // does not show the rank icons '1', '2', '3', '4', '5'

    char *trackTimeString;
    int iVar3;
    u_int *trackTime;
    short sVar5;
    short unk_text_flags;
    short pos[2];
    RECT rectangle;
    struct HighScoreTrack *highScoreTrack;
    unsigned short local_40; // NOTE used before initialization
    unsigned int unk_counter = 0;
    struct GameTracker *gGT = sdata->gGT;

    struct Driver *driver = gGT->drivers[0];

    // 0x49*4 = 0x124, size of each HighScoreTrack
    // 0x24*4 = sizeof(highScoreEntry)*6, which changes from Time Trial to Relic
    highScoreTrack = (struct HighScoreTrack *)sdata->gameProgress.highScoreTracks + (int)mode * 0x24 + sdata->gGT->levelID * 0x49;

    // Fly-in Interpolation
    UI_Lerp2D_Linear(&pos[0], (int)paramX, paramY, (int)paramX, paramY, sdata->framesSinceRaceEnded, 0x14);

    // "BEST TIMES"
    DecalFont_DrawLine(sdata->lngStrings[369], (int)pos[0], (int)pos[1], 1, 0xffff8000);

    for (int i = 0; i < 5; i++)
    {
        // Draw icon, name, and time of the
        // 5 best times in Time Trial

        // pointer to the track time of this high score
        trackTime = &highScoreTrack->scoreEntry[i + 1].time; // TODO: Verify if i or i+1

        // If this loop index is a new high score
        if ((int)gGT->newHighScoreIndex == i)
        {
            // make name color flash every odd frame
            sVar5 = 4;

            // if timer on clock is an even number
            if ((gGT->timer & 2) == 0)
            {
                // use default color
                sVar5 = *(short *)((int)trackTime + 0x16) + 5;
            }

            // flash color of time
            unk_text_flags = (short)((gGT->timer & 2) << 1);
        }

        // If your current time is not on "best times" list
        else
        {
            // dont flash color of time
            unk_text_flags = 0;

            // dont flash color of name, stick with default
            sVar5 = *(short *)((int)trackTime + 0x16) + 5;
        }
        iVar3 = (paramY + 0x11) + (unk_counter & 0xffff);

        // Make a rank on the high score list ('1', '2', '3', '4', '5')
        // by taking the binary value of the rank (0, 1, 2, 3, 4),
        // and adding the ascii value of '1'
        char *unk_memoryAddress = (char *)0x8009f700;
        *unk_memoryAddress = (char)i + '1';

        // Draw String for Rank ('1', '2', '3', '4', '5')
        DecalFont_DrawLine(unk_memoryAddress, (int)(((u_int)(paramX - 0x52) + 0x20) * 0x10000) >> 0x10,
                           (iVar3 - 1) * 0x10000 >> 0x10, 2, 4);

        // Draw Character Icon
        // NOTE: First param needs review
        short characterIconID = *(short *)(&data.MetaDataCharacters->iconID + (*(short *)((int)trackTime + 0x16)) * 0x10);
        MENUBOX_DrawPolyGT4((struct Icon *)(gGT->ptrIcons[characterIconID]),
                            (short)(paramX - 0x52), ((paramY + 0x11) * 0x10000 >> 0x10) + (short)unk_counter,
                            &gGT->backBuffer->primMem,
                            gGT->tileView->ptrOT,
                            (u_int *)0x800a04d0, (u_int *)0x800a04d0, (u_int *)0x800a04d0, (u_int *)0x800a04d0, 1, 0x1000);

        // Draw Name, which is 4 bytes after pointer to Time (puVar6)
        DecalFont_DrawLine(highScoreTrack->scoreEntry[i + 1].name, ((int)(paramX - 0x1f)), iVar3 * 0x10000 >> 0x10, 3, (int)sVar5);

        // make a string for time
        trackTimeString = MENUBOX_DrawTime(*trackTime);

        // Draw time
        DecalFont_DrawLine(trackTimeString, ((int)(paramX - 0x1f)), (iVar3 + 0x11) * 0x10000 >> 0x10, 2, (int)unk_text_flags);

        // If this loop index is a new high score
        if ((int)gGT->newHighScoreIndex == i)
        {
            // Check the order that variables are declared on stack
            // These four variables are actually a RECT starting at local_60
            rectangle.x = local_40 - 4;
            rectangle.y = (short)(paramY + 0x11) + (short)unk_counter - 1;
            rectangle.w = 0xab;
            rectangle.h = 0x1a;

            // Draw a rectangle to highlight your time on the "Best Times" list
            CTR_Box_DrawClearBox(&rectangle, &sdata->menuRowHighlight_Normal, 1,
                                 gGT->tileView->ptrOT,
                                 &gGT->backBuffer->primMem);
        }

        sVar5 = paramX;

        unk_counter += 0x1a;
    }

    // If this is Time Trial Mode
    if (mode == 0)
    {
        // Change the way text flickers
        unk_text_flags = -0x8000;

        // If you got a new best lap
        if (((gGT->unknownFlags_1d44 & 0x4000000) != 0) && ((gGT->timer & 2) != 0))
        {
            // Same logic to make text flicker as earlier in the function, but different colors
            unk_text_flags = -0x7ffc;
        }

        // "BEST LAP"
        DecalFont_DrawLine(sdata->lngStrings[368], (int)paramX, (int)((short)(paramY) + 0x95), 1,
                           0xffff8000);

        // make a string for best lap
        // NOTE: Verify this
        trackTimeString = MENUBOX_DrawTime(highScoreTrack->scoreEntry->time);

        // Print amount of time
        DecalFont_DrawLine(trackTimeString, (int)sVar5, (paramY + 0xa6) * 0x10000 >> 0x10, 2, (int)unk_text_flags);
    }

    // If this is Relic Mode
    else
    {
        // "YOUR TIME"
        DecalFont_DrawLine(sdata->lngStrings[197], (int)paramX,
                           (paramY + 0x95) * 0x10000 >> 0x10, 1, 0xffff8000);

        // make a string for your current track time
        trackTimeString = MENUBOX_DrawTime(driver->timeElapsedInRace);

        // Print amount of time
        DecalFont_DrawLine(trackTimeString, (int)sVar5, (paramY + 0xa6) * 0x10000 >> 0x10, 2, -0x8000);
    }

    rectangle.w = 0xc0;
    rectangle.h = 0xb4;
    rectangle.x = pos[0] - 0x60;
    rectangle.y = pos[1] - 4;

    // Draw 2D Menu rectangle background
    MENUBOX_DrawInnerRect(&rectangle, 4, gGT->backBuffer->otMem.startPlusFour);

    return;
}