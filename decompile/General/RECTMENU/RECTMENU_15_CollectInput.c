#include <common.h>

void DECOMP_RECTMENU_CollectInput()
{
	int i;
	int numListen;
	struct RectMenu* activeSub;
	
	sdata->AnyPlayerTap = 0;
	sdata->AnyPlayerHold = 0;
	activeSub = sdata->activeSubMenu;
	
	// what "actually" is the logic here? what gets set, when?
	// this contradicts logic in RECTMENU_ProcessInput where only P1 is listened to
	if((activeSub == 0) || (numListen = 4, (activeSub->state & ALL_PLAYERS_USE_MENU) != 0))
	{
		numListen = sdata->gGT->numPlyrNextGame;
	}
	
	struct GamepadBuffer* gb = 
		&sdata->gGamepads->gamepad[0];
	
#ifdef REBUILD_PS1	
	if ((gb[0].buttonsTapped & BTN_CROSS) != 0)
	{
		gb[1].buttonsTapped = BTN_CROSS;
		gb[2].buttonsTapped = BTN_CROSS;
		gb[3].buttonsTapped = BTN_CROSS;
	}
	else
	{
		gb[1].buttonsTapped = 0;
		gb[2].buttonsTapped = 0;
		gb[3].buttonsTapped = 0;
	}
	
	sdata->gameProgress.unlocks[0] = -1;
#endif

	for(i = 0; i < numListen; i++)
	{
		sdata->buttonTapPerPlayer[i] = gb->buttonsTapped;
		sdata->buttonHeldPerPlayer[i] = gb->buttonsHeldCurrFrame;
		gb++;

		sdata->AnyPlayerTap |= sdata->buttonTapPerPlayer[i];
		sdata->AnyPlayerHold |= sdata->buttonHeldPerPlayer[i];
	}
}