#include <common.h>

void MainInit_FinalizeInit(struct GameTracker *gGT)
{
    char i;
    char numPlyr;
    u_char *puVar3;
    struct GameTracker *gGT;
    struct TileView *view;
    struct Driver *d;
    struct Level *lev1;
    struct Instance *inst;

    // enable collisions with all temporary walls
    // (adv hub doors, tiger temple teeth, etc)
    sdata->doorAccessFlags = 0;

    // add a bookmark
    MEMPACK_PushState();

    gGT->tileView[0].distanceToScreen_PREV = 0x100;
    gGT->tileView[0].distanceToScreen_CURR = 0x100;

    // erase all threadBucket structs
    memset(gGT->threadBuckets[0], 0, 0x168);

    // threadBuckets.player
    gGT->threadBuckets[PLAYER].s_longName = 0x8008d30c;  // PLAYER
    gGT->threadBuckets[PLAYER].s_shortName = 0x8008d314; // PLYR

    // threadBuckets.robot
    gGT->threadBuckets[ROBOT].s_longName = 0x8008d31c;  // ROBOT
    gGT->threadBuckets[ROBOT].s_shortName = 0x8008d324; // RBOT

    // threadBuckets.static
    gGT->threadBuckets[STATIC].s_longName = 0x8008d32c;  // STATIC
    gGT->threadBuckets[STATIC].s_shortName = 0x8008d334; // STAT

    // threadBuckets.mine
    gGT->threadBuckets[MINE].s_longName = 0x8008d33c;  // MINE
    gGT->threadBuckets[MINE].s_shortName = 0x8008d33c; // MINE

    // threadBuckets.warppad
    gGT->threadBuckets[WARPPAD].s_longName = 0x8008d344;  // WARPPAD
    gGT->threadBuckets[WARPPAD].s_shortName = 0x8008d34c; // WRPD

    // threadBuckets.tracking
    gGT->threadBuckets[TRACKING].s_longName = 0x80011434;  // TRACKING
    gGT->threadBuckets[TRACKING].s_shortName = 0x8008d354; // TRKG

    // player threads can pause
    gGT->threadBuckets[PLAYER].boolCantPause = 0;

    gGT->threadBuckets[PLAYER].unk2[0] = 0x40;
    gGT->threadBuckets[PLAYER].unk2[1] = 0x40;
    gGT->threadBuckets[PLAYER].unk2[2] = 0x80;

    // robotcar threads can pause
    gGT->threadBuckets[ROBOT].boolCantPause = 0;

    gGT->threadBuckets[ROBOT].unk2[0] = 0x40;
    gGT->threadBuckets[ROBOT].unk2[1] = 0x80;
    gGT->threadBuckets[ROBOT].unk2[2] = 0x40;

    // static threads cant pause
    gGT->threadBuckets[STATIC].boolCantPause = 1;

    gGT->threadBuckets[STATIC].unk2[0] = 0x40;
    gGT->threadBuckets[STATIC].unk2[1] = 0x80;
    gGT->threadBuckets[STATIC].unk2[2] = 0x80;

    // mine threads can pause
    gGT->threadBuckets[MINE].boolCantPause = 0;

    gGT->threadBuckets[MINE].unk2[0] = 0x80;
    gGT->threadBuckets[MINE].unk2[1] = 0x80;
    gGT->threadBuckets[MINE].unk2[2] = 0x80;

    // warppad threads cant pause
    gGT->threadBuckets[WARPPAD].boolCantPause = 1;

    gGT->threadBuckets[WARPPAD].unk2[0] = 0x80;
    gGT->threadBuckets[WARPPAD].unk2[1] = 0x40;
    gGT->threadBuckets[WARPPAD].unk2[2] = 0x80;

    // tracking threads can pause
    gGT->threadBuckets[TRACKING].boolCantPause = 0;

    gGT->threadBuckets[TRACKING].unk2[0] = 0x80;
    gGT->threadBuckets[TRACKING].unk2[1] = 0x80;
    gGT->threadBuckets[TRACKING].unk2[2] = 0x80;

    // threadBuckets.burst
    gGT->threadBuckets[BURST].s_longName = 0x8008d35c;  // BURST
    gGT->threadBuckets[BURST].s_shortName = 0x8008d364; // BRST

    // threadBuckets.blowUp
    gGT->threadBuckets[BLOWUP].s_longName = 0x8008d36c;  // BLOWUP
    gGT->threadBuckets[BLOWUP].s_shortName = 0x8008d374; // BLWP

    // threadBuckets.turbo
    gGT->threadBuckets[TURBO].s_longName = 0x8008d37c;  // TURBO
    gGT->threadBuckets[TURBO].s_shortName = 0x8008d384; // TRBO

    // threadBuckets.spider
    gGT->threadBuckets[SPIDER].s_longName = 0x8008d38c;  // SPIDER
    gGT->threadBuckets[SPIDER].s_shortName = 0x8008d394; // SPDR

    // threadBuckets.follower
    gGT->threadBuckets[FOLLOWER].s_longName = 0x80011440;  // FOLLOWER
    gGT->threadBuckets[FOLLOWER].s_shortName = 0x8008d39c; // FLWR

    // threadBuckets.startText
    gGT->threadBuckets[STARTTEXT].s_longName = 0x8001144c; // STARTTEXT

    // burst threads can pause
    gGT->threadBuckets[BURST].boolCantPause = 0;

    gGT->threadBuckets[BURST].unk2[0] = 0x80;
    gGT->threadBuckets[BURST].unk2[1] = 0x40;
    gGT->threadBuckets[BURST].unk2[2] = 0x80;

    // blowup threads can pause
    gGT->threadBuckets[BLOWUP].boolCantPause = 0;

    gGT->threadBuckets[BLOWUP].unk2[0] = 0x80;
    gGT->threadBuckets[BLOWUP].unk2[1] = 0x80;
    gGT->threadBuckets[BLOWUP].unk2[2] = 0;

    // turbo threads can pause
    gGT->threadBuckets[TURBO].boolCantPause = 0;

    gGT->threadBuckets[TURBO].unk2[0] = 0;
    gGT->threadBuckets[TURBO].unk2[1] = 0;
    gGT->threadBuckets[TURBO].unk2[2] = 0x80;

    // spider threads can pause
    gGT->threadBuckets[SPIDER].boolCantPause = 0;

    gGT->threadBuckets[SPIDER].unk2[0] = 0x80;
    gGT->threadBuckets[SPIDER].unk2[1] = 0x40;
    gGT->threadBuckets[SPIDER].unk2[2] = 0x80;

    // follower threads can pause
    gGT->threadBuckets[FOLLOWER].boolCantPause = 0;

    gGT->threadBuckets[FOLLOWER].unk2[0] = 0x40;
    gGT->threadBuckets[FOLLOWER].unk2[1] = 0x40;
    gGT->threadBuckets[FOLLOWER].unk2[2] = 0x80;

    // threadBuckets.starttext
    gGT->threadBuckets[STARTTEXT].s_shortName = 0x8008d3a4; // STXT

    // threadBuckets.other
    gGT->threadBuckets[OTHER].s_longName = 0x8008d3ac;  // OTHER
    gGT->threadBuckets[OTHER].s_shortName = 0x8008d3b4; // OTHR

    // threadBuckets.akuAku
    gGT->threadBuckets[AKUAKU].s_longName = 0x8008d3bc;  // AKUAKU
    gGT->threadBuckets[AKUAKU].s_shortName = 0x8008d3c4; // AKUU

    // threadBuckets.camera
    gGT->threadBuckets[CAMERA].s_longName = 0x8008d3cc;  // CAMERA
    gGT->threadBuckets[CAMERA].s_shortName = 0x8008d3d4; // CAMR

    // threadBuckets.hud
    gGT->threadBuckets[HUD].s_longName = 0x8008d3dc;  // HUD
    gGT->threadBuckets[HUD].s_shortName = 0x8008d3e0; // THUD
    
    // threadBuckets.pause
    gGT->threadBuckets[PAUSE].s_longName = 0x8008d3e8; // PAUSE
    gGT->threadBuckets[PAUSE].s_shortName = 0x8008d3f0; // PAUS

    // starttext threads can pause
    gGT->threadBuckets[STARTTEXT].boolCantPause = 0;

    gGT->threadBuckets[STARTTEXT].unk2[0] = 0x80;
    gGT->threadBuckets[STARTTEXT].unk2[2] = 0x80;
    gGT->threadBuckets[STARTTEXT].unk2[1] = 0x40;

    // "other" threads can pause
    gGT->threadBuckets[OTHER].boolCantPause = 0;

    gGT->threadBuckets[OTHER].unk2[0] = 0x80;
    gGT->threadBuckets[OTHER].unk2[1] = 0x40;
    gGT->threadBuckets[OTHER].unk2[2] = 0x40;

    // aku threads can pause
    gGT->threadBuckets[AKUAKU].boolCantPause = 0;

    gGT->threadBuckets[AKUAKU].unk2[0] = 0x80;
    gGT->threadBuckets[AKUAKU].unk2[1] = 0x40;
    gGT->threadBuckets[AKUAKU].unk2[2] = 0x40;

    // camera threads cant pause
    gGT->threadBuckets[CAMERA].boolCantPause = 1;

    gGT->threadBuckets[CAMERA].unk2[0] = 0x80;
    gGT->threadBuckets[CAMERA].unk2[1] = 0x80;
    gGT->threadBuckets[CAMERA].unk2[2] = 0x40;

    // hud threads cant pause
    gGT->threadBuckets[HUD].boolCantPause = 1;

    gGT->threadBuckets[HUD].unk2[0] = 0x80;
    gGT->threadBuckets[HUD].unk2[1] = 0x80;
    gGT->threadBuckets[HUD].unk2[2] = 0x80;

    // pause threads can pause
    gGT->threadBuckets[PAUSE].boolCantPause = 0;

    gGT->threadBuckets[PAUSE].unk2[0] = 0;
    gGT->threadBuckets[PAUSE].unk2[1] = 0x80;
    gGT->threadBuckets[PAUSE].unk2[2] = 0;

    // reset particle linked lists
    gGT->particleList_ordinary = NULL;
    gGT->particleList_heatWarp = NULL;

    // reset number of particles
    gGT->numParticles = 0;

    // deadc0ed, FUN_8006c684
    // RNG stuff
    gGT->deadcoed_struct.unk1 = 0x30215400;
    gGT->deadcoed_struct.unk2 = 0x493583fe;

    for (i = 0; i < 12; i++)
    {
        gGT[0x16c] = 0;
        *(short *)(gGT + 0x16a) = 1000;
        gGT[0x1ad] = 0;
        gGT[0x1ae] = 0;
        gGT = gGT + 0x4a;
    }

    // erase everything in all pools
    MainInit_JitPoolsReset(gGT);

    // 0x1d7c
    gGT->trackLength_x_numLaps_x_8 =

        // track length
        // gGT -> level -> respawn points[0] -> dist_to_finish
        gGT->level1->ptr_restart_points[0].distToFinish *

        // number of laps * 8
        sdata->gGT->numLaps * 8;

    MainInit_Drivers(gGT);

    // assume 1P fov
    numPlyr = 1;

    // if you are not in main menu
    if ((gGT->gameMode1 & MAIN_MENU) == 0)
    {
        numPlyr = gGT->numPlyrCurrGame;
    }

    // Initialize four TileView, 4 main screens
    TileView_Init(gGT->tileView[0], 0, numPlyr);
    TileView_Init(gGT->tileView[1], 1, numPlyr);
    TileView_Init(gGT->tileView[2], 2, numPlyr);
    TileView_Init(gGT->tileView[3], 3, numPlyr);

    // Initialize TileView
    view = gGT->tileView_UI;
    TileView_Init(view, 0, 1);

    // rotX = 180 degrees
    view->rot[0] = 0x800;

    TileView_SetPsyqGeom(view);

    TileView_SetMatrixVP(view);

    // If HUD is enabled
    if ((gGT->hudFlags & 2) != 0)
    {
        UI_INSTANCE_InitAll();
    }

    gGT->unk1cac[4] = 2;

    for (i = 0; i < 8; i++)
    {
        // get pointer to player structure of each driver
        d = gGT->drivers[i];

        // if pointer is not nullptr
        if (d != NULL)
        {
            // get instance
            inst = d->instSelf;

            // if loop iteration is less than numPlyrCurrGame,
            // basically: if this driver is a human player
            if (i < gGT->numPlyrCurrGame)
            {
                // param_1 + iVar9
                // pointer to cameraDC buffer

                // param_1 + iVar10
                // pointer to tileView buffer

                // CAM_Init for all cameras
                CAM_Init(gGT->cameraDC[i], i, d, gGT->tileView[i]);

                if (
                    // If not in main menu (character selection, track selection, any part of it)
                    ((gGT->gameMode1 & MAIN_MENU) == 0) ||
                    (i < 1)
                    )
                {
                    // remove frozen camera flag
                    gGT->cameraDC[0].flags &= 0xffff7fff;
                }
                else
                {

                    // add frozen camera flag
                    gGT->cameraDC[0].flags |= 0x8000;
                }
            }

            // if instance is valid
            if (inst != 0)
            {
                // set the scale (x, y, z)
                inst->scale[0] = 0xccc;
                inst->scale[1] = 0xccc;
                inst->scale[2] = 0xccc;
            }
        }
    }

    // If you are drawing the main menu
    if (gGT->levelID == MAIN_MENU_LEVEL)
    {
        // set demo countdown timer to 30 seconds
        gGT->demoCountdownTimer = 900;
    }

    // copy InstDef to InstancePool
    INSTANCE_LevInitAll(gGT->level1->ptrInstDefs, gGT->level1->numInstances);

    // Debug_ToggleNormalSpawn == normal spawn
    if (gGT->Debug_ToggleNormalSpawn != 0)
    {
        MainGameStart_Initialize(gGT, 1);

        if (
            // if you're in Demo Mode
            (gGT->boolDemoMode != 0) &&
            (
                // if numPlyrCurrGame is not zero
                sdata->gGT->numPlyrCurrGame != 0
            )
            )
        {
            for (i = 0; i < gGT->numPlyrCurrGame; i++)
            {
                // turn driver into Robotcar
                BOTS_Driver_Convert(gGT->drivers[i]);
            }
        }
    }

    // execute all camera thread update functions
    ThTick_RunBucket(gGT->threadBuckets[CAMERA].thread);

    // lev -> clearColor rgb
    sdata->LevClearColorRGB[0] = (u_int) (char*)(gGT->level1->clearColorRGBA)[0];
    sdata->LevClearColorRGB[1] = (u_int) (char*)(gGT->level1->clearColorRGBA)[1];
    sdata->LevClearColorRGB[2] = (u_int) (char*)(gGT->level1->clearColorRGBA)[2];

    if (((gGT->numPlyrCurrGame == 1) &&
         // top half disabled
        (gGT->level1->clearColor[0].enable != 0)) &&
         // bottom half disabled
        (gGT->level1->clearColor[1].enable != 0))
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

    *(int*)&gGT->db[0].drawEnv.r0 = gGT->level1->clearColorRGBA;

    *(int*)&gGT->db[1].drawEnv.r0 = gGT->level1->clearColorRGBA;

    if (
        // if LEV pointer is valid
        (gGT->level1 != NULL) &&

        // If LEV's meshInfo is valid
        (gGT->level1->ptr_mesh_info != NULL))
    {
        LevInstDef_UnPack();
    }

    MainInit_VisMem(gGT);

    MainInit_RainBuffer(gGT);

    lev1 = gGT->level1;

    // animates water, 1P mode
    AnimateWater1P(
        gGT->timer,

        lev1->numWaterVertices,

        lev1->ptr_water,

        // lev->restart (maskgrab)
        lev1->ptr_tex_waterEnvMap,

        lev1->unk5);

    gGT->tileView_UI.fadeFromBlack_desiredResult = 0x1000;
    gGT->tileView_UI.fade_step = 0x200;

    numPlyr = gGT->numPlyrCurrGame;

    if (numPlyr == 0)
    {
        trap(0x1c00);
    }
    if (((u_int)numPlyr == 0xffffffff) && ((int)lev1->unkStarData[0] == -0x80000000))
    {
        trap(0x1800);
    }

    // number of stars per screen = number of stars in level, divided by number of players
    gGT->stars.numStars = (short)(lev1->unkStarData[0] / numPlyr);

    // other star-related data
    gGT->stars.unk[0] = lev1->unkStarData[1];
    gGT->stars.unk[1] = lev1->unkStarData[2];
    gGT->stars.unk[2] = lev1->unkStarData[3];

    // erase confetti data
    gGT->confetti.numParticles_curr = 0;
    gGT->confetti.numParticles_max = 0;
    gGT->confetti.unk2 = 0;

    // confetti VelY is negative, to move downward
    gGT->confetti.velY = 0xfffffff6;

    puVar3 = sdata->gGT + 0xc; // swapchain index?

    // clear array of confetti winners (?)
    for (i = 3; i > -1; i--)
    {
        // 0x2558 - 0xC = 0x254c though
        *(int*)(puVar3 + 0x2558) = 0;
        puVar3 = puVar3 + -4;
    }

    BOTS_EmptyFunc();

    if (
        ((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&

        ((gGT->podiumRewardID) != 0))
    {
        CS_Podium_FullScene_Init();
    }

    if ((gGT->gameMode1 & GAME_CUTSCENE) != 0)
    {
        // CameraDC, freecam mode
        gGT->CameraDC.cameraMode = 3;

        // disable all HUD flags
        gGT->hudFlags = 0;

        CS_LevCamera_OnInit();
    }

    RobotcarWeapons_Init();
}
