#include <common.h>

void DECOMP_AH_WarpPad_MenuBoxFuncPtr(struct MenuBox* mb)
{
	struct GameTracker* gGT = sdata->gGT;
	
	if(mb->rowSelected == 0)
	{
		gGT->gameMode2 |= TOKEN_RACE;
	}
	
	else
	{
		gGT->gameMode1 |= RELIC_RACE;
	}
	
	// optimizes to JMP
	DECOMP_MENUBOX_Hide(mb);
	return;
}