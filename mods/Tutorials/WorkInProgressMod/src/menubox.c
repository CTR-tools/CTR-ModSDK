#include <common.h>

extern RECT r;
u_int metaPhysID = 0;

void ProcessInputs(struct GameTracker* gGT, int* driverClass, u_int buttonsTapped)
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

// the main function
void heyguys(struct GameTracker* gGT)
{
	MainFreeze_SafeAdvDestroy(); // probably mandatory

	RECT glowingcursor;
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

	int* driverClass = &data.MetaDataCharacters[data.characterIDs[0]].engineID; // just a shorthand for the driver class

	// process inputs
	u_int buttonsTapped = sdata->gGamepads->gamepad[0].buttonsTapped;
	ProcessInputs(sdata->gGT, driverClass, buttonsTapped);

	//
	u_int metaPhysColor = ORANGE;
	if
	(
		metaPhysID == 9 || metaPhysID == 11 || metaPhysID == 12 || metaPhysID == 18 ||
		metaPhysID == 20 || metaPhysID == 21 || metaPhysID == 22 || metaPhysID == 42 || metaPhysID == 61
	)
		metaPhysColor = BLUE;

	sprintf(metaPhys, "%d\n", data.metaPhys[metaPhysID].value[*driverClass]);
	sprintf(metaPhysIDString, "%d\n", metaPhysID);

	DecalFont_DrawLine(driverClassString[*driverClass], SCREEN_WIDTH/2, SCREEN_HEIGHT/4, FONT_BIG, (CENTER_TEXT | ORANGE)); // draw current metaPhys value
	DecalFont_DrawLine(metaPhysIDString, SCREEN_WIDTH/2, SCREEN_HEIGHT/3, FONT_BIG, (CENTER_TEXT | metaPhysColor));
	DecalFont_DrawLine(metaPhys, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, FONT_BIG, (CENTER_TEXT | metaPhysColor)); // draw current metaPhys value

	// draw glowing cursor
	glowingcursor.x = 40;
	glowingcursor.w = 40;
	glowingcursor.y = 128;
	glowingcursor.h = 50;
	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour, &sdata->gGT->backBuffer->primMem);

	MENUBOX_DrawInnerRect(&r, 4, (u_long *)(sdata->gGT->backBuffer->otMem).startPlusFour); // draw the actual menubox background
}