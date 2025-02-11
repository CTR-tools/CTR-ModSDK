#include <common.h>

void DECOMP_VehBirth_TeleportSelf(struct Driver *d, u_char spawnFlag, int spawnPosY)
{
    char boolSpawnAtBossDoor;
    char numInstances;
    short *warppadRot=0;
    short posTop[3];
    short posBottom[3];
    short warppadPos[3];
    u_int gameMode2;

    struct PosRot
    {
        short pos[3];
        short rot[3];
    };

    struct GameTracker *gGT = sdata->gGT;
    struct Level* level1 = gGT->level1;
	struct Instance* dInst = d->instSelf;

#ifndef REBUILD_PS1
    struct ScratchpadStruct* sps = (struct ScratchpadStruct*)0x1f800108;
#else
    char scratchpad[0x1000];
    struct ScratchpadStruct* sps = (struct ScratchpadStruct*)&scratchpad[0];
#endif

    // cheat flags
    gameMode2 = gGT->gameMode2;
	gGT->gameMode2 &= ~(SPAWN_AT_BOSS | 2);

#if 0
    // Check LEV data for nullptr
    if (level1 == NULL || level1->ptr_mesh_info == NULL)
    {
        return;
    }
#endif

    // ground and wall quadblock flags
    sps->Union.QuadBlockColl.qbFlagsWanted = 0x3000;

    sps->Union.QuadBlockColl.qbFlagsIgnored = 0;
    
	// collision triangles, 2 (low-LOD) & 8 (hi-LOD)
    sps->Union.QuadBlockColl.searchFlags = 
		(gGT->numPlyrCurrGame > 3) ? 2 : 0;

    sps->ptr_mesh_info = level1->ptr_mesh_info;

	gGT->gameMode2 &= ~(VEH_FREEZE_DOOR);

    struct PosRot* posRot;
	short* rotArr;
	short rotDeltaY;

    // if you are mask grabbed
    if ((spawnFlag & 1) == 0)
    {
		posBottom[0] = (d->posCurr.x >> 8);
		posBottom[1] = (d->posCurr.y >> 8);
		posBottom[2] = (d->posCurr.z >> 8);
		
		posRot = posBottom;
		rotArr = &d->rotCurr.x;
		rotDeltaY = 0;
    }

	// If just obtained Roo boss key
	// spawn in front of hub door, beach-to-gemstone
	else if (
		(gGT->podiumRewardID == 99) &&
		(gGT->currAdvProfile.numKeys == 1))
	{
        gGT->gameMode2 |= VEH_FREEZE_DOOR;
		
		// Stripped out OG code to do trigonometry
		// on the door, just rig the results
		posBottom[0] = 0xC676;
		posBottom[1] = 0x17a-0x80;
		posBottom[2] = 0xFC79;

		// Rigged to Door#5
		posRot = posBottom;
		rotArr = &level1->ptrInstDefs[10].rot[0];
		rotDeltaY = 0x800;
    }

	// if you want to spawn outside boss door
    else if (
			// After leaving a boss race
			(
				// Set in 222 EndRace function
				((gameMode2 & SPAWN_AT_BOSS) != 0)
			) ||
			
			// Before starting a boss cutscene
			(
				// Just won the last trophy on the hub
				(gGT->podiumRewardID == 0x62) &&
				((gGT->currAdvProfile.numTrophies & 3) == 0)
			)
	)
    {
        // position outside boss door
        posRot = &level1->ptrSpawnType2_PosRot[1].posCoords[6];
		
		// spawn facing boss door
		rotArr = &posRot->rot[0];
		rotDeltaY = 0x400;
		
		// if just beat boss
		if ((gameMode2 & SPAWN_AT_BOSS) != 0)
		{
            // just finished pinstripe boss,
            if (gGT->prevLEV == HOT_AIR_SKYWAY)
			{
				// if spawn by pinstripe, dont face wall
				if(gGT->levelID == CITADEL_CITY)
					rotDeltaY = 0x800;
				
				// else if spawn by oxide,
				// do nothing, rotation already faces the door
			}
			
			// if just beat ANY other boss
			else
			{
				// spawn facing AWAY from door
				rotDeltaY = 0xC00;
			}
		}
    }
	
	// adventure hub + podium reward
    else if (
			// must check adventure arena, cause winning 
			// a sapphire relic and hitting RETRY will 
			// set podiumRewardID=RELIC, then spawn in the void
			((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&
			(gGT->podiumRewardID != 0)
		)
    {
        // spawn on the podium in the adv hub
		posRot = &level1->ptrSpawnType2_PosRot[1].posCoords[0];
		rotArr = &posRot->rot[0];
		rotDeltaY = 0;
    }
	
	// adventure hub + exit portal
    else if (
			
			((gGT->gameMode1 & ADVENTURE_ARENA) != 0) &&
			(
				(gGT->prevLEV >= 100) || // Gem Cups
				(gGT->prevLEV <= LAB_BASEMENT) // Other Portals
				
			)
		)
    {
        // get position where driver should spawn on map,
        // outside warppad they previously entered
        warppadRot = DECOMP_AH_WarpPad_GetSpawnPosRot(&warppadPos);
		
		posRot = warppadPos;
		rotArr = warppadRot;
		rotDeltaY = 0x400;
    }
	
	// normal track,
	// or advHub return from:
	//		main menu
	//		adv garage
	//		scrapbook
	//		credits
	else
	{
		// DEBUG TEST
		#if 0
		gGT->numLaps = 1;
		if(d->driverID != 0)
		#endif
		
        // racer crossed the start line backwards,
        // so lap doesn't count when race starts
        d->actionsFlagSet |= 0x1000000;

		#ifndef REBUILD_PS1
        d->distanceToFinish_checkpoint = level1->ptr_restart_points[0].distToFinish << 3;
		#endif

        // get coords where driver based on driver order (0-7)
        posRot = &level1->DriverSpawn[sdata->kartSpawnOrderArray[d->driverID]];
		rotArr = &posRot->rot[0];
		rotDeltaY = 0x400;
	}

    posBottom[0] = posRot->pos[0];
    posBottom[1] = posRot->pos[1] + 0x80;
    posBottom[2] = posRot->pos[2];
	
    posTop[0] = posBottom[0];
    posTop[1] = posBottom[1] - 0x100;
    posTop[2] = posBottom[2];
	
	d->rotCurr.x = rotArr[0];
	d->rotCurr.y = (rotArr[1] + rotDeltaY) & 0xfff;
	d->rotCurr.z = rotArr[2];

	#ifdef REBUILD_PC

	for(int i = 0; i < 7; i++)
		sdata->kartSpawnOrderArray[i] = i;

    // position index on starting line
    posRot = &level1->DriverSpawn[sdata->kartSpawnOrderArray[d->driverID]];

    // rotation data of all 8 drivers on starting line
    d->rotCurr.x = posRot->rot[0];
    d->rotCurr.y = posRot->rot[1] + 0x400;
    d->rotCurr.z = posRot->rot[2];

    d->posCurr.x = posRot->pos[0] << 8;
    d->posCurr.y = (posRot->pos[1]-0x40) << 8;
    d->posCurr.z = posRot->pos[2] << 8;

	dInst->matrix.t[0] = posRot->pos[0];
	dInst->matrix.t[1] = (posRot->pos[1]-0x40);
	dInst->matrix.t[2] = posRot->pos[2];

    ConvertRotToMatrix(&dInst->matrix.m, &d->rotCurr.x);

	#else

    COLL_SearchTree_FindQuadblock_Touching(&posTop[0], &posBottom[0], sps, 0);

    // if collision was not found
    if (sps->boolDidTouchQuadblock == 0)
    {
        d->AxisAngle3_normalVec[0] = 0;
        d->AxisAngle3_normalVec[1] = 0x1000;
        d->AxisAngle3_normalVec[2] = 0;
    }
    // if it was found
    else
    {
        d->AxisAngle3_normalVec[0] = *(short*)&sps->unk4C[0x24];
        d->AxisAngle3_normalVec[1] = *(short*)&sps->unk4C[0x26];
        d->AxisAngle3_normalVec[2] = *(short*)&sps->unk4C[0x28];
        d->lastValid = *(int*)&sps->unk4C[0x34];
    }

    // set all normal vectors to spawn
    d->AxisAngle1_normalVec.x = d->AxisAngle3_normalVec[0];
    d->AxisAngle2_normalVec[0] = d->AxisAngle3_normalVec[0];
    d->AxisAngle1_normalVec.y = d->AxisAngle3_normalVec[1];
    d->AxisAngle2_normalVec[1] = d->AxisAngle3_normalVec[1];
    d->AxisAngle1_normalVec.z = d->AxisAngle3_normalVec[2];
    d->AxisAngle2_normalVec[2] = d->AxisAngle3_normalVec[2];

    //for (int i = 0; i < 1; i++) // maybe this is done two times, because it was a do-while?
    {
        // set normal vector to spawn
        d->AxisAngle4_normalVec[0] = d->AxisAngle2_normalVec[0];
        d->AxisAngle4_normalVec[1] = d->AxisAngle2_normalVec[1];
        d->AxisAngle4_normalVec[2] = d->AxisAngle2_normalVec[2];
        // iVar9 = iVar9 + 8;
    }

    // player structure X, Y, Z
    d->posCurr.x = (int)(sps->Union.QuadBlockColl.hitPos[0]) << 8;
    d->posCurr.y = (int)(sps->Union.QuadBlockColl.hitPos[1] + spawnPosY) * 0x100;
    d->posCurr.z = (int)(sps->Union.QuadBlockColl.hitPos[2]) << 8;

    // duplicate of coordinate variables
    d->posPrev.x = d->posCurr.x;
    d->posPrev.y = d->posCurr.y;
    d->posPrev.z = d->posCurr.z;

    // save quadblock height
    d->quadBlockHeight = (int) sps->Union.QuadBlockColl.hitPos[1] << 8;

	#endif

    d->speed = 0;
    d->speedApprox = 0;
    d->jumpHeightCurr = 0;
    d->jumpHeightPrev = 0;
    d->unk_offset3B2 = 0;
    d->matrixArray = 0;
    d->matrixIndex = 0;
    d->jump_LandingBoost = 0;
    d->jumpMeter = 0;
    d->jumpMeterTimer = 0;
    d->turnAngleCurr = 0;
    d->unk_LerpToForwards = 0;
    d->turnAnglePrev = 0;
    d->rotCurr.w = 0;
    d->rotPrev.w = 0;
    d->ChangeState_param2 = 0;
    d->jumpSquishStretch = 0;
    d->underDriver = 0;
    d->distanceDrivenBackwards = 0;
    d->clockReceive = 0;
    d->revEngineState = 0;
	
    d->angle = d->rotCurr.y;
    d->rotPrev.x = d->rotCurr.x;
    d->rotPrev.y = d->rotCurr.y;
    d->rotPrev.z = d->rotCurr.z;

    // set animation to zero
    dInst->animIndex = 0;

    // halfway
    dInst->animFrame = FPS_DOUBLE(10);

	#if 0 // 10 =
		VehFrameInst_GetStartFrame(

			0, // midpoint

			VehFrameInst_GetNumAnimFrames(
				dInst, 	// driver instance
				0				// anim #0, steer
			)
		);
	#endif

    // Set Scale (x, y, z)
    dInst->scale[0] = 0xCCC;
    dInst->scale[1] = 0xCCC;
    dInst->scale[2] = 0xCCC;

    // turn off 7th and 20th bits of Actions Flag set (means ? (7) and racer is not in the air (20))
    d->actionsFlagSet &= ~(0x80040);

    if ((spawnFlag & 2) == 0)
        return;

    if (dInst->thread->modelIndex == DYNAMIC_PLAYER)
    {
        DECOMP_CAM_StartOfRace(&gGT->cameraDC[d->driverID]);

        dInst->thread->funcThTick = 
			((gGT->gameMode1 & (GAME_CUTSCENE | MAIN_MENU)) == 0) 
				? NULL 
				: DECOMP_VehBirth_NullThread;

        // set OnInit function
        d->funcPtrs[0] =
			((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				? DECOMP_VehStuckProc_RevEngine_Init
				: DECOMP_VehPhysProc_Driving_Init;
	}

    d->lapIndex = 0;
    d->numWumpas = 0;
    d->lapTime = 0;
    d->distanceToFinish_curr = 0;

    d->BattleHUD.numLives = gGT->battleSetup.lifeLimit;

    // turn off 21th and 26th flags of Actions Flag set
    //(means racer is not an AI and racer hasn't finished the race)
    d->actionsFlagSet &= ~(0x2100000);

    d->numHeldItems = 0;
    d->PickupLetterHUD.numCollected = 0;

	char weaponId = 0xf; // no item
    if ((gameMode2 & CHEAT_MASK) != 0) weaponId = 7;
	if ((gameMode2 & CHEAT_TURBO) != 0) weaponId = 0;
	if ((gameMode2 & CHEAT_BOMBS) != 0) weaponId = 1;
	if ((gameMode2 & CHEAT_WUMPA) != 0) d->numWumpas = 99;
	if ((gameMode2 & CHEAT_ENGINE) != 0) d->superEngineTimer = 0x2d00;
    d->heldItemID = weaponId;


    if (
        // If Permanent Invisibility Cheat is Enabled
        ((gameMode2 & CHEAT_INVISIBLE) != 0) &&

        // only make players invisible, not AIs
        (d->driverID < gGT->numPlyrCurrGame))
    {
        dInst->flags &= ~(DRAW_TRANSPARENT); // originally (DRAW_TRANSPARENT (0x10000) | GHOST_DRAW_TRANSPARENT (0x6000))

        dInst->flags |= GHOST_DRAW_TRANSPARENT;

        d->invisibleTimer = 0x2d00;
    }
}
