#include <common.h>

void DECOMP_MainInit_Drivers(struct GameTracker *gGT)
{
    char i;
    char numPlyrCurrGame = gGT->numPlyrCurrGame;
    u_char numDrivers;
    u_int uVar3;
    int gameMode = gGT->gameMode1;
    struct Driver* d;

    for (i = 0; i < 8; i++)
        gGT->drivers[i] = NULL;

    gGT->numBotsNextGame = 0;

#ifndef REBUILD_PS1
    if ((gameMode & (GAME_CUTSCENE | ADVENTURE_ARENA | MAIN_MENU)) == 0)
    {
        BOTS_Adv_AdjustDifficulty();
    }

    GhostReplay_Init1();

    if (LOAD_IsOpen_RacingOrBattle())
    {
        RB_MinePool_Init();
    }
#endif

    // Spawn all players,
	// This MUST be in reverse order,
	// because of threadBucket linked list order
    for (i = numPlyrCurrGame-1; i >= 0; i--)
    {
		gGT->drivers[i] = VehInit_Player(i);
    }
	
#ifndef REBUILD_PS1
	// spawn all AIs
    if (
        (
			// exclude cutscene, relic, Time Trial,
			// Adventure Hub, Main Menu, Battle
            ((gameMode & 0x2c122020) == 0) &&

            // numPlyrCurrGame requires AIs
            (numPlyrCurrGame < 3)
		) &&
        (
            // in Arcade or Adventure
            (gameMode & (ARCADE_MODE | ADVENTURE_MODE)) != 0
		)
	   )
    {
        // If you're in Boss Mode
        // 0x80000000
        if (gameMode < 0)
        {
            numDrivers = numPlyrCurrGame+1;
        }
		
		// Purple Gem Cup
		else if (gGT->cup.cupID == 4)
		{
            numDrivers = numPlyrCurrGame+4;
		}

        else if (numPlyrCurrGame == 1)
		{
			numDrivers = 8;
		}
		
        else //if (numPlyrCurrGame == 2)
		{
			numDrivers = 6;
		}

        // Spawn AIs
        for (i = numPlyrCurrGame; i < numDrivers; i++)
        {
            // spawn an AI at this character index
            BOTS_Driver_Init(i);
        }
    }

    // If number of AIs is not zero
    if (gGT->numBotsNextGame != 0)
    {
        EngineAudio_InitOnce(0x10, 0x8080);
        EngineAudio_InitOnce(0x11, 0x8080);
    }
#endif

    // if this is main menu
    if ((gameMode & MAIN_MENU) != 0)
    {
		// fill up 4 players
        for (i = numPlyrCurrGame; i < 4; i++)
        {
            gGT->drivers[i] = VehInit_Player(i);
        }
    }

#ifndef REBUILD_PS1
    // if you're in time trial, not main menu, not loading.
    // basically, if you're in time trial gameplay
    if ((gameMode & 0x20022000) == TIME_TRIAL)
    {
        GhostReplay_Init2();

        GhostTape_Start();
    }
#endif
}
