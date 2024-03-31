#include <common.h>

void MM_JumpTo_Scrapbook();

RECT window1 = {0, 0, 400, 130};
char options[14] = "\0";
char arrowText[4] = "-\0";
char numberText[4] = "x\0";
char onText[4] = "on\0";
char offText[4] = "off\0";

char line0[16] = "Track:\0";
char line1[16] = "Border:\0";
char line2[16] = "Players:\0";

char line3[16] = "Player1:\0";
char line4[16] = "Player2:\0";
char line5[16] = "Player3:\0";
char line6[16] = "Player4:\0";

char* linePlayer[4] = 
{
	&line3[0],
	&line4[0],
	&line5[0],
	&line6[0]
};

// base address of Single menu data,
// this is an awful method, I'll fix it later

// sep3
#if BUILD == SepReview
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xCB0) // 0x800b341c
#define SIN_SIZE 16
#define ICON_OFFSET 2

// usa retail
#elif BUILD == UsaRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xF08) // 0x800b53b0
#define SIN_SIZE 16
#define ICON_OFFSET 2

// store trial
#elif BUILD == JpnTrial
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0x14A4) // 0x800b4e40
#define SIN_SIZE 20
#define ICON_OFFSET 4

// europe
#elif BUILD == EurRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xF88) // 0x800b5b8c
#define SIN_SIZE 20
#define ICON_OFFSET 4

// japan retail
#elif BUILD == JpnRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0x14cc) // 0x800b93ec
#define SIN_SIZE 20
#define ICON_OFFSET 4

#else
#error HookCups needs a macro for addresses
#endif

// first frame after spawning is complete
void RunTrafficLightHook()
{	
	// BORDER
	if(data.characterIDs[5] == 1)
		sdata->gGT->gameMode1 |= BATTLE_MODE;
}

void RunUpdateHook()
{
	struct GamepadBuffer* gpb;
	short* cIDs;
	int tap;
	
	int i = 0;
	
	
	
	// === Initial Essentials ===
	
	
	
	// if 1P or 2P arcade,
	// characterIDs for AIs are overwritten
	// after we start the loading anyway
	#define PLAYER1 	cIDs[0]
	#define PLAYER2 	cIDs[1]
	#define PLAYER3 	cIDs[2]
	#define PLAYER4 	cIDs[3]
	#define TRACK		cIDs[4]
	#define BORDER		cIDs[5]
	#define PLAYERS		cIDs[6]
	#define ROW			cIDs[7]
	
	// saves instructions by sharing pointer
	cIDs = &data.characterIDs[0];
	
	// arcade mode (ignored in 3P/4P)
	sdata->gGT->gameMode1 |= ARCADE_MODE;
	
	// prevent error message for gamepads
	sdata->gGT->numPlyrNextGame = 1;
	
	// lock, dont decrease,
	// prevents main menu from leaving,
	// prevents demo mode from leaving
	sdata->gGT->demoCountdownTimer = 9999;
	
	// do nothing else unless in main menu
	if(sdata->gGT->levelID != MAIN_MENU_LEVEL) return;
	else
	{
		// NOP function
		*(int*)((int)UI_VsQuipDrawAll + 0) = 0x3E00008;
		*(int*)((int)UI_VsQuipDrawAll + 4) = 0;
		
		// remove battle mode
		sdata->gGT->gameMode1 &= ~BATTLE_MODE;
	}
	
	tap = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	// shut any menu
	sdata->ptrActiveMenu = 0;
	
	
	
	// ==== Menu Logic and Input ====
	
	
		
	// from custom cups
	#define SIN_TRACK() *(char*)(SIN_ADDR + SIN_SIZE*TRACK + 0)
	
	// defaults
	if(ROW == 7)
	{
		PLAYER1 = 0;
		PLAYER2 = 1;
		PLAYER3 = 2;
		PLAYER4 = 3;
		TRACK = 0;
		BORDER = 0;
		PLAYERS = 4;
		ROW = 0;
	}
	
	if(tap == BTN_RIGHT)
	{
		if(ROW == 0) TRACK++;
		if(ROW == 1) BORDER++;
		if(ROW == 2) PLAYERS++;

		for(i < 0; i < 4; i++)
		{
			if(ROW == 3+i) cIDs[i]++;
		}
	}
	
	if(tap == BTN_LEFT)
	{
		if(ROW == 0) TRACK--;
		if(ROW == 1) BORDER--;
		if(ROW == 2) PLAYERS--;

		for(i < 0; i < 4; i++)
		{
			if(ROW == 3+i) cIDs[i]--;
		}
	}
	
	if(tap == BTN_UP) ROW--;
	if(tap == BTN_DOWN) ROW++;
	
	if(ROW < 0) ROW = 0;
	if(ROW > 2+PLAYERS) ROW = 2+PLAYERS;
	
	for(i < 0; i < 4; i++)
	{
		if(cIDs[i] < 0) cIDs[i] = 0;
		if(cIDs[i] > 0xF) cIDs[i] = 0xF;
	}
	
	if(TRACK < 0) TRACK = 0;
	if(TRACK > 17) TRACK = 17;
	
	if(BORDER < 0) BORDER = 0;
	if(BORDER > 1) BORDER = 1;
	
	if(PLAYERS < 1) PLAYERS = 1;
	if(PLAYERS > 4) PLAYERS = 4;

	
		
	// ==== Draw Menu ====
	
	
	
	if(ROW <= 2) 	DecalFont_DrawLine(arrowText, 20, 10 + ROW * 10, FONT_SMALL, ORANGE);
	else			DecalFont_DrawLine(arrowText, 20, 20 + ROW * 10, FONT_SMALL, ORANGE);

	// TRACK
	DecalFont_DrawLine(line0, 40, 10, FONT_SMALL, PAPU_YELLOW);
	DecalFont_DrawLine(sdata->lngStrings[SIN_TRACK() + 0x6e],
		160, 10, FONT_SMALL, PAPU_YELLOW);
	
	// BORDER
	DecalFont_DrawLine(line1, 		40, 20, FONT_SMALL, PAPU_YELLOW);
	numberText[0] = '0' + BORDER;
	DecalFont_DrawLine(numberText, 	160, 20, FONT_SMALL, PAPU_YELLOW);
	
	// PLAYERS
	DecalFont_DrawLine(line2, 		40, 30, FONT_SMALL, PAPU_YELLOW);
	numberText[0] = '0' + PLAYERS;
	DecalFont_DrawLine(numberText, 	160, 30, FONT_SMALL, PAPU_YELLOW);

	// PLAYER1-4
	for(i = 0; i < PLAYERS; i++)
	{
		// line
		DecalFont_DrawLine(linePlayer[i], 40, 50+i*10, FONT_SMALL, PAPU_YELLOW);
		
		// print character IDs
		DecalFont_DrawLine(
		
		sdata->lngStrings[
			data.MetaDataCharacters[
				cIDs[i]
			].name_LNG_long
		],
		160, 50+i*10, FONT_SMALL, PAPU_YELLOW);
		
	}
	
	// These background boxes are the same used in Battle/VS End-Of-Race comments
	RECTMENU_DrawInnerRect(&window1,1,sdata->gGT->backBuffer->otMem.startPlusFour);
	
	
	
	// === Starting Demo Mode ===
	
	
	// input
	if((tap & BTN_START) != 0)
	{
		sdata->gGT->boolDemoMode = 1;
		sdata->gGT->numPlyrCurrGame = PLAYERS;
		sdata->gGT->numPlyrNextGame = PLAYERS;
		MainRaceTrack_RequestLoad(SIN_TRACK());
	}
}
