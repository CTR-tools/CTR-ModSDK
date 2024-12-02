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
#endif

    DECOMP_GhostReplay_Init1();

    if (DECOMP_LOAD_IsOpen_RacingOrBattle())
    {
        DECOMP_RB_MinePool_Init();
    }

    // Spawn all players,
	// This MUST be in reverse order,
	// because of threadBucket linked list order
    for (i = numPlyrCurrGame-1; i >= 0; i--)
    {
		gGT->drivers[i] = DECOMP_VehBirth_Player(i);
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
		else if(
			
			// If you are in Adventure cup
			((gameMode & ADVENTURE_CUP) != 0) &&

			// purple gem cup
			(gGT->cup.cupID == 4)
		)
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
		// Init AI engine sounds
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
            gGT->drivers[i] = DECOMP_VehBirth_Player(i);
        }
    }
	
#ifdef REBUILD_PS1
	i = 0;
	int driverID = 0;
	struct Model* m;
	while (1)
	{
		m = sdata->PLYROBJECTLIST[i++];

		// "token"
		if(*(int*)&m->name[0] == 0x656b6f74)
		{
			// Player 1 always comes after Token
			break;
		}

		if (m == 0)
		{
			i = 0;
			break;
		}
	}
	
	if(gGT->numPlyrCurrGame == 1)
	{
		driverID = 0;
	}
	
	else if(gGT->numPlyrCurrGame == 2)
	{
		gGT->drivers[0]->instSelf->model = data.driverModel_lowLOD[0];
		gGT->drivers[1]->instSelf->model = data.driverModel_lowLOD[1];
		driverID = 2;
	}
	
	else
	{
		gGT->drivers[0]->instSelf->model = data.driverModel_lowLOD[0];
		gGT->drivers[1]->instSelf->model = data.driverModel_lowLOD[1];
		gGT->drivers[2]->instSelf->model = data.driverModel_lowLOD[2];
		
		if(gGT->numPlyrCurrGame == 4)
			gGT->drivers[3]->instSelf->model = sdata->PLYROBJECTLIST[i++];	
		
		driverID = 8;
	}
	
	for(driverID; driverID < 7; driverID++)
	{
		if(gGT->drivers[driverID] == 0) break;
		gGT->drivers[driverID]->instSelf->model = sdata->PLYROBJECTLIST[i++];
	}

	// leave commented, or it crashes Adventure->New
	#if 0
	for(driverID = 0; driverID < 7; driverID++)
	{
		if(gGT->drivers[driverID] == 0) break;
		printf("%s\n", gGT->drivers[driverID]->instSelf->model->name);
	}
	#endif
	
#endif

    // if you're in time trial, not main menu, not loading.
    // basically, if you're in time trial gameplay
    if ((gameMode & 0x20022000) == TIME_TRIAL)
    {
        DECOMP_GhostReplay_Init2();

        DECOMP_GhostTape_Start();
		
		#ifdef REBUILD_PS1
		
		// 0: human ghost
		// 1: n tropy / oxide
		if(sdata->ptrGhostTape[1] != 0)
		{
			// N Tropy to Oxide	
			void** pointers = ST1_GETPOINTERS(gGT->level1->ptrSpawnType1);
			if(sdata->ptrGhostTape[1]->gh == pointers[ST1_NOXIDE])
				i++;
		}
		
		gGT->threadBuckets[GHOST].thread->inst->model = 
			sdata->PLYROBJECTLIST[i++];
			
		struct Model** humanPlyrDriverModel =
			&gGT->threadBuckets[PLAYER].thread->inst->model;
			
		// that's characterIDs[1] from the MPK
		// humanGhost = *humanPlyrDriverModel,
		
		// then replace with intended P1 model
		*humanPlyrDriverModel =
			data.driverModel_lowLOD[0];
		#endif
    }
}
