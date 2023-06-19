#include <common.h>

u_int metaPhysID = 0;

force_inline void ProcessInputs(struct GameTracker* gGT, int* driverClass, u_int buttonsTapped)
{
	if (buttonsTapped & BTN_L1) metaPhysID = (metaPhysID + 64) % 65;
	if (buttonsTapped & BTN_R1) metaPhysID = (metaPhysID + 1) % 65;

	if (buttonsTapped & BTN_L2) *driverClass = (*driverClass + 3) % 4;
	if (buttonsTapped & BTN_R2) *driverClass = (*driverClass + 1) % 4;

	if (gGT->gameMode1 & PAUSE_ALL)
	{
		if (gGT->cooldownfromPauseUntilUnpause == 0)
		{
			if (buttonsTapped & (BTN_SELECT | BTN_START))
			{
				VehInit_SetConsts(gGT->drivers[0]);
				MENUBOX_ClearInput();
				gGT->gameMode1 &= ~PAUSE_1;
				MainFrame_TogglePauseAudio(0);
				OtherFX_Play(1, 1);
				MainFreeze_SafeAdvDestroy();
				ElimBG_Deactivate(gGT);
				MENUBOX_Hide(sdata->ptrActiveMenuBox);
				gGT->cooldownFromUnpauseUntilPause = 5;
			}
		}
	}
}

force_inline void DisplayMenuBox(struct GameTracker* gGT, int* driverClass)
{
	extern RECT r;
	extern RECT glowingcursor;
	char metaPhys[] = "         ";
	char metaPhysIDString[] = "     ";
	
	char* driverClassString[4] =
	{
		"BALANCED",
		"ACCELERATION",
		"SPEED",
		"TURN",
		//"UNLIMITED"
	};

	// driver stats that differ between classes are colored blue
	// only 9 stats are in this category
	u_int metaPhysColor = ORANGE;
	if
	(
		metaPhysID == 9 || metaPhysID == 11 || metaPhysID == 12 || metaPhysID == 18 ||
		metaPhysID == 20 || metaPhysID == 21 || metaPhysID == 22 || metaPhysID == 42 || metaPhysID == 61
	)
		metaPhysColor = BLUE;

	sprintf(metaPhys, "%d\n", data.metaPhys[metaPhysID].value[*driverClass]);
	sprintf(metaPhysIDString, "%d\n", metaPhysID);

	DecalFont_DrawLine(driverClassString[*driverClass], SCREEN_WIDTH/2, SCREEN_HEIGHT/4, FONT_BIG, (CENTER_TEXT | ORANGE)); // display current driver class
	DecalFont_DrawLine(metaPhysIDString, SCREEN_WIDTH/2, SCREEN_HEIGHT/3, FONT_BIG, (CENTER_TEXT | metaPhysColor)); // display current metaPhys ID
	DecalFont_DrawLine(metaPhys, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, FONT_BIG, (CENTER_TEXT | metaPhysColor)); // display current metaPhys value

	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor

	MENUBOX_DrawInnerRect(&r, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menubox background
}

// the MenuBox function
void heyguys(struct MenuBox*)
{
	MainFreeze_SafeAdvDestroy(); // probably mandatory

	ProcessInputs(sdata->gGT, &data.MetaDataCharacters[data.characterIDs[0]].engineID, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenuBox(sdata->gGT, &data.MetaDataCharacters[data.characterIDs[0]].engineID);
}