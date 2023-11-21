#include <common.h>

#ifdef REBUILD_PC
int holdCurr=0;
int holdPrev=0;
int tap=0;
#endif

void DECOMP_MENUBOX_CollectInput()
{
	int i;
	int numListen;
	struct MenuBox* activeSub;
	
	sdata->AnyPlayerTap = 0;
	sdata->AnyPlayerHold = 0;
	activeSub = sdata->activeSubMenu;
	
	// what "actually" is the logic here? what gets set, when?
	// this contradicts logic in MENUBOX_ProcessInput where only P1 is listened to
	if((activeSub == 0) || (numListen = 4, (activeSub->state & ALL_PLAYERS_USE_MENU) != 0))
	{
		numListen = sdata->gGT->numPlyrNextGame;
	}
	
#ifdef REBUILD_PC
	if (WIN_GetPressUp())
		holdCurr |= BTN_UP;

	if (WIN_GetPressDown())
		holdCurr |= BTN_DOWN;

	if (WIN_GetPressLeft())
		holdCurr |= BTN_LEFT;

	if (WIN_GetPressRight())
		holdCurr |= BTN_RIGHT;

	if (WIN_GetPressCross())
		holdCurr |= BTN_CROSS;

	if (WIN_GetPressTriangle())
		holdCurr |= BTN_TRIANGLE;

	tap = holdCurr & ~holdPrev;
	holdPrev = holdCurr;

	sdata->buttonTapPerPlayer[0] = tap;
	sdata->buttonHeldPerPlayer[0] = holdCurr;
	
	if ((tap & BTN_CROSS) != 0)
	{
		sdata->buttonTapPerPlayer[1] = BTN_CROSS;
		sdata->buttonTapPerPlayer[2] = BTN_CROSS;
		sdata->buttonTapPerPlayer[3] = BTN_CROSS;
	}
	
	holdCurr = 0;

	sdata->gameProgress.unlocks[0] = -1;
#endif

	for(i = 0; i < numListen; i++)
	{
#ifndef REBUILD_PC
		sdata->buttonTapPerPlayer[i] = sdata->gGamepads->gamepad[i].buttonsTapped;
		sdata->buttonHeldPerPlayer[i] = sdata->gGamepads->gamepad[i].buttonsHeldCurrFrame;
#endif

		sdata->AnyPlayerTap |= sdata->buttonTapPerPlayer[i];
		sdata->AnyPlayerHold |= sdata->buttonHeldPerPlayer[i];
	}
}