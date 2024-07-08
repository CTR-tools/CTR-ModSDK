#include <common.h>

void DECOMP_VehBirth_TeleportSelf(struct Driver *d, u_char spawnFlag, int spawnPosY)
{
    char i;
    char boolSpawnAtBossDoor;
    char numPlyr;
    char weaponId;
    char numInstances;
    short levId;
    short prevLev;
    short rotY;
    short rotZ;
    short *warppadRot=0;
    short *check;
    short posTop[3];
    short posBottom[3];
    short warppadPos[3];
    int angle;
    u_int gameMode2;

    struct PosRot
    {
        short pos[3];
        short rot[3];
    };

    struct InstDef *levInstDef;
    struct PosRot *posRot=0;
    struct GameTracker *gGT = sdata->gGT;
    struct Level* level1 = gGT->level1;

#ifndef REBUILD_PS1
    struct ScratchpadStruct* sps = 0x1f800108;
#else
    char scratchpad[0x1000];
    struct ScratchpadStruct* sps = &scratchpad[0];
#endif

    // cheat flags
    gameMode2 = gGT->gameMode2;

    numPlyr = gGT->numPlyrCurrGame;

    levId = gGT->levelID;
    prevLev = gGT->prevLEV;

    boolSpawnAtBossDoor = false;

    // by default, dont spawn by a hub door
    levInstDef = NULL;

    // Check LEV data for nullptr
    if (level1 == NULL || level1->ptr_mesh_info == NULL)
    {
        return;
    }

    // ground and wall quadblock flags
    sps->Union.QuadBlockColl.qbFlagsWanted = 0x3000;

    sps->Union.QuadBlockColl.qbFlagsIgnored = 0;
    // collision triangles, 2 (low-LOD) & 8 (hi-LOD)
    sps->Union.QuadBlockColl.searchFlags = (numPlyr > 3) ? 2 : 0;

    sps->ptr_mesh_info = level1->ptr_mesh_info;

    gGT->gameMode1 &= ~(POINT_LIMIT);

    // if you are mask grabbed
    if ((spawnFlag & 1) == 0)
    {
        // Ordinary player position
        posBottom[0] = (short)(d->posCurr.x >> 8);
        posBottom[1] = (short)(d->posCurr.y >> 8) + 0x80;
        posBottom[2] = (short)(d->posCurr.z >> 8);
    }

    // if you are spawning into the world for the first time,
    // could be startline, or adv hub spawn in several places
    else
    {
        // spawn in front of hub door, beach-to-gemstone
        if (
            // If you are at podium after winning a Key
            (gGT->podiumRewardID == 99) &&

            // If you have one boss key
            (gGT->currAdvProfile.numKeys == 1))
        {
            // lev number instDef
            numInstances = level1->numInstances;

            // lev instDefs
            levInstDef = level1->ptrInstDefs;

            // // if there are instDefs, loop through instDefs
            for (i = 0; i < numInstances; i++, levInstDef++)
            {
                // if door is found
                if (((
                        // InstDef+0xC+0xC (modelID) == 0x7a (STATIC_DOOR)
                        (levInstDef->modelID == STATIC_ADVHUB_DOORS) &&

                        // if name == "door"
                        ((int*)&levInstDef->name[0] == 0x726f6f64)) &&

                        //  name == "#5"
                        ((short*)&levInstDef->name[4] == 0x3523)) &&

                        // last 8 bytes of 16-byte name, all zeros
                        (((int*)&levInstDef->name[8] == 0 && ((int*)&levInstDef[12] == 0)))

                    // then leave loop
                    )
                    {
                        break;
                    }
            }

            // if the hub door was found, because not all instDefs were checked, then go to spawn
            if (i < numInstances)
                goto KART_SPAWN;

            // no InstDef found with "door" title,
            // so spawn outside boss door instead
            levInstDef = NULL;
        }

        // If you not at hub-door after beating Roo
        else
        {
            // if you are at podium for winning a trophy
            if (gGT->podiumRewardID == 0x62)
            {
                // By default, you have all 4 trophies on a hub,
                // but we are about to determine if that's true
                boolSpawnAtBossDoor = true;

                // Hub ID
                check = &data.advHubTrackIDs[(levId - 0x1a) * 4];
                // check 4 track trophies
                for (char i = 0; i < 4; i++)
                {
                    // if you haven't unlocked any trophy in this hub
                    if (CHECK_ADV_BIT(sdata->advProgress.rewards, check[i] + 6) == 0)
                    {
                        // record that not all 4 trophies are collected on this hub
                        boolSpawnAtBossDoor = false;
                        break;
                    }
                }

                // if you have all 4 trophies on a hub but you also already unlocked the boss key
                if (boolSpawnAtBossDoor && (CHECK_ADV_BIT(sdata->advProgress.rewards, levId + 0x44) != 0))
                {
                    // dont spawn outside boss garage
                    boolSpawnAtBossDoor = false;
                }
            }
        }
    KART_SPAWN:
        // if you just exited boss race
        if ((gameMode2 & 1) != 0)
        {
            // spawn outside boss door
            boolSpawnAtBossDoor = true;
        }

        // if not spawning at hub door (door not found)
        if (levInstDef == NULL)
        {
            // if you want to spawn outside boss door
            if (boolSpawnAtBossDoor)
            {
                // position outside boss door
                posRot = &level1->ptrSpawnType2_PosRot[1].posCoords[6];
                posBottom[0] = posRot->pos[0];
                posBottom[1] = posRot->pos[1];
                posBottom[2] = posRot->pos[2];
            }
            // If spawning anywhere else
            else
            {

                // If you're not in Adventure Arena,
                // Therefore, if spawning at startline of race track
                if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
                {
                LAB_80058158:

                    // racer crossed the start line backwards,
                    // so lap doesn't count when race starts
                    d->actionsFlagSet |= 0x1000000;

#ifndef REBUILD_PS1
                    d->distanceToFinish_checkpoint = level1->ptr_restart_points[0].distToFinish << 3;
#endif

                    // get coords where driver based on driver order (0-7)
                    posRot = &level1->DriverSpawn[sdata->kartSpawnOrderArray[d->driverID]];

                    // get position where each of the 8 drivers should spawn, from LEV
                    posBottom[0] = posRot->pos[0];
                    posBottom[1] = posRot->pos[1] + 0x80;
                    posBottom[2] = posRot->pos[2];
                }

                // if you are in adventure arena
                else
                {
                    // if no podium reward
                    if (gGT->podiumRewardID == 0)
                    {

                        // if you just came from any of these...
                        if (
							(prevLev == MAIN_MENU_LEVEL) ||
							(prevLev == ADVENTURE_CHARACTER_SELECT) ||
                            (prevLev == -1) ||
							(prevLev == SCRAPBOOK) ||
							((unsigned int)(prevLev - 0x2c) < 0x14)
							)
                            goto LAB_80058158;

                        // get position where driver should spawn on map,
                        // outside warppad they previously entered

                        warppadRot = DECOMP_AH_WarpPad_GetSpawnPosRot(&warppadPos);
                        posBottom[0] = warppadPos[0];
                        posBottom[1] = warppadPos[1] + 0x80;
                        posBottom[2] = warppadPos[2];
                    }

                    // if you have a podium reward
                    else
                    {
                        // spawn on the podium in the adv hub
                        posBottom[0] = posRot->pos[0];
                        posBottom[1] = posRot->pos[1] + 0x80;
                        posBottom[2] = posRot->pos[2];
                    }
                }
            }
        }

        // if spawning at hub door
        else
        {
            gameMode2 |= VEH_FREEZE_DOOR;

            // do trigonometry to take hub door
            angle = levInstDef->rot[1];

            // posX =
            // instDef posX + (where door starts)
            // doorLengthX + (to get to midpoint between two doors)
            // perpendicularX (to spawn away from door)
            posBottom[0] = levInstDef->pos[0] + (short)(DECOMP_MATH_Cos(angle) >> 1) + (short)(DECOMP_MATH_Cos(angle + 0x400) >> 3);

            // posY = instDef posY + random height offset
            posBottom[1] = levInstDef->pos[1] + 0x17a;

            // posZ =
            // instDef posZ + (where door starts)
            // doorLengthZ + (to get to midpoint between two doors)
            // perpendicularZ (to spawn away from door)
            posBottom[2] = levInstDef->pos[2] + (short)(DECOMP_MATH_Sin(angle) >> 1) + (short)(DECOMP_MATH_Sin(angle + 0x400) >> 3);
		}
    }

    posTop[0] = posBottom[0];
    posTop[1] = posBottom[1] - 0x100;
    posTop[2] = posBottom[2];

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

	d->instSelf->matrix.t[0] = posRot->pos[0];
	d->instSelf->matrix.t[1] = (posRot->pos[1]-0x40);
	d->instSelf->matrix.t[2] = posRot->pos[2];

    ConvertRotToMatrix(&d->instSelf->matrix.m, &d->rotCurr.x);

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

    for (i = 0; i < 1; i++) // maybe this is done two times, because it was a do-while?
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

    // if you are spawning into the world for the first time,
    // could be startline, or adv hub spawn in several places
    if ((spawnFlag & 1) != 0)
    {
        if (levInstDef == NULL)
        {
#ifndef REBUILD_PS1
            // get desired rotation of driver when leaving portal, or spawning at startline
			posRot = &level1->ptrSpawnType2_PosRot[1].posCoords[6];
			angle = posRot->rot[1] & 0xfff;
#else
            angle = 0;
#endif

			// if spawning outside boss door
            if (boolSpawnAtBossDoor)
            {
                angle += 0x400U;

                // if just finished a boss race
                if ((gameMode2 & 1) != 0)
                {

                    if (levId == CITADEL_CITY)
                    {
                        // rotate 90 degrees to the right,
                        // so you dont have a wall in your face
                        angle += 0x400;
                    }
                    // if not...
                    else
                    {
                        if ((levId == GEM_STONE_VALLEY) &&

                            // just finished pinstripe boss,
                            // spawned by oxide's door
                            (gGT->prevLEV == HOT_AIR_SKYWAY))
                        {
                            // use default rotation, face oxide's door
                            d->rotCurr.y = angle;
                            goto DEFAULT_ROTATION;
                        }

                        // If driver spawned to any other boss,
                        // for any other reason

                        // rotate 180 degrees, facing away from boss door
                        angle += 0x800;
                    }

                    // bitwise AND, do not go over 0x1000 (360 degrees)
                    d->rotCurr.y = angle & 0xfff;
                }
            DEFAULT_ROTATION:
                gameMode2 &= ~(1 | 2);
            }
            // if not outside boss door
            else
            {
                if ((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
                {
                STARTLINE_ROT:

                    // position index on starting line
                    posRot = &level1->DriverSpawn[sdata->kartSpawnOrderArray[d->driverID]];

                    // rotation data of all 8 drivers on starting line
                    d->rotCurr.x = posRot->rot[0];
                    rotY = posRot->rot[1];
                    rotZ = posRot->rot[2];
                }
                // if on adv hub
                else
                {
                    // podium reward
                    if (gGT->podiumRewardID != 0)
                    {
                        // set rotation, expecting driver to spawn on podium
                        d->rotCurr.y = angle;
                        goto LAB_80058568;
                    }

                    if (
							// If you just came from the main menu
							(gGT->prevLEV == MAIN_MENU_LEVEL) ||

							// If you just came from "nothing"
							(gGT->prevLEV == -1) ||

							// if WarpPad_ReturnToMap failed to find a matching portal
							(warppadRot == NULL)
                        )

                        // skip
                        goto STARTLINE_ROT;

                    // rotation data from spawning near hub warppad,
                    // after leaving a race or event
                    d->rotCurr.x = warppadRot[0];
                    rotY = warppadRot[1];
                    rotZ = warppadRot[2];
                }
                d->rotCurr.y = rotY + 0x400U & 0xfff;
                d->rotCurr.z = rotZ;
            }
        }
        else
        {
            d->rotCurr.y = levInstDef->rot[1] + 0x800U & 0xfff;
            gameMode2 &= ~(1 | 2);
        }
    }
LAB_80058568:

    d->speed = 0;
    d->speedApprox = 0;
    d->jumpHeightCurr = 0;
    d->jumpHeightPrev = 0;
    d->unk_offset3B2 = 0;
    d->angle = d->rotCurr.y;
    d->rotPrev.x = d->rotCurr.x;
    d->rotPrev.y = d->rotCurr.y;
    d->rotPrev.z = d->rotCurr.z;

    if (
        (levInstDef != NULL) &&

        // if spawning into world (not mask grab)
        ((spawnFlag & 1) != 0))
    {
        // spawn with speed (what? when does that ever happen?)
        d->speed = 0xa00;
    }

    // set animation to zero
    d->instSelf->animIndex = 0;

    // halfway
    d->instSelf->animFrame = FPS_DOUBLE(10);

	#if 0 // 10 =
		VehFrameInst_GetStartFrame(

			0, // midpoint

			VehFrameInst_GetNumAnimFrames(
				d->instSelf, 	// driver instance
				0				// anim #0, steer
			)
		);
	#endif

    // Set Scale (x, y, z)
    d->instSelf->scale[0] = 0xCCC;
    d->instSelf->scale[1] = 0xCCC;
    d->instSelf->scale[2] = 0xCCC;

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

    // turn off 7th and 20th bits of Actions Flag set (means ? (7) and racer is not in the air (20))
    d->actionsFlagSet &= ~(0x80040);

    if ((spawnFlag & 2) == 0)
        return;

    if (d->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
    {
        DECOMP_CAM_StartOfRace(&gGT->cameraDC[d->driverID]);

        void Veh_NullThread();
        d->instSelf->thread->funcThTick = ((gGT->gameMode1 & (GAME_CUTSCENE | MAIN_MENU)) == 0) ? NULL : Veh_NullThread;

        // set OnInit function
        d->funcPtrs[0] =
			((gGT->gameMode1 & ADVENTURE_ARENA) == 0)
				? DECOMP_VehStuckProc_RevEngine_Init
				: DECOMP_VehPhysProc_Driving_Init;
	}

    d->lapIndex = 0;

    d->numWumpas = 0;

    d->lapTime = 0;

    // no lap progress
    d->distanceToFinish_curr = 0;

    // turn off 21th and 26th flags of Actions Flag set
    //(means racer is not an AI and racer hasn't finished the race)
    d->actionsFlagSet &= ~(0x2100000);

    // If unlimited wumpa cheat is enabledy
    d->numWumpas = ((gameMode2 & CHEAT_WUMPA) == 0) ? 0 : 99;

    // set Held item to none
    d->heldItemID = 0xf;

    d->numHeldItems = 0;

    // collected zero C-T-R letters
    d->PickupLetterHUD.numCollected = 0;

    // set weaponID to mask
    weaponId = 7;

    // if unlimited masks is disabled
    if ((gameMode2 & CHEAT_MASK) == 0)
    {
        // if unlimited turbos is disabled
        if ((gameMode2 & CHEAT_TURBO) == 0)
        {
            // if infinite bombs is disabled
            if ((gameMode2 & CHEAT_BOMBS) == 0)
                goto SKIP_WEAPON;

            // set weaponID to bomb
                weaponId = 1;
        }
        // set weaponID to turbo
        weaponId = 0;
    }

    // set weaponID
    d->heldItemID = weaponId;

SKIP_WEAPON:

    // set driver's life limit to the global life limit
    d->BattleHUD.numLives = gGT->battleSetup.lifeLimit;

    if (
        // If Permanent Invisibility Cheat is Enabled
        ((gameMode2 & CHEAT_INVISIBLE) != 0) &&

        // Player / AI structure + 0x4a shows driver index (0-7)

        // driver ID must be less than numPlyrCurrGame,
        // which makes the cheat apply to players and not AIs
        (d->driverID < numPlyr))
    {
        d->instSelf->flags &= ~(DRAW_TRANSPARENT); // originally (DRAW_TRANSPARENT (0x10000) | GHOST_DRAW_TRANSPARENT (0x6000))

        d->instSelf->flags |= GHOST_DRAW_TRANSPARENT;

        d->invisibleTimer = 0x2d00;
    }

    // If Super Engine Cheat
    if ((gameMode2 & CHEAT_ENGINE) != 0)
    {
        d->superEngineTimer = 0x2d00;
    }
}
