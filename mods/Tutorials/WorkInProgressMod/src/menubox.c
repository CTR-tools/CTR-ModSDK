#include <common.h>

void DECOMP_MainFreeze_MenuPtrOptions(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy();

	u_int uVar6 = *(u_short *)&gGT->frontBuffer & 0xfeff;
	*(u_short *)&gGT->frontBuffer = uVar6;

	gGT->db[0].drawEnv.clip.y = 0;

	RECT glowingcursor;
	RECT menuBoxBG;

	glowingcursor.x = 40;
	glowingcursor.w = 40;
	glowingcursor.y = 128;
	glowingcursor.h = 50;
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	menuBoxBG.x = 0x38;
	menuBoxBG.w = 400;
	menuBoxBG.h = 0x87;
	menuBoxBG.y = 0x14;
	MENUBOX_DrawInnerRect(&menuBoxBG, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);

	if (sdata->AnyPlayerTap & (BTN_TRIANGLE | BTN_START | BTN_SQUARE_one))
	{
		OtherFX_Play(1, 1);
		OptionsMenu_TestSound(0, 0);
		MENUBOX_ClearInput();
		sdata->ptrDesiredMenuBox = MainFreeze_GetMenuBox();
	}
	return;
}
