#include <common.h>

// Does not fit byte budget
void DebugFont_Init(struct GameTracker* gGT)
{
	struct Icon* debugFontIcon = gGT->ptrIcons[0x42];
	
	if(debugFontIcon == 0) return;
	
	sdata->debugFont.pixelX = debugFontIcon->X1;
	sdata->debugFont.pixelY = debugFontIcon->Y1;
	sdata->debugFont.paletteXY = debugFontIcon->paletteXY;
	sdata->debugFont.pageXY = debugFontIcon->pageXY;
}