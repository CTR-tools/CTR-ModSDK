#include <common.h>
#include "global.h"

struct MenuRow menuRows[9] =
{
	{0,0,1,0,0},
	{0,0,2,1,1},
	{0,1,3,2,2},
	{0,2,4,3,3},
	{0,3,5,4,4},
	{0,4,6,5,5},
	{0,5,7,6,6},
	{0,6,7,7,7},

	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};

void RECTMENU_OnPressX(struct RectMenu* b);

struct RectMenu menu =
{
	// custom string made myself
	.stringIndexTitle = 0x4e,

	.posX_curr = 0, // X position
	.posY_curr = 0,  // Y position

	.unk1 = 0,

	// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
	// 0x100000 disables TRIANGLE button to prevent crashing
	.state = 0x100083,

	.rows = menuRows,

	.funcPtr = RECTMENU_OnPressX,

	.drawStyle = 0x4,	// 0xF0 looks like load/save

	.posX_prev = 0,
	.posY_prev = 0,

	.rowSelected = 0,
	.unk1c = 0,
	.unk1e = 0,
	.width = 0,
	.height = 0,

	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};

char* OnPressX_SetPtr;
char* OnPressX_SetLock;
int pageMax;

int MenuFinished()
{
	return *OnPressX_SetLock;
}

char* countryNames[8] =
{
	"Europe",
	"USA NYC",
	"Mexico",
	"Brazil",
	"Australia",
	"Singapore",
	"Beta",
	"Private Room",
};

void NewPage_ServerCountry()
{
	int i;

	menu.posX_curr = 0x198; // X position
	menu.posY_curr = 0x84;  // Y position

	// override "LAPS" "3/5/7",
	// and other unimportant strings
	for(i = 0; i < 8; i++)
	{
		menuRows[i].stringIndex = 0x9a+i;
		sdata->lngStrings[0x9a+i] = countryNames[i];
	}

	#ifdef ONLINE_BETA_MODE
	for(i = 0; i < 6; i++)
	#else
	i = 6;
	#endif

		menuRows[i].stringIndex |= 0x8000;
}

void MenuWrites_ServerCountry()
{
	pageMax = 0;
	OnPressX_SetPtr = &octr->serverCountry;
	OnPressX_SetLock = &octr->serverLockIn1;
}

int GetNumRoom()
{
	int numRooms = 0;

#if 0
	switch(octr->serverCountry)
	{

	}
#endif

	return 16;
}

int GetRoomChar(int pn)
{
	if(pn <= 9)
	{
		return '0' + pn;
	}

	// 10 or more
	else
	{
		return 'A' + (pn-10);
	}
}

void NewPage_ServerRoom()
{
	int i;

	// override "LAPS" "3/5/7"
	sdata->lngStrings[0x9a] = "ROOM 1 - x/8";
	sdata->lngStrings[0x9b] = "ROOM 2 - x/8";
	sdata->lngStrings[0x9c] = "ROOM 3 - x/8";
	sdata->lngStrings[0x9d] = "ROOM 4 - x/8";
	sdata->lngStrings[0x9e] = "ROOM 5 - x/8";
	sdata->lngStrings[0x9f] = "ROOM 6 - x/8";
	sdata->lngStrings[0xa0] = "ROOM 7 - x/8";
	sdata->lngStrings[0xa1] = "ROOM 8 - x/8";

	int pn = octr->PageNumber;

	for(i = 0; i < 8; i++)
	{
		menuRows[i].stringIndex = 0x809a+i;
		sdata->lngStrings[0x9a+i][5] = GetRoomChar(8*pn + i+1);
		sdata->lngStrings[0x9a+i][9] = '0' + (octr->clientCount[8*pn+i]);

		// handle locked rows
		if(octr->clientCount[8*pn+i] > 8)
			sdata->lngStrings[0x9a+i][9] = '0' + (octr->clientCount[8*pn+i]) - 8;
	}

	int numRooms = GetNumRoom();

	for(i = 0; i < 8; i++)
	{
		// unlock row if...
		if(8*pn+i < numRooms)
			if(octr->clientCount[8*pn+i] <= 7)
				menuRows[i].stringIndex &= 0x7FFF;
	}
}

void MenuWrites_ServerRoom()
{
	// pageMax
	// 0: 1-4 rooms
	// 1: 5-8 rooms
	// 2: 9-12 rooms

	int numRooms = GetNumRoom();
	pageMax = ((numRooms-1)&0xfffc)/8;

	OnPressX_SetPtr = &octr->serverRoom;
	OnPressX_SetLock = &octr->serverLockIn2;
}

void NewPage_Tracks()
{
	int i;

	for(i = 0; i < 8; i++)
	{
		menuRows[i].stringIndex =
			data.metaDataLEV[8*octr->PageNumber+i].name_LNG;
	}
}

void MenuWrites_Tracks()
{
	pageMax = 3;
	OnPressX_SetPtr = &octr->levelID;
	OnPressX_SetLock = &octr->boolLockedInLevel;
}

void NewPage_Laps()
{
	int i;

	// override "LAPS" with "1",
	// reset "3" "5" "7" in case overwritten
	sdata->lngStrings[0x9a] = "1";
	sdata->lngStrings[0x9b] = "3";
	sdata->lngStrings[0x9c] = "5";
	sdata->lngStrings[0x9d] = "7";
	sdata->lngStrings[0x9e] = "-";
	sdata->lngStrings[0x9f] = "-";
	sdata->lngStrings[0xa0] = "-";
	sdata->lngStrings[0xa1] = "-";

	#if 0
	// Monday event
	sdata->lngStrings[0x9e] = "30";
	sdata->lngStrings[0x9f] = "60";
	sdata->lngStrings[0xa0] = "90";
	sdata->lngStrings[0xa1] = "120";
	#endif


	for(i = 0; i < 4; i++)
	{
		// default, set all to unlocked
		menuRows[i].stringIndex = 0x9a+i;
		menuRows[4+i].stringIndex = 0x809a+4+i;
		#if 0
		menuRows[4+i].stringIndex = 0x9a+4+i;
		#endif

		#if 0
		// if not monday
		if(octr->special != 1)
		{
			sdata->lngStrings[0x9a+4+i] = "-";
			menuRows[4+i].stringIndex = 0x809a+4+i;
		}
		#endif
	}
}

void MenuWrites_Laps()
{
	OnPressX_SetPtr = &octr->lapID;
	OnPressX_SetLock = &octr->boolLockedInLap;
}

void NewPage_Characters()
{
	int i;

	for(i = 0; i < 8; i++)
	{
		menuRows[i].stringIndex =
			data.MetaDataCharacters[8*octr->PageNumber+i].name_LNG_long;
	}
}

void MenuWrites_Characters()
{
	pageMax = 1;
	OnPressX_SetPtr = &data.characterIDs[0];
	OnPressX_SetLock = &octr->boolLockedInCharacters[octr->DriverID];
}

int pressedX = 0;
void UpdateMenu()
{
	if (pressedX == 1)
	{
		pressedX = 0;
		menu.rowSelected = 0;
	}

	RECTMENU_Show(&menu);

	int buttons = sdata->gGamepads->gamepad[0].buttonsTapped;

	if (buttons & BTN_LEFT) { octr->PageNumber = max(0, octr->PageNumber - 1); }
	if (buttons & BTN_RIGHT) { octr->PageNumber = min(pageMax, octr->PageNumber + 1); }
	if (buttons & (BTN_LEFT | BTN_RIGHT)) { DECOMP_OtherFX_Play(0, 1); }

	if (pageMax == 0) { return; }

	int string =
		(('1' + octr->PageNumber) << 0) |
		('/' << 8) |
		(('1' + pageMax) << 16);

	DECOMP_MainFreeze_ConfigDrawArrows(menu.posX_curr, 0x48, &string);

	DecalFont_DrawLine(&string,menu.posX_curr,0x48,FONT_BIG,JUSTIFY_CENTER|WHITE);
}

void RECTMENU_OnPressX(struct RectMenu* b)
{
	int i;

	RECTMENU_Hide(b);
	sdata->ptrDesiredMenu = 0;

	*OnPressX_SetPtr = (8 * octr->PageNumber) + b->rowSelected;
	*OnPressX_SetLock = 1;

	octr->PageNumber = 0;
	pressedX = 1;

	RECTMENU_ClearInput();
}

