#include <common.h>
#include "menubox.h"

u_int metaPhysID = 0;
u_int digitSelected = 0;

force_inline void ProcessInputs(struct GameTracker* gGT, int* driverClass, u_int buttonsTapped)
{
	// Triangle: Print class values to console log
	if (buttonsTapped & BTN_TRIANGLE)
	{
		for(int i = 0; i < 65; i++)
		{
			printf("%s - %s - %d\n", sdata->lngStrings[1 + *driverClass], sdata->lngStrings[10 + i], data.metaPhys[i].value[*driverClass]);
		}
	}

	// L1 & R1: switch stat
	if (buttonsTapped & BTN_L1) metaPhysID = (metaPhysID + 64) % 65;
	if (buttonsTapped & BTN_R1) metaPhysID = (metaPhysID + 1) % 65;

	// L2 & R2: change driver class
	if (buttonsTapped & BTN_L2) *driverClass = (*driverClass + 3) % 4;
	if (buttonsTapped & BTN_R2) *driverClass = (*driverClass + 1) % 4;

	// Left & Right: switch stat value digit
	if (buttonsTapped & BTN_LEFT) digitSelected = (digitSelected + 1) % 5;
	if (buttonsTapped & BTN_RIGHT) digitSelected = (digitSelected + 4) % 5;

	// Up & Down: increment/decrement stat value
	switch(digitSelected)
	{
		case 0:
			if (buttonsTapped & BTN_UP)
				data.metaPhys[metaPhysID].value[*driverClass] += 1;
			if (buttonsTapped & BTN_DOWN)
				data.metaPhys[metaPhysID].value[*driverClass] -= 1;
			break;
		case 1:
			if (buttonsTapped & BTN_UP)
				data.metaPhys[metaPhysID].value[*driverClass] += 10;
			if (buttonsTapped & BTN_DOWN)
				data.metaPhys[metaPhysID].value[*driverClass] -= 10;
			break;
		case 2:
			if (buttonsTapped & BTN_UP)
				data.metaPhys[metaPhysID].value[*driverClass] += 100;
			if (buttonsTapped & BTN_DOWN)
				data.metaPhys[metaPhysID].value[*driverClass] -= 100;
			break;
		case 3:
			if (buttonsTapped & BTN_UP)
				data.metaPhys[metaPhysID].value[*driverClass] += 1000;
			if (buttonsTapped & BTN_DOWN)
				data.metaPhys[metaPhysID].value[*driverClass] -= 1000;
			break;
		case 4:
			if (buttonsTapped & BTN_UP)
				data.metaPhys[metaPhysID].value[*driverClass] += 10000;
			if (buttonsTapped & BTN_DOWN)
				data.metaPhys[metaPhysID].value[*driverClass] -= 10000;
			break;
	}

	// Select: open and close menu (can also be closed with Start)
	if (gGT->gameMode1 & PAUSE_ALL)
	{
		if (gGT->cooldownfromPauseUntilUnpause == 0)
		{
			if (buttonsTapped & (BTN_SELECT | BTN_START))
			{
				VehInit_SetConsts(gGT->drivers[0]); // needed so the stat edit and class switch can actually happen

				if (buttonsTapped & BTN_SELECT)
				{
					// other stuff taken from the original game code (see MainFrame_GameLogic)
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
}

force_inline void DrawNumbers(struct GameTracker* gGT, int* driverClass, u_int color)
{
	u_int cursorX[5] = {ones.x + 3, tens.x + 3, hundreds.x + 3, thousands.x + 3, ten_thousands.x + 3};

	char metaPhysOnes[] = "  ";
	char metaPhysTens[] = "  ";
	char metaPhysHundreds[] = "  ";
	char metaPhysThousands[] = "  ";
	char metaPhysTen_Thousands[] = "  ";

	u_int onesValue = data.metaPhys[metaPhysID].value[*driverClass] % 10;
	u_int tensValue = (data.metaPhys[metaPhysID].value[*driverClass]/10) % 10;
	u_int hundredsValue = (data.metaPhys[metaPhysID].value[*driverClass]/100) % 10;
	u_int thousandsValue = (data.metaPhys[metaPhysID].value[*driverClass]/1000) % 10;
	u_int ten_thousandsValue = (data.metaPhys[metaPhysID].value[*driverClass]/10000) % 10;

	sprintf(metaPhysOnes, "%d\n", onesValue);
	sprintf(metaPhysTens, "%d\n", tensValue);
	sprintf(metaPhysHundreds, "%d\n", hundredsValue);
	sprintf(metaPhysThousands, "%d\n", thousandsValue);
	sprintf(metaPhysTen_Thousands, "%d\n", ten_thousandsValue);

	DecalFont_DrawLine(metaPhysOnes, ones.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysTens, tens.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysHundreds, hundreds.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysThousands, thousands.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysTen_Thousands, ten_thousands.x+5, ones.y + 5, FONT_BIG, color);

	glowingcursor.x = cursorX[digitSelected];

	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor

	MENUBOX_DrawInnerRect(&ones, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	MENUBOX_DrawInnerRect(&tens, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	MENUBOX_DrawInnerRect(&hundreds, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	MENUBOX_DrawInnerRect(&thousands, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	MENUBOX_DrawInnerRect(&ten_thousands, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
}

force_inline void DisplayMenuBox(struct GameTracker* gGT, int* driverClass)
{
	char metaPhysIDString[] = " ";
	
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

	sprintf(metaPhysIDString, "%d\n", metaPhysID);

	DecalFont_DrawLine(driverClassString[*driverClass], SCREEN_WIDTH/2, SCREEN_HEIGHT/4, FONT_SMALL, (CENTER_TEXT | ORANGE)); // display current driver class
	DecalFont_DrawLine(metaPhysIDString, SCREEN_WIDTH/2, SCREEN_HEIGHT/3, FONT_BIG, (CENTER_TEXT | metaPhysColor)); // display current metaPhys ID

	DrawNumbers(gGT, driverClass, metaPhysColor);

	MENUBOX_DrawInnerRect(&r, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menubox background
}

// the MenuBox function
void StatsEditor(struct MenuBox* mb)
{
	MainFreeze_SafeAdvDestroy(); // probably mandatory

	ProcessInputs(sdata->gGT, &data.MetaDataCharacters[data.characterIDs[0]].engineID, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenuBox(sdata->gGT, &data.MetaDataCharacters[data.characterIDs[0]].engineID);
}
