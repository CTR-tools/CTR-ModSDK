#include <common.h>
#include "menu.h"

u_int metaPhysID = 0;
u_int digitSelected = 0;

force_inline void ProcessInputs(struct GameTracker* gGT, int* metaPhys, int* driverClass, u_int buttonsTapped)
{
	// Triangle: Print class values to console log
	if (buttonsTapped & BTN_TRIANGLE)
	{
		for(int i = 0; i < 65; i++)
		{
			#if BUILD == UsaRetail
			printf
			(
				"%s - %s: %d\n", sdata->lngStrings[588 + *driverClass],
				sdata->lngStrings[593 + i],
				*(int*)((int)&data.metaPhys[i].size + *driverClass * 4) // fix for USAPentaUnlimited
			);
			#else
			printf
			(
				"%s - %s: %d\n", sdata->lngStrings[588 + *driverClass],
				sdata->lngStrings[593 + i],
				data.metaPhys[i].value[*driverClass]
			);
			#endif
			OtherFX_Play(0x6a, 1);
		}
	}

	if (buttonsTapped & (BTN_L1 | BTN_R1 | BTN_L2 | BTN_R2 | BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)) OtherFX_Play(0, 1);

	// L1 & R1: switch stat
	if (buttonsTapped & BTN_L1) metaPhysID = (metaPhysID + 64) % 65;
	if (buttonsTapped & BTN_R1) metaPhysID = (metaPhysID + 1) % 65;

	// L2 & R2: change driver class
	if (buttonsTapped & BTN_L2) *driverClass = (*driverClass + 4) % 5;
	if (buttonsTapped & BTN_R2) *driverClass = (*driverClass + 1) % 5;

	// Left & Right: switch stat value digit
	if (buttonsTapped & BTN_LEFT) digitSelected = (digitSelected + 1) % 5;
	if (buttonsTapped & BTN_RIGHT) digitSelected = (digitSelected + 4) % 5;

	int increase = 1;

	if (buttonsTapped & (BTN_UP | BTN_DOWN))
	{
		for(u_int i = 0; i < digitSelected; i++)
		{
			increase *= 10;
		}

		if (buttonsTapped & BTN_UP)
		{
			metaPhys[*driverClass] += increase;

			if ((data.metaPhys[metaPhysID].size == 1) && metaPhys[*driverClass] > 256)
				metaPhys[*driverClass] = 255;
			if ((data.metaPhys[metaPhysID].size == 2) && metaPhys[*driverClass] > 65536)
				metaPhys[*driverClass] = 65535;
		}

		if (buttonsTapped & BTN_DOWN)
		{
			metaPhys[*driverClass] -= increase;
			
			if ((data.metaPhys[metaPhysID].size == 1) && metaPhys[*driverClass] < -129)
				metaPhys[*driverClass] = -128;
			if ((data.metaPhys[metaPhysID].size == 2) && metaPhys[*driverClass] < -32769)
				metaPhys[*driverClass] = -32768;
		}
	}

	// Select: open and close menu (can also be closed with Start)
	if (gGT->gameMode1 & PAUSE_ALL)
	{
		if (gGT->cooldownfromPauseUntilUnpause == 0)
		{
			if (buttonsTapped & (BTN_SELECT | BTN_START))
			{
				VehBirth_SetConsts(gGT->drivers[0]); // needed so the stat edit and class switch can actually happen

				if (buttonsTapped & BTN_SELECT)
				{
					// other stuff taken from the original game code (see MainFrame_GameLogic)
					RECTMENU_ClearInput();
					gGT->gameMode1 &= ~PAUSE_1;
					MainFrame_TogglePauseAudio(0);
					OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate(gGT);
					RECTMENU_Hide(sdata->ptrActiveMenu);
					gGT->cooldownFromUnpauseUntilPause = FPS_DOUBLE(5);
				}
			}
		}
	}
}

force_inline void DrawNumbers(struct GameTracker* gGT, int* metaPhys, int* driverClass, u_int color)
{
	u_int cursorX[5] = {ones.x + 3, tens.x + 3, hundreds.x + 3, thousands.x + 3, ten_thousands.x + 3};

	char metaPhysOnes[] = "  ";
	char metaPhysTens[] = "  ";
	char metaPhysHundreds[] = "  ";
	char metaPhysThousands[] = "  ";
	char metaPhysTen_Thousands[] = "  ";

	u_int onesValue = metaPhys[*driverClass] % 10;
	u_int tensValue = (metaPhys[*driverClass]/10) % 10;
	u_int hundredsValue = (metaPhys[*driverClass]/100) % 10;
	u_int thousandsValue = (metaPhys[*driverClass]/1000) % 10;
	u_int ten_thousandsValue = (metaPhys[*driverClass]/10000) % 10;

	sprintf(metaPhysOnes, "%d\n", abs(onesValue));
	sprintf(metaPhysTens, "%d\n", abs(tensValue));
	sprintf(metaPhysHundreds, "%d\n", abs(hundredsValue));
	sprintf(metaPhysThousands, "%d\n", abs(thousandsValue));
	sprintf(metaPhysTen_Thousands, "%d\n", abs(ten_thousandsValue));

	if (metaPhys[*driverClass] < 0)
	{
		DecalFont_DrawLine("-", ten_thousands.x+5 - 27, ones.y + 5, FONT_BIG, color);
	}

	DecalFont_DrawLine(metaPhysOnes, ones.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysTens, tens.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysHundreds, hundreds.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysThousands, thousands.x+5, ones.y + 5, FONT_BIG, color);
	DecalFont_DrawLine(metaPhysTen_Thousands, ten_thousands.x+5, ones.y + 5, FONT_BIG, color);

	glowingcursor.x = cursorX[digitSelected];

	CTR_Box_DrawClearBox(&glowingcursor, &sdata->menuRowHighlight_Normal, 1, (u_long *)(gGT->backBuffer->otMem).startPlusFour, &gGT->backBuffer->primMem); // draw glowing cursor

	RECTMENU_DrawInnerRect(&ones, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	RECTMENU_DrawInnerRect(&tens, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	RECTMENU_DrawInnerRect(&hundreds, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	RECTMENU_DrawInnerRect(&thousands, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
	RECTMENU_DrawInnerRect(&ten_thousands, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour);
}

force_inline void DisplayMenu(struct GameTracker* gGT, int* metaPhys, int* driverClass)
{
	// driver stats that differ between classes are colored blue
	// only 9 stats are in this category
	u_int metaPhysColor = ORANGE;
	if
	(
		metaPhysID == 9 || metaPhysID == 11 || metaPhysID == 12 || metaPhysID == 18 ||
		metaPhysID == 20 || metaPhysID == 21 || metaPhysID == 22 || metaPhysID == 42 || metaPhysID == 61
	)
		metaPhysColor = BLUE;

	DecalFont_DrawLine(sdata->lngStrings[588 + *driverClass], SCREEN_WIDTH/2, SCREEN_HEIGHT/4, FONT_SMALL, (JUSTIFY_CENTER | ORANGE)); // display current driver class
	DecalFont_DrawLine(sdata->lngStrings[593 + metaPhysID], SCREEN_WIDTH/2, SCREEN_HEIGHT/3, FONT_SMALL, (JUSTIFY_CENTER | metaPhysColor)); // display current metaPhys ID

	DrawNumbers(gGT, metaPhys, driverClass, metaPhysColor);

	RECTMENU_DrawInnerRect(&r, 4, (u_long *)(gGT->backBuffer->otMem).startPlusFour); // draw the actual menu background
}

// the Menu function
void StatsEditor(struct RectMenu* menu)
{
	MainFreeze_SafeAdvDestroy(); // probably mandatory

	#if BUILD == UsaRetail
		int* metaPhys = &data.metaPhys[metaPhysID].size; // fix for USAPentaUnlimited
	#else
		int* metaPhys = data.metaPhys[metaPhysID].value;
	#endif

	ProcessInputs(sdata->gGT, metaPhys, &data.MetaDataCharacters[data.characterIDs[0]].engineID, sdata->gGamepads->gamepad[0].buttonsTapped);
	DisplayMenu(sdata->gGT, metaPhys, &data.MetaDataCharacters[data.characterIDs[0]].engineID);
}
