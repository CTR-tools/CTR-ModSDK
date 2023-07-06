#include <common.h>

/*
Ghidra name: FUN_8009f704
Status: Done
Byte budget: 308/444
Called in:
  - 224.c
*/
void DECOMP_TT_EndEvent_DisplayTime(int paramX, short paramY, u_int UI_DrawRaceClockFlags)
{
	struct GameTracker* gGT;
	struct Driver* d;
	short textWidth;
	short pos[2];
	RECT rectangle;
	
	gGT = sdata->gGT;
	d = gGT->drivers[0];

	textWidth = DecalFont_GetLineWidth(sdata->lngStrings[0xc4], 1);

	// Fly-in Interpolation
	UI_Lerp2D_Linear(&pos[0], (paramX - (0x88 - textWidth) / 2), paramY, (paramX - (0x88 - textWidth) / 2), paramY, sdata->framesSinceRaceEnded, 0x14);

	// "YOUR TIME"
	DecalFont_DrawLine(sdata->lngStrings[197], paramX, ((u_int)pos[1] - 0x4c), FONT_BIG, (CENTER_TEXT | ORANGE));

	UI_DrawRaceClock(pos[0], pos[1], UI_DrawRaceClockFlags, d);

	rectangle.x = (pos[0] - textWidth) - 6;
	rectangle.y = pos[1] - 0x50;

	rectangle.w = textWidth + 0x94;
	rectangle.h = 99;

	// Draw 2D Menu rectangle background
	MENUBOX_DrawInnerRect(&rectangle, 4, gGT->backBuffer->otMem.startPlusFour);

	return;
}