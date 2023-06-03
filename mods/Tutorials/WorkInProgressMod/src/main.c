#include <common.h>

int mike = 0;

RECT r =
{
	.x = 32,
	.w = 448,
	.y = 39,
	.h = 130,
};

int Hello_Main()
{
	if(sdata->gGT->numPlyrCurrGame == 1)
	{
		if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SELECT) mike = (mike + 1) % 2;

		if (mike)
		{
			DecalFont_DrawLine("and so it begins", 10, 190, FONT_SMALL, COCO_MAGENTA);
			MENUBOX_DrawInnerRect(&r, 4, (u_long*)(sdata->gGT->backBuffer->otMem).startPlusFour);
			MainFreeze_SafeAdvDestroy();
		}
	}
}