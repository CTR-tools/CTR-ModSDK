void TT_EndEvent_DisplayTime(int paramX, short paramY, u_int UI_DrawRaceClockFlags)
{
	short strLineWidthTOTAL;
	u_int drivers;
	short posX;
	u_short posY;
	struct RECT rectangle;
	
	drivers = sdata->gGT->drivers[0];
	
	// "TOTAL"
	strLineWidthTOTAL = DecalFont_GetLineWidth(lngStrings[0x310], 1);
	
	// Fly-in Interpolation
	UI_Lerp2D_Linear(&posX, (paramX - (0x88 - (int)strLineWidthTOTAL) / 2) * 0x10000 >> 0x10, (int)paramY, (paramX - (0x88 - (int)strLineWidthTOTAL) / 2) * 0x10000 >> 0x10, (int)paramY, sdata->framesSinceRaceEnded, 0x14);
				 
	// "YOUR TIME"
	DecalFont_DrawLine(sdata->lngStrings[0x314], (int)paramX, (int)(((u_int)posY - 0x4c) * 0x10000) >> 0x10, 1, 0xffff8000);
				 
	UI_DrawRaceClock((int)posX, (int)(short)posY, UI_DrawRaceClockFlags, drivers);
	
	strLineWidthTOTAL = DecalFont_GetLineWidth(sdata->lngStrings[0x310], 1);
	
	rectangle.x = (posX - strLineWidthTOTAL) - 6;
	rectangle.y = posY - 0x50;
	
	rectangle.w = DecalFont_GetLineWidth(sdata->lngStrings[0x310], 1);
	
	rectangle.w = rectangle.w + 0x94;
	rectangle.h = 99;
	
	// Draw 2D Menu rectangle background
	MenuBox_DrawInnerRect(&rectangle, 4, sdata->gGT->backBuffer->otMem.startPlusFour);
	
	return;
}