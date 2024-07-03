//these make it not compile?
//#include <common.h>
//#include "global.h"

void (*funcs[NUM_STATES]) () =
{
	StatePS1_Launch_EnterPID,
	StatePS1_Launch_PickServer,
	StatePS1_Launch_PickRoom,
	StatePS1_Launch_Error,
	StatePS1_Lobby_AssignRole,
	StatePS1_Lobby_HostTrackPick,
	StatePS1_Lobby_GuestTrackWait,
	StatePS1_Lobby_CharacterPick,
	StatePS1_Lobby_WaitForLoading,
	StatePS1_Lobby_StartLoading,
	StatePS1_Game_WaitForRace,
	StatePS1_Game_StartRace,
	StatePS1_Game_EndRace
};

RECT endRaceRECT =
{
	.x = 8,
	.y = 8,
	.w = 0x200-0x20,
	.h = 0xc8,
};

void ThreadFunc(struct Thread* t)
{
	int i;

	struct GameTracker* gGT = sdata->gGT;
	octr->boolPlanetLEV = gGT->levelID == 0x26;

	if(octr->boolPlanetLEV)
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

	// if client is intentionally idle
	if(octr->boolClientBusy)
	{
		i = WIN_CLIENT_SYNC_LEN - 2;
	}

	// if client should not be idle
	else
	{
		for(i = WIN_CLIENT_SYNC_LEN - 2; i >= 0; i--)
			octr->windowsClientSync[i+1] = octr->windowsClientSync[i];

		for(i = WIN_CLIENT_SYNC_LEN - 2; i >= 0; i--)
			if(octr->windowsClientSync[i+1] != octr->windowsClientSync[i])
				break;
	}

	//debug info
	//static char literallyAnyClientSync = 0;
	//char top_vals[33], bot_vals[33];
	//for (char ii = 0; ii < 32; ii++)
	//{
	//	//if (octr->windowsClientSync[ii] != 0/* || octr->windowsClientSync[ii + 32] != 0*/)
	//	//	literallyAnyClientSync |= 1;
	//	/*char c = octr->windowsClientSync[ii];
	//	if (c == 0)
	//		c = '0';
	//	else
	//	{
	//		c = c + 'A' - 1;
	//		c = (c < 'A') ? '.' : c;
	//		c = (c > 'Z') ? '.' : c;
	//	}
	//	top_vals[ii] = c;*/
	//	char tc = (octr->windowsClientSync[ii] % 10) + '0', bc = (octr->windowsClientSync[ii + 32] % 10) + '0';
	//	top_vals[ii] = tc;
	//	bot_vals[ii] = bc;
	//}
	//top_vals[32] = bot_vals[32] = '\0';
	//DecalFont_DrawLine((literallyAnyClientSync ? "t" : "f"), 0x100, 0x30, FONT_SMALL, JUSTIFY_CENTER | PAPU_YELLOW);
	//DecalFont_DrawLine(top_vals, 0x100, 0x38, FONT_SMALL, JUSTIFY_CENTER | PAPU_YELLOW);
	//DecalFont_DrawLine(bot_vals, 0x100, 0x40, FONT_SMALL, JUSTIFY_CENTER | PAPU_YELLOW);
	//char ptr[] = { 'p','t','r',':',' ','x','x','x','x','x','x','x','x','\0' }; //ind 5-12
	//0 = 30
	//9 = 39
	//A = 41
	//F = 46 //8000c027
	/*int ptrAddr = (int)&octr;
	for (char iii = 0; iii < 8; iii++)
	{
		if ((ptrAddr & 0xf) <= 9)
			ptr[12 - iii] = '0' + (ptrAddr & 0xf);
		else
			ptr[12 - iii] = 'A' + ((ptrAddr & 0xf) - 10);
		ptrAddr >>= 4;
	}
	DecalFont_DrawLine(ptr, 0x100, 0x48, FONT_SMALL, JUSTIFY_CENTER | PAPU_YELLOW);*/

	// if client didn't update the game in WIN_CLIENT_SYNC_LEN - 4 *or* WIN_CLIENT_SYNC_LEN / 2 frames (idk which).
	int boolCloseClient =
		(i == -1) &&
		(octr->CurrState > LAUNCH_ENTER_PID);

	// if client closed, or server disconnected
	if(boolCloseClient || (octr->CurrState < 0))
	{
		sdata->ptrActiveMenu = 0;

		if(octr->boolPlanetLEV)
		{
			// if closed==1, go to 0 ("please open client")
			// if closed==0, go to 1 (server select)
			octr->CurrState = !boolCloseClient;

			octr->serverLockIn1 = 0;
			octr->serverLockIn2 = 0;
			return;
		}

		// calls memset on OnlineCTR struct
		octr_entryHook();

		// if closed==1, go to 0 ("please open client")
		// if closed==0, go to 1 (server select)
		octr->CurrState = !boolCloseClient;

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

	// gameplay
	if (octr->CurrState >= GAME_WAIT_FOR_RACE)
	{
		void DrawOverheadNames();
		DrawOverheadNames();
	}

	if (octr->CurrState >= 0)
		funcs[octr->CurrState]();

	// if connecting, or entering IP
	if (octr->boolClientBusy)
	{
		DecalFont_DrawLine(
			"SEE CLIENT WINDOW",
			0x100,0x80,FONT_SMALL,JUSTIFY_CENTER|PAPU_YELLOW);
	}

	// not gameplay, must draw LAST
	if (octr->CurrState <= LOBBY_WAIT_FOR_LOADING)
	{
		void PrintTimeStamp();
		PrintTimeStamp();

		// if not viewing planet
		if(!octr->boolPlanetLEV)
		{
			struct RectMenu* m = sdata->ptrActiveMenu;

			// draw menu now because it is drawn
			// later, which puts it behind our background
			if(m != 0)
			{
				// clear width, then get width
				int width = 0;
				DECOMP_RECTMENU_GetWidth(m, &width, 1);

				// draw
				DECOMP_RECTMENU_DrawSelf(m, 0, 0, (int)width);
			}

			DECOMP_RECTMENU_DrawInnerRect(
				&endRaceRECT, 0, gGT->backBuffer->otMem.startPlusFour);
		}
	}

	#if 0
	if(strcmp("debugcam", octr->nameBuffer[0]) == 0)
	{
		void Freecam();
		Freecam();
	}
	#endif
}