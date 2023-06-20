#include <common.h>

void DECOMP_MENUBOX_CollectInput()
{
	int i;
	int numListen;
	
	sdata->AnyPlayerTap = 0;
	sdata->AnyPlayerHold = 0;
	
	// what "actually" is the logic here? what gets set, when?
	// this contradicts logic in MENUBOX_ProcessInput where only P1 is listened to
	if((sdata->activeSubMenu == 0) || (numListen = 4, (sdata->activeSubMenu->state & ALL_PLAYERS_USE_MENU) != 0))
	{
		numListen = sdata->gGT->numPlyrNextGame;
	}
	
	for(i = 0; i < numListen; i++)
	{
		sdata->buttonTapPerPlayer[i] = sdata->gGamepads->gamepad[i].buttonsTapped;
		sdata->buttonHeldPerPlayer[i] = sdata->gGamepads->gamepad[i].buttonsHeldCurrFrame;
		
		sdata->AnyPlayerTap |= sdata->buttonTapPerPlayer[i];
		sdata->AnyPlayerHold |= sdata->buttonHeldPerPlayer[i];
	}
}