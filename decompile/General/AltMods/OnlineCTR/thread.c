void ThreadFunc(struct Thread* t)
{
	int i;
	
	struct GameTracker* gGT = sdata->gGT;
	if(gGT->levelID == 0x26)
	{
		*(int*)0x800ae54c = 0x3e00008;
		*(int*)0x800ae550 = 0;
		
        // freecam mode
        gGT->cameraDC[0].cameraMode = 3;

        // disable all HUD flags
        gGT->hudFlags = 0;
		
		struct PushBuffer* pb = &gGT->pushBuffer[0];
		
		pb->pos[0] = 0x3D;
		pb->pos[1] = 0xF8;
		pb->pos[2] = 0xF879;
		
		pb->rot[0] = 0x841;
		pb->rot[1] = 0x77c;
		pb->rot[2] = 0xff5;
	}
	
	// only disable for no$psx testing,
	// which can force in-game with 8000c000=LOBBY_START_LOADING
	#if 1
	for(i = 3; i >= 0; i--)
		octr->time[i+1] = octr->time[i];
	
	for(i = 3; i >= 0; i--)
		if(octr->time[i+1] != octr->time[i])
			break;
	
	// if client didn't update the game in 4 frames
	int boolCloseClient = 
		(i == -1) &&
		(octr->CurrState >= LAUNCH_FIRST_INIT);
		
	// if server disconnects mid-game
	// (currState < 0)
	
	if(boolCloseClient || (octr->CurrState < 0))
	{
		// reset, including CurrState
		memset(octr, 0, sizeof(struct OnlineCTR));
		
		sdata->ptrActiveMenu = 0;
		octr_entryHook();

		// stop music, 
		// stop "most FX", let menu FX ring
		Music_Stop();
		howl_StopAudio(1,1,0);
		sdata->unkAudioState = 0;
	
		// load next level
		//sdata->gGT->gameMode1 = LOADING;
		//sdata->Loading.stage = 0;
		
		// load with flag animation
		DECOMP_MainRaceTrack_RequestLoad(0x26);
		
		// kill thread,
		// dont execute again until game loads
		t->flags |= 0x800;
		return;
	}
	#endif
	
	if (octr->CurrState <= LOBBY_WAIT_FOR_LOADING)
	{
		void PrintTimeStamp();
		PrintTimeStamp();
	}
	
	if (octr->CurrState >= GAME_WAIT_FOR_RACE)
	{
		void DrawOverheadNames();
		DrawOverheadNames();
	}
	
	if (octr->CurrState >= 0)
		octr->funcs[octr->CurrState]();
	
	if(strcmp("debugcam", &octr->nameBuffer[0]) == 0)
	{
		void Freecam();
		Freecam();
	}
}