#include <common.h>

void DECOMP_MainInit_FinalizeInit(struct GameTracker *gGT)
{
    int i;
    int numPlyr;
    u_char *puVar3;
    struct Driver *d;
    struct Level *lev1;
    struct Instance *inst;
	
	// === Naughty Dog Bug ===
	// Quitting a race while heldItem is warpball,
	// never resets this flag, and then the game
	// can not give warpball again until you reboot
	gGT->gameMode1 &= ~(WARPBALL_HELD);
	
    // enable collisions with all temporary walls
    // (adv hub doors, tiger temple teeth, etc)
    sdata->doorAccessFlags = 0;

    // add a bookmark
    DECOMP_MEMPACK_PushState();

    gGT->pushBuffer[0].distanceToScreen_PREV = 0x100;
    gGT->pushBuffer[0].distanceToScreen_CURR = 0x100;

    // erase all threadBucket structs
    memset(&gGT->threadBuckets[0], 0, sizeof(struct ThreadBucket) * NUM_BUCKETS);

#if 0
    gGT->threadBuckets[PLAYER].s_longName = 0x8008d30c;  // PLAYER
    gGT->threadBuckets[PLAYER].s_shortName = 0x8008d314; // PLYR
    gGT->threadBuckets[ROBOT].s_longName = 0x8008d31c;  // ROBOT
    gGT->threadBuckets[ROBOT].s_shortName = 0x8008d324; // RBOT
    gGT->threadBuckets[STATIC].s_longName = 0x8008d32c;  // STATIC
    gGT->threadBuckets[STATIC].s_shortName = 0x8008d334; // STAT
    gGT->threadBuckets[MINE].s_longName = 0x8008d33c;  // MINE
    gGT->threadBuckets[MINE].s_shortName = 0x8008d33c; // MINE
    gGT->threadBuckets[WARPPAD].s_longName = 0x8008d344;  // WARPPAD
    gGT->threadBuckets[WARPPAD].s_shortName = 0x8008d34c; // WRPD
    gGT->threadBuckets[TRACKING].s_longName = 0x80011434;  // TRACKING
    gGT->threadBuckets[TRACKING].s_shortName = 0x8008d354; // TRKG
#endif

    gGT->threadBuckets[PLAYER].boolCantPause = 0;
    gGT->threadBuckets[PLAYER].unk2[0] = 0x40;
    gGT->threadBuckets[PLAYER].unk2[1] = 0x40;
    gGT->threadBuckets[PLAYER].unk2[2] = 0x80;

    gGT->threadBuckets[ROBOT].boolCantPause = 0;
    gGT->threadBuckets[ROBOT].unk2[0] = 0x40;
    gGT->threadBuckets[ROBOT].unk2[1] = 0x80;
    gGT->threadBuckets[ROBOT].unk2[2] = 0x40;

    gGT->threadBuckets[STATIC].boolCantPause = 1;
    gGT->threadBuckets[STATIC].unk2[0] = 0x40;
    gGT->threadBuckets[STATIC].unk2[1] = 0x80;
    gGT->threadBuckets[STATIC].unk2[2] = 0x80;

    gGT->threadBuckets[MINE].boolCantPause = 0;
    gGT->threadBuckets[MINE].unk2[0] = 0x80;
    gGT->threadBuckets[MINE].unk2[1] = 0x80;
    gGT->threadBuckets[MINE].unk2[2] = 0x80;

    gGT->threadBuckets[WARPPAD].boolCantPause = 1;
    gGT->threadBuckets[WARPPAD].unk2[0] = 0x80;
    gGT->threadBuckets[WARPPAD].unk2[1] = 0x40;
    gGT->threadBuckets[WARPPAD].unk2[2] = 0x80;

    gGT->threadBuckets[TRACKING].boolCantPause = 0;
    gGT->threadBuckets[TRACKING].unk2[0] = 0x80;
    gGT->threadBuckets[TRACKING].unk2[1] = 0x80;
    gGT->threadBuckets[TRACKING].unk2[2] = 0x80;

#if 0
    gGT->threadBuckets[BURST].s_longName = 0x8008d35c;  // BURST
    gGT->threadBuckets[BURST].s_shortName = 0x8008d364; // BRST
    gGT->threadBuckets[BLOWUP].s_longName = 0x8008d36c;  // BLOWUP
    gGT->threadBuckets[BLOWUP].s_shortName = 0x8008d374; // BLWP
    gGT->threadBuckets[TURBO].s_longName = 0x8008d37c;  // TURBO
    gGT->threadBuckets[TURBO].s_shortName = 0x8008d384; // TRBO
    gGT->threadBuckets[SPIDER].s_longName = 0x8008d38c;  // SPIDER
    gGT->threadBuckets[SPIDER].s_shortName = 0x8008d394; // SPDR
    gGT->threadBuckets[FOLLOWER].s_longName = 0x80011440;  // FOLLOWER
    gGT->threadBuckets[FOLLOWER].s_shortName = 0x8008d39c; // FLWR
    gGT->threadBuckets[STARTTEXT].s_longName = 0x8001144c; // STARTTEXT
#endif

    gGT->threadBuckets[BURST].boolCantPause = 0;
    gGT->threadBuckets[BURST].unk2[0] = 0x80;
    gGT->threadBuckets[BURST].unk2[1] = 0x40;
    gGT->threadBuckets[BURST].unk2[2] = 0x80;

    gGT->threadBuckets[BLOWUP].boolCantPause = 0;
    gGT->threadBuckets[BLOWUP].unk2[0] = 0x80;
    gGT->threadBuckets[BLOWUP].unk2[1] = 0x80;
    gGT->threadBuckets[BLOWUP].unk2[2] = 0;

    gGT->threadBuckets[TURBO].boolCantPause = 0;
    gGT->threadBuckets[TURBO].unk2[0] = 0;
    gGT->threadBuckets[TURBO].unk2[1] = 0;
    gGT->threadBuckets[TURBO].unk2[2] = 0x80;

    gGT->threadBuckets[SPIDER].boolCantPause = 0;
    gGT->threadBuckets[SPIDER].unk2[0] = 0x80;
    gGT->threadBuckets[SPIDER].unk2[1] = 0x40;
    gGT->threadBuckets[SPIDER].unk2[2] = 0x80;

    gGT->threadBuckets[FOLLOWER].boolCantPause = 0;
    gGT->threadBuckets[FOLLOWER].unk2[0] = 0x40;
    gGT->threadBuckets[FOLLOWER].unk2[1] = 0x40;
    gGT->threadBuckets[FOLLOWER].unk2[2] = 0x80;

#if 0
    gGT->threadBuckets[STARTTEXT].s_shortName = 0x8008d3a4; // STXT
    gGT->threadBuckets[OTHER].s_longName = 0x8008d3ac;  // OTHER
    gGT->threadBuckets[OTHER].s_shortName = 0x8008d3b4; // OTHR
    gGT->threadBuckets[AKUAKU].s_longName = 0x8008d3bc;  // AKUAKU
    gGT->threadBuckets[AKUAKU].s_shortName = 0x8008d3c4; // AKUU
    gGT->threadBuckets[CAMERA].s_longName = 0x8008d3cc;  // CAMERA
    gGT->threadBuckets[CAMERA].s_shortName = 0x8008d3d4; // CAMR
    gGT->threadBuckets[HUD].s_longName = 0x8008d3dc;  // HUD
    gGT->threadBuckets[HUD].s_shortName = 0x8008d3e0; // THUD
    gGT->threadBuckets[PAUSE].s_longName = 0x8008d3e8;  // PAUSE
    gGT->threadBuckets[PAUSE].s_shortName = 0x8008d3f0; // PAUS
#endif

    gGT->threadBuckets[STARTTEXT].boolCantPause = 0;
    gGT->threadBuckets[STARTTEXT].unk2[0] = 0x80;
    gGT->threadBuckets[STARTTEXT].unk2[2] = 0x80;
    gGT->threadBuckets[STARTTEXT].unk2[1] = 0x40;

    gGT->threadBuckets[OTHER].boolCantPause = 0;
    gGT->threadBuckets[OTHER].unk2[0] = 0x80;
    gGT->threadBuckets[OTHER].unk2[1] = 0x40;
    gGT->threadBuckets[OTHER].unk2[2] = 0x40;

    gGT->threadBuckets[AKUAKU].boolCantPause = 0;
    gGT->threadBuckets[AKUAKU].unk2[0] = 0x80;
    gGT->threadBuckets[AKUAKU].unk2[1] = 0x40;
    gGT->threadBuckets[AKUAKU].unk2[2] = 0x40;

    gGT->threadBuckets[CAMERA].boolCantPause = 1;
    gGT->threadBuckets[CAMERA].unk2[0] = 0x80;
    gGT->threadBuckets[CAMERA].unk2[1] = 0x80;
    gGT->threadBuckets[CAMERA].unk2[2] = 0x40;

    gGT->threadBuckets[HUD].boolCantPause = 1;
    gGT->threadBuckets[HUD].unk2[0] = 0x80;
    gGT->threadBuckets[HUD].unk2[1] = 0x80;
    gGT->threadBuckets[HUD].unk2[2] = 0x80;

    gGT->threadBuckets[PAUSE].boolCantPause = 0;
    gGT->threadBuckets[PAUSE].unk2[0] = 0;
    gGT->threadBuckets[PAUSE].unk2[1] = 0x80;
    gGT->threadBuckets[PAUSE].unk2[2] = 0;

    // particles
    gGT->particleList_ordinary = NULL;
    gGT->particleList_heatWarp = NULL;
    gGT->numParticles = 0;

    // deadc0ed, FUN_8006c684
    // RNG stuff
    gGT->deadcoed_struct.unk1 = 0x30215400;
    gGT->deadcoed_struct.unk2 = 0x493583fe;

    for (i = 0; i < 12; i++)
    {
        gGT->DecalMP[i].inst = NULL;
        *(short *)&gGT->DecalMP[i].data[0] = 1000;
        
		gGT->DecalMP[i].ptrOT1 = 0;
		gGT->DecalMP[i].ptrOT2 = 0;
    }

    DECOMP_MainInit_JitPoolsReset(gGT);
	
    lev1 = gGT->level1;

#ifndef REBUILD_PS1
    // 0x1d7c
    gGT->trackLength_x_numLaps_x_8 =
        lev1->ptr_restart_points[0].distToFinish *
        gGT->numLaps * 8;
#endif

#ifndef USE_ONLINE
	// OG code
    DECOMP_MainInit_Drivers(gGT);
#else
	void OnlineInit_Drivers(struct GameTracker* gGT);
	OnlineInit_Drivers(gGT);
#endif

    // assume 1P fov
    numPlyr = 1;

    // if you are not in main menu
    if ((gGT->gameMode1 & MAIN_MENU) == 0)
    {
        numPlyr = gGT->numPlyrCurrGame;
    }

    // Initialize four PushBuffer, 4 main screens
    DECOMP_PushBuffer_Init(&gGT->pushBuffer[0], 0, numPlyr);
    DECOMP_PushBuffer_Init(&gGT->pushBuffer[1], 1, numPlyr);
    DECOMP_PushBuffer_Init(&gGT->pushBuffer[2], 2, numPlyr);
    DECOMP_PushBuffer_Init(&gGT->pushBuffer[3], 3, numPlyr);

    struct PushBuffer* pb;
    
	pb = &gGT->pushBuffer_UI;
    DECOMP_PushBuffer_Init(pb, 0, 1);
	
    pb->rot[0] = 0x800;
    DECOMP_PushBuffer_SetPsyqGeom(pb);
	DECOMP_PushBuffer_SetMatrixVP(pb);

    if ((gGT->hudFlags & 2) != 0)
    {
        DECOMP_UI_INSTANCE_InitAll();
    }

    gGT->unk1cac[4] = 2;

    for (i = 0; i < 8; i++)
    {
        // get pointer to player structure of each driver
        d = gGT->drivers[i];

        // if pointer is not nullptr
        if (d == NULL) continue;
        
        inst = d->instSelf;
        if (inst != 0)
        {
            inst->scale[0] = 0xccc;
            inst->scale[1] = 0xccc;
            inst->scale[2] = 0xccc;
        }

        if (i < gGT->numPlyrCurrGame)
        {
            DECOMP_CAM_Init(&gGT->cameraDC[i], i, d, &gGT->pushBuffer[i]);

			// freeze camera of P1, only in main menu
            if (
				((gGT->gameMode1 & MAIN_MENU) == 0) ||
				(i < 1)
				)
			{
				// remove frozen camera flag
				gGT->cameraDC[i].flags &= 0xffff7fff;
			}
			else
			{
				gGT->cameraDC[i].flags |= 0x8000;
			}
		}
    }

    if (gGT->levelID == MAIN_MENU_LEVEL)
    {
        // 30 seconds
        gGT->demoCountdownTimer = FPS_DOUBLE(900);
    }

    // copy InstDef to InstancePool
    DECOMP_INSTANCE_LevInitAll(lev1->ptrInstDefs, lev1->numInstances);

    // Debug_ToggleNormalSpawn == normal spawn
    if (gGT->Debug_ToggleNormalSpawn != 0)
    {
        DECOMP_MainGameStart_Initialize(gGT, 1);

        if (gGT->boolDemoMode != 0)
        {
            for (i = 0; i < gGT->numPlyrCurrGame; i++)
            {
#ifndef REBUILD_PS1
                BOTS_Driver_Convert(gGT->drivers[i]);
#endif
            }
        }
    }

#ifndef REBUILD_PS1
    // execute all camera thread update functions
    ThTick_RunBucket(gGT->threadBuckets[CAMERA].thread);
#endif

// dont write unused variables
#if 0
    // lev -> clearColor rgb
    sdata->LevClearColorRGB[0] = (u_int)(char *)(lev1->clearColorRGBA)[0];
    sdata->LevClearColorRGB[1] = (u_int)(char *)(lev1->clearColorRGBA)[1];
    sdata->LevClearColorRGB[2] = (u_int)(char *)(lev1->clearColorRGBA)[2];
#endif

	// Used in Coco Park, encoded as Blue
    *(int *)&gGT->db[0].drawEnv.isbg = lev1->clearColorRGBA<<8;
    *(int *)&gGT->db[1].drawEnv.isbg = lev1->clearColorRGBA<<8;

    if (
		(gGT->numPlyrCurrGame == 1) &&
        (lev1->clearColor[0].enable != 0) &&
        (lev1->clearColor[1].enable != 0)
		)
    {
        // set isbg of both DBs to false
        gGT->db[0].drawEnv.isbg = 0;
        gGT->db[1].drawEnv.isbg = 0;
    }
    else
    {
        // set isbg of both DBs to true
        gGT->db[0].drawEnv.isbg = 1;
        gGT->db[1].drawEnv.isbg = 1;
    }

    if (lev1 != NULL)
		if (lev1->ptr_mesh_info != NULL)
			DECOMP_LevInstDef_UnPack(lev1->ptr_mesh_info);

#ifndef REBUILD_PS1
    MainInit_VisMem(gGT);
    MainInit_RainBuffer(gGT);

    // animates water, 1P mode
    AnimateWater1P(
        gGT->timer,
        lev1->numWaterVertices,
        lev1->ptr_water,
        lev1->ptr_tex_waterEnvMap,
        lev1->unk5);
#endif

    gGT->pushBuffer_UI.fadeFromBlack_desiredResult = 0x1000;
    gGT->pushBuffer_UI.fade_step = 0x200;

    numPlyr = gGT->numPlyrCurrGame;

	// stars
    gGT->stars.numStars = (short)(lev1->unkStarData[0] / numPlyr);
    gGT->stars.unk[0] = lev1->unkStarData[1];
    gGT->stars.unk[1] = lev1->unkStarData[2];
    gGT->stars.unk[2] = lev1->unkStarData[3];

	// confetti
    gGT->confetti.numParticles_curr = 0;
    gGT->confetti.numParticles_max = 0;
    gGT->confetti.unk2 = 0;
    gGT->confetti.velY = -10;

    for (i = 0; i < 4; i++)
    {
        gGT->winnerIndex[i] = 0;
    }

#if 0
    BOTS_EmptyFunc();
#endif

#ifdef USE_ONLINE
	void octr_initHook();
	octr_initHook();
	
	// quit, so confetti doesn't initialize
	// when loading into Polar Credits LEV
	return;
#endif

#ifndef REBUILD_PS1
    if ((gGT->gameMode1 & ADVENTURE_ARENA) != 0)
		if (gGT->podiumRewardID != 0)
			CS_Podium_FullScene_Init();
    
    if ((gGT->gameMode1 & GAME_CUTSCENE) != 0)
    {
        // freecam mode
        gGT->cameraDC[0].cameraMode = 3;

        // disable all HUD flags
        gGT->hudFlags = 0;

        CS_LevCamera_OnInit();
    }

    PickupBots_Init();
#endif
}
