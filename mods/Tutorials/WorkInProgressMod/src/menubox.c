#include <common.h>

void DECOMP_MainFreeze_MenuPtrOptions(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy();

	// 0 for no racing wheels
	// 1 for racing wheels
	u_short areThereRacingWheels = 0;
	short sVar8 = (4 - areThereRacingWheels) - (u_short)sdata->gGT->numPlyrCurrGame;

	data.Options_HighlightBar_PosY[8][0] = sVar8 * -10 + 0x77;

	u_int uVar6 = *(u_short *)&gGT->frontBuffer & 0xfeff;
	*(u_short *)&gGT->frontBuffer = uVar6;

	if (2 < gGT->numPlyrCurrGame)
	{
		*(u_short *)&gGT->frontBuffer = uVar6 | 0x100;
	}

	gGT->db[0].drawEnv.clip.y = 0;

	RECT glowingcursor;
	RECT titleSeparatorLine;
	RECT menuBoxBG;

	glowingcursor.x = 0x4a;
	glowingcursor.w = 0x16c;
	glowingcursor.y = data.Options_HighlightBar_PosY[gGT->db[0].drawEnv.clip.y][0] + 0x14;
	glowingcursor.h = data.Options_HighlightBar_PosY[gGT->db[0].drawEnv.clip.y][1];
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	titleSeparatorLine.x = 66;
	titleSeparatorLine.y = 43;
	titleSeparatorLine.w = 380;
	titleSeparatorLine.h = 2;
	MENUBOX_DrawOuterRect_Edge(&titleSeparatorLine, (u_int)&sdata->battleSetup_Color_UI_1, 0x20, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour);

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
