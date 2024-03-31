#include "global.h"

struct MenuRow menuRows[5] =
{	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 1,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 0,
		.rowOnPressDown = 2,
		.rowOnPressLeft = 1,
		.rowOnPressRight = 1,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 1,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 2,
		.rowOnPressRight = 2,
	},
	
	{
		.stringIndex = 0,
		.rowOnPressUp = 2,
		.rowOnPressDown = 3,
		.rowOnPressLeft = 3,
		.rowOnPressRight = 3,
	},
	
	// NULL, end of menu
	{
		.stringIndex = 0xFFFF,
		.rowOnPressUp = 0,
		.rowOnPressDown = 0,
		.rowOnPressLeft = 0,
		.rowOnPressRight = 0,
	}
};
	
struct RectMenu menuBox =
{
	// custom string made myself
	.stringIndexTitle = 0x17d, 
	
	.posX_curr = 0x160, // X position
	.posY_curr = 0x74,  // Y position
	
	.unk1 = 0,
	
	// 0b11, 2 centers X, 1 centers Y, 0x80 for tiny text
	.state = 3,

	.rows = menuRows,

	.funcPtr = 0,

	.drawStyle = 0x4,	// 0xF0 looks like load/save
	
	.posX_prev = 0,
	.posY_prev = 0,
	
	.rowSelected = 0,
	.unk1a = 0,
	.unk1e = 0,
	.width = 0,
	.height = 0,
	
	.ptrNextBox_InHierarchy = 0,
	.ptrPrevBox_InHierarchy = 0,
};

void SetNames_Tracks()
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.metaDataLEV[4*octr->PageNumber+i].name_LNG;
	}
}

void SetNames_Characters()
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	for(i = 0; i < 4; i++)
	{
		menuRows[i].stringIndex = 
			data.MetaDataCharacters[4*octr->PageNumber+i].name_LNG_long;
	}
}


void StatePS1_Launch_EnterPID()
{	
	DecalFont_DrawLine("Attach Windows Client To Continue",0x8,0xd0,FONT_SMALL,ORANGE);
}

void StatePS1_Launch_EnterIP()
{	
	DecalFont_DrawLine("Client Attached",0x8,0xc8,FONT_SMALL,PLAYER_GREEN);
	DecalFont_DrawLine("Enter IP Address",0x8,0xd0,FONT_SMALL,ORANGE);
}

void StatePS1_Launch_ConnectFailed()
{
	DecalFont_DrawLine("Server Not Found",0x8,0xc8,FONT_SMALL,PLAYER_RED);
	DecalFont_DrawLine("Please Try Again",0x8,0xd0,FONT_SMALL,ORANGE);
}

void StatePS1_Launch_FirstInit()
{
	// starting at index 381 (0x17d) is
	// dialogue for adventure hints
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// initialize string pointer,
	// this works cause "OnlineCTR" is stored in RDATA
	sdata->lngStrings[0x17d] = "OnlineCTR";
	
	// unlock everything
	sdata->advProgress.rewards[0] = 0xffffffff;
	sdata->advProgress.rewards[1] = 0xffffffff;
	sdata->advProgress.rewards[2] = 0xffffffff;
	sdata->advProgress.rewards[3] = 0xffffffff;
	sdata->advProgress.rewards[4] = 0xffffffff;
	sdata->advProgress.rewards[5] = 0xffffffff;
	
	// 8mb RAM expansion, for emulators that support it.
	// Needed for 3 or more players on Adv Hub
	sdata->mempack[0].lastFreeByte = 0x807ff800;
	sdata->mempack[0].endOfAllocator = 0x807ff800;

	sdata->ptrActiveMenu = 0;

	// keep running till the client gets a result,
	// DriverID is set to -1 on windows-side before this.

	for(i = 0; i < 8; i++)
	{
		data.characterIDs[i] = 0;
		octr->boolLockedInCharacter_Others[i] = 0;
	}
}

void StatePS1_Lobby_AssignRole()
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	if(octr->DriverID == 0)
	{		
		octr->CurrState = LOBBY_HOST_TRACK_PICK;
	}
	
	else if (octr->DriverID > 0)
	{
		octr->CurrState = LOBBY_GUEST_TRACK_WAIT;
	}
}

void DrawClientCountStats()
{
	char message[32];
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	sprintf(message, "ClientID: %d", octr->DriverID);
	DecalFont_DrawLine(message,0x8,0x20,FONT_SMALL,ORANGE);
	
	sprintf(message, "NumTotal: %d", octr->NumDrivers);
	DecalFont_DrawLine(message,0x8,0x28,FONT_SMALL,ORANGE);
}

void RECTMENU_OnPressX_Track(struct RectMenu* b)
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	RECTMENU_Hide(b);
	sdata->ptrDesiredMenu = 0;
	
	sdata->gGT->levelID = (4 * octr->PageNumber) + b->rowSelected;
	
	octr->boolLockedInTrack = 1;
}

