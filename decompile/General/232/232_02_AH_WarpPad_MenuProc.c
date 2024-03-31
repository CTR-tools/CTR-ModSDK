#include <common.h>

void DECOMP_AH_WarpPad_MenuProc(struct RectMenu* menu)
{
	struct GameTracker* gGT = sdata->gGT;
	
	if(menu->rowSelected == 0)
	{
		gGT->gameMode2 |= TOKEN_RACE;
	}
	
	else
	{
		gGT->gameMode1 |= RELIC_RACE;
	}
	
	// optimizes to JMP
	DECOMP_RECTMENU_Hide(menu);
	return;
}