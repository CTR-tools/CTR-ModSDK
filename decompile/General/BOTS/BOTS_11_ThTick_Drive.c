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

	int elapsedMilliseconds = sdata->gGT->elapsedTimeMS; //local_34
	int iVar4 = -elapsedMilliseconds;

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

		unsigned int botFlags = botDriver->botFlags;
		short botEstimatePos[3];

		/////// START
		if ((botFlags & 0xc0) == 0x40)
		{
			short uVar11 = nextNavFrameOfConcern->pathIndexOfffff; //also uVar20 = (uint)uVar11

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
				botEstimatePos = botDriver->botData.estimatePos;

				//idk how to better write this
				botDriver->botNavFrame = (struct NavFrame*)(((unsigned int)firstNavFrameOnPath) + ((((unsigned int)uVar11) & 0x3ff) * 0x14));

				BOTS_SetRotation(botDriver, 0);

				nextNavFrameOfConcern = botDriver->botNavFrame;
			}
		}
		else /////// END
		{
			//todo
			if (450 < sdata->unk_counter_upTo450)
			{
				struct Driver* otherDriver = NULL; //iVar4
				if ((botFlags & 1) == 0)
				{
					int iVar3 = 1000;
					short sVar7 = 1000;

					//idk = probably a pointer to `struct Driver*`->unk598 of some `struct Driver*`
					//sizeof(typeof(`struct Driver*`->unk598)) == 0x94 probably.
					struct Item* idk = (struct Item*)DECOMP_List_GetFirstItem(&sdata->unk_NavRelated[botDriver->botPath]);
					while (idk != NULL)
					{
						//todo
						if (((char*)idk) - 0x598 != (char*)botDriver)
						{
							int iVar13 = (*(int*)(((char*)idk) + 0xc) - *(int*)botDriver->botNavFrame->pos) * -0x33333333 >> 2;
							if (iVar13 << 0x10 < 0)
							{
								iVar13 += sdata->NavPath_ptrHeader[botDriver->botPath]->numPoints;
							}
							if (iVar13 << 0x10 < iVar3 << 0x10)
							{
								iVar3 = iVar13;
								otherDriver = (struct Driver*)(((char*)idk) - 0x598);
							}
						}
						sVar7 = (short)iVar3;

						idk = LIST_GetNextItem(idk);
					}

					if (iVar4 != NULL && sVar7 < 3)
					{
						int diff = botDriver->distanceToFinish_curr - otherDriver->distanceToFinish_curr;

						if (diff < 0)
						{
							diff += sdata->gGT->level1->ptr_restart_points->distToFinish * 8;
						}
						if (diff < 0x200)
						{
							short uVar11 = nextNavFrameOfConcern->pathIndexOfffff; //also uVar20 = (uint)uVar11

							if (uVar11 < 0xc00)
							{
								DECOMP_List_RemoveMember(sdata->unk_NavRelated[botDriver->botPath], botDriver->unk598);

								int iVar4 = uVar11 >> 0xa;
								botDriver->botPath = uVar11 >> 10;

								DECOMP_List_AddFront(sdata->unk_NavRelated[iVar4], botDriver->unk598);

								iVar4 = sdata->NavPath_ptrNavFrameArray[iVar4];

								goto //TODO
							}
						}
					}
				}
			}
		}

		//puVar5 = gGT but different?

		if ((botDriver->actionsFlagSet & 1) == 0)
		{
			int ZY = (botDriver->unk5bc[0x18] * botDriver->unk5bc[0x18]) + (botDriver->unk5bc[0x14] * botDriver->unk5bc[0x14]); //sqrZY

			if (0x2b110000 < sqrZY) //sqrZY
			{
				ZY = SquareRoot0_stub(sqrZY);

				int zVel = botDriver->unk5bc[0x18] * 0x6900; //iVar3

				if (ZY == 0)
				{
					//trap(0x1c00);
				}
				if ((ZY == -1) && (zVel == -0x80000000))
				{
					//trap(0x1800);
				}
				int yVel = botDriver->unk5bc[0x14] * 0x6900; //iVar15
				if (ZY == 0)
				{
					//trap(0x1c00);
				}
				if ((ZY == -1) && (yVel == -0x80000000))
				{
					//trap(0x1800);
				}
				botDriver->unk5bc[0x18] = (zVel /  ZY);
				botDriver->unk5bc[0x14] = (yVel /  ZY);
			}
		}
		else
		{
			botDriver->actionsFlagSet &= 0xfff7ffff;

			//iVar4 = sdata->bestHumanRank

			struct Driver* bestDriverRank = sdata->bestHumanRank;

			if ((sdata->gGT->gameMode1 & 0x4000000) != 0)
			{
				bestDriverRank = sdata->bestRobotRank;
			}

			int speed;
			int velocityAccountingForTerrain;

			if (bestDriverRank == NULL || (bestDriverRank == botDriver))
			{
				speed = sdata->gGT->constVal_9000;
			}
			else
			{
				int driverRank = botDriver->driverRank;
				bool isInAdvArcadeOrVSCup = false;
				if ((sdata->gGT->gameMode1 & 0x10000000) != 0 || (sdata->gGT->gameMode2 & 0x10) != 0)
				{
					isInAdvArcadeOrVSCup = true;
				}

				if (sdata->gGT->drivers[0]->driverRank < botDriver->driverRank)
				{
					driverRank--;
				}

				if (1 < sdata->gGT->numPlyrCurrGame && sdata->gGT->drivers[1]->driverRank <= driverRank)
				{
					driverRank--;
				}

				if ((sdata->gGT->gameMode1 & 0x10000000) != 0 || (sdata->gGT->gameMode2 & 0x10) != 0)
				{
					driverRank = sdata->accelerateOrder[botDriver->driverID];
					if (sdata->accelerateOrder[0] < 2)
					{
						driverRank--;
					}
					if (sdata->accelerateOrder[1] < 2)
					{
						driverRank--;
					}
				}

				short sVar7;

				if (bestDriverRank->lapIndex == 0)
				{
					sVar7 = sdata->arcade_difficultyParams[0xB];
				}
				else
				{
					if (bestDriverRank->lapIndex == sdata->gGT->numLaps - 1)
					{
						sVar7 = sdata->arcade_difficultyParams[0xD];
					}
					else
					{
						sVar7 = sdata->arcade_difficultyParams[0xC];
					}
				}

				int distToFinish = sdata->gGT->level1->ptr_restart_points->distToFinish * 8;

				int lapIndex = bestDriverRank->lapIndex;

				if ((bestDriverRank->actionsFlagSet & 0x1000000) != 0)
				{
					lapIndex--;
				}

				int botLapIndex = botDriver->lapIndex;

				if ((botDriver->actionsFlagSet & 0x1000000) != 0)
				{
					botLapIndex--;
				}

				//not super meaningful, probably just a difficulty statistic
				int iVar15 = ((distToFinish - bestDriverRank->distanceToFinish_curr) + (lapIndex * distToFinish)) - ((distToFinish - botDriver->distanceToFinish_curr) + (botLapIndex * distToFinish)) - sdata->arcade_difficultyParams[driverRank + sVar7];

				//// CONTINUE FROM HERE

				int iVar13;
				if (isInAdvArcadeOrVSCup && ((driverRank & 0xffff) == 0))
				{
					if (iVar15 < 1)
					{
					LAB_800147e8:
						iVar13 = sdata->arcade_difficultyParams[0x9];
					}
					else
					{
						if (botDriver->lapIndex < sdata->gGT->numLaps - 1)
						{
							iVar13 = sdata->cup_difficultyParams[0x8];
						}
						else
						{
						code_r0x800147c4:
							iVar13 = sdata->cup_difficultyParams[0x8] + sdata->cup_difficultyParams[0xA];
						}
					}
				}
				else
				{
					if (iVar15 < 1) goto LAB_800147e8;
					if (sdata->gGT->numLaps - 1 <= botDriver->lapIndex) goto code_r0x800147c4;
					iVar13 = sdata->arcade_difficultyParams[0x8];
				}
				int botVelocity = iVar15; //botVelocity == iVar3
				if (iVar15 < 0)
					botVelocity = -iVar15;
				int iVar9 = iVar13;
				if (iVar13 < 0)
					iVar9 = -iVar13;

				botVelocity = iVar9 * (((botVelocity + 0x80) * 0x1000) / 0xa00) >> 0xc;
				bool local_38 = 0 < iVar15;
				botVelocity = botVelocity + ((botVelocity << 3) / 100) * (7 - driverRank);

				if (iVar9 < botVelocity)
					botVelocity = iVar9;
				if (ivar13 < 0)
					botVelocity = -iVar9;

				int bestDriverWumpaCount = bestDriverRank->numWumpas; //iVar15, assume max of 9?
				if (9 < bestDriverWumpaCount)
					bestDriverWumpaCount = 9;

				int turboMult = bestDriverRank->turboConst; //iVar13, max of 5
				if (5 < turboMult)
					turboMult = 5;

				int netSpeedStat = (((bestDriverRank->const_AccelSpeed_ClassStat - bestDriverRank->const_Speed_ClassStat) * 0x1000) / 5) - 1;

				int speedAdditional = ((bestDriverRank->const_Speed_ClassStat << 3) / 10) + ((bestDriverWumpaCount * iVar9) / 10 + iVar13 * iVar9 >> 0xc);

				if (0x6900 < speedAdditional)
					speedAdditional = 0x6900;

				botVelocity += speedAdditional;

				if (botVelocity < 0x5dc1)
				{
					if (botVelocity < 0x1c20)
						botVelocity = 0x1c20;
				}
				else
					botVelocity = 24000;

				if (botDriver->reserves == 0)
					botDriver->botData.botFlags &= 0xffffffef;
				else
				{
					if ((botDriver->botData.botFlags & 0x10) == 0)
						botVelocity += botDriver->fireSpeedCap;
					else
						botVelocity = botDriver->fireSpeedCap + 10000;
				}

				if (botDriver->clockReceive != 0 || botDriver->squishTimer != 0)
					botVelocity = botVelocity * 0xc00 >> 0xc;

				if ((botDriver->botData.botFlags & 2) == 0)
				{
					if (botDriver->instTntRecv != NULL || botDriver->thCloud != NULL)
					{
						speedAdditional = (botDriver->const_DamagedSpeed << 0x10) >> 0x11;

						//goto //TODO
						botVelocity -= speedAdditional; //just do it here, gotos are stupid
					}
				}
				else
				{
					*(short*)&botDriver->botData.unk5bc[0x8] = 0;

					if (data.characterIDs[botDriver->driverID] == 0xf)
					{
						speedAdditional = (botDriver->const_DamagedSpeed << 0x10) >> 0x12;

						botVelocity -= speedAdditional;
					}
					else
					{
						botVelocity -= botDriver->const_DamagedSpeed;
					}
				}
				if (botVelocity < 0)
				{
					botVelocity = 0;
				}

				struct Terrain* botTerrain = botDriver->terrainMeta1;

				speedAdditional = (*(int*)&botDriver->botData.unk5bc[0x18]) - (botDriver->const_PedalFriction_Forward * botTerrain->accel_impact >> 8);

				(*(int*)&botDriver->botData.unk5bc[0x18]) = speedAdditional;

				if (speedAdditional < 0)
					(*(int*)&botDriver->botData.unk5bc[0x18]) = 0;
				if (0x6900 < botVelocity)
					botVelocity = 0x6900;

				//// CONTINUE FROM HERE 2

				int velocityAccountingForTerrain = botVelocity * botTerrain->unk_0x34[2] >> 8;

				if ((botTerrain->unk_0x34[1] & 0x80) == 0)
				{
				LAB_80014b34:
					if ((*(int*)&botDriver->botData.unk5bc[0x18]) < velocityAccountingForTerrain)
					{
					LAB_80014b48:
						short accel;
						if (botDriver->reserves < 1)
						{
							accel = botDriver->const_Accel_ClassStat;
						}
						else
						{
							accel = botDriver->const_Accel_Reserves;
						}
						botVelocity = accel * botTerrain->unk_0x34[3] >> 8;

						if (botDriver->botData.botAccel != 0)
						{
							botDriver->botData.botAccel--;
							botVelocity = (botVelocity * (0x100 - sdata->AI_AccelFrameSteps * sdata->accelerateOrder[botDriver->driverID])) >> 8;
						}

						(*(int*)&botDriver->botData.unk5bc[0x18]) += botVelocity;
					}
				}
				else
				{
					botVelocity = *(int*)&botDriver->botData.unk5bc[0x18] >> 1;

					if (*(int*)&botDriver->botData.unk5bc[0x18] < velocityAccountingForTerrain) goto LAB_80014b48;

					*(int*)&botDriver->botData.unk5bc[0x18] = botVelocity;
					if (botVelocity < velocityAccountingForTerrain)
					{
						*(int*)&botDriver->botData.unk5bc[0x18] = velocityAccountingForTerrain;
						goto LAB_80014b34;
					}
				}

				int levelID = sdata->gGT->levelID; // iVar3

				if ((levelID == 7 || levelID == 5) || levelID == 0xc) //hot air skyway, papu's pyramid, polar pass.
				{
					int botPathIndex = botDriver->botData.botPath; //iVar3

					if (levelID == 0xc)
					{
						botPathIndex += 3;
					}
					else
					{
						if (levelID == 5)
						{
							botPathIndex += 6;
						}
						else if (levelID == 0x10) //what the heck isn't this dead code?
						{
							botPathIndex += 9;
						}
					}
				}

				//why are we casting an address and doing arithmatic on it? as far as I can tell, this is what the original code was doing.
				int wtf = (int)((int)botEstimatePos - *(int*)&sdata->NavPath_ptrNavFrameArray[botDriver->botData.botPath]->pos[0]) * 0x33334000 >> 0x10;

				if ((data.botsThrottle[botPathIndex] <= wtf && wtf < data.botsThrottle[botPathIndex] + 0xb) && 9000 < *(int*)botDriver->botData.unk5bc[0x18])
				{
					*(short*)&botDriver->botData.unk5bc[0x8] = 0;

					*(int*)&botDriver->botData.unk5bc[0x18] -= 100 + botDriver->const_Accel_ClassStat;
				}
			}

			if (0x80 < *(char*)(((int)botEstimatePos) + 9)) //after the estimate pos is estimate rot, which is probably what is being checked here. (check euler pitch)
			{
				velocityAccountingForTerrain += botDriver->unk47E;

				if (*(int*)&botDriver->botData.unk5bc[0x18] < velocityAccountingForTerrain)
				{
					int sinOfAngle = MATH_Sin(*(char*)(((int)botEstimatePos) + 9) << 4);

					*(int*)&botDriver->botData.unk5bc[0x18] -= botDriver->const_Gravity * sinOfAngle >> 0xc; //force on a slope due to gravity
				}

				botDriver->fireSpeed = velocityAccountingForTerrain;
			}
		}

		if (0x6400 < *(int*)&botDriver->botData.unk5bc[0x18])
		{
			*(int*)&botDriver->botData.unk5bc[0x18] = 0x6400;
		}

		int idk = *(int*)&botDriver->botData.unk5bc[0x18] * elapsedMilliseconds >> 5;
		if (idk < 0)
		{
			idk = 0;
		}
		idk += *(int*)&botDriver->botData.unk5a8;
		//"idk"'s lifetime doesn't end here probably bc it isn't used.
		//idk = velocity * deltaTime, probably a deltaPosition ?estimate?
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