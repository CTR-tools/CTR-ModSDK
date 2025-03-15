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

	if (botDriver->botData.weaponCooldown != 0)
	{
		botDriver->botData.weaponCooldown--;
	}

	if (botDriver->ChangeState_param2 == 0)
	{
		if ((botDriver->actionsFlagSet & 0x2000000) == 0 && botDriver->botData.weaponCooldown != 0)
		{
			botDriver->botData.weaponCooldown--;
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

	//(*(short*)&botDriver->unk5bc[0x2]) = 0;
	botDriver->botData.unk5bc.drift_unk1 = 0;
	botDriver->kartState = KS_NORMAL;

	botDriver->actionsFlagSetPrevFrame = botDriver->actionsFlagSet;
	botDriver->actionsFlagSet &= 0x7ffffbfd;

	int speedApprox = botDriver->speedApprox; //iVar4

	if (speedApprox < 0)
		speedApprox = -speedApprox;

	if ((botDriver->actionsFlagSet & 1) == 0) {
		speedApprox += 0xf00;
	}
	else {
		speedApprox = ((speedApprox << 1) >> 1);
	}

	bool local_38; //something to do with incrementing the fire level when drift boosting
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

	struct NavFrame* navFrameOfConcern = (struct NavFrame*)&botDriver->botData.estimatePos[0]; //psVar19
	struct NavFrame* nextNavFrameOfConcern; //psVar21

	if ((botDriver->botData.botFlags & 1) == 0)
	{
		navFrameOfConcern = botDriver->botData.botNavFrame;
		nextNavFrameOfConcern = navFrameOfConcern + 1;
		if (sdata->NavPath_ptrHeader[botDriver->botData.botPath]->last <= nextNavFrameOfConcern)
		{
			nextNavFrameOfConcern = NavPath_ptrNavFrameArray[0];
		}
	}
	else
	{
		nextNavFrameOfConcern = botDriver->botData.botNavFrame;
	}

	struct BucketSearchParams cpwb_param_2; //.pos[3] unused?
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
			xyz[0] = botDriver->xSpeed + botDriver->botData.unk5bc.ai_accelAxis[0]; //(*(int*)&botDriver->unk5bc[0x1c]);
			xyz[1] = botDriver->ySpeed + botDriver->botData.unk5bc.ai_accelAxis[1]; //(*(int*)&botDriver->unk5bc[0x20]);
			xyz[2] = botDriver->zSpeed + botDriver->botData.unk5bc.ai_accelAxis[2]; //(*(int*)&botDriver->unk5bc[0x24]);
			//similar to BucketSearchParams usage, idk if this will overrun the stack from assignment within this call, needs investigation.
			VehPhysCrash_AnyTwoCars(botThread, (u_short*)cpwb_param_2, &xyz[0]);
		}
	}

	//puVar5 = sdata->gGT

	if (botDriver->botData.ai_progress_cooldown == 0)
	{
		int trafficLightsTimer = sdata->gGT->trafficLightsTimer;

		if (data.characterIDs[botDriver->driverID] == 0xf) //check is oxide
		{
			//Pretend there is less time (oxide is a cheater)
			trafficLightsTimer -= 0x1e0;
		}

		if (0 < trafficLightsTimer) goto give_this_label_a_better_name3; //if race not started, then skip

		if (sdata->gGT->boolDemoMode != 0 &&
			(botDriver->botData.botFlags & 0x100) == 0 &&
			botThread->modelIndex == 0x18)
		{
			botDriver->botData.botFlags |= 0x100;
			DECOMP_CAM_EndOfRace(sdata->gGT->cameraDC[botDriver->driverID], botDriver);
		}

		if ((botDriver->botData.botFlags & 0x200) == 0)
		{ //first frame of race
			botDriver->botData.botFlags |= 0x200;

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

		unsigned int botFlags = botDriver->botData.botFlags;

		/////// START
		if ((botFlags & 0xc0) == 0x40)
		{
			short uVar11 = nextNavFrameOfConcern->pathIndexOfffff; //also uVar20 = (uint)uVar11

			//memory bounds check for the navFrame???
			int idk = ((((int)uVar11) << 0x10) >> 0x1a); //6 bits
			if (((int)(uVar20 << 0x10) >> 0x10 < 0xc00) &&
				idk == *(((char*)&botDriver->botData.unk626) + 1)) //compare to Driver* + 0x627
			{
				botDriver->botData.botFlags |= 0x80;

				DECOMP_LIST_RemoveMember(sdata->unk_NavRelated[botDriver->botData.botPath], &botDriver->botData.item);

				botDriver->botData.botPath = (short)(int)uVar11 >> 10;

				DECOMP_LIST_AddFront(sdata->unk_NavRelated[idk], botDriver->botData.item);

				struct NavFrame* firstNavFrameOnPath = sdata->NavPath_ptrNavFrameArray[idk];
			LAB_800144a0:
				navFrameOfConcern = (struct NavFrame*)&botDriver->botData.estimatePos[0];

				//idk how to better write this
				botDriver->botData.botNavFrame = (struct NavFrame*)(((unsigned int)firstNavFrameOnPath) + ((((unsigned int)uVar11) & 0x3ff) * 0x14));

				BOTS_SetRotation(botDriver, 0);

				nextNavFrameOfConcern = botDriver->botData.botNavFrame;
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
					struct Item* idk = (struct Item*)DECOMP_List_GetFirstItem(&sdata->unk_NavRelated[botDriver->botData.botPath]);
					while (idk != NULL)
					{
						//todo
						if (((char*)idk) - 0x598 != (char*)botDriver)
						{
							int iVar13 = (*(int*)(((char*)idk) + 0xc) - *(int*)botDriver->botData.botNavFrame->pos) * -0x33333333 >> 2;
							if (iVar13 << 0x10 < 0)
							{
								iVar13 += sdata->NavPath_ptrHeader[botDriver->botData.botPath]->numPoints;
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
							// this line may be wrong
							short uVar11 = nextNavFrameOfConcern->pathIndexOfffff; //also uVar20 = (uint)uVar11

							if (uVar11 < 0xc00)
							{
								DECOMP_LIST_RemoveMember(sdata->unk_NavRelated[botDriver->botData.botPath], &botDriver->botData.item);

								int iVar4 = uVar11 >> 0xa;
								botDriver->botData.botPath = uVar11 >> 10;

								DECOMP_LIST_AddFront(sdata->unk_NavRelated[iVar4], &botDriver->botData.item);

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
			int ZY = (botDriver->botData.unk5bc.ai_speedLinear[0] * botDriver->botData.unk5bc.ai_speedLinear[0]) + (botDriver->botData.unk5bc.ai_speedY * botDriver->botData.unk5bc.ai_speedY);

			if (0x2b110000 < sqrZY) //sqrZY
			{
				ZY = SquareRoot0_stub(sqrZY);

				int zVel = botDriver->botData.unk5bc.ai_speedLinear[0] * 0x6900; //iVar3

#if 0 //in the OG game
				if (ZY == 0)
				{
					//trap(0x1c00);
				}
				if ((ZY == -1) && (zVel == -0x80000000))
				{
					//trap(0x1800);
				}
#endif
				int yVel = botDriver->botData.unk5bc.ai_speedY * 0x6900; //iVar15
#if 0 //in the OG game
				if (ZY == 0)
				{
					//trap(0x1c00);
				}
				if ((ZY == -1) && (yVel == -0x80000000))
				{
					//trap(0x1800);
				}
#endif
				botDriver->botData.unk5bc.ai_speedLinear[0] = (zVel / ZY);
				botDriver->botData.unk5bc.ai_speedY = (yVel / ZY);
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
				local_38 = 0 < iVar15;
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

				//Pickup on struct Driver->BotData translation here

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
				int wtf = (int)((int)navFrameOfConcern - *(int*)&sdata->NavPath_ptrNavFrameArray[botDriver->botData.botPath]->pos[0]) * 0x33334000 >> 0x10;

				if ((data.botsThrottle[botPathIndex] <= wtf && wtf < data.botsThrottle[botPathIndex] + 0xb) && 9000 < *(int*)botDriver->botData.unk5bc[0x18])
				{
					*(short*)&botDriver->botData.unk5bc[0x8] = 0;

					*(int*)&botDriver->botData.unk5bc[0x18] -= 100 + botDriver->const_Accel_ClassStat;
				}
			}

			if (0x80 < navFrameOfConcern->goBackCount)
			{
				velocityAccountingForTerrain += botDriver->unk47E;

				if (*(int*)&botDriver->botData.unk5bc[0x18] < velocityAccountingForTerrain)
				{
					int sinOfAngle = MATH_Sin(navFrameOfConcern->goBackCount << 4);

					*(int*)&botDriver->botData.unk5bc[0x18] -= botDriver->const_Gravity * sinOfAngle >> 0xc; //force on a slope due to gravity
				}

				botDriver->fireSpeed = velocityAccountingForTerrain;
			}
		}

		if (0x6400 < *(int*)&botDriver->botData.unk5bc[0x18])
		{
			*(int*)&botDriver->botData.unk5bc[0x18] = 0x6400;
		}

		int idk = *(int*)&botDriver->botData.unk5bc[0x18] * elapsedMilliseconds >> 5; //iVar4
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

	int idk = navFrameOfConcern->flags; //local_44
	int idk2 = navFrameOfConcern->specialBits; //local_40
	//local_3c == 0
	if ((idk2 & 0x80) != 0)
	{
		botDriver->botData.botFlags |= 0x20;
	}

	int gravity;
	if ((botDriver->botData.botFlags & 0x20) == 0)
	{
		gravity = botDriver->const_Gravity;
	}
	else
	{
		gravity = (botDriver->const_Gravity * 41) / 100;
	}

	int speedY = botDriver->botData.unk5bc.ai_speedY -= (gravity * elapsedMilliseconds >> 5);

	if (speedY < -0x5000)
	{
		botDriver->botData.unk5bc.ai_speedY = 0xffffb000;
	}

	botDriver->botData.ai_posBackup[1] += (botDriver->botData.unk5bc.ai_speedY * elapsedMilliseconds >> 5);

	short navDist; //sVar7

	if ((botDriver->actionsFlagSet & 1) == 0)
	{
		//unk[1] may be distToNextNavXZ
		navDist = navFrameOfConcern->unk[1];
		//navDist = botDriver->botData.distToNextNavXZ;
	}
	else
	{
		//unk[0] may be distToNextNavXYZ
		navDist = navFrameOfConcern->unk[0];
		//navDist = botDriver->botData.distToNextNavXYZ;
	}

	int local_3c = 0;
	char local_30 = 0;
	if ((navFrameOfConcern->specialBits & 0x10) != 0)
	{
		local_3c = navFrameOfConcern->specialBits;
	}
	int iVar15 = iVar4_lifetime_2 >> 8;
	int iVar3;

	for (iVar3 = navDist; iVar3 <= iVar15; iVar15 -= iVar3)
	{
		navFrameOfConcern = nextNavFrameOfConcern;

		iVar4_lifetime_2 += iVar3 * -0x100;

		int index = botDriver->botData.botPath; //index = iVar13

		nextNavFrameOfConcern = NAVFRAME_GETNEXTFRAME(navFrameOfConcern);

		iVar15 -= iVar3;

		if (sdata->NavPath_ptrHeader[index]->last <= nextNavFrameOfConcern)
		{
			nextNavFrameOfConcern = sdata->NavPath_ptrNavFrameArray[index];
		}

		if (botDriver->botData.ai_posBackup[1] >> 8 < nextNavFrameOfConcern->pos[1] && ((navFrameOfConcern->flags & 0x200) != 0))
		{
			DECOMP_BOTS_Killplane(botThread);
		}

		idk |= navFrameOfConcern->flags;
		idk2 |= navFrameOfConcern->specialBits;

		int uVar8;
		if ((botDriver->botData.botFlags & 0x80) == 0)
		{
			uVar8 = 0xfffffffe;
		}
		else
		{
			uVar8 = 0xffffff3e;
		}

		botDriver->botData.botFlags &= uVar8;

		short unk;

		if (local_30 == 0 && (0x9e < navFrameOfConcern->rot[3] - 0x31))
		{
			if ((botDriver->actionsFlagSet & 1) == 0)
				; //goto todo

			unk = navFrameOfConcern->unk[0];
		}
		else
		{
			local_30 = 1;

			unk = navFrameOfConcern->unk[1];
		}

		iVar3 = unk;

		if ((navFrameOfConcern->specialBits & 0x10) != 0)
		{
			local_3c = navFrameOfConcern->specialBits;
		}
	}

	botDriver->botData.unk5a8 = iVar4_lifetime_2;

	int actionFlagsBuildup = (idk & 2) << 10; // uVar20

	botDriver->actionsFlagSet &= 0xfffee7ff;

	if ((idk & 0x2000) != 0)
	{
		actionFlagsBuildup |= 0x10000;
	}

	if ((idk & 4) != 0)
	{
		//normally goes to uVar8, but doing it to actionFlagsBuildup should be equivalent.
		actionFlagsBuildup |= 0x1000;
	}

	botDriver->actionsFlagSet = actionFlagsBuildup;

	struct Terrain* terrain = VehAfterColl_GetTerrain(navFrameOfConcern->flags >> 3);

	botDriver->terrainMeta1 = terrain;

	if ((navFrameOfConcern->specialBits & 0x20) != 0)
	{
		short vertSplit;
		if ((navFrameOfConcern->specialBits & 0xf) == 0)
		{
			vertSplit = sdata->gGT->level1->splitLines[0];
		}
		else
		{
			vertSplit = sdata->gGT->level1->splitLines[1];
		}

		botInstance->vertSplit = vertSplit;

		botInstance->flags |= 0x4000;
	}

	if ((navFrameOfConcern->specialBits & 0x30) == 0 && (botThread->modelIndex != 0x4b))
	{
		int transparency = (navFrameOfConcern->specialBits & 0xf) * 0x9c00;

		botDriver->alphaScaleBackup = ((botDriver->alphaScaleBackup * 100) + transparency >> 8);

		botInstance->alphaScale = ((botInstance->alphaScale * 0x100) + transparency >> 8);
	}

	if ((botDriver->actionsFlagSet & 0x1000) == 0 || (actionFlagsBuildup & 0x1800) == 0)
	{
		botDriver->turbo_MeterRoomLeft = 0;
		*(short*)&botDriver->botData.unk5bc[0x8] = 0;
		*(short*)&botDriver->botData.unk5bc[0xA] = 0;
	}
	else
	{ //The curly braces for this block are wrong
		botDriver->actionsFlagSet |= 0x80;
		*(short*)&botDriver->botData.unk5bc[0x8] += elapsedMilliseconds;
		int uVar6;
		//this ugly tree of ifs may have been a switch perhaps?
		if ((*(short*)&botDriver->botData.unk5bc[0x8] * 0x10000 >> 0x10 < 0xb41) || (5 < *(short*)&botDriver->botData.unk5bc[0xA]))
		{
			if ((*(short*)&botDriver->botData.unk5bc[0x8] < 0x961) || (uVar6 = 5, 4 < *(short*)&botDriver->botData.unk5bc[0xA]))
			{
				if ((*(short*)&botDriver->botData.unk5bc[0x8] < 0x781) || (3 < *(short*)&botDriver->botData.unk5bc[0xA]))
				{
					if ((0x5a0 < *(short*)&botDriver->botData.unk5bc[0x8]) && (uVar6 = 3, *(short*)&botDriver->botData.unk5bc[0xA] < 3))
						; //goto //todo
					if ((*(short*)&botDriver->botData.unk5bc[0x8] < 0x3c1) || (1 < *(short*)&botDriver->botData.unk5bc[0xA]))
					{
						if ((0x1e0 < *(short*)&botDriver->botData.unk5bc[0x8]) && (uVar6 = 1, *(short*)&botDriver->botData.unk5bc[0xA] < 1))
						{
							//goto //todo
						}
					}
					else
					{
						//trigger a turbo boost?
						*(short*)&botDriver->botData.unk5bc[0xA] = 2;
						botDriver->turbo_MeterRoomLeft = 0;

						VehFire_Increment(botDriver, 0xf0, 2, local_38 << 7);
					}
				}
				else
				{
					//trigger a turbo boost?
					*(short*)&botDriver->botData.unk5bc[0xA] = 4;
					botDriver->turbo_MeterRoomLeft = 0;

					VehFire_Increment(botDriver, 0x1e0, 2, local_38 << 8);
				}
			}
			else
			{
				//trigger a turbo boost?
				*(short*)&botDriver->botData.unk5bc[0xA] = uVar6;
				botDriver->turbo_MeterRoomLeft = 0xa0;
			}
		}
		else
		{
			//trigger a turbo boost?
			*(short*)&botDriver->botData.unk5bc[0xA] = 6;
			botDriver->turbo_MeterRoomLeft = 0;

			VehFire_Increment(botDriver, 0x2d0, 2, local_38 * 0x180);
		}
	}

	if ((idk & 0x100) != 0)
	{
		VehFire_Increment(botDriver, 0x78, 1, 0x900);

		botDriver->botData.botFlags |= 0x10;
	}

	if ((idk & 0x1) != 0)
	{
		VehFire_Increment(botDriver, 0x2d0, 1, 0x900);

		botDriver->botData.botFlags |= 0x10;
	}

	if ((botDriver->botData.botFlags & 1) == 0)
	{
		botDriver->botData.botNavFrame = navFrameOfConcern;

		short botPath = botDriver->botData.botPath;

		nextNavFrameOfConcern = NAVFRAME_GETNEXTFRAME(navFrameOfConcern);

		if (sdata->NavPath_ptrHeader[botPath]->last <= nextNavFrameOfConcern)
		{
			nextNavFrameOfConcern = sdata->NavPath_ptrNavFrameArray[0];
		}
	}

	int percentage; //aka iVar13
	if (iVar3 == 0)
		percentage = 0;
	else
	{
		percentage = (iVar15 << 0xc) / iVar3;

#if 0 //traps in the OG code.
		if (iVar3 == 0)
			;//trap(0x1c00)
		if ((iVar3 == -1) && (iVar15 << 0xc == -0x80000000))
			;//trap(0x1800)
#endif
	}

	botDriver->posPrev.x = botDriver->posCurr.x;
	botDriver->posPrev.y = botDriver->posCurr.y;
	botDriver->posPrev.z = botDriver->posCurr.z;

	botDriver->rotPrev.x = botDriver->rotCurr.x;
	botDriver->rotPrev.y = botDriver->rotCurr.y;
	botDriver->rotPrev.z = botDriver->rotCurr.z;

	botDriver->botData.ai_posBackup[0] = (navFrameOfConcern->pos[0] + ((nextNavFrameOfConcern->pos[0] - navFrameOfConcern->pos[0]) * percentage >> 0xc)) * 0x100;
	botDriver->quadBlockHeight = (navFrameOfConcern->pos[1] + ((nextNavFrameOfConcern->pos[1] - navFrameOfConcern->pos[1]) * percentage >> 0xc)) * 0x100;
	botDriver->botData.ai_posBackup[2] = (navFrameOfConcern->pos[2] + ((nextNavFrameOfConcern->pos[2] - navFrameOfConcern->pos[2]) * percentage >> 0xc)) * 0x100;

	if ((botDriver->botData.botFlags & 0x8) != 0)
	{
		botDriver->botData.unk5bc.ai_accelAxis[1] = 0;
		botDriver->botData.unk5bc.ai_velAxis[0] += botDriver->botData.unk5bc.ai_accelAxis[0];
		botDriver->botData.unk5bc.ai_velAxis[1] += botDriver->botData.unk5bc.ai_accelAxis[1];
		botDriver->botData.unk5bc.ai_velAxis[2] += botDriver->botData.unk5bc.ai_accelAxis[2];
		int preX = botDriver->botData.unk5bc.ai_accelAxis[0]; //iVar3
		botDriver->botData.unk5bc.ai_accelAxis[0] >>= 1;
		int preZ = botDriver->botData.unk5bc.ai_accelAxis[2]; //iVar15
		botDriver->botData.unk5bc.ai_accelAxis[2] >>= 1;
		botDriver->botData.unk5bc.ai_velAxis[1] += botDriver->botData.unk5bc.ai_accelAxis[1];
		botDriver->botData.unk5bc.ai_velAxis[0] += preX;
		preX = botDriver->botData.unk5bc.ai_velAxis[0];
		botDriver->botData.unk5bc.ai_velAxis[2] += preZ;
		if (preX != 0)
		{
			if (preX < 1)
			{
				botDriver->botData.unk5bc.ai_velAxis[0] = preX + 0x444;
				if (0 < preX + 0x444); //goto todo
				if (botDriver->botData.unk5bc.ai_accelAxis[0] == 0)
				{
					botDriver->botData.unk5bc.ai_accelAxis[0] = 0x444;
				}
			}
			else
			{
				botDriver->botData.unk5bc.ai_velAxis[0] = preX - 0x444;
				if (preX - 0x444 < 0)
				{
					botDriver->botData.unk5bc.ai_velAxis[0] = 0;
				}
				else
				{
					if (botDriver->botData.unk5bc.ai_accelAxis[0] == 0)
					{
						botDriver->botData.unk5bc.ai_accelAxis[0] = 0xfffffbbc;
					}
				}
			}
		}
		int preZ = botDriver->botData.unk5bc.ai_velAxis[2]; //new scope of iVar3?
		if (preZ != 0)
		{
			if (preZ < 1)
			{
				botDriver->botData.unk5bc.ai_velAxis[2] = preZ + 0x444;
				if (0 < preZ + 0x444); //goto todo
				if (botDriver->botData.unk5bc.ai_accelAxis[2] == 0)
				{
					botDriver->botData.unk5bc.ai_accelAxis[2] = 0x444;
				}
			}
			else
			{
				botDriver->botData.unk5bc.ai_velAxis[2] = preZ - 0x444;
				if (preZ - 0x444 < 0)
				{
					botDriver->botData.unk5bc.ai_velAxis[2] = 0;
				}
				else
				{
					if (botDriver->botData.unk5bc.ai_accelAxis[2] == 0)
					{
						botDriver->botData.unk5bc.ai_accelAxis[2] = 0xfffffbbc;
					}
				}
			}
		}
		if (botDriver->botData.unk5bc.ai_velAxis[0] == 0 && botDriver->botData.unk5bc.ai_velAxis[2] == 0)
		{
			botDriver->botData.botFlags &= 0xfffffff7;
		}
	}

	if ((botDriver->botData.botFlags & 0x9) == 0)
	{
		botDriver->ai_quadblock_checkpointIndex = navFrameOfConcern->goBackCount;
	}
	else
	{
		int uVar8 = (nextNavFrameOfConcern->rot[1] * 0x10) + (navFrameOfConcern->rot[1] * -0x10) & 0xfff;
		if (0x7ff < uVar8)
		{
			uVar8 -= 0x1000;
		}

		botDriver->botData.ai_rot4[1] = navFrameOfConcern->rot[1] * 0x10 + ((uVar8 * percentage) >> 0xc) & 0xfff;

		struct BucketSearchParams buckSearchParams;
		buckSearchParams.pos[0] = botDriver->botData.ai_posBackup[0] + botDriver->botData.unk5bc.ai_velAxis[0] >> 8;
		short sVar7 = botDriver->botData.ai_posBackup[1] + botDriver->botData.unk5bc.ai_velAxis[1] >> 8;
		buckSearchParams.pos[1] = sVar7 - 0x100;
		//TODO CONCAT22
		buckSearchParams.pos[2] = botDriver->botData.ai_posBackup[2] + botDriver->botData.unk5bc.ai_velAxis[2] >> 8;
		//TODO: more stuff here local_8c

		/*
		* from my understanding:
			first param: 98 is x, 96 is y, 94 is z
			second param: 92 is padding, 90 is x, 8e is y, 8c is z
		*/

		sps->ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
		sps->Union.QuadBlockColl.qbFlagsWanted = 0x1000;
		sps->Union.QuadBlockColl.qbFlagsIgnored = 0x10;
		sps->Union.QuadBlockColl.searchFlags = 2;

		COLL_SearchBSP_CallbackQUADBLK(&buckSearchParams, , sps, 0);

		if (sps->boolDidTouchQuadblock)
		{
			botDriver->quadBlockHeight = sps->Union.QuadBlockColl.hitPos[1] << 8;

			botDriver->ai_quadblock_checkpointIndex = sps->Set2.ptrQuadblock->checkpointIndex;

			VehPhysForce_RotAxisAngle(botInstance->matrix, &sps->Set2.normalVec[0], botDriver->botData.ai_rot4[1]);

			botDriver->AxisAngle3_normalVec[0] = sps->Set2.normalVec[0];
			botDriver->AxisAngle3_normalVec[1] = sps->Set2.normalVec[1];
			botDriver->AxisAngle3_normalVec[2] = sps->Set2.normalVec[2];

			//this line is cringe.
			botInstance->bitCompressed_NormalVector_AndDriverIndex = (sps->Set2.normalVec[0] >> 6) & 0xff | (sps->Set2.normalVec[1] & 0x3fc0) << 2 | ((sps->Set2.normalVec[2] >> 6) & 0xff) << 0x10 | (botDriver->driverID + 1) * 0x1000000;

			if ((sps->Set2.ptrQuadblock->quadFlags & 0x200) != 0)
			{
				DECOMP_BOTS_Killplane(botThread);
			}
		}
	}
	iVar4_lifetime_2 >>= 8;
	if (botDriver->botData.ai_posBackup[1] < botDriver->quadBlockHeight)
	{
		int oldBotFlags = botDriver->botData.botFlags; //uVar8
		botDriver->botData.botFlags &= 0xffffffdf;

		if ((navFrameOfConcern->flags & 0x200) == 0)
		{
			if ((oldBotFlags & 2) == 0)
			{
				if ((botDriver->actionsFlagSet & 1) == 0)
				{
					if (botDriver->instSelf->thread->modelIndex == 0x18)
					{
						int mapped = DECOMP_VehCalc_MapToRange(botDriver->jumpHeightCurr - botDriver->jumpHeightPrev, 0x300, 0x1400, 0x4b, 200); //uVar8

						int volume; //uVar20
						if (mapped < 0)
						{
							volume = 0;
						}
						else
						{
							volume = mapped & 0xff;

							if (0xff < mapped)
							{
								volume = 0xff;
							}
						}
						int flags;
						if ((botDriver->actionsFlagSet & 0x10000) == 0)
						{
							flags = volume << 0x10 | 0x8080;
						}
						else
						{
							flags = volume << 0x10 | 0x1008080;
						}

						OtherFX_Play_LowLevel(7, 1, flags);
					}
					int iVar3 = navFrameOfConcern->unk[1];
					if (iVar3 != 0)
					{
#if 0
						if (iVar3 == 0)
						{
							trap(0x1c00);
						}
						if ((iVar3 == -1) && (iVar4_lifetime_2 * navFrameOfConcern->unk[0] == -0x80000000))
						{
							trap(0x1800);
						}
#endif
						botDriver->botData.unk5a8 = (iVar4_lifetime_2 * navFrameOfConcern->unk[0]) / iVar3 << 8;
					}
					short sVar7 = botDriver->jump_LandingBoost;

					if (sVar7 < 0x5a1)
					{
						if (0x3c0 < sVar7)
						{
							iVar4_lifetime_2 = local_38 * 0x60;
							//goto todo
						}
						if (0x280 < sVar7)
						{
							iVar4_lifetime_2 = 0;
							//goto todo
						}
					}
					else
					{
						iVar4_lifetime_2 = local_38 * 0xc0;

						VehFire_Increment(botDriver, 0x2d0, 2, iVar4_lifetime_2);
					}
					botDriver->actionsFlagSet |= 2;
				}
				iVar4_lifetime_2 = botDriver->quadBlockHeight - botDriver->posPrev.y;

				botDriver->botData.ai_posBackup[1] = botDriver->quadBlockHeight;

				botDriver->botData.ai_posBackup[0] = iVar4_lifetime_2;

				if ((idk & 0x400) != 0 || (botDriver->instTntRecv != NULL))
				{
					int oldActionsFlags = botDriver->actionsFlagSet;

					botDriver->actionsFlagSet |= 0x400;

					botDriver->botData.unk5bc.ai_speedY = iVar4_lifetime_2 + 0x1400;

					if (botThread->modelIndex == 0x18)
					{
						OtherFX_Play_Echo(8, 1, oldActionsFlags >> 0x10 & 1);
					}
				}
				if (16000 < botDriver->botData.unk5bc.ai_speedY)
				{
					botDriver->botData.unk5bc.ai_speedY = 16000;
				}

				if ((idk & 0x1800) == 0)
				{
					botDriver->botData.unk5bc.drift_unk1 = 0;

					botDriver->kartState = KS_NORMAL;
				}
				else
				{
					botDriver->kartState = KS_DRIFTING;

					if ((idk & 0x800) == 0)
					{
						botDriver->botData.unk5bc.drift_unk1 = 0x2aa;
					}
					else
					{
						botDriver->botData.unk5bc.drift_unk1 = 0xfd56;
					}
				}
			}
			else
			{
				if (((botDriver->actionsFlagSet & 1) == 0))
				{
					int iVar3 = navFrameOfConcern->unk[1];
					if (iVar3 != 0)
					{
#if 0
						if (iVar3 == 0)
						{
							trap(0x1c00);
						}
						if ((iVar3 == -1) && (iVar4_lifetime_2 * navFrameOfConcern->unk[0] == -0x80000000))
						{
							trap(0x1800);
						}
#endif
						botDriver->botData.unk5a8 = (iVar4_lifetime_2 * navFrameOfConcern->unk[0]) / iVar3 << 8;
					}
				}
				iVar4_lifetime_2 = -botDriver->botData.unk5bc.ai_speedY >> 1;

				botDriver->botData.unk5bc.ai_speedY = iVar4_lifetime_2;

				if (iVar4_lifetime_2 < 0)
				{
					botDriver->botData.unk5bc.ai_speedY = -iVar4_lifetime_2;
				}

				char bVar10 = botDriver->botData.unk626 + 1;
				botDriver->botData.unk626 = bVar10;

				if (botDriver->botData.unk5ba == 1)
				{
					botDriver->actionsFlagSet |= 0x1800;
				}
				else
				{
					if (botDriver->botData.unk5ba == 2 && (2 < bVar10))
					{
						botDriver->botData.ai_progress_cooldown = 10;
						botDriver->botData.unk5bc.ai_speedLinear = 0;
						botDriver->botData.botFlags &= 0xfffffff9;
					}
				}

				botDriver->botData.ai_posBackup[1] = botDriver->quadBlockHeight;
			}
		}
		else
		{
			DECOMP_BOTS_Killplane(botThread);
		}

		botDriver->jump_LandingBoost = 0;
		botDriver->actionsFlagSet |= 1;
	}
	else
	{
		if ((local_30 == 0 && (botDriver->actionsFlagSet & 1) != 0))
		{
			int iVar3 = navFrameOfConcern->unk[0];
			if (iVar3 != 0)
			{
#if 0
				if (iVar3 == 0)
				{
					trap(0x1c00);
				}
				if ((iVar3 == -1) && (iVar4 * navFrameOfConcern->unk[1] == -0x80000000))
				{
					trap(0x1800);
				}
#endif
				botDriver->botData.unk5a8 = (iVar4 * navFrameOfConcern->unk[1]) / iVar3 << 8;
			}
		}

		botDriver->actionsFlagSet = botDriver->actionsFlagSet & 0xfffffffe | 0x80000;

		botDriver->jump_LandingBoost += elapsedMilliseconds;// idk & 0x1800;
	}

	iVar4_lifetime_2 = 0x18;

	if (botDriver->botData.unk5ba.drift_unk1 != 0)
	{
		iVar4_lifetime_2 = 0x60;
	}

	int iVar3 = botDriver->botData.unk5bc.ai_mulDrift - iVar4_lifetime_2;
	if (botDriver->botData.unk5ba.drift_unk1 < botDriver->botData.unk5bc.ai_mulDrift)
	{
		botDriver->botData.unk5bc.ai_mulDrift = iVar3;

		if (iVar3 * 0x10000 >> 0x10 < botDriver->botData.unk5ba.drift_unk1)
		{
			botDriver->botData.unk5bc.ai_mulDrift = botDriver->botData.unk5ba.drift_unk1;
		}
	}
	else
	{
		iVar4_lifetime_2 += botDriver->botData.unk5bc.ai_mulDrift;

		botDriver->botData.unk5bc.ai_mulDrift = iVar4_lifetime_2;

		if (botDriver->botData.unk5ba.drift_unk1 < iVar4_lifetime_2 * 0x10000 >> 0x10)
		{
			botDriver->botData.unk5bc.ai_mulDrift = botDriver->botData.unk5ba.drift_unk1;
		}
	}
	botDriver->multDrift = botDriver->botData.unk5bc.ai_mulDrift;

	if ((botDriver->botData.botFlags & 2) != 0)
	{
		short sVar7 = botDriver->botData.unk5ba;
		if (sVar7 == 2)
		{
			botDriver->botData.unk5bc.rotXZ -= 1;
		}
		else
		{
			if (sVar7 < 3)
			{
				if (sVar7 == 1)
				{
					short squishCooldownMaybe = *(short*)&botDriver->botData.unk5bc.ai_squishCooldown;
					int alsoSquishCooldownMaybe = botDriver->botData.unk5bc.ai_squishCooldown - 0xc;
					botDriver->botData.unk5bc.ai_squishCooldown = alsoSquishCooldownMaybe;
					botDriver->botData.unk5bc.ai_mulDrift += squishCooldownMaybe;
					if (alsoSquishCooldownMaybe < 0x100)
					{
						botDriver->botData.unk5bc.ai_squishCooldown = 0;
						botDriver->botData.unk5bc.ai_mulDrift = 0;
						botDriver->botData.unk5bc.ai_speedLinear = 0;
						botDriver->botData.botFlags &= 0xfffffff9;
					}
					//uVar2 = 3;
					//label
					//botDriver->kartState = uVar2;
				}
			}
			else
			{
				if (sVar7 == 3)
				{
					//TODO
				}
				else
				{
					if (sVar7 == 5)
					{
						//TODO
					}
				}
			}
		}
	}

	if (botDriver->forcedJump_trampoline != 0)
	{
		int turtleJumpForce = botDriver->const_JumpForce * 3; //iVar4

		if (botDriver->forcedJump_trampoline != 2)
		{
			turtleJumpForce /= 2;
		}

		if (botDriver->botData.unk5bc.ai_speedY < turtleJumpForce)
		{
			botDriver->botData.unk5bc.ai_speedY = turtleJumpForce; //only overwrite the velocity if our vertical velocity is less than the turtleJumpForce
		}

		botDriver->forcedJump_trampoline = 0;
	}

	if (
		((local_40 & 0x10) != 0) &&
		(0x1c1f < botDriver->botData.unk5bc.ai_speedLinear || data.characterIDs[botDriver->driverID] == 0xf)
		)
	{
		int iVar4 = (local_3c & 0xf);
		botDriver->botData.unk5bc.ai_speedY = sdata->NavPath_ptrHeader[botDriver->botData.botPath]->rampPhys2[iVar4];
		botDriver->botData.unk5bc.ai_speedLinear = sdata->NavPath_ptrHeader[botDriver->botData.botPath]->rampPhys1[iVar4];

		if (data.characterIDs[botDriver->driverID] == 0xf)
		{
			botDriver->botData.unk5bc.ai_squishCooldown = 0;
			botDriver->botData.unk5bc.ai_mulDrift = 0;
			botDriver->botData.botFlags &= 0xfffffff9;
		}
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