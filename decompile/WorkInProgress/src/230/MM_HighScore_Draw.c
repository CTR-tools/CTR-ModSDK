#include <common.h>

void MM_HighScore_Draw(u_short trackIndex, u_int rowIndex, u_int posX, u_int posY)
{
    char i;
    short numColor;
    short sVar1;
    short lineWidth;
    u_char **colorPtr;
    short levelID;
    struct HighScoreEntry *entry;
    u_int uVar9;
    u_int uVar10;
    RECT videoBox;
    short offsetX;
    short offsetY;

    struct GameTracker *gGT = sdata->gGT;

    offsetX = (short)posX;
    uVar10 = posX & 0xffff;
    offsetY = (short)posY;
    uVar9 = posY & 0xffff;

    numColor = ((sdata->frameCounter & 4) == 0) ? RED : ORANGE;

    levelID = OVR_230.arcadeTracks[trackIndex].levID;

    lineWidth = DecalFont_GetLineWidth(sdata->lngStrings[data.MetaDataLEV[levelID].name_LNG], 1);

    lineWidth = (short)(lineWidth - (lineWidth >> 15) >> 1);

    // get color data
    colorPtr = (u_char **)&data.ptrColor[numColor];

    struct Icon **iconPtrArray =
        ICONGROUP_GETICONS(gGT->iconGroup[4]);

    // Draw arrow pointing Left
    DecalHUD_Arrow2D(
        // largeFont arrow
        iconPtrArray[0x38],

        (offsetX - lineWidth) + 0xec,
        offsetY + 0x15,

        // pointer to PrimMem struct
        &gGT->backBuffer->primMem,
        // pointer to OT mem
        gGT->tileView_UI.ptrOT,
        *colorPtr[0],
        *colorPtr[1],
        *colorPtr[2],
        *colorPtr[3],

        0, 0x1000, 0x800);

    DecalHUD_Arrow2D(
        // largeFont arrow
        iconPtrArray[0x38],

        (lineWidth + offsetX) + 0x112,
        offsetY + 0x15,

        // pointer to PrimMem struct
        &gGT->backBuffer->primMem,
        // pointer to PrimMem struct
        gGT->tileView_UI.ptrOT,

        *colorPtr[0],
        *colorPtr[1],
        *colorPtr[2],
        *colorPtr[3],

        0, 0x1000, 0);

    // draw track name
    DecalFont_DrawLine(sdata->lngStrings[data.MetaDataLEV[levelID].name_LNG],
                       (short)(posX + 0x100),
                       (short)(posY + 0xe),
                       FONT_BIG, JUSTIFY_CENTER);

    if ((rowIndex & 0xffff) == 0)
    {
        for (i = 0; i < 2; i++)
        {
            GAMEPROG_GetPtrHighScoreTrack();
            if (CHECK_ADV_BIT(
                sdata->gameProgress.highScoreTracks[levelID].timeTrialFlags,
                OVR_230.highscore_unkflags[i]) != 0)
                {
                    colorPtr = (u_char **)&data.ptrColor[OVR_230.colorIndexArray[i]];

                    DecalHUD_DrawPolyGT4(gGT->iconGroup[5][10].name,
                                         offsetX + (i * 0x10) + 0xf0,
                                         offsetY + 4,
                                         // pointer to PrimMem struct
                                         &gGT->backBuffer->primMem,
                                         // pointer to OT mem
                                         gGT->tileView_UI.ptrOT,
                                         *colorPtr[0],
                                         *colorPtr[1],
                                         *colorPtr[2],
                                         *colorPtr[3], 0, 0x1000);
                }
        }
        GAMEPROG_GetPtrHighScoreTrack();
    }

    entry = sdata->gameProgress.highScoreTracks[levelID].scoreEntry[rowIndex];

    u_int iconColor = OVR_230.highscore_iconColor;

    MM_HighScore_Text3D(sdata->lngStrings[0xb3], (uVar10 + 0x20), (uVar9 + 0x2b), FONT_SMALL, 0);

    // If you're in Time Trial section of High Scores
    if (rowIndex == 0)
    {
        // "BEST LAP TIME:"
        MM_HighScore_Text3D(sdata->lngStrings[0xb4], (uVar10 + 0x124), (uVar9 + 0x2b), FONT_SMALL, 0);

        // Character Name
        MM_HighScore_Text3D(entry->name,
                            (uVar10 + 0x160),
                            (uVar9 + 0x39),
                            FONT_BIG,
                            entry->characterID + 5);

        // Draw time string
        MM_HighScore_Text3D(MENUBOX_DrawTime(entry->time),
                            (uVar10 + 0x160),
                            (uVar9 + 0x4a),
                            FONT_SMALL, 0);
        // Character Icon
        MENUBOX_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[entry->characterID].iconID],

                            offsetX + 0x124, offsetY + 0x38,
                            // pointer to PrimMem struct
                            &gGT->backBuffer->primMem,
                            // pointer to OT mem
                            (gGT->tileView_UI).ptrOT,

                            iconColor, iconColor, iconColor, iconColor,
                            1, 0x1000);
    }

    // Draw five "best track times"
    // Icon, Name, and Time

    for (i = 0; i < 5; i++)
    {
        entry = sdata->gameProgress.highScoreTracks[levelID].scoreEntry[rowIndex];
        char j = i + 2;

        // Character Icon
        MENUBOX_DrawPolyGT4(gGT->ptrIcons[data.MetaDataCharacters[entry->characterID].iconID],

                            OVR_230.transitionMeta_HighScores[j * 5].currX + offsetX + 0x20,
                            OVR_230.transitionMeta_HighScores[j * 5].currY + offsetY + (i << 0xf) + 0x39,
                            // pointer to PrimMem struct
                            &gGT->backBuffer->primMem,
                            // pointer to OT mem
                            gGT->tileView_UI.ptrOT,

                            iconColor, iconColor, iconColor, iconColor, 1, 0x1000);

        // draw the name string
        MM_HighScore_Text3D(entry->name,
                            OVR_230.transitionMeta_HighScores[j * 5].currX + uVar10 + 0x5c,
                            OVR_230.transitionMeta_HighScores[j * 5].currY + uVar9 + (i * 0x1f) + 0x39,
                            FONT_BIG,
                            entry->characterID + 5);

        // draw the Time string
        MM_HighScore_Text3D(MENUBOX_DrawTime(entry->time),
                            OVR_230.transitionMeta_HighScores[j * 5].currX + uVar10 + 0x5c,
                            OVR_230.transitionMeta_HighScores[j * 5].currY + uVar9 + (i * 0x1f) + 0x4a,
                            FONT_SMALL, 0);
    }

    videoBox.w = 0xb0;
    videoBox.h = 0x4b;
    videoBox.x = offsetX + 0x124;
    videoBox.y = offsetY + 0x5a;

    MM_TrackSelect_Video_Draw(&videoBox, &OVR_230.arcadeTracks, trackIndex, 0, 0);
}