void PrintTimeStamp()
{
	int boolEndOfRace = !octr->boolPlanetLEV;

	int posX = 56 + 0xC*boolEndOfRace;
	int posY = 198 - 0xC*boolEndOfRace;
	DECOMP_DecalFont_DrawLine(__TIME__, posX, posY, FONT_SMALL, DARK_RED);
	DECOMP_DecalFont_DrawLine(__DATE__, posX, posY+8, FONT_SMALL, DARK_RED);
}

void PrintCharacterStats()
{
	char message[32];
	int slot;
	int i;
	int color;


	#if 0
	char* title = "Classic Gameplay Mode";

	if(octr->special == 1)
	{
		title = "Monday Extra Laps";
	}

	if(octr->special == 2)
	{
		title = "Wednesday Inf Masks";
	}

	if(octr->special == 3)
	{
		title = "Friday Inf Bombs";
	}

	DecalFont_DrawLine(title,0x100,0x18,FONT_SMALL,JUSTIFY_CENTER|WHITE);
	#endif




	DecalFont_DrawLine(
		countryNames[octr->serverCountry],
		0x10, 0x10, FONT_SMALL, 0);

	char* roomName = "ROOM x";
	roomName[5] = GetRoomChar(octr->serverRoom+1);

	DecalFont_DrawLine(
		roomName,
		0x10, 0x18, FONT_SMALL, 0);



	int numDead = 0;
	for(i = 0; i < octr->NumDrivers; i++)
		if(octr->nameBuffer[i][0] == 0)
			numDead++;

	int posX;
	int boolEndOfRace = !octr->boolPlanetLEV;

	posX = 0x130 - 0x20*boolEndOfRace;
	sprintf(message, "Players: %d/8", (octr->NumDrivers-numDead));
	DecalFont_DrawLine(message,posX,0x58,FONT_SMALL,0);

	int h = 0;

	// UI-test
	// octr->NumDrivers = 8;

	for(i = 0; i < octr->NumDrivers; i++)
	{
		// convert client index to local index
		if(i == octr->DriverID) slot = 0;
		if(i < octr->DriverID) slot = i+1;
		if(i > octr->DriverID) slot = i;

		char* str = octr->nameBuffer[slot];

		// UI-test
		// str[0] = 'A';

		if(str[0] == 0) continue;

		// 0x19 - red
		// 0x1A - green
		int color =
			octr->boolLockedInCharacters[i] ?
			PLAYER_GREEN : PLAYER_RED;

		int posY = 0x60+h;
		h += 8;

		posX = 0x130 - 0x20*boolEndOfRace;
		sprintf(message, "%s:", str);
		DecalFont_DrawLine(message,posX,posY,FONT_SMALL,color);

		if(octr->CurrState < LOBBY_CHARACTER_PICK)
			continue;

		char* characterName =
			sdata->lngStrings[
				data.MetaDataCharacters[
					data.characterIDs[slot]
				].name_LNG_short];

		posX = 0x1AC - 0x20*boolEndOfRace;
		DecalFont_DrawLine(characterName,posX,posY,FONT_SMALL,color);
	}

	posX = 0x138 - 0x20*boolEndOfRace;
	int posY = 0xb8 - 0xC*boolEndOfRace;
	DecalFont_DrawLine("Return to main menu",posX,posY,FONT_SMALL,0);
	DecalFont_DrawLine("During Race or Lobby",posX-0x8,posY+0x8,FONT_SMALL,0);
	DecalFont_DrawLine("With the Select Button",posX-0x18,posY+0x10,FONT_SMALL,RED);
}

char* onlineLapString = "Laps: 000\0";
void PrintRecvTrack()
{
	char message[32];

	sprintf(message, "Track: %s",
				sdata->lngStrings
				[
					data.metaDataLEV[octr->levelID].name_LNG
				]
			);

	int boolEndOfRace = !octr->boolPlanetLEV;

	// UI-test
	// boolEndOfRace = 1;

	int posX = 0x118 - 0x20*boolEndOfRace;

	int numLaps = sdata->gGT->numLaps;
	onlineLapString[6] = '0' + ((numLaps / 100) % 10);
	onlineLapString[7] = '0' + ((numLaps / 10) % 10);
	onlineLapString[8] = '0' + (numLaps % 10);

	DecalFont_DrawLine(message,posX,0x38,FONT_SMALL,PAPU_YELLOW);
	DecalFont_DrawLine(onlineLapString,posX+2,0x40,FONT_SMALL,PAPU_YELLOW);
}