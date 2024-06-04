
void StatePS1_Launch_EnterPID()
{	
	DECOMP_DecalFont_DrawLine(
		"Attach Windows Client To Continue",
		0x100,0xA8,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Launch_EnterIP()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_ServerCountry();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	UpdateMenu();
	NewPage_ServerCountry();
}

void StatePS1_Launch_ConnectFailed()
{
	DECOMP_DecalFont_DrawLine(
		"Server Not Found",
		0x100,0xA8,FONT_SMALL,JUSTIFY_CENTER|PLAYER_RED);
		
	DECOMP_DecalFont_DrawLine(
		"Please Try Again",
		0x100,0xB0,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void ResetPsxGlobals()
{
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

	for(int i = 0; i < 8; i++)
	{
		data.characterIDs[i] = 0;
		octr->boolLockedInCharacters[i] = 0;
	}
}

extern struct RectMenu menu;

// should rename to EnterRoom
void StatePS1_Launch_FirstInit()
{
	// these can share same register with optimization
	int buttons;
	
	DecalFont_DrawLine("For Special Events, pick odd room, 1,3,5...",0x100,0x14,FONT_SMALL,JUSTIFY_CENTER|PAPU_YELLOW);
	DecalFont_DrawLine("For Classic Game, pick even room, 2,4,6...",0x100,0x1c,FONT_SMALL,JUSTIFY_CENTER|PAPU_YELLOW);
	
	MenuWrites_ServerRoom();
	
	// If already picked
	if(MenuFinished() == 1) 
	{
		ResetPsxGlobals();
		return;
	}
	
	UpdateMenu();
	NewPage_ServerRoom();
	
	int serverTotal = 0;
	for(int i = 0; i < 16; i++)
	{
		int curr = octr->clientCount[i];
		if(curr > 8) curr -= 8;
		serverTotal += curr;
	}
	
	char* text = "Server Total: 000";
	text[14] = '0' + ((serverTotal / 100) % 10);
	text[15] = '0' + ((serverTotal / 10) % 10);
	text[16] = '0' + (serverTotal % 10);
	
	DecalFont_DrawLine(
		text,
		menu.posX_curr,0xb8,
		FONT_SMALL,JUSTIFY_CENTER|PAPU_YELLOW);
}

void StatePS1_Lobby_AssignRole()
{	
	menu.posX_curr = 0x70; // X position
	menu.posY_curr = 0x84;  // Y position

	if(octr->DriverID == 0)
	{		
		octr->CurrState = LOBBY_HOST_TRACK_PICK;
	}
	
	else if (octr->DriverID > 0)
	{
		octr->CurrState = LOBBY_GUEST_TRACK_WAIT;
	}
}

void StatePS1_Lobby_HostTrackPick()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_Tracks();
	
	// If already picked
	if(MenuFinished() == 1)
	{
		if(octr->levelID > TURBO_TRACK)
		{
			octr->lapID = 0;
			octr->boolLockedInLap = 1;
		}
		
		// do this without adding to enum,
		// cause that means changing PS1/PC
		void FakeState_Lobby_HostLapPick();
		FakeState_Lobby_HostLapPick();
		return;
	}
	
	PrintCharacterStats();
	
	UpdateMenu();
	NewPage_Tracks();
}

void FakeState_Lobby_HostLapPick()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_Laps();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	PrintCharacterStats();
	
	UpdateMenu();
	NewPage_Laps();
}

void StatePS1_Lobby_GuestTrackWait()
{
	PrintCharacterStats();
	
	// close menu
	sdata->ptrActiveMenu = 0;
		
	DECOMP_DecalFont_DrawLine(
		"waiting for host",
		menu.posX_curr,0xA8,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
		
	DECOMP_DecalFont_DrawLine(
		"to pick the track",
		menu.posX_curr,0xB0,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Lobby_CharacterPick()
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	MenuWrites_Characters();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	PrintCharacterStats();
	PrintRecvTrack();
	
	UpdateMenu();
	NewPage_Characters();
	
	// get menu
	struct RectMenu* b = sdata->ptrActiveMenu;
	
	if(b != 0)
	{
		// update real-time
		data.characterIDs[0] = (8 * octr->PageNumber) + b->rowSelected;
	}
}

void StatePS1_Lobby_WaitForLoading()
{
	PrintCharacterStats();
	PrintRecvTrack();
	
	// waiting for all charactesr
	DECOMP_DecalFont_DrawLine(
		"Hope you win!",
		menu.posX_curr,menu.posY_curr,
		FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Lobby_StartLoading()
{
	PrintCharacterStats();
	PrintRecvTrack();
	
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
	sdata->unkAudioState = 0;
	
	struct GameTracker* gGT = sdata->gGT;
	
	// for battle tracks
	gGT->gameMode1 = LOADING | BATTLE_MODE;
	
	if(
		(octr->levelID <= TURBO_TRACK) ||
		(octr->levelID >= GEM_STONE_VALLEY)
	  )
	{
		// for all other tracks
		gGT->gameMode1 = LOADING | ARCADE_MODE;
	}
	
	// instant load
	//sdata->Loading.stage = 0;
	
	// load with flag animation
	DECOMP_MainRaceTrack_RequestLoad(octr->levelID);
	
	// dont kill thread,
	// it will die when loading screen covers screen
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
	// psx doesnt need to do anything here
}

void StatePS1_Game_EndRace()
{
	// psx doesnt need to do anything here
}