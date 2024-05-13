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
	
struct RectMenu menu =
{
	// custom string made myself
	.stringIndexTitle = 0x17d, 
	
	.posX_curr = 0xB0, // X position
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
	.unk1c = 0,
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

void PrintTimeStamp()
{
	DECOMP_DecalFont_DrawLine(__DATE__, WIDE_PICK(5, 100-40), 206, FONT_SMALL, DARK_RED);
	DECOMP_DecalFont_DrawLine(__TIME__, WIDE_PICK(170, 228-40), 206, FONT_SMALL, DARK_RED);
}

void StatePS1_Launch_EnterPID()
{	
	DECOMP_DecalFont_DrawLine(
		"Attach Windows Client To Continue",
		0x100,0x68,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Launch_EnterIP()
{	
	DECOMP_DecalFont_DrawLine(
		"Client Attached",
		0x100,0x68,FONT_SMALL,JUSTIFY_CENTER|PLAYER_GREEN);
	
	DECOMP_DecalFont_DrawLine(
		"Enter IP Address",
		0x100,0x70,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Launch_ConnectFailed()
{
	DECOMP_DecalFont_DrawLine(
		"Server Not Found",
		0x100,0x68,FONT_SMALL,JUSTIFY_CENTER|PLAYER_RED);
		
	DECOMP_DecalFont_DrawLine(
		"Please Try Again",
		0x100,0x70,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
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
	DrawCharacterStats();
	
	// open menu, set defaults
	if(sdata->ptrActiveMenu != &menu)
	{
		octr->PageNumber = 0;
		menu.rowSelected = 0;
		menu.funcPtr = RECTMENU_OnPressX_Track;
		SetNames_Tracks();
		RECTMENU_Show(&menu);
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
	DrawCharacterStats();
		
	DECOMP_DecalFont_DrawLine(
		"waiting for host",
		menu.posX_curr,0x68,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
		
	DECOMP_DecalFont_DrawLine(
		"to pick the track",
		menu.posX_curr,0x70,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
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
	
	sprintf(message, "Players: %d/8", octr->NumDrivers);
	DecalFont_DrawLine(message,0x128,0x40,FONT_SMALL,0);
	
	for(i = 0; i < octr->NumDrivers; i++)
	{	
		// convert client index to local index
		if(i == octr->DriverID) slot = 0;
		if(i < octr->DriverID) slot = i+1;
		if(i > octr->DriverID) slot = i;

		// 0x19 - red
		// 0x1A - green
		int color = 
			octr->boolLockedInCharacter_Others[i] ? 
			PLAYER_GREEN : PLAYER_RED;
		
		sprintf(message, "%s:", &octr->nameBuffer[slot * 0xc]);
		DecalFont_DrawLine(message,0x128,0x48+i*0x8,FONT_SMALL,color);
		
		if(octr->CurrState < LOBBY_CHARACTER_PICK)
			continue;
		
		char* characterName =
			sdata->lngStrings[
				data.MetaDataCharacters[
					data.characterIDs[slot]
				].name_LNG_short];
				
		DecalFont_DrawLine(characterName,0x1A8,0x48+i*0x8,FONT_SMALL,color);
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
	if(sdata->ptrActiveMenu != &menu)
	{
		octr->PageNumber = 0;
		menu.rowSelected = 0;
		menu.funcPtr = RECTMENU_OnPressX_Character;
		SetNames_Characters();
		RECTMENU_Show(&menu);
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
	
	data.characterIDs[0] = (4 * octr->PageNumber) + menu.rowSelected;
}

void StatePS1_Lobby_WaitForLoading()
{
	DrawClientCountStats();
	DrawCharacterStats();
	DrawRecvTrack();
	
	// waiting for all charactesr
	DECOMP_DecalFont_DrawLine(
		"Hope you win!",
		menu.posX_curr,menu.posY_curr,
		FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Lobby_StartLoading()
{
	#if USE_K1 == 0
	struct OnlineCTR* octr = (struct OnlineCTR*)0x8000C000;
	#endif
	
	DrawClientCountStats();
	DrawCharacterStats();
	DrawRecvTrack();
	
	DECOMP_DecalFont_DrawLine(
		"LOADING...",
		menu.posX_curr,menu.posY_curr,
		FONT_SMALL,JUSTIFY_CENTER|ORANGE);
	
	// variable reuse, wait a few frames,
	// so screen updates with green names
	octr->CountPressX++;
	if(octr->CountPressX < FPS_DOUBLE(15)) return;
	
	// stop music, 
	// stop "most FX", let menu FX ring
	Music_Stop();
	howl_StopAudio(1,1,0);
	
	// load next level
	sdata->gGT->gameMode1 = LOADING | ARCADE_MODE;
	sdata->Loading.stage = 0;
}

void StatePS1_Game_WaitForRace()
{
	struct GameTracker* gGT = sdata->gGT;
	gGT->trafficLightsTimer = 0xf40;
	
	if((gGT->gameMode1 & START_OF_RACE) != 0)
		return;
	
	// Copy from DrawUnpluggedMsg
	
	int posY;
	RECT window;
	int i;
	
	// position of error
	posY = data.errorPosY[sdata->errorMessagePosIndex];
	
	window.x = 0xffec;
	window.y = posY - 3;
	window.w = 0x228;
	window.h = 0;
	
	// PLEASE CONNECT A CONTROLLER
	DECOMP_DecalFont_DrawLine(
		"WAITING FOR PLAYERS...",
		0x100, posY + window.h, FONT_SMALL, (JUSTIFY_CENTER | ORANGE));
		
	// add for each line
	window.h += 8;
	
	// add 3 pixels above, 3 pixels bellow
	window.h += 6;
		
	DECOMP_RECTMENU_DrawInnerRect(&window, 1, gGT->backBuffer->otMem.startPlusFour);
}

void StatePS1_Game_StartRace()
{
	// deal with weapons
}