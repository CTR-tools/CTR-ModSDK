
void StatePS1_Launch_EnterPID()
{	
	DECOMP_DecalFont_DrawLine(
		"Attach Windows Client To Continue",
		0x100,0x68,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Launch_EnterIP()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_ServerCountry();
	
	// If already picked
	if(MenuFinished() == 1)
	{
		// if picked PRIVATE
		if(octr->serverCountry == 3)
		{
			// lock-in ROOM, skip room selection
			octr->serverLockIn2 = 1;
			return;
		}
		
		// do this without adding to enum,
		// cause that means changing PS1/PC
		void StatePS1_Launch_EnterRoom();
		StatePS1_Launch_EnterRoom();
		return;
	}
	
	// first frame here
	if(sdata->ptrActiveMenu == 0)
	{
		ResetMenu();
		NewPage_ServerCountry();

	}
	
	int old = octr->PageNumber;
	UpdateMenu();
	if(old != octr->PageNumber)
		NewPage_ServerCountry();
}

void StatePS1_Launch_EnterRoom()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_ServerRoom();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	// first frame here
	if(sdata->ptrActiveMenu == 0)
	{
		ResetMenu();
		NewPage_ServerRoom();
	}
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
		octr->boolLockedInCharacters[i] = 0;
	}
}

void StatePS1_Lobby_AssignRole()
{	
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
		if(sdata->gGT->levelID > TURBO_TRACK)
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
	
	PrintClientCountStats();
	PrintCharacterStats();
	
	// first frame here
	if(sdata->ptrActiveMenu == 0)
	{
		ResetMenu();
		NewPage_Tracks();

	}
	
	int old = octr->PageNumber;
	UpdateMenu();
	if(old != octr->PageNumber)
		NewPage_Tracks();
}

void FakeState_Lobby_HostLapPick()
{
	// these can share same register with optimization
	int buttons;
	
	MenuWrites_Laps();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	PrintClientCountStats();
	PrintCharacterStats();
	
	// first frame here
	if(sdata->ptrActiveMenu == 0)
	{
		ResetMenu();
		NewPage_Laps();
	}
}

void StatePS1_Lobby_GuestTrackWait()
{
	PrintClientCountStats();
	PrintCharacterStats();
		
	DECOMP_DecalFont_DrawLine(
		"waiting for host",
		menu.posX_curr,0x68,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
		
	DECOMP_DecalFont_DrawLine(
		"to pick the track",
		menu.posX_curr,0x70,FONT_SMALL,JUSTIFY_CENTER|ORANGE);
}

void StatePS1_Lobby_CharacterPick()
{
	// these can share same register with optimization
	int buttons;
	int i;
	
	MenuWrites_Characters();
	
	// If already picked
	if(MenuFinished() == 1) return;
	
	PrintClientCountStats();
	PrintCharacterStats();
	PrintRecvTrack();
			
	// first frame here
	if(sdata->ptrActiveMenu == 0)
	{
		ResetMenu();
		NewPage_Characters();
	}
	
	int old = octr->PageNumber;
	UpdateMenu();
	if(old != octr->PageNumber)
		NewPage_Characters();
	
	// get menu
	struct RectMenu* b = sdata->ptrActiveMenu;
	
	if(b != 0)
	{
		// update real-time
		data.characterIDs[0] = (4 * octr->PageNumber) + b->rowSelected;
	}
}

void StatePS1_Lobby_WaitForLoading()
{
	PrintClientCountStats();
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
	PrintClientCountStats();
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
		(gGT->levelID <= TURBO_TRACK) ||
		(gGT->levelID >= GEM_STONE_VALLEY)
	  )
	{
		// for all other tracks
		gGT->gameMode1 = LOADING | ARCADE_MODE;
	}
	
	// start loading,
	// this also kills all threads,
	// so this wont execute twice
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
	// psx doesnt need to do anything here
}

void StatePS1_Game_EndRace()
{
	// psx doesnt need to do anything here
}