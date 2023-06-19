#include <common.h>

extern RECT r;

void heyguys(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy();

	RECT glowingcursor;
	RECT menuBoxBG;

	glowingcursor.x = 40;
	glowingcursor.w = 40;
	glowingcursor.y = 128;
	glowingcursor.h = 50;
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	MENUBOX_DrawInnerRect(&r, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);
}
