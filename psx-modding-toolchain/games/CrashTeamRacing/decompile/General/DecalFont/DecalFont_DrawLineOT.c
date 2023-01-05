#include <common.h>

void DecalFont_DrawLine(char* str, int posX, int posY, short fontType, int flags);

void DECOMP_DecalFont_DrawLineOT(char* str, int posX, int posY, short fontType, int flags, u_long* ot)
{
	// backup original
	u_long * backupOT;
	backupOT = sdata->gGT->camera110_UI.ptrOT;

	// set new
	sdata->gGT->camera110_UI.ptrOT = ot;

	// draw
	DecalFont_DrawLine(str, posX, posY, fontType, flags);

	// restore
	sdata->gGT->camera110_UI.ptrOT = backupOT;
}