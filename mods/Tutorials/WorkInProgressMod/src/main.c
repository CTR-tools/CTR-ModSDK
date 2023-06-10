#include <common.h>

int isSelectPause = 0;

RECT r =
{
	.x = 32,
	.w = 448,
	.y = 39,
	.h = 130,
};

int Hello_Main()
{
	struct GameTracker* gGT = sdata->gGT;

	if (gGT->numPlyrCurrGame == 1)
	{
		if (sdata->gGamepads->gamepad[0].buttonsTapped & BTN_SELECT)
			isSelectPause = (isSelectPause + 1) % 2;

		if (isSelectPause)
		{
			DecalFont_DrawLine("and so it begins", 10, 190, FONT_SMALL, COCO_MAGENTA);

			//MENUBOX_DrawInnerRect(&r, 4, (u_long*)(gGT->backBuffer->otMem).startPlusFour);
		}
	}
}