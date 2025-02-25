#include <common.h>

//NOT DONE YET

void DECOMP_BOTS_ThTick_Drive(struct Thread* botThread)
{
	struct ScratchpadStruct* sps = (struct ScratchpadStruct*)0x1f800108;
	struct Driver* botDriver = (struct Driver*)botThread->object; //iVar17
	struct Instance* botInstance = (struct Instance*)botThread->inst; //iVar22

	//local_34 = sdata->gGT->elapsedTimeMS;

	botDriver->turbo_MeterRoomLeft = 0;
	botDriver->forwardDir = 0;

	botInstance->flags &= 0xffff9fff;

	if (botDriver->weaponCooldown != 0)
	{
		botDriver->weaponCooldown--;
	}

	if (botDriver->ChangeState_param2 == 0)
	{
		if ((botDriver->actionsFlagSet & 0x2000000) == 0 && botDriver->weaponCooldown != 0)
		{
			botDriver->weaponCooldown--;
		}
	}
	else
	{
		DECOMP_BOTS_ChangeState(botDriver, botDriver->ChangeState_param2, (struct Driver*)botDriver->ChangeState_param3, botDriver->ChangeState_param4);
	}

	int iVar4 = sdata->gGT->elapsedTimeMS;

	botDriver->reserves += iVar4;
	if (botDriver->reserves * 0x1000 < 0)
		botDriver->reserves = 0;

	botDriver->turbo_outsideTimer += iVar4;
	if (botDriver->turbo_outsideTimer * 0x1000 < 0)
		botDriver->turbo_outsideTimer = 0;

	botDriver->squishTimer += iVar4;
	if (botDriver->squishTimer * 0x1000 < 0)
		botDriver->squishTimer = 0;

	botDriver->burnTimer += iVar4;
	if (botDriver->burnTimer * 0x1000 < 0)
		botDriver->burnTimer = 0;

	botDriver->clockReceive += iVar4;
	if (botDriver->clockReceive * 0x1000 < 0)
		botDriver->clockReceive = 0;

	(*(short*)&botDriver->unk5bc[0x2]) = 0;
	botDriver->kartState = KS_NORMAL;

	botDriver->actionsFlagSetPrevFrame = botDriver->actionsFlagSet;
	botDriver->actionsFlagSet &= 0x7ffffbfd;

	int speedApprox = botDriver->speedApprox; //iVar4

	if (speedApprox < 0)
		speedApprox = -speedApprox;

	if ((botDriver->actionsFlagSet & 1) == 0) {
		speedApprorx += 0xf00;
	}
	else {
		speedApprox = ((speedApprox << 1) >> 1);
	}

	short idk = (((speedApprox * 0x89) + (botDriver->unkSpeedValue2 * 0x177)) * 8 >> 0xC);
	botDriver->unkSpeedValue2 = idk;

	if ((botDriver->actionsFlagSetPrevFrame & 8) == 0)
	{
		int baseSpeed = botDriver->baseSpeed;
		if (baseSpeed < 0)
			baseSpeed = -baseSpeed;

		if (baseSpeed < 0x201) {
			baseSpeed = botDriver->speedApprox;
			if (baseSpeed < 0)
				baseSpeed = -baseSpeed;

			if (baseSpeed < 0x201) goto give_this_label_a_better_name;
		}

		botDriver->unkSpeedValue1 -= idk;
	}
give_this_label_a_better_name:

	if (botDriver->unkSpeedValue1 < 1 && (botDriver->tireColor & 1) == 0)
	{
		botDriver->unkSpeedValue1 = 0x1e00;
		botDriver->tireColor = 0x2e606061;
	}
	else
	{
		botDriver->tireColor = 0x2e808080;
	}

	struct NavFrame* navFrameOfConcern = (struct NavFrame*)&botDriver->estimatePos[0]; //psVar19
	struct NavFrame* nextNavFrameOfConcern; //psVar21

	if ((botDriver->botFlags & 1) == 0)
	{
		navFrameOfConcern = botDriver->botNavFrame;
		nextNavFrameOfConcern = currNavFrame + 1;
		if (sdata->NavPath_ptrHeader[botDriver->botPath]->last <= nextNavFrameOfConcern)
		{
			nextNavFrameOfConcern = NavPath_ptrNavFrameArray[0];
		}
	}
	else
	{
		nextNavFrameOfConcern = botDriver->botNavFrame;
	}

	struct Need_New_Name cpwb_param_2; //.pos[3] unused?
	cpwb_param_2.pos[0] = (short)(botDriver->posCurr.x >> 8);
	cpwb_param_2.pos[1] = (short)(botDriver->posCurr.y >> 8);
	cpwb_param_2.pos[2] = (short)(botDriver->posCurr.z >> 8);
	cpwb_param_2.th = NULL;
	cpwb_param_2.radius = 0x7fffffff;

	struct Thread* uVar12;

	if ((botThread->flags & 0x1800) == 0)
	{
		if (botThread->modelIndex == 0x18)
		{
			DECOMP_PROC_CollidePointWithBucket(botThread->siblingThread, (short*)cpwb_param_2);

			uVar12 = sdata->gGT->threadBuckets[ROBOT].thread;
		}
		else
		{
			if (botThread->modelIndex != 0x3f) goto give_this_label_a_better_name2;

			uVar12 = botThread->siblingThread;
		}

		DECOMP_PROC_CollidePointWithBucket(uVar12, (short*)cpwb_param_2);
	}
give_this_label_a_better_name2:

	if (cpwb_param_2.th != NULL)
	{
		int iVar4 = botThread->driver_HitRadius + cpwb_param_2.th->driver_HitRadius;
		if (cpwb_param_2.radius < iVar4 * iVar4)
		{
			int xyz[3];
			xyz[0] = botDriver->xSpeed + (*(int*)&botDriver->unk5bc[0x1c]);
			xyz[1] = botDriver->ySpeed + (*(int*)&botDriver->unk5bc[0x20]);
			xyz[2] = botDriver->zSpeed + (*(int*)&botDriver->unk5bc[0x24]);
			//similar to Need_New_Name usage, idk if this will overrun the stack from assignment within this call, needs investigation.
			VehPhysCrash_AnyTwoCars(botThread, (u_short*)cpwb_param_2, &xyz[0]);
		}
	}

	//puVar5 = sdata->gGT

	if (botDriver->ai_progress_cooldown == 0)
	{
		int trafficLightsTimer = sdata->gGT->trafficLightsTimer;

		if (data.characterIDs[botDriver->driverID] == 0xf) //check is oxide
		{
			//Pretend there is less time (oxide is a cheater)
			trafficLightsTimer -= 0x1e0;
		}

		if (0 < trafficLightsTimer) goto give_this_label_a_better_name3; //if race not started, then skip

		if (sdata->gGT->boolDemoMode != 0 &&
			(botDriver->botFlags & 0x100) == 0 &&
			botThread->modelIndex == 0x18)
		{
			botDriver->botFlags |= 0x100;
			DECOMP_CAM_EndOfRace(sdata->gGT->cameraDC[botDriver->driverID], botDriver);
		}

		if ((botDriver->botFlags & 0x200) == 0)
		{ //first frame of race
			botDriver->botFlags |= 0x200;

			if (data.characterIDs[botDriver->driverID] == 0xf)
			{ //if oxide, then talk
				Voiceline_RequestPlay(0, 0xf, 0x10);
			}

			if (
					( //if in front row & 25% chance
						(sdata->kartSpawnOrderArray[botDriver->driverID] < 3) &&
						RngDeadCoed((u_int*)&gGT->deadcoed_struct) < 0x40
					) ||
					data.characterIDs[botDriver->driverID] == 0xf //or oxide
				)
			{ //start the race with a boost
				DECOMP_VehFire_Increment(botDriver, 0x2d0, 1, 0x180);

				DECOMP_VehFire_Audio(botDriver, 0x180);
			}
		}

		//between these start and end tags, there's confusing variable lifetime that needs to be looked at closer.
		/////// START
		if ((botDriver->botFlags & 0xc0) == 0x40)
		{
			struct NavFrame* uVar11 = nextNavFrameOfConcern + 1; //also uVar20 = (uint)uVar11

			//memory bounds check for the navFrame???
			int idk = ((((int)uVar11) << 0x10) >> 0x1a); //6 bits
			if (((int)(uVar20 << 0x10) >> 0x10 < 0xc00) &&
				idk == *(((char*)&botDriver->unk626) + 1)) //compare to Driver* + 0x627
			{
				botDriver->botFlags |= 0x80;

				DECOMP_LIST_RemoveMember(sdata->unk_NavRelated[botDriver->botPath], (struct Item*)&botDriver->unk598);

				botDriver->botPath = (short)(int)uVar11 >> 10;

				DECOMP_LIST_AddFront(sdata->unk_NavRelated[idk], (struct Item*)&botDriver->unk598);

				struct NavFrame* firstNavFrameOnPath = sdata->NavPath_ptrNavFrameArray[idk];
				LAB_800144a0:
				//botDriver->estimatePos

				//idk how to better write this
				botDriver->botNavFrame = (struct NavFrame*)(((unsigned int)firstNavFrameOnPath) + ((((unsigned int)uVar11) & 0x3ff) * 0x14));

				BOTS_SetRotation(botDriver, 0);

				//psVar21 = botDriver->botNavFrame
			}
		}
		else /////// END
		{
			//todo
		}

		//todo
	}
	else
	{
	give_this_label_a_better_name3:
		botInstance->scale[0] = 0xccc;
		botInstance->scale[1] = 0xccc;
		botInstance->scale[2] = 0xccc;

		(*(int*)&botDriver->unk5bc[0x18]) = 0; //AI speed

		if (botDriver->ai_progress_cooldown != 0)
		{
			botDriver->ai_progress_cooldown--;
		}

		iVar4_lifetime_2 = botDriver->unk5a8;
	}

	// END OF TOP-DOWN
	// ========================================================================

	// This middle chunk of the function hasn't been looked at yet.

	// ========================================================================
	// BEGINNING OF BOTTOM-UP

	VehPhysForce_TranslateMatrix(botThread, botDriver);

	VehPhysForce_RotAxisAngle(&botDriver->matrixMovingDir, &botDriver->AxisAngle2_normalVec[0], botDriver->angle);

	VehFrameProc_Driving(botThread, botDriver);

	if ((botDriver->botFlags & 2) != 0 && botDriver->unk5ba == 2)
	{
		short rot[3];
		rot[0] = (*(short*)&botDriver->unk5bc[0]) << 8;
		rot[2] = 0;
		rot[1] = (*(short*)&botDriver->unk5bc[0] * 0xe0);

		ConvertRotToMatrix(&sdata->rotXZ, &rot[0]);

		MATH_MatrixMul(&sdata->rotXYZ, &botInstance->matrix, &sdata->rotXZ);

		MATH_MatrixMul(&botInstance->matrix, &sdata->rotXYZ, &sdata->arcadeDiff);

		//MATRIX is only 30 bytes, but is 32 because there's 2 bytes of padding (at the end?) this additional data is stored there?
		(*(int*)(((char*)botInstance) + 0x48)) += 0x20;
	}

	if ((botDriver->botFlags & 4) == 0)
	{
		VehEmitter_DriverMain(botThread, botDriver);
	}

	if (botInstance->thread->modelIndex == 0x18) //why doesn't the original code just use botThread???
	{
		EngineSound_Player(botDriver);
	}

	short camRot = botDriver->angle - (botDriver->ai_rotY_608 & 0xfff);

	botDriver->rotCurr.w = -camRot;

	if (0x7ff < camRot) {
		camRot |= 0xf000;
	}

	botDriver->ai_rotY_608 += (camRot >> 3) & 0xfff;

	if (botThread->modelIndex == 0x18)
	{
		short posTop[3];
		short posBot[3];

		posTop[0] = (short)((botDriver->ai_posBackup[0] + (*(int*)&botDriver->unk5bc[0x28])) >> 8);
		posBot[1] = (short)((botDriver->ai_posBackup[1] + (*(int*)&botDriver->unk5bc[0x28 + 0x4])) >> 8);
		posTop[1] = posBot[1] - 0x100;
		posBot[1] += 0x40;
		posTop[2] = (short)((botDriver->ai_posBackup[2] + (*(int*)&botDriver->unk5bc[0x28 + 0x8])) >> 8);
		posBot[0] = posTop[0];
		posBot[2] = posTop[2];

		sps->ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
		sps->Union.QuadBlockColl.qbFlagsWanted = 0x1000;
		sps->Union.QuadBlockColl.qbFlagsIgnored = 0;
		sps->Union.QuadBlockColl.searchFlags = 2;

		COLL_SearchTree_FindQuadblock_Touching((u_int*)&posTop[0], (u_int*)&posBot[0], sps, 0);

		if (sps->boolDidTouchQuadblock)
		{
			botDriver->underDriver = (struct QuadBlock*)&sps->unk4C[0x34];
		}
	}
}