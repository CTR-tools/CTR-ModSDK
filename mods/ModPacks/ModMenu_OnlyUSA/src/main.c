#include <common.h>

int boolShow = 1;
RECT window1 = {0, 0, 300, 130};
RECT window2 = {0, 150, 480, 64};
char options[14] = "\0";
char arrowText[4] = "-\0";
char onText[4] = "on\0";
char offText[4] = "off\0";
char line0[16] = "Retro Fueled\0";
char line1[16] = "RAM Expansion\0";
char line2[12] = "Super Hard\0"; // just change value, prereq Super Hard Mode
char line3[12] = "Disable HUD\0";
char line4[16] = "Nitro Fuel 2P\0";
char line5[12] = "Unlock All\0";
char line6[16] = "Sportsmanship\0"; // Loser -> Finished
char line7[12] = "No Weapons\0";
char line8[16] = "Character ID\0";
char pauseText[24] = "Press Select to Hide\0";
char idText[4] = "x\0";
char hardText[4] = "x\0";

char desc0a[24] = "NF physics by Redhotbr\0";
char desc0b[34] = "Changes reserve rules and turbos\0";
char desc1a[34] = "Modded PS1 or EMU can use 8mb RAM\0";
char desc1b[34] = "Wont work on unmodded console\0";
char desc2a[38] = "Swap difficulty of Super Hard Mode\0";
char desc2b[34] = "SHM turns on if value is changed\0";
char desc3a[28] = "Disable HUD while racing\0";
char desc3b[24] = "Does not remove menus\0";
char desc4a[28] = "Side by side 2P splitscreen\0";
char desc4b[34] = "Requires Disable HUD\0";
char desc5a[20] = "Beat Adventure 101\0";
char desc5b[28] = "Unlock all cars and tracks\0";
char desc6a[30] = "Change Loser text to Finished\0";
char desc6b[34] = "When you lose VS or Battle mode\0";
char desc7a[34] = "No weapons for players or bots\0";
char desc7b[30] = "Turn VS into 2P-4P Time Trial\0";
char desc8a[30] = "Change character in adventure\0";
char desc8b[34] = "and save the choice to memcard\0";
char* descPtrs[18] =
{
	desc0a, desc0b,
	desc1a, desc1b,
	desc2a, desc2b,
	desc3a, desc3b,
	desc4a, desc4b,
	desc5a, desc5b,
	desc6a, desc6b,
	desc7a, desc7b,
	desc8a, desc8b,
};
char menuFooter[38] = "Mod menu v3 by Niko   Apr 23 2022\0";

// Mod Menu
void RunUpdateHook(void)
{
	int i;
	char* currDescA;
	char* currDescB;
	struct GamepadBuffer* c;
	int tap;

	c = &sdata->gGamepads->gamepad[0];
	tap = c->buttonsTapped;

	if (tap & BTN_SELECT)
	{
		boolShow = !boolShow;
	}

	if (!boolShow) return;

	// User Input ====================================

	if (tap & BTN_UP)
	{
		options[12]--;

		if(options[12] == -1)
			options[12] = 0;
	}

	if (tap & BTN_DOWN)
	{
		options[12]++;

		if(options[12] > 8)
			options[12] = 8;
	}

	// Super Hard
	if(options[12] == 2)
	{
		if (tap & BTN_LEFT)
		{
			*(unsigned short*)0x80012658 =
			*(unsigned short*)0x80012658 - 0x50;

			if(((*(unsigned short*)0x80012658) / 0x50) < 4)
				*(unsigned short*)0x80012658 = 0x140;
		}

		if (tap & BTN_RIGHT)
		{
			*(unsigned short*)0x80012658 =
			*(unsigned short*)0x80012658 + 0x50;

			if(((*(unsigned short*)0x80012658) / 0x50) > 9)
				*(unsigned short*)0x80012658 = 0x2D0;
		}

		// Enable SHM cheat
		if(((*(unsigned short*)0x80012658) / 0x50) > 4)
		{
			*(unsigned int*)0x80096b28 =
			*(unsigned int*)0x80096b28 | 0x200000;
		}

		// Disable SHM cheat
		else
		{
			*(unsigned int*)0x80096b28 =
			*(unsigned int*)0x80096b28 & 0xFFDFFFFF;
		}
	}

	// Character ID
	if(options[12] == 8)
	{
		if (tap & BTN_LEFT)
		{
			*(char*)0x80086e84 =
			*(char*)0x80086e84 - 1;

			if(*(char*)0x80086e84 == -1)
				*(char*)0x80086e84 = 0;
		}

		if (tap & BTN_RIGHT)
		{
			*(char*)0x80086e84 =
			*(char*)0x80086e84 + 1;

			if(*(char*)0x80086e84 > 0xf)
				*(char*)0x80086e84 = 0xf;
		}

		// overwrite character in profile
		*(char*)0x8008FBCE = *(char*)0x80086e84;
	}

	// If you tap Cross or Circle
		if (tap & (BTN_CROSS | BTN_CIRCLE))
		options[options[12]] = !options[options[12]];

	// If Disable HUD is off, turn off NF 2P
	if(!options[3]) options[4] = 0;

	// If NF 2P is enabled, turn on Disable HUD
	if(options[4]) options[3] = 1;

	// Draw main Strings =================================

	DecalFont_DrawLine(arrowText, 20, 10 + (short)(options[12] * 10), FONT_SMALL, ORANGE);

	DecalFont_DrawLine(line0, 40, 10, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line1, 40, 20, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line2, 40, 30, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line3, 40, 40, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line4, 40, 50, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line5, 40, 60, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line6, 40, 70, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line7, 40, 80, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(line8, 40, 90, FONT_SMALL, PAPU_YELLOW);

	DecalFont_DrawLine(pauseText, 20, 110, FONT_SMALL, PERIWINKLE);

	for(i = 0; i < 8; i++)
	{
		if(i == 2)
			continue;

		DecalFont_DrawLine
		(
			options[i] ? onText : offText,			// string
			240, 									// X pos
			10 + i * 10, 							// Y pos
			FONT_SMALL, 							// size
			options[i] ? TINY_GREEN : CORTEX_RED	// index of Color array
		);
	}

	// Super Hard
	// 0x12658
	hardText[0] = (char)((*(unsigned short*)0x80012658) / 0x50) + '0';
	DecalFont_DrawLine(hardText, 240, 30, FONT_SMALL, PERIWINKLE);

	// Character ID
	// Avoid using "else" cause that's extra ASM

	// 0xA - 0xF
	idText[0] = *(unsigned char*)0x80086e84 - 10 + 'A';

	// 0 - 9
	if(*(unsigned char*)0x80086e84 < 10)
		idText[0] = *(unsigned char*)0x80086e84 + '0';

	// Print string
	DecalFont_DrawLine(idText, 240, 90, FONT_SMALL, PERIWINKLE);

	// Test Colors ===============================

	// test all the colors
	#if 0
	for(i = 0; i < 20; i++)
	{
		DecalFont_DrawLine(onText, 400, i * 10, FONT_SMALL, i);
	}
	#endif

	// Description Box ============================

	// Get the strings
	currDescA = descPtrs[options[12] * 2 + 0];
	currDescB = descPtrs[options[12] * 2 + 1];

	// Draw the strings
	DecalFont_DrawLine(currDescA, 20, 160, FONT_SMALL, PERIWINKLE);
	DecalFont_DrawLine(currDescB, 20, 170, FONT_SMALL, PERIWINKLE);

	// Draw additional footer
	DecalFont_DrawLine(menuFooter, 20, 200, FONT_SMALL, PERIWINKLE);

	// Activate Cheats ============================

	// Enable RF
	if(options[0])
	{
		*(unsigned char*)0x8005AF76 = 0x0;
		*(unsigned char*)0x8005EC65 = 0x8;
		*(unsigned char*)0x8006224C = 0xBC;
		*(unsigned char*)0x8006224E = 0x22;
		*(unsigned char*)0x8006224F = 0x8E;
		*(unsigned char*)0x80062250 = 0x2;
		*(unsigned char*)0x80062252 = 0xB8;
		*(unsigned char*)0x80062253 = 0x30;
		*(unsigned char*)0x80062254 = 0x20;
		*(unsigned char*)0x80062256 = 0xB9;
		*(unsigned char*)0x80062257 = 0x30;
		*(unsigned char*)0x80062258 = 0x6;
		*(unsigned char*)0x8006225B = 0x17;
		*(unsigned char*)0x8006225C = 0x20;
		*(unsigned char*)0x8006225D = 0xC0;
		*(unsigned char*)0x8006225E = 0x19;
		*(unsigned char*)0x8006225F = 0x3;
		*(unsigned char*)0x80062260 = 0x4;
		*(unsigned char*)0x80062262 = 0x20;
		*(unsigned char*)0x80062263 = 0x13;
		*(unsigned char*)0x8006227C = 0x22;
		*(unsigned char*)0x8006227E = 0x19;
		*(unsigned char*)0x8006227F = 0x20;
		*(unsigned char*)0x8006228C = 0x3;
		*(unsigned char*)0x8006229C = 0x2;
		*(unsigned char*)0x8006229E = 0x19;
		*(unsigned char*)0x8006229F = 0x13;
		*(unsigned char*)0x800622A0 = 0x0;
		*(unsigned char*)0x800622A2 = 0x0;
		*(unsigned char*)0x800622A3 = 0x0;
		*(unsigned char*)0x800622A4 = 0x2;
		*(unsigned char*)0x800622A6 = 0x40;
		*(unsigned char*)0x800622A7 = 0x14;
		*(unsigned char*)0x800622A8 = 0x6;
		*(unsigned char*)0x800622AA = 0x2;
		*(unsigned char*)0x800622AB = 0x24;
		*(unsigned char*)0x800622AC = 0x1C;
		*(unsigned char*)0x800622AE = 0x82;
		*(unsigned char*)0x800622AF = 0x16;
	}

	// Disable RF
	else
	{
		*(unsigned char*)0x8005AF76 = 0x40;
		*(unsigned char*)0x8005EC65 = 0x1;
		*(unsigned char*)0x8006224C = 0x1C;
		*(unsigned char*)0x8006224E = 0xB8;
		*(unsigned char*)0x8006224F = 0x8F;
		*(unsigned char*)0x80062250 = 0x0;
		*(unsigned char*)0x80062252 = 0x0;
		*(unsigned char*)0x80062253 = 0x0;
		*(unsigned char*)0x80062254 = 0x7;
		*(unsigned char*)0x80062256 = 0x0;
		*(unsigned char*)0x80062257 = 0x13;
		*(unsigned char*)0x80062258 = 0x0;
		*(unsigned char*)0x8006225B = 0x0;
		*(unsigned char*)0x8006225C = 0xBC;
		*(unsigned char*)0x8006225D = 0x0;
		*(unsigned char*)0x8006225E = 0x22;
		*(unsigned char*)0x8006225F = 0x8E;
		*(unsigned char*)0x80062260 = 0x0;
		*(unsigned char*)0x80062262 = 0x0;
		*(unsigned char*)0x80062263 = 0x0;
		*(unsigned char*)0x8006227C = 0x0;
		*(unsigned char*)0x8006227E = 0x0;
		*(unsigned char*)0x8006227F = 0x0;
		*(unsigned char*)0x8006228C = 0x2;
		*(unsigned char*)0x8006229C = 0x0;
		*(unsigned char*)0x8006229E = 0x0;
		*(unsigned char*)0x8006229F = 0x0;
		*(unsigned char*)0x800622A0 = 0x3;
		*(unsigned char*)0x800622A2 = 0x40;
		*(unsigned char*)0x800622A3 = 0x14;
		*(unsigned char*)0x800622A4 = 0x6;
		*(unsigned char*)0x800622A6 = 0x2;
		*(unsigned char*)0x800622A7 = 0x24;
		*(unsigned char*)0x800622A8 = 0x1D;
		*(unsigned char*)0x800622AA = 0x82;
		*(unsigned char*)0x800622AB = 0x16;
		*(unsigned char*)0x800622AC = 0x0;
		*(unsigned char*)0x800622AE = 0x0;
		*(unsigned char*)0x800622AF = 0x0;
	}

	// Enable RAM exansion
	if(options[1])
	{
		*(unsigned int*)0x800990EC = *(unsigned int*)0x807FF800;
		*(unsigned int*)0x800990F0 = *(unsigned int*)0x807FF800;
	}

	// Disable RAM expansion
	else
	{
		*(unsigned int*)0x800990EC = *(unsigned int*)0x801FF800;
		*(unsigned int*)0x800990F0 = *(unsigned int*)0x801FF800;
	}

	// skip options[2] for super hard

	// Enable "No HUD"
	if(options[3])
	{
		// set to 0
		*(unsigned char*)0x8001B038 = 0;
	}

	// Disable "No HUD"
	else
	{
		// set to 1
		*(unsigned char*)0x8001B038 = 1;
	}

	// Enable NF 2P
	if(options[4])
	{
		*(unsigned char*)0x800375A8 = 0x3;
		*(unsigned char*)0x80037644 = 0x2;
		*(unsigned char*)0x800427B5 = 0x1;
		*(unsigned char*)0x800427C0 = 0x0;
		*(unsigned char*)0x800427C1 = 0x1;
		*(unsigned char*)0x800427D0 = 0xD8;
		*(unsigned char*)0x800427EC = 0x1C;
		*(unsigned char*)0x800427F1 = 0x1;
		*(unsigned char*)0x800427F8 = 0xD8;
		*(unsigned char*)0x80042818 = 0x1E;
	}

	// Disable NF 2P
	else
	{
		*(unsigned char*)0x800375A8 = 0x2;
		*(unsigned char*)0x80037644 = 0x3;
		*(unsigned char*)0x800427B5 = 0x2;
		*(unsigned char*)0x800427C0 = 0x6E;
		*(unsigned char*)0x800427C1 = 0x0;
		*(unsigned char*)0x800427D0 = 0x6A;
		*(unsigned char*)0x800427EC = 0x1E;
		*(unsigned char*)0x800427F1 = 0x2;
		*(unsigned char*)0x800427F8 = 0x6A;
		*(unsigned char*)0x80042818 = 0x1C;
	}

	// Unlock All
	if(options[5])
	{
		// 101 adventure mode
		*(unsigned int*)0x8008fba4 = 0xFFFFFFFF;
		*(unsigned int*)0x8008fba8 = 0xFFFFFFFF;
		*(unsigned int*)0x8008fbac = 0xFFFFFFFF;
		*(unsigned int*)0x8008fbb0 = 0xFFFFFFFF;

		// All characters, tracks, cups
		*(unsigned int*)0x8008e6ec = 0xFFFFFFFF;
	}

	// No "else" for UnlockAll

	// Enable sportsmanship
	if(options[6])
	{
		*(unsigned short*)0x80054188 = 0x78;
	}

	// Disable sportsmanship -- like a jerk!
	else
	{
		*(unsigned short*)0x80054188 = 0x50C;
	}

	// Enable "no weapons"
	if(options[7])
	{
		*(unsigned int*)0x8006540C = 0x3e00008;
	}

	// Disable "no weapons"
	else
	{
		*(unsigned int*)0x8006540C = 0x27BDFFA0;
	}

	// No "if options[8]" for characterID

	// These background boxes are the same used in Battle/VS End-Of-Race comments
	RECTMENU_DrawInnerRect(&window1,1,sdata->gGT->backBuffer->otMem.startPlusFour);
	RECTMENU_DrawInnerRect(&window2,1,sdata->gGT->backBuffer->otMem.startPlusFour);
}










