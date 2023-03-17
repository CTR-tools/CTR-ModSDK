#include <common.h>

void DECOMP_DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, u_long* ot)
{
	// backup original
	u_long * backupOT;
	backupOT = sdata->gGT->tileView_UI.ptrOT;

	// set new
	sdata->gGT->tileView_UI.ptrOT = ot;

	// draw
	DecalFont_DrawLine(str, posX, posY, fontType, flags);

	// restore
	sdata->gGT->tileView_UI.ptrOT = backupOT;
}