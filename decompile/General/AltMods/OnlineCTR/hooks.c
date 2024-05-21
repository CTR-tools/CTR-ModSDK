int OnlineGetNumDrivers()
{
	return octr->NumDrivers;
}

void octr_entryHook()
{
	// Until VehBirth_TeleportSelf is rewritten
	// AdvHub, replace default spawn with unused
	// start-line spawn, turn BEQ to JMP
	*(char*)0x80058072 = 0;
	
	// BOTS_Adv_AdjustDifficulty(); must be called before
	// initializing any AI, either BOTS_Driver_Init or
	// from BOTS_Driver_Convert. If AIs are wanted, then
	// put that call in OnlineInit_Drivers, but for now
	// just disable BOTS_Driver_Convert
	*(int*)0x80017318 = 0x3E00008;
	*(int*)0x8001731c = 0;
	
	// remove cutscene threads
	for(int i = 0x96; i < 0xa6; i++)
	{
		data.MetaDataModels[i].LInB = 0;
	}
	
	// ======== Globals ============
	
	#if USE_K1 == 1
	octr = 0x8000C000;
	#endif
		
	// default for first LEV, before gameplay
	memset(octr, 0, sizeof(struct OnlineCTR));
	octr->IsBootedPS1 = 1;

	// FSM for menus
	octr->funcs[LAUNCH_ENTER_PID] = StatePS1_Launch_EnterPID;
	octr->funcs[LAUNCH_ENTER_IP] = StatePS1_Launch_EnterIP;
	octr->funcs[LAUNCH_CONNECT_FAILED] = StatePS1_Launch_ConnectFailed;
	octr->funcs[LAUNCH_FIRST_INIT] = StatePS1_Launch_FirstInit;
	octr->funcs[LOBBY_ASSIGN_ROLE] = StatePS1_Lobby_AssignRole;
	octr->funcs[LOBBY_HOST_TRACK_PICK] = StatePS1_Lobby_HostTrackPick;
	octr->funcs[LOBBY_GUEST_TRACK_WAIT] = StatePS1_Lobby_GuestTrackWait;
	octr->funcs[LOBBY_CHARACTER_PICK] = StatePS1_Lobby_CharacterPick;
	octr->funcs[LOBBY_WAIT_FOR_LOADING] = StatePS1_Lobby_WaitForLoading;
	octr->funcs[LOBBY_START_LOADING] = StatePS1_Lobby_StartLoading;
	octr->funcs[GAME_WAIT_FOR_RACE] = StatePS1_Game_WaitForRace;
	octr->funcs[GAME_START_RACE] = StatePS1_Game_StartRace;
	octr->funcs[GAME_END_RACE] = StatePS1_Game_EndRace;
}

// this runs after the end of MainInit_FinalizeInit,
// which is also after the end of camera initialization
void octr_initHook()
{
	void ThreadFunc();
	
	// small stack pool, pause thread (those threads can't pause)
	PROC_BirthWithObject(0x30f, ThreadFunc, 0, 0);
	
	sdata->lngStrings[0x17D] = "OnlineCTR";
	sdata->lngStrings[0x4e] = "OnlineCTR";
	
	struct GameTracker* gGT = sdata->gGT;
	if(gGT->levelID <= TURBO_TRACK)
	{
		DECOMP_CAM_StartOfRace(&gGT->cameraDC[0]);
		gGT->gameMode1 |= START_OF_RACE;
		gGT->hudFlags &= ~(1);
	}
}

// replace MainInit_Drivers
void OnlineInit_Drivers(struct GameTracker* gGT)
{	
	int i;
	int bitFlag;
	struct Driver* dr;
		
	for(i = 0; i < 8; i++)
	{
		gGT->drivers[i] = 0;
		sdata->kartSpawnOrderArray[i] = i;
	}
	
	// if first boot
	if(gGT->levelID == CREDITS_POLAR)
	{
		gGT->drivers[0] = VehBirth_Player(0);
		return;
	}
	
	if(DECOMP_LOAD_IsOpen_RacingOrBattle())
		DECOMP_RB_MinePool_Init();
	
	// 8 spawn positions
	bitFlag = 7;
	
	// override for battle maps
	if(
		(gGT->levelID > TURBO_TRACK) &&
		(gGT->levelID < GEM_STONE_VALLEY)
	  )
	{
		// 4 spawn positions
		bitFlag = 3;
	}
	
	// All clients must spawn drivers in the same order,
	// so that pointers can be sent over network
	
	int numDead = 0;
	
	for(i = 0; i < octr->DriverID; i++)
	{
		if(octr->nameBuffer[(i+1)*0xC] == 0)
		{
			numDead++;
			continue;
		}
		
		// init, save
		dr = DECOMP_VehBirth_Player(i+1);
		gGT->drivers[i+1] = dr;
		
		// fakeID, teleport
		dr->driverID = (i-numDead)&bitFlag;
		VehBirth_TeleportSelf(dr,3,0);
		
		// realID
		dr->driverID = i+1;
		
		#ifdef USE_60FPS
		// needed cause VehBirth_TeleportSelf
		// has not been rewritten yet for decomp
		dr->instSelf->animFrame = FPS_DOUBLE(10);
		#endif
	}
	
	// init, save
	dr = DECOMP_VehBirth_Player(0);
	gGT->drivers[0] = dr;
	
	// fakeID, teleport
	dr->driverID = (i-numDead)&bitFlag;
	VehBirth_TeleportSelf(dr,3,0);
	
	// realID
	dr->driverID = 0;
	
	#ifdef USE_60FPS
	// needed cause VehBirth_TeleportSelf
	// has not been rewritten yet for decomp
	dr->instSelf->animFrame = FPS_DOUBLE(10);
	#endif
	
	for(i = i+1; i < octr->NumDrivers; i++)
	{
		if(octr->nameBuffer[i*0xC] == 0)
		{
			numDead++;
			continue;
		}
		
		// init, save
		dr = DECOMP_VehBirth_Player(i);
		gGT->drivers[i] = dr;
		
		// fakeID, teleport
		dr->driverID = (i-numDead)&bitFlag;
		VehBirth_TeleportSelf(dr,3,0);
		
		// realID
		dr->driverID = i;
		
		#ifdef USE_60FPS
		// needed cause VehBirth_TeleportSelf
		// has not been rewritten yet for decomp
		dr->instSelf->animFrame = FPS_DOUBLE(10);
		#endif
	}
	
	if(gGT->levelID != 0x26)
		octr->CurrState = GAME_WAIT_FOR_RACE;
}

RECT windowText = {0x118, 0x40, 0xD8, 0};

void OnlineEndOfRace()
{
	char message[32];
	int numDead = 0;
	int skipRow = 0;
	struct Driver* d = sdata->gGT->drivers[0];
	
	// if "you" are still racing, do nothing
	if((d->actionsFlagSet & 0x2000000) == 0)
		return;
	
	octr->CurrState = GAME_END_RACE;
	
	// if "you" finished race,
	DECOMP_DecalFont_DrawLine("FINISHED!", 0x100, 206, FONT_SMALL, JUSTIFY_CENTER|ORANGE);
	
	windowText.h = 0;
	
	int i;
	for(i = 0; i < octr->NumDrivers; i++)
		if(octr->nameBuffer[i*0xC] == 0)
			numDead++;
	
	for(i = 0; i < octr->NumDrivers; i++)
	{
		// skip drivers still racing
		if(octr->RaceEnd[i].time == 0)
		{
			skipRow++;
			continue;
		}
		
		int slot = octr->RaceEnd[i].slot;
		
		// skip disconnected drivers
		if(octr->nameBuffer[slot * 0xc] == 0)
		{
			skipRow++;
			continue;
		}
		
		sprintf(message, "%s:", &octr->nameBuffer[slot * 0xc]);
		
		int color = ORANGE;
		if(slot == 0)
			color = BLUE;
		
		DecalFont_DrawLine(
			message,
			0x120,0x48+i*0x8,FONT_SMALL,color);
		
		DecalFont_DrawLine(
			DECOMP_RECTMENU_DrawTime(octr->RaceEnd[i].time),
			0x1A0,0x48+i*0x8,FONT_SMALL,color);
			
		windowText.h += 8;
	}
	
	int lastY = 0x48+(i*0x8)-(skipRow*0x8);
	
	if(octr->numDriversEnded == (octr->NumDrivers-numDead))
	{
		DecalFont_DrawLine(
			"Restart in 6 seconds",
			0x120,lastY,FONT_SMALL,RED);
			
		windowText.h += 8;
	}
	
	else
	{
		sprintf(
			message, 
			"Waiting for %d more",
			(octr->NumDrivers-numDead) - octr->numDriversEnded);
		
		DecalFont_DrawLine(
			message,
			0x120,lastY,FONT_SMALL,PAPU_YELLOW);
			
		windowText.h += 8;
	}
	
	
	windowText.h += 0x10;
	
	struct DB *backBuffer = 
		sdata->gGT->backBuffer;

	DECOMP_RECTMENU_DrawInnerRect(
		&windowText, 1, 
		backBuffer->otMem.startPlusFour);
}

void Online_OtherFX_RecycleNew(
		u_int* soundID_Count, u_int newSoundID, u_int modifyFlags)
{
	struct Driver* d = sdata->gGT->drivers[0];
	
	if(
		((int)soundID_Count != (int)&d->driverAudioPtrs[0]) &&
		((int)soundID_Count != (int)&d->driverAudioPtrs[1]) &&
		((int)soundID_Count != (int)&d->driverAudioPtrs[2]) &&
		((int)soundID_Count != (int)&d->driverAudioPtrs[3])
	  )
	{
		// For now, mute everyone who is not Player1.
		// In the future, modify Vol/LR
		return;
	}
	
	int local = *soundID_Count;
	
    if (
		// if this sound is already playing
		(local != 0) &&

        // if soundID doesn't match new ID
        ((local & 0xffff) != newSoundID)
	   )
    {
        OtherFX_Stop1(local);
        
		*soundID_Count = 0;
		local = 0;
    }

    if (newSoundID != -1)
    {
        // if this is a new sound
        if (local == 0)
        {
            *soundID_Count = 
				OtherFX_Play_LowLevel(newSoundID & 0xffff, 0, modifyFlags);
        }
        // if not a new sound,
        // modification of old sound
        else
        {
            OtherFX_Modify(local, modifyFlags);
        }
    }
}
