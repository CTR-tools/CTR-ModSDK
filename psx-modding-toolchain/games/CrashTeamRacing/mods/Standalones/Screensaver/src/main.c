#include <common.h>

void DecalFont_DrawLine(char*, int, int, int, int);
void DrawTextBackground(RECT* r, int flag, void* ot);
void EndOfRace_DrawAllComments();

RECT window1 = {0, 0, 400, 130};
char options[14] = "\0";
char arrowText[4] = "-\0";
char onText[4] = "on\0";
char offText[4] = "off\0";

char line0[16] = "Track:\0";
char line1[16] = "Border:\0";
char line2[16] = "Players:\0";

char line3[16] = "Player1:\0";
char line4[16] = "Player2:\0";
char line5[16] = "Player3:\0";
char line6[16] = "Player4:\0";

char** linePlayer[4] = 
{
	&line3[0],
	&line4[0],
	&line5[0],
	&line6[0]
};

void RunUpdateHook()
{
	int i;
	
	struct GamepadBuffer* gpb;
	short* cIDs;
	int tap;
	
	// lock, dont decrease,
	// prevents main menu from leaving,
	// prevents demo mode from leaving
	sdata.gGT->demoCountdownTimer = 9999;
	
	// do nothing else unless in main menu
	if(sdata.gGT->levelID != 0x27) return;
	else
	{
		// NOP function
		*(int*)((int)EndOfRace_DrawAllComments + 0) = 0x3E00008;
		*(int*)((int)EndOfRace_DrawAllComments + 4) = 0;
	}
	
	tap = sdata.PtrGamepadSystem->controller[0].buttonsTapped;
	
	// saves instructions by sharing pointer
	cIDs = &data.characterIDs[0];
	
	// if 1P or 2P arcade,
	// characterIDs for AIs are overwritten
	// after we start the loading anyway
	#define PLAYER1 	cIDs[0]
	#define PLAYER2 	cIDs[1]
	#define PLAYER3 	cIDs[2]
	#define PLAYER4 	cIDs[3]
	#define TRACK		cIDs[4]
	#define BORDER		cIDs[5]
	
	if(BORDER > 1) BORDER = 1;
	
	// shut any menu
	sdata.ptrActiveMenuBox = 0;
	
	// draw custom menu
	DecalFont_DrawLine(arrowText, 20, 10 + (short)(options[12] * 10), 2, 0);

	DecalFont_DrawLine(line0, 40, 10, 2, 14);
	DecalFont_DrawLine(line1, 40, 20, 2, 14);
	DecalFont_DrawLine(line2, 40, 30, 2, 14);
	
	for(i = 0; i < sdata.gGT->numScreens; i++)
	{
		// line
		DecalFont_DrawLine(linePlayer[i], 40, 50+i*10, 2, 14);
		
		// print character IDs
		DecalFont_DrawLine(
		
		sdata.lngStrings[
			data.MetaDataCharacters[
				cIDs[i]
			].name_LNG_long
		],
		160, 50+i*10, 2, 14);
		
	}
	
	// These background boxes are the same used in Battle/VS End-Of-Race comments
	DrawTextBackground(&window1,1,sdata.gGT->backBuffer->otMem.startPlusFour);
	
	// input
	if((tap & BTN_START) != 0)
	{
		sdata.gGT->boolDemoMode = 1;
		sdata.gGT->numPlayers = 4;
		sdata.gGT->numScreens = 4;
		Level_RequestNewLEV(TRACK);
	}
}
