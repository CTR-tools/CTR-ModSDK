#include <common.h>

extern u_int UDCTRM_MI_mirrorMode; 

void SwapDirection(u_int toggle)
{
	char normal[] = {BTN_LEFT, BTN_RIGHT};
	char swap[] = {BTN_RIGHT, BTN_LEFT};
	for (char i = 0; i < 2; i++)
		data.gamepadMapBtn[i + 2].output = (toggle) ? swap[i] : normal[i];
}

void Remap_Main()
{
	if ((sdata->gGT->gameMode1 & (PAUSE_1 | END_OF_RACE | MAIN_MENU)) == 0)
		SwapDirection(UDCTRM_MI_mirrorMode);
	else
		SwapDirection(0);
}