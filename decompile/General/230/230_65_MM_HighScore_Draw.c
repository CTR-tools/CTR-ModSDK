#include <common.h>

void MM_HighScore_Draw(u_short trackIndex, u_int rowIndex, u_int posX, u_int posY)
{
    char i;
    short numColor;
    short sVar1;
    short lineWidth;
    int* colorPtr;
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

    levelID = OVR_230.arcadeTracks[trackIndex].levID;

    lineWidth = DecalFont_GetLineWidth(sdata->lngStrings[data.metaDataLEV[levelID].name_LNG], 1);
    lineWidth = lineWidth >> 1;

    // get color data
    numColor = ((sdata->frameCounter & 4) == 0) ? RED : ORANGE;
    colorPtr = data.ptrColor[numColor];

    struct Icon **iconPtrArray =
        ICONGROUP_GETICONS(gGT->iconGroup[4]);

    // Draw arrow pointing Left
    DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        OVR_230.transitionMeta_HighScores[0].currX + (offsetX - lineWidth) + 0xec,
        OVR_230.transitionMeta_HighScores[0].currY + offsetY + 0x15,
        &gGT->backBuffer->primMem,
        gGT->tileView_UI.ptrOT,
        colorPtr[0],
        colorPtr[1],
        colorPtr[2],
        colorPtr[3],
        0, 0x1000, 0x800);

	// Draw arrow pointing Right
    DecalHUD_Arrow2D(
        iconPtrArray[0x38],
        OVR_230.transitionMeta_HighScores[0].currX + (lineWidth + offsetX) + 0x112,
        OVR_230.transitionMeta_HighScores[0].currY + offsetY + 0x15,
        &gGT->backBuffer->primMem,
        gGT->tileView_UI.ptrOT,
        colorPtr[0],
        colorPtr[1],
        colorPtr[2],
        colorPtr[3],
        0, 0x1000, 0);

    // draw track name
    DecalFont_DrawLine(
		sdata->lngStrings[data.metaDataLEV[levelID].name_LNG],
		OVR_230.transitionMeta_HighScores[0].currX + (short)(posX + 0x100),
		OVR_230.transitionMeta_HighScores[0].currY + (short)(posY + 0xe),
		FONT_BIG, JUSTIFY_CENTER);
					   
    u_int iconColor = OVR_230.highscore_iconColor;

	// "BEST TRACK TIMES"
    MM_HighScore_Text3D(sdata->lngStrings[0xb3], 
		OVR_230.transitionMeta_HighScores[1].currX + (uVar10 + 0x20), 
		OVR_230.transitionMeta_HighScores[1].currY + (uVar9 + 0x2b), 
		FONT_SMALL, 0);
	
	// first entry: Time Trial or Relic
    entry = &sdata->gameProgress.highScoreTracks[levelID].scoreEntry[rowIndex*6];

	// if Time Trial
	// with ghost stars, and Best Lap
    if ((rowIndex & 0xffff) == 0)
    {
		// draw ghost stars
        for (i = 0; i < 2; i++)
        {	
            if (
					((
						sdata->gameProgress.highScoreTracks[levelID].timeTrialFlags >>
						OVR_230.highscore_unkflags[i]
					)&1) != 0
				)
                {
                    colorPtr = data.ptrColor[OVR_230.colorIndexArray[i]];

					struct Icon** ptrIconArray;
					ptrIconArray = ICONGROUP_GETICONS(gGT->iconGroup[5]);

                    DecalHUD_DrawPolyGT4(
						ptrIconArray[0x37],
						OVR_230.transitionMeta_HighScores[0].currX + offsetX + (i * 0x10) + 0xf0,
						OVR_230.transitionMeta_HighScores[0].currY + offsetY + 4,
						// pointer to PrimMem struct
						&gGT->backBuffer->primMem,
						// pointer to OT mem
						gGT->tileView_UI.ptrOT,
						colorPtr[0],
						colorPtr[1],
						colorPtr[2],
						colorPtr[3], 0, 0x1000);
                }
        }
		
        // "BEST LAP TIME:"
        MM_HighScore_Text3D(
			sdata->lngStrings[0xb4], 
			OVR_230.transitionMeta_HighScores[7].currX + (uVar10 + 0x124), 
			OVR_230.transitionMeta_HighScores[7].currY + (uVar9 + 0x2b), 
			FONT_SMALL, 0);

        // Character Name
        MM_HighScore_Text3D(
			entry[0].name,
			OVR_230.transitionMeta_HighScores[7].currX + (uVar10 + 0x160),
			OVR_230.transitionMeta_HighScores[7].currY + (uVar9 + 0x39),
			FONT_BIG,
			entry[0].characterID + 5);

        // Draw time string
        MM_HighScore_Text3D(
			MENUBOX_DrawTime(entry[0].time),
			OVR_230.transitionMeta_HighScores[7].currX + (uVar10 + 0x160),
			OVR_230.transitionMeta_HighScores[7].currY + (uVar9 + 0x4a),
			FONT_SMALL, 0);
        // Character Icon
        MENUBOX_DrawPolyGT4(
			gGT->ptrIcons[data.MetaDataCharacters[entry[0].characterID].iconID],
			OVR_230.transitionMeta_HighScores[7].currX + (offsetX + 0x124), 
			OVR_230.transitionMeta_HighScores[7].currY + (offsetY + 0x38),
			&gGT->backBuffer->primMem,
			(gGT->tileView_UI).ptrOT,
			iconColor, iconColor, iconColor, iconColor,
			1, 0x1000);
    }

    // Draw five "best track times"
    // Icon, Name, and Time
    for (i = 0; i < 5; i++)
    {
        char j = i + 2;

        // Character Icon
        MENUBOX_DrawPolyGT4(
			gGT->ptrIcons[data.MetaDataCharacters[entry[i+1].characterID].iconID],
			OVR_230.transitionMeta_HighScores[j].currX + offsetX + 0x20,
			OVR_230.transitionMeta_HighScores[j].currY + offsetY + (i * 0x1f) + 0x39,
			&gGT->backBuffer->primMem,
			gGT->tileView_UI.ptrOT,
			iconColor, iconColor, iconColor, iconColor,
			1, 0x1000);

        // draw the name string
        MM_HighScore_Text3D(
			entry[i+1].name,
			OVR_230.transitionMeta_HighScores[j].currX + uVar10 + 0x5c,
			OVR_230.transitionMeta_HighScores[j].currY + uVar9 + (i * 0x1f) + 0x39,
			FONT_BIG,
			entry[i+1].characterID + 5);

        // draw the Time string
        MM_HighScore_Text3D(
			MENUBOX_DrawTime(entry[i+1].time),
			OVR_230.transitionMeta_HighScores[j].currX + uVar10 + 0x5c,
			OVR_230.transitionMeta_HighScores[j].currY + uVar9 + (i * 0x1f) + 0x4a,
			FONT_SMALL, 0);
    }

    videoBox.w = 0xb0;
    videoBox.h = 0x4b;
    videoBox.x = OVR_230.transitionMeta_HighScores[9].currX + offsetX + 0x124;
    videoBox.y = OVR_230.transitionMeta_HighScores[9].currY + offsetY + 0x5a;

    MM_TrackSelect_Video_Draw(
		&videoBox, &OVR_230.arcadeTracks, trackIndex, 
		(OVR_230.highScore_transitionState == EXITING_MENU), 0);
}