void StatePS1_Lobby_HostTrackPick()
{
	// these can share same register with optimization
	int buttons;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	// quit, if a choice has already been made
	if(octr->boolLockedInTrack) return;
	
	// Probably not needed since adding "AssignRole",
	// invert a "guest" that is accidentally assigned "host"
	if(octr->DriverID != 0)
	{
		octr->CurrState = LOBBY_GUEST_TRACK_WAIT;
		sdata->ptrActiveMenu = 0;
	}
	
	DrawClientCountStats();
	
	// open menu, set defaults
	if(sdata->ptrActiveMenu != &menuBox)
	{
		octr->PageNumber = 0;
		menuBox.rowSelected = 0;
		menuBox.funcPtr = RECTMENU_OnPressX_Track;
		SetNames_Tracks();
		RECTMENU_Show(&menuBox);
	}
	
	buttons = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	// BTN_LEFT = 0x4
	// BTN_RIGHT = 0x8
	// some crazy math to optimize this
	
	if(buttons & 0xC)
	{
		octr->PageNumber += (buttons-6)/2;
	
		if (octr->PageNumber < 0) octr->PageNumber = 0;
		if (octr->PageNumber > 7) octr->PageNumber = 7;
		SetNames_Tracks();
	}
}

void StatePS1_Lobby_GuestTrackWait()
{
	DrawClientCountStats();
	
	DecalFont_DrawLine("Waiting for Host to Pick Track",0x8,0xd0,FONT_SMALL,ORANGE);
}

void DrawRecvTrack()
{
	char message[32];
	sprintf(message, "Track: %s", 
				sdata->lngStrings
				[
					data.metaDataLEV[sdata->gGT->levelID].name_LNG
				]
			);
	
	DecalFont_DrawLine(message,0x8,0x10,FONT_SMALL,PLAYER_BLUE);
}

void DrawCharacterStats()
{
	char message[32];
	int slot;
	int i;
	int color;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	for(i = 0; i < octr->NumDrivers; i++)
	{	
		if(i == octr->DriverID) slot = 0;
		if(i < octr->DriverID) slot = i+1;
		if(i > octr->DriverID) slot = i;
		
		sprintf(message, "Client %d: %s", i, 
			sdata->lngStrings[
				data.MetaDataCharacters[
					data.characterIDs[slot]
				].name_LNG_short]);
		
		// 0x19 - red
		// 0x1A - green
		int color = 
			octr->boolLockedInCharacter_Others[i] ? 
			PLAYER_GREEN : PLAYER_RED;
	
		DecalFont_DrawLine(message,0x8,0x48+i*0x8,FONT_SMALL,color);
	}
}

void RECTMENU_OnPressX_Character(struct RectMenu* b)
{
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	RECTMENU_Hide(b);
	sdata->ptrDesiredMenu = 0;
	
	data.characterIDs[0] = (4 * octr->PageNumber) + b->rowSelected;
	
	octr->boolLockedInCharacter = 1;
	octr->boolLockedInCharacter_Others[octr->DriverID] = 1;
}

void StatePS1_Lobby_CharacterPick()
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	DrawClientCountStats();
	DrawCharacterStats();
	DrawRecvTrack();
	
	// will switch to WaitForLoad soon
	if(octr->boolLockedInCharacter == 1) return;
	
	// open menu, set defaults
	if(sdata->ptrActiveMenu != &menuBox)
	{
		octr->PageNumber = 0;
		menuBox.rowSelected = 0;
		menuBox.funcPtr = RECTMENU_OnPressX_Character;
		SetNames_Characters();
		RECTMENU_Show(&menuBox);
	}
	
	buttons = sdata->gGamepads->gamepad[0].buttonsTapped;
	
	// BTN_LEFT = 0x4
	// BTN_RIGHT = 0x8
	// some crazy math to optimize this
	
	if(buttons & 0xC)
	{
		octr->PageNumber += (buttons-6)/2;
	
		if (octr->PageNumber < 0) octr->PageNumber = 0;
		if (octr->PageNumber > 3) octr->PageNumber = 3;
		SetNames_Characters();
	}
	
	data.characterIDs[0] = (4 * octr->PageNumber) + menuBox.rowSelected;
}

void StatePS1_Lobby_WaitForLoading()
{
	DrawClientCountStats();
	DrawCharacterStats();
	DrawRecvTrack();
	
	DecalFont_DrawLine("Waiting for All Characters",0x8,0xd0,FONT_SMALL,ORANGE);
}

void StatePS1_Lobby_StartLoading()
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	DrawClientCountStats();
	DrawCharacterStats();
	DrawRecvTrack();
	DecalFont_DrawLine("LOADING...",0x100,0x6c,FONT_SMALL,ORANGE);
	
	// variable reuse, wait a few frames,
	// so screen updates with green names
	octr->CountPressX++;
	if(octr->CountPressX < 3) return;
	
	// stop music, 
	// stop "most FX", let menu FX ring
	Music_Stop();
	howl_StopAudio(1,1,0);
	
	// load next level
	sdata->gGT->gameMode1 = 0x40000000;
	sdata->Loading.stage = 0;
	octr->CurrState = GAME_WAIT_FOR_RACE;
}

void StatePS1_Game_WaitForRace()
{
	// lock traffic lights off-screen,
	// put message on-screen
}

void StatePS1_Game_StartRace()
{
	// deal with weapons
}