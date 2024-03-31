#include <common.h>
#include "extradifficulty.h"

void UDCTRM_ED_FuncPtr(struct RectMenu* menu)
{
	short row = menu->rowSelected;

	// if uninitialized
	if (row == -1)
	{
		menu->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
		return;
	}

	// if you are on a valid row
	if (row < EXD_VALID_ROWS)
	{
		if (row == ROW_SUPER_HARD)
			sdata->gGT->arcadeDifficulty = 0x140; // original super hard cheat value
		else if (row == ROW_ULTRA_HARD)
			sdata->gGT->arcadeDifficulty = 0x280; // popular ultra hard gameshark code
		else
			sdata->gGT->arcadeDifficulty = D230.cupDifficultySpeed[row];

		D230.desiredMenuIndex = 2;
		D230.MM_State = 2;
		menu->state |= ONLY_DRAW_TITLE;
	}
}