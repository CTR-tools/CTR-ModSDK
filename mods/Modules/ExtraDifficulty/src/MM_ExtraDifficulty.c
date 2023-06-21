#include <common.h>
#include "extradifficulty.h"

void MM_ExtraDifficulty(struct MenuBox* mb)
{
	short row = mb->rowSelected;

	// if uninitialized
	if (row == -1)
	{
		mb->ptrPrevBox_InHierarchy->state &= ~(ONLY_DRAW_TITLE | DRAW_NEXT_MENU_IN_HIERARCHY);
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
			sdata->gGT->arcadeDifficulty = OVR_230.cupDifficultySpeed[row];

		OVR_230.desiredMenu = 2;
		OVR_230.MM_State = 2;
		mb->state |= ONLY_DRAW_TITLE;
	}
}