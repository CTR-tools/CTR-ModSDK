#include <common.h>

void SwapDirection(u_int toggle)
{
	char normal[] = {BTN_LEFT, BTN_RIGHT};
	char swap[] = {BTN_RIGHT, BTN_LEFT};
	for (char i = 0; i < 2; i++)
		data.gamepadMapBtn[i + 2].output = (toggle) ? swap[i] : normal[i];
}

void Remap_Main()
{
#define toggle *(int *)0x8000FFF0

	if ((sdata->gGT->gameMode1 & (PAUSE_1 | END_OF_RACE | MAIN_MENU)) == 0)
		SwapDirection(toggle);
	else
		SwapDirection(0);
}