#include <common.h>

void DECOMP_DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, OTTYPE* ot)
{
	struct GameTracker* gGT;
	OTTYPE* backupOT;
	
	gGT = sdata->gGT;
	
	// backup
	backupOT = gGT->tileView_UI.ptrOT;

	// alter
	gGT->tileView_UI.ptrOT = ot;

	// draw
	DECOMP_DecalFont_DrawLine(str, posX, posY, fontType, flags);

	// reset
	gGT->tileView_UI.ptrOT = backupOT;
}