#include <common.h>

void DECOMP_DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, u_long* ot)
{
	struct GameTracker* gGT;
	u_long * backupOT;
	
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