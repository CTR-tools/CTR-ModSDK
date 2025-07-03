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

	botDriver->reserves -= elapsedMilliseconds;
	if (botDriver->reserves * 0x1000 < 0)
		botDriver->reserves = 0;

	botDriver->turbo_outsideTimer -= elapsedMilliseconds;
	if (botDriver->turbo_outsideTimer * 0x1000 < 0)
		botDriver->turbo_outsideTimer = 0;

	botDriver->squishTimer -= elapsedMilliseconds;
	if (botDriver->squishTimer * 0x1000 < 0)
		botDriver->squishTimer = 0;

	botDriver->burnTimer -= elapsedMilliseconds;
	if (botDriver->burnTimer * 0x1000 < 0)
		botDriver->burnTimer = 0;

	botDriver->clockReceive -= elapsedMilliseconds;
	if (botDriver->clockReceive * 0x1000 < 0)
		botDriver->clockReceive = 0;

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
		speedApprox = ((speedApprox << 1) >> 1); //why does the OG code do this? is this just abs(speedApprox)?
	}

	bool local_38; //something to do with incrementing the fire level when drift boosting
	short unkSpeedThing = (((speedApprox * 0x89) + (botDriver->unkSpeedValue2 * 0x177)) * 8 >> 0xC); //sVar7
	botDriver->unkSpeedValue2 = unkSpeedThing;

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

		botDriver->unkSpeedValue1 -= unkSpeedThing;
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
			nextNavFrameOfConcern = sdata->NavPath_ptrNavFrameArray[0];
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
		if (botThread->modelIndex == DYNAMIC_PLAYER)
		{
			DECOMP_PROC_CollidePointWithBucket(botThread->siblingThread, (short*)&cpwb_param_2);

			uVar12 = sdata->gGT->threadBuckets[ROBOT].thread;
		}
		else
		{
			if (botThread->modelIndex != DYNAMIC_ROBOT_CAR) goto give_this_label_a_better_name2;

			uVar12 = botThread->siblingThread;
		}

		DECOMP_PROC_CollidePointWithBucket(uVar12, (short*)&cpwb_param_2);
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
			VehPhysCrash_AnyTwoCars(botThread, (u_short*)&cpwb_param_2, &xyz[0]);
		}
	}

	//puVar5 = sdata->gGT

	int deltaPosThisFrame; //iVar4

	if (botDriver->botData.ai_progress_cooldown == 0)
	{
		int trafficLightsTimer = sdata->gGT->trafficLightsTimer;

		if (data.characterIDs[botDriver->driverID] == NITROS_OXIDE) //check is oxide
		{
			//Pretend there is less time (oxide is a cheater)
			trafficLightsTimer -= 0x1e0;
		}

		if (0 < trafficLightsTimer) goto give_this_label_a_better_name3; //if race not started, then skip

		if (sdata->gGT->boolDemoMode != 0 &&
			(botDriver->botData.botFlags & 0x100) == 0 &&
			botThread->modelIndex == DYNAMIC_PLAYER)
		{
			botDriver->botData.botFlags |= 0x100;
			DECOMP_CAM_EndOfRace(&sdata->gGT->cameraDC[botDriver->driverID], botDriver);
		}

		if ((botDriver->botData.botFlags & 0x200) == 0)
		{ //first frame of race
			botDriver->botData.botFlags |= 0x200;

			if (data.characterIDs[botDriver->driverID] == NITROS_OXIDE)
			{ //if oxide, then talk
				Voiceline_RequestPlay(0, 0xf, 0x10);
			}

			if (
				( //if in front row & 25% chance
					(sdata->kartSpawnOrderArray[botDriver->driverID] < 3) &&
					RngDeadCoed((u_int*)&sdata->gGT->deadcoed_struct) < 0x40
					) ||
				data.characterIDs[botDriver->driverID] == NITROS_OXIDE
				)
			{ //start the race with a boost
				DECOMP_VehFire_Increment(botDriver, 0x2d0, 1, 0x180);

				DECOMP_VehFire_Audio(botDriver, 0x180);
			}
		}

		//between these start and end tags, there's confusing variable lifetime that needs to be looked at closer.

		unsigned int botFlags = botDriver->botData.botFlags; //uVar8

		if ((botFlags & 0xc0) == 0x40)
		{
			short pathIndexOfWhat = nextNavFrameOfConcern->pathIndexOfffff; //uVar11, also uVar20 = (uint)uVar11

			int truncatedPathIndexOfWhat = pathIndexOfWhat >> 0xa; //uVar18
			if (pathIndexOfWhat < 0xc00 && truncatedPathIndexOfWhat == *(((char*)&botDriver->botData.unk626) + 1))
			{
				botDriver->botData.botFlags = botFlags | 0x80;

				DECOMP_LIST_RemoveMember(&sdata->navBotList[botDriver->botData.botPath], &botDriver->botData.item);

				botDriver->botData.botPath = (short)(int)pathIndexOfWhat >> 10;

				DECOMP_LIST_AddFront(&sdata->navBotList[truncatedPathIndexOfWhat], &botDriver->botData.item);

				struct NavFrame* firstNavFrameOnPath = sdata->NavPath_ptrNavFrameArray[truncatedPathIndexOfWhat];
			//LAB_800144a0:
				navFrameOfConcern = (struct NavFrame*)&botDriver->botData.estimatePos[0];

				botDriver->botData.botNavFrame = firstNavFrameOnPath + (pathIndexOfWhat & 0x3ff);

				BOTS_SetRotation(botDriver, 0);

				nextNavFrameOfConcern = botDriver->botData.botNavFrame;
			}
		}
		else
		{
			if (450 < sdata->unk_counter_upTo450)
			{
				struct Driver* otherDriver = NULL; //iVar4
				if ((botFlags & 1) == 0)
				{
					int iVar3 = 1000;
					short sVar7 = 1000;

					struct BotData* botData = (struct BotData*)DECOMP_LIST_GetFirstItem(&sdata->navBotList[botDriver->botData.botPath]); //iVar15
					while (botData != NULL)
					{
						if (((char*)botData) - offsetof(struct Driver, botData) != (char*)botDriver)
						{
							int iVar13 = botData->botNavFrame - botDriver->botData.botNavFrame; //the index offset that botData is.

							if (iVar13 < 0)
							{
								iVar13 += sdata->NavPath_ptrHeader[botDriver->botData.botPath]->numPoints;
							}
							if (iVar13 < iVar3)
							{
								iVar3 = iVar13;
								otherDriver = (struct Driver*)(((char*)botData) - offsetof(struct Driver, botData));
							}
						}
						sVar7 = (short)iVar3;

						botData = (struct BotData*)LIST_GetNextItem((struct Item*)botData);
					}

					if (otherDriver != NULL && sVar7 < 3)
					{
						int diff = botDriver->distanceToFinish_curr - otherDriver->distanceToFinish_curr;

						if (diff < 0)
						{
							diff += sdata->gGT->level1->ptr_restart_points->distToFinish * 8;
						}
						if (diff < 0x200)
						{
							short pathIndexOfWhat = nextNavFrameOfConcern->pathIndexOfffff; //also uVar20 = (uint)uVar11

							if (pathIndexOfWhat < 0xc00)
							{
								DECOMP_LIST_RemoveMember(&sdata->navBotList[botDriver->botData.botPath], &botDriver->botData.item);

								int truncatedPathIndexOfWhat = pathIndexOfWhat >> 0xa; //iVar4

								botDriver->botData.botPath = pathIndexOfWhat >> 10;

								DECOMP_LIST_AddFront(&sdata->navBotList[truncatedPathIndexOfWhat], &botDriver->botData.item);

								struct NavFrame* firstNavFrameOnPath = sdata->NavPath_ptrNavFrameArray[truncatedPathIndexOfWhat];

								//goto LAB_800144a0; //instead of goto, just copy/paste

								navFrameOfConcern = (struct NavFrame*)&botDriver->botData.estimatePos[0];

								botDriver->botData.botNavFrame = firstNavFrameOnPath + (pathIndexOfWhat & 0x3ff);

								BOTS_SetRotation(botDriver, 0);

								nextNavFrameOfConcern = botDriver->botData.botNavFrame;
							}
						}
					}
				}
			}
		}

		//PICK IT UP HEREEEEEEEEEEEEEEEEEEEEEEEEEEEE

		//puVar5 = gGT but different?

		if ((botDriver->actionsFlagSet & 1) == 0)
		{
			int ZYsqr = (botDriver->botData.unk5bc.ai_speedLinear * botDriver->botData.unk5bc.ai_speedLinear) + (botDriver->botData.unk5bc.ai_speedY * botDriver->botData.unk5bc.ai_speedY);

			if (0x2b110000 < ZYsqr) //sqrZY
			{
				int ZY = SquareRoot0_stub(ZYsqr);

				int zVel = botDriver->botData.unk5bc.ai_speedLinear * 0x6900; //iVar3

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
				botDriver->botData.unk5bc.ai_speedLinear = (zVel / ZY);
				botDriver->botData.unk5bc.ai_speedY = (yVel / ZY);
			}
		}
		else
		{
			botDriver->actionsFlagSet &= 0xfff7ffff;

			struct Driver* bestDriverRank = sdata->bestHumanRank; //iVar4

			if ((sdata->gGT->gameMode1 & RELIC_RACE) != 0)
			{
				bestDriverRank = sdata->bestRobotRank;
			}

			int botVelocity; //iVar3

			if (bestDriverRank == NULL || (bestDriverRank == botDriver))
			{
				botVelocity = sdata->gGT->constVal_9000;
			}
			else
			{
				int driverRank = botDriver->driverRank; //uVar8
				bool isInAdvArcadeOrVSCup = false; //bVar1
				if ((sdata->gGT->gameMode1 & ADVENTURE_CUP) != 0 || (sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
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

				if ((sdata->gGT->gameMode1 & ADVENTURE_CUP) != 0 || (sdata->gGT->gameMode2 & CUP_ANY_KIND) != 0)
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

				short difficultyStat; //sVar7

				if (bestDriverRank->lapIndex == 0)
				{
					difficultyStat = sdata->arcade_difficultyParams[0xB];
				}
				else
				{
					if (bestDriverRank->lapIndex == sdata->gGT->numLaps - 1)
					{
						difficultyStat = sdata->arcade_difficultyParams[0xD];
					}
					else
					{
						difficultyStat = sdata->arcade_difficultyParams[0xC];
					}
				}

				int distToFinish = sdata->gGT->level1->ptr_restart_points->distToFinish * 8; //iVar3

				int lapIndex = bestDriverRank->lapIndex; //uVar20

				if ((bestDriverRank->actionsFlagSet & 0x1000000) != 0)
				{
					lapIndex--;
				}

				int botLapIndex = botDriver->lapIndex; //uVar18

				if ((botDriver->actionsFlagSet & 0x1000000) != 0)
				{
					botLapIndex--;
				}

				//not super meaningful, probably just a difficulty statistic
				int complexDifficultyStat = ((distToFinish - bestDriverRank->distanceToFinish_curr) + (lapIndex * distToFinish)) - ((distToFinish - botDriver->distanceToFinish_curr) + (botLapIndex * distToFinish)) - sdata->arcade_difficultyParams[driverRank + difficultyStat]; //iVar15

				int otherDifficultyStat; //iVar13
				if (isInAdvArcadeOrVSCup && ((driverRank & 0xffff) == 0))
				{
					if (complexDifficultyStat < 1)
					{
						otherDifficultyStat = sdata->arcade_difficultyParams[0x9];
					}
					else
					{
						if (botDriver->lapIndex < sdata->gGT->numLaps - 1)
						{
							otherDifficultyStat = sdata->cup_difficultyParams[0x8];
						}
						else
						{
							otherDifficultyStat = sdata->cup_difficultyParams[0x8] + sdata->cup_difficultyParams[0xA];
						}
					}
				}
				else
				{
					if (complexDifficultyStat < 1)
					{
						otherDifficultyStat = sdata->arcade_difficultyParams[0x9];
					}
					else
					{
						if (sdata->gGT->numLaps - 1 <= botDriver->lapIndex)
						{
							otherDifficultyStat = sdata->cup_difficultyParams[0x8] + sdata->cup_difficultyParams[0xA];
						}
						else
						{
							otherDifficultyStat = sdata->arcade_difficultyParams[0x8];
						}
					}
				}
				botVelocity = complexDifficultyStat; //iVar3
				if (complexDifficultyStat < 0)
					botVelocity = -complexDifficultyStat;
				int iVar9 = otherDifficultyStat;
				if (otherDifficultyStat < 0)
					iVar9 = -otherDifficultyStat;

				botVelocity = iVar9 * (((botVelocity + 0x80) * 0x1000) / 0xa00) >> 0xc;
				local_38 = 0 < complexDifficultyStat;
				botVelocity = botVelocity + ((botVelocity << 3) / 100) * (7 - driverRank);

				if (iVar9 < botVelocity)
					botVelocity = iVar9;
				if (otherDifficultyStat < 0)
					botVelocity = -iVar9;

				int bestDriverWumpaCount = bestDriverRank->numWumpas; //iVar15, assume max of 9?
				if (9 < bestDriverWumpaCount)
					bestDriverWumpaCount = 9;

				int turboMult = bestDriverRank->turboConst; //iVar13, max of 5
				if (5 < turboMult)
					turboMult = 5;

				int netSpeedStat = (((bestDriverRank->const_AccelSpeed_ClassStat - bestDriverRank->const_Speed_ClassStat) * 0x1000) / 5) - 1; //iVar9

				int additionalVelocity = ((bestDriverRank->const_Speed_ClassStat << 3) / 10) + ((bestDriverWumpaCount * netSpeedStat) / 10 + turboMult * netSpeedStat >> 0xc); //iVar4

				if (0x6900 < additionalVelocity)
					additionalVelocity = 0x6900;

				botVelocity += additionalVelocity;

				if (botVelocity < 0x5dc1)
				{
					if (botVelocity < 0x1c20)
						botVelocity = 0x1c20;
				}
				else
					botVelocity = 24000;
			}

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
					int damagedVelocityPenalty = botDriver->const_DamagedSpeed / 2; //iVar4

					botVelocity -= damagedVelocityPenalty;
				}
			}
			else
			{
				botDriver->botData.unk5bc.ai_turboMeter = 0;

				if (data.characterIDs[botDriver->driverID] == NITROS_OXIDE)
				{
					int damagedVelocityPenalty = botDriver->const_DamagedSpeed / 4; //iVar4

					botVelocity -= damagedVelocityPenalty;
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

			struct Terrain* botTerrain = botDriver->terrainMeta1; //iVar15

			int velSomethingIdk = botDriver->botData.unk5bc.ai_speedLinear - (botDriver->const_PedalFriction_Forward * botTerrain->accel_impact >> 8); //iVar4

			botDriver->botData.unk5bc.ai_speedLinear = velSomethingIdk;

			if (velSomethingIdk < 0)
				botDriver->botData.unk5bc.ai_speedLinear = 0;
			if (0x6900 < botVelocity)
				botVelocity = 0x6900;

			int velocityAccountingForTerrain = botVelocity * botTerrain->unk_0x34[2] >> 8; //iVar4

			if ((botTerrain->unk_0x34[1] & 0x80) == 0)
			{
			LAB_80014b34:
				if (botDriver->botData.unk5bc.ai_speedLinear < velocityAccountingForTerrain)
				{
				LAB_80014b48:
					short accel; //sVar7
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

					botDriver->botData.unk5bc.ai_speedLinear += botVelocity;
				}
			}
			else
			{
				botVelocity = botDriver->botData.unk5bc.ai_speedLinear / 2;

				if (botDriver->botData.unk5bc.ai_speedLinear < velocityAccountingForTerrain) goto LAB_80014b48;

				botDriver->botData.unk5bc.ai_speedLinear = botVelocity;
				if (botVelocity < velocityAccountingForTerrain)
				{
					botDriver->botData.unk5bc.ai_speedLinear = velocityAccountingForTerrain;
					goto LAB_80014b34;
				}
			}

			int levelID = sdata->gGT->levelID; // iVar3

			if ((levelID == HOT_AIR_SKYWAY || levelID == PAPU_PYRAMID) || levelID == POLAR_PASS)
			{
				int botPathIndex = botDriver->botData.botPath; //iVar3

				if (levelID == POLAR_PASS)
				{
					botPathIndex += 3;
				}
				else
				{
					if (levelID == PAPU_PYRAMID)
					{
						botPathIndex += 6;
					}
					else if (levelID == SLIDE_COLISEUM) //what the heck isn't this dead code?
					{
						botPathIndex += 9;
					}
				}

				//why are we casting an address and doing arithmatic on it? as far as I can tell, this is what the original code was doing.
				int wtf = (int)((int)navFrameOfConcern - *(int*)&sdata->NavPath_ptrNavFrameArray[botDriver->botData.botPath]->pos[0]) * 0x33334000 >> 0x10; //iVar15

				if ((data.botsThrottle[botPathIndex] <= wtf && wtf < data.botsThrottle[botPathIndex] + 0xb) && 9000 < botDriver->botData.unk5bc.ai_speedLinear)
				{
					botDriver->botData.unk5bc.ai_turboMeter = 0;

					botDriver->botData.unk5bc.ai_speedLinear -= 100 + botDriver->const_Accel_ClassStat;
				}
			}

			if ((unsigned char)0x80u < navFrameOfConcern->goBackCount)
			{
				velocityAccountingForTerrain += botDriver->unk47E;

				if (botDriver->botData.unk5bc.ai_speedLinear < velocityAccountingForTerrain)
				{
					int sinOfAngle = MATH_Sin(navFrameOfConcern->goBackCount << 4);

					botDriver->botData.unk5bc.ai_speedLinear -= botDriver->const_Gravity * sinOfAngle >> 0xc; //force on a slope due to gravity
				}

				botDriver->fireSpeed = velocityAccountingForTerrain;
			}
		}

		if (0x6400 < botDriver->botData.unk5bc.ai_speedLinear)
		{
			botDriver->botData.unk5bc.ai_speedLinear = 0x6400;
		}

		deltaPosThisFrame = botDriver->botData.unk5bc.ai_speedLinear * elapsedMilliseconds >> 5; //iVar4
		if (deltaPosThisFrame < 0)
		{
			deltaPosThisFrame = 0;
		}
		deltaPosThisFrame += botDriver->botData.unk5a8;
	}
	else
	{
	give_this_label_a_better_name3:
		botInstance->scale[0] = 0xccc;
		botInstance->scale[1] = 0xccc;
		botInstance->scale[2] = 0xccc;

		botDriver->botData.unk5bc.ai_speedLinear = 0;

		if (botDriver->botData.ai_progress_cooldown != 0)
		{
			botDriver->botData.ai_progress_cooldown--;
		}

		deltaPosThisFrame = botDriver->botData.unk5a8;
	}

	int navFrameFlags = navFrameOfConcern->flags; //local_44 idk
	int navFrameSpecialBits = navFrameOfConcern->specialBits; //local_40 idk2
	//local_3c == 0
	if ((navFrameSpecialBits & 0x80) != 0)
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

	int speedY = botDriver->botData.unk5bc.ai_speedY -= (gravity * elapsedMilliseconds >> 5); //iVar3

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
	int iVar15 = deltaPosThisFrame >> 8;
	int iVar3;

	for (iVar3 = navDist; iVar3 <= iVar15; iVar15 -= iVar3)
	{
		navFrameOfConcern = nextNavFrameOfConcern;

		deltaPosThisFrame += iVar3 * -0x100;

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

		navFrameFlags |= navFrameOfConcern->flags;
		navFrameSpecialBits |= navFrameOfConcern->specialBits;

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

		short unk; //sVar7

		if (local_30 == 0 && (0x9e < navFrameOfConcern->rot[3] - 0x31))
		{
			if ((botDriver->actionsFlagSet & 1) == 0)
			{
				unk = navFrameOfConcern->unk[1];
			}
			else
			{
				unk = navFrameOfConcern->unk[0];
			}
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

	botDriver->botData.unk5a8 = deltaPosThisFrame;

	int actionFlagsBuildup = (navFrameFlags & 2) << 10; // uVar20

	botDriver->actionsFlagSet &= 0xfffee7ff;

	if ((navFrameFlags & 0x2000) != 0)
	{
		actionFlagsBuildup |= 0x10000;
	}

	if ((navFrameFlags & 4) != 0)
	{
		actionFlagsBuildup |= 0x1000;
	}

	botDriver->actionsFlagSet = actionFlagsBuildup;

	struct Terrain* terrain = VehAfterColl_GetTerrain((u_char)(navFrameOfConcern->flags >> 3));

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

	if ((navFrameOfConcern->specialBits & 0x30) == 0 && (botThread->modelIndex != DYNAMIC_GHOST))
	{
		int transparency = (navFrameOfConcern->specialBits & 0xf) * 0x9c00;

		botDriver->alphaScaleBackup = ((botDriver->alphaScaleBackup * 100) + transparency >> 8);

		botInstance->alphaScale = ((botInstance->alphaScale * 0x100) + transparency >> 8);
	}

	if ((botDriver->actionsFlagSet & 0x1000) == 0 || (actionFlagsBuildup & 0x1800) == 0)
	{
		botDriver->turbo_MeterRoomLeft = 0;
		botDriver->botData.unk5bc.ai_turboMeter = 0;
		botDriver->botData.unk5bc.ai_fireLevel = 0;
	}
	else
	{
		botDriver->actionsFlagSet |= 0x80;
		botDriver->botData.unk5bc.ai_turboMeter += elapsedMilliseconds;
		int uVar6;
		//this ugly tree of ifs may have been a switch perhaps?
		if ((botDriver->botData.unk5bc.ai_turboMeter < 0xb41) || (5 < botDriver->botData.unk5bc.ai_fireLevel))
		{
			if ((botDriver->botData.unk5bc.ai_turboMeter < 0x961) || (uVar6 = 5, 4 < botDriver->botData.unk5bc.ai_fireLevel))
			{
				if ((botDriver->botData.unk5bc.ai_turboMeter < 0x781) || (3 < botDriver->botData.unk5bc.ai_fireLevel))
				{
					if ((0x5a0 < botDriver->botData.unk5bc.ai_turboMeter) && (uVar6 = 3, botDriver->botData.unk5bc.ai_fireLevel < 3))
						goto LAB_800153d0;
					if ((botDriver->botData.unk5bc.ai_turboMeter < 0x3c1) || (1 < botDriver->botData.unk5bc.ai_fireLevel))
					{
						if ((0x1e0 < botDriver->botData.unk5bc.ai_turboMeter) && (uVar6 = 1, botDriver->botData.unk5bc.ai_fireLevel < 1))
						{
							goto LAB_800153d0;
						}
					}
					else
					{
						//trigger a turbo boost?
						botDriver->botData.unk5bc.ai_fireLevel = 2;
						botDriver->turbo_MeterRoomLeft = 0;

						VehFire_Increment(botDriver, 0xf0, 2, local_38 << 7);
					}
				}
				else
				{
					//trigger a turbo boost?
					botDriver->botData.unk5bc.ai_fireLevel = 4;
					botDriver->turbo_MeterRoomLeft = 0;

					VehFire_Increment(botDriver, 0x1e0, 2, local_38 << 8);
				}
			}
			else
			{
			LAB_800153d0:
				//trigger a turbo boost?
				botDriver->botData.unk5bc.ai_fireLevel = uVar6;
				botDriver->turbo_MeterRoomLeft = 0xa0;
			}
		}
		else
		{
			//trigger a turbo boost?
			botDriver->botData.unk5bc.ai_fireLevel = 6;
			botDriver->turbo_MeterRoomLeft = 0;

			VehFire_Increment(botDriver, 0x2d0, 2, local_38 * 0x180);
		}
	}

	if ((navFrameFlags & 0x100) != 0)
	{
		VehFire_Increment(botDriver, 0x78, 1, 0x900);

		botDriver->botData.botFlags |= 0x10;
	}

	if ((navFrameFlags & 0x1) != 0)
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

	int percentage; //iVar13
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
		//this block of += nonsense may not be 100% correct.
		botDriver->botData.unk5bc.ai_accelAxis[1] = 0;
		botDriver->botData.unk5bc.ai_velAxis[0] += botDriver->botData.unk5bc.ai_accelAxis[0];
		botDriver->botData.unk5bc.ai_velAxis[1] += botDriver->botData.unk5bc.ai_accelAxis[1];
		botDriver->botData.unk5bc.ai_velAxis[2] += botDriver->botData.unk5bc.ai_accelAxis[2];
		int preAccelX = botDriver->botData.unk5bc.ai_accelAxis[0]; //iVar3
		int preAccelZ = botDriver->botData.unk5bc.ai_accelAxis[2]; //iVar15
		botDriver->botData.unk5bc.ai_accelAxis[0] >>= 1;
		botDriver->botData.unk5bc.ai_accelAxis[2] >>= 1;
		botDriver->botData.unk5bc.ai_velAxis[0] += botDriver->botData.unk5bc.ai_accelAxis[0];
		botDriver->botData.unk5bc.ai_velAxis[1] += botDriver->botData.unk5bc.ai_accelAxis[1];
		botDriver->botData.unk5bc.ai_velAxis[2] += botDriver->botData.unk5bc.ai_accelAxis[2];

		botDriver->botData.unk5bc.ai_velAxis[2] += preAccelZ;

		int preX = botDriver->botData.unk5bc.ai_velAxis[0]; //iVar3
		if (preX != 0)
		{
			if (preX < 1)
			{
				botDriver->botData.unk5bc.ai_velAxis[0] = preX + 0x444;
				if (0 < preX + 0x444)
				{
					botDriver->botData.unk5bc.ai_velAxis[0] = 0;
				}
				else
				{
					if (botDriver->botData.unk5bc.ai_accelAxis[0] == 0)
					{
						botDriver->botData.unk5bc.ai_accelAxis[0] = 0x444;
					}
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
		int preZ = botDriver->botData.unk5bc.ai_velAxis[2]; //iVar3
		if (preZ != 0)
		{
			if (preZ < 1)
			{
				botDriver->botData.unk5bc.ai_velAxis[2] = preZ + 0x444;
				if (0 < preZ + 0x444)
				{
					botDriver->botData.unk5bc.ai_velAxis[2] = 0;
				}
				else
				{
					if (botDriver->botData.unk5bc.ai_accelAxis[2] == 0)
					{
						botDriver->botData.unk5bc.ai_accelAxis[2] = 0x444;
					}
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
		botDriver->botData.ai_quadblock_checkpointIndex = navFrameOfConcern->goBackCount;
	}
	else
	{
		int funnyYRotation = (nextNavFrameOfConcern->rot[1] * 0x10) + (navFrameOfConcern->rot[1] * -0x10) & 0xfff; //uVar8
		if (0x7ff < funnyYRotation)
		{
			funnyYRotation -= 0x1000;
		}

		botDriver->botData.ai_rot4[1] = navFrameOfConcern->rot[1] * 0x10 + ((funnyYRotation * percentage) >> 0xc) & 0xfff;

		short top[3];
		top[0] = botDriver->botData.ai_posBackup[0] + botDriver->botData.unk5bc.ai_velAxis[0] >> 8;
		short sVar7 = botDriver->botData.ai_posBackup[1] + botDriver->botData.unk5bc.ai_velAxis[1] >> 8;
		top[1] = sVar7 - 0x100;
		top[2] = botDriver->botData.ai_posBackup[2] + botDriver->botData.unk5bc.ai_velAxis[2] >> 8;

		short bot[3];
		bot[0] = top[0]; //OG code does CONCAT22 for 0/1, but with endianness in mind, I think this is right?
		bot[1] = sVar7 + 0x80;
		bot[2] = top[2];




		/*
		    from my understanding:
			first param: 98 is x, 96 is y, 94 is z
			second param: 92 is padding, 90 is x, 8e is y, 8c is z
		*/

		sps->ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
		sps->Union.QuadBlockColl.qbFlagsWanted = 0x1000;
		sps->Union.QuadBlockColl.qbFlagsIgnored = 0x10;
		sps->Union.QuadBlockColl.searchFlags = 2;

		COLL_SearchBSP_CallbackQUADBLK((u_int*)&top[0], (u_int*)&bot[0], sps, 0);

		if (sps->boolDidTouchQuadblock)
		{
			botDriver->quadBlockHeight = sps->Union.QuadBlockColl.hitPos[1] << 8;

			botDriver->botData.ai_quadblock_checkpointIndex = sps->Set2.ptrQuadblock->checkpointIndex;

			VehPhysForce_RotAxisAngle(&botInstance->matrix, &sps->Set2.normalVec[0], botDriver->botData.ai_rot4[1]);

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
	deltaPosThisFrame >>= 8;
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
					if (botDriver->instSelf->thread->modelIndex == DYNAMIC_PLAYER)
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
						if ((iVar3 == -1) && (deltaPosThisFrame * navFrameOfConcern->unk[0] == -0x80000000))
						{
							trap(0x1800);
						}
#endif
						botDriver->botData.unk5a8 = (deltaPosThisFrame * navFrameOfConcern->unk[0]) / iVar3 << 8;
					}
					short sVar7 = botDriver->jump_LandingBoost;

					if (sVar7 < 0x5a1)
					{
						if (0x3c0 < sVar7)
						{
							deltaPosThisFrame = !!local_38 * 0x60;
						}
						else if (0x280 < sVar7)
						{
							deltaPosThisFrame = 0;
						}
					}
					else
					{
						deltaPosThisFrame = !!local_38 * 0xc0;
					}
					VehFire_Increment(botDriver, 0x2d0, 2, deltaPosThisFrame);
					botDriver->actionsFlagSet |= 2;
				}
				deltaPosThisFrame = botDriver->quadBlockHeight - botDriver->posPrev.y;

				botDriver->botData.ai_posBackup[1] = botDriver->quadBlockHeight;

				botDriver->botData.ai_posBackup[0] = deltaPosThisFrame;

				if ((navFrameFlags & 0x400) != 0 || (botDriver->instTntRecv != NULL))
				{
					int oldActionsFlags = botDriver->actionsFlagSet;

					botDriver->actionsFlagSet |= 0x400;

					botDriver->botData.unk5bc.ai_speedY = deltaPosThisFrame + 0x1400;

					if (botThread->modelIndex == DYNAMIC_PLAYER)
					{
						OtherFX_Play_Echo(8, 1, oldActionsFlags >> 0x10 & 1);
					}
				}
				if (16000 < botDriver->botData.unk5bc.ai_speedY)
				{
					botDriver->botData.unk5bc.ai_speedY = 16000;
				}

				if ((navFrameFlags & 0x1800) == 0)
				{
					botDriver->botData.unk5bc.drift_unk1 = 0;

					botDriver->kartState = KS_NORMAL;
				}
				else
				{
					botDriver->kartState = KS_DRIFTING;

					if ((navFrameFlags & 0x800) == 0)
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
						if ((iVar3 == -1) && (deltaPosThisFrame * navFrameOfConcern->unk[0] == -0x80000000))
						{
							trap(0x1800);
						}
#endif
						botDriver->botData.unk5a8 = (deltaPosThisFrame * navFrameOfConcern->unk[0]) / iVar3 << 8;
					}
				}
				deltaPosThisFrame = -botDriver->botData.unk5bc.ai_speedY >> 1;

				botDriver->botData.unk5bc.ai_speedY = deltaPosThisFrame;

				if (deltaPosThisFrame < 0)
				{
					botDriver->botData.unk5bc.ai_speedY = -deltaPosThisFrame;
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

	int iVar4_lifetime_3 = 0x18;

	if (botDriver->botData.unk5bc.drift_unk1 != 0)
	{
		iVar4_lifetime_3 = 0x60;
	}

	int iVar3_lifetime_2 = botDriver->botData.unk5bc.ai_mulDrift - iVar4_lifetime_3;
	if (botDriver->botData.unk5bc.drift_unk1 < botDriver->botData.unk5bc.ai_mulDrift)
	{
		botDriver->botData.unk5bc.ai_mulDrift = iVar3_lifetime_2;

		if (iVar3_lifetime_2 < botDriver->botData.unk5bc.drift_unk1)
		{
			botDriver->botData.unk5bc.ai_mulDrift = botDriver->botData.unk5bc.drift_unk1;
		}
	}
	else
	{
		iVar4_lifetime_3 += botDriver->botData.unk5bc.ai_mulDrift;

		botDriver->botData.unk5bc.ai_mulDrift = iVar4_lifetime_3;

		if (botDriver->botData.unk5bc.drift_unk1 < iVar4_lifetime_3)
		{
			botDriver->botData.unk5bc.ai_mulDrift = botDriver->botData.unk5bc.drift_unk1;
		}
	}
	botDriver->multDrift = botDriver->botData.unk5bc.ai_mulDrift;

	if ((botDriver->botData.botFlags & 2) != 0)
	{
		char newKartState; //uVar2
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
					newKartState = 3;
					botDriver->kartState = newKartState;
				}
			}
			else
			{
				if (sVar7 == 3)
				{
					int sVar7 = botDriver->botData.unk5bc.ai_squishCooldown; //deref as short
					int iVar4 = botDriver->botData.unk5bc.ai_squishCooldown + -0xc;
					botDriver->botData.unk5bc.ai_squishCooldown = iVar4;
					botDriver->botData.unk5bc.ai_mulDrift += sVar7;
					if (iVar4 < 0x200)
					{
						botDriver->botData.unk5bc.ai_squishCooldown = 0;
						botDriver->botData.unk5bc.ai_mulDrift = 0;
					}
					iVar4 = botDriver->botData.unk5bc.rotXZ - elapsedMilliseconds;
					botDriver->botData.unk5bc.rotXZ = iVar4;
					if (iVar4 * 0x10000 < 1)
					{
						botDriver->botData.unk5bc.ai_speedY = 0x1400;
						botDriver->botData.botFlags &= 0xfffffff9;
						botDriver->actionsFlagSet |= 0x400;
					}
				}
				else
				{
					if (sVar7 == 5)
					{
						struct Thread* plant = botDriver->plantEatingMe;

						struct Instance* plantInst = plant->inst;

						if (botDriver->botData.unk5bc.rotXZ < 0xb40)
						{
							SVECTOR v;
							v.vx = 0xfa;
							if (plant != NULL && (plant->inst != NULL || (v.vx = -0xfa, plant->inst->prev == NULL)))
							{
								v.vx = 0xfa;
							}
							v.vy = 0;
							v.vz = 0x2ee;

							SetRotMatrix(&plantInst->matrix);
							SetTransMatrix(&plantInst->matrix);

							VECTOR v2;
							long l3;

							RotTrans(&v, &v2, &l3);

							sdata->gGT->pushBuffer[botDriver->driverID].pos[0] = v2.vx;
							sdata->gGT->pushBuffer[botDriver->driverID].pos[1] = plantInst->matrix.t[1] + 0xc0;
							sdata->gGT->pushBuffer[botDriver->driverID].pos[2] = v2.vz;

							int camDriverXDelta = v2.vx - plantInst->matrix.t[0];
							int camY = sdata->gGT->pushBuffer[botDriver->driverID].pos[1];
							int driverY = plantInst->matrix.t[1];
							int camDriverZDelta = v2.vz - plantInst->matrix.t[2];

							int rotY = ratan2(camDriverXDelta, camDriverZDelta);
							sdata->gGT->pushBuffer[botDriver->driverID].rot[1] = rotY;

							int rotX = SquareRoot0_stub(camDriverXDelta * camDriverXDelta + camDriverZDelta * camDriverZDelta);
							rotX = ratan2(camY - driverY, rotX);

							sdata->gGT->pushBuffer[botDriver->driverID].rot[0] = 0x800 - rotX;
							sdata->gGT->pushBuffer[botDriver->driverID].rot[2] = 0;
						}

						botDriver->botData.unk5bc.ai_speedLinear = 0;
						int iVar4 = botDriver->botData.unk5bc.rotXZ - elapsedMilliseconds;
						botDriver->botData.unk5bc.rotXZ = iVar4;
						newKartState = 5;
						if (iVar4 * 0x10000 < 1) //what is this condition
						{
							botDriver->botData.botFlags &= 0xfffffff9;
							botInstance->flags &= 0xffffff7f;
							botDriver->botData.ai_progress_cooldown = 1;
							DECOMP_BOTS_MaskGrab(botThread);
							newKartState = 5; //why re-assign it to the same value?
						}
						botDriver->kartState = newKartState;
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
		((navFrameSpecialBits & 0x10) != 0) &&
		(0x1c1f < botDriver->botData.unk5bc.ai_speedLinear || data.characterIDs[botDriver->driverID] == NITROS_OXIDE)
		)
	{
		int iVar4 = (local_3c & 0xf);
		botDriver->botData.unk5bc.ai_speedY = sdata->NavPath_ptrHeader[botDriver->botData.botPath]->rampPhys2[iVar4];
		botDriver->botData.unk5bc.ai_speedLinear = sdata->NavPath_ptrHeader[botDriver->botData.botPath]->rampPhys1[iVar4];

		if (data.characterIDs[botDriver->driverID] == NITROS_OXIDE)
		{
			botDriver->botData.unk5bc.ai_squishCooldown = 0;
			botDriver->botData.unk5bc.ai_mulDrift = 0;
			botDriver->botData.botFlags &= 0xfffffff9;
		}
	}

	if (0x9e < navFrameOfConcern->rot[3] - 0x31 &&
		0x9e < nextNavFrameOfConcern->rot[3] - 0x31)
	{
		if ((botDriver->botData.botFlags & 1) == 0 && (botDriver->actionsFlagSet & 1) != 0)
		{
			//lerped value between two navframes?
			int uVar8 = (nextNavFrameOfConcern->rot[0] * 0x10) + (navFrameOfConcern->rot[0] * -0x10 & 0xffff);
			if (0x7ff < uVar8)
			{
				uVar8 -= 0x1000;
			}

			botDriver->botData.ai_rot4[0] = navFrameOfConcern->rot[0] * 0x10 + ((uVar8 * percentage) >> 0xc) & 0xfff;

			//lerped value between two navframes?
			uVar8 = (nextNavFrameOfConcern->rot[2] * 0x10) + (navFrameOfConcern->rot[2] * -0x10 & 0xffff);
			if (0x7ff < uVar8)
			{
				uVar8 -= 0x1000;
			}

			botDriver->botData.ai_rot4[2] = navFrameOfConcern->rot[2] * 0x10 + ((uVar8 * percentage) >> 0xc) & 0xfff;
		}

		//lerped value between two navframes?
		int other_uVar8 = nextNavFrameOfConcern->rot[1] * 0x10 + navFrameOfConcern->rot[1] * -0x10 & 0xfff;
		if (0x7ff < other_uVar8)
		{
			other_uVar8 -= 0x1000;
		}

		botDriver->botData.ai_rot4[1] = navFrameOfConcern->rot[1] * 0x10 + ((other_uVar8 * percentage) >> 0xc) & 0xfff;

		if ((botDriver->botData.botFlags & 1) != 0)
		{
			other_uVar8 = 0;
		}

		other_uVar8 = other_uVar8 * 2 - botDriver->turnAngleCurr & 0xfff;

		bool bVar1 = other_uVar8 < 0x21;
		if (0x7ff < other_uVar8)
		{
			other_uVar8 -= 0x1000;
			bVar1 = other_uVar8 < 0x21;
		}
		if (bVar1)
		{
			if (other_uVar8 < -0x20)
			{
				other_uVar8 = 0xffffffe0;
			}
		}
		else
		{
			other_uVar8 = 0x20;
		}
		other_uVar8 += botDriver->turnAngleCurr;
		botDriver->turnAngleCurr = other_uVar8;

		short sVar7;
		if (botDriver->botData.unk5bc.drift_unk1 == 0)
		{
			other_uVar8 &= 0xfff;
			sVar7 = other_uVar8;
			botDriver->botData.unk5bc.ai_simpTurnState = sVar7;
			if (0x7ff < other_uVar8)
			{
				botDriver->botData.unk5bc.ai_simpTurnState = sVar7 - 0x1000;
			}
			sVar7 = botDriver->botData.unk5bc.ai_simpTurnState >> 2;
		}
		else
		{
			int uVar11 = -botDriver->botData.unk5bc.ai_mulDrift & 0xfff;

			botDriver->botData.unk5bc.ai_simpTurnState = uVar11;
			if (0x7ff < uVar11)
			{
				botDriver->botData.unk5bc.ai_simpTurnState = uVar11 - 0x1000;
			}

			sVar7 = botDriver->botData.unk5bc.ai_simpTurnState >> 3;
		}
		botDriver->botData.unk5bc.ai_simpTurnState = sVar7;

		other_uVar8 = botDriver->botData.unk5bc.ai_simpTurnState - botDriver->wheelRotation & 0xfff;
		bool other_bVar1 = other_uVar8 < 0x21;

		if (0x7ff < other_uVar8)
		{
			other_uVar8 -= 0x1000;
			other_bVar1 = other_uVar8 < 0x21;
		}
		sVar7 = other_uVar8;
		if (other_bVar1)
		{
			if (other_uVar8 < -0x20)
			{
				sVar7 = -0x20;
			}
		}
		else
		{
			sVar7 = 0x20;
		}

		botDriver->wheelRotation += sVar7;
		botDriver->simpTurnState = botDriver->botData.unk5bc.ai_simpTurnState;
	}

	botDriver->rotCurr.x = botDriver->botData.ai_rot4[0];
	botDriver->rotCurr.y = botDriver->botData.ai_rot4[1];
	botDriver->rotCurr.z = botDriver->botData.ai_rot4[2];

	int badnessRecieveTimer = botDriver->clockReceive; //iVar4

	if (badnessRecieveTimer == 0)
	{
		badnessRecieveTimer = botDriver->squishTimer;
		if (badnessRecieveTimer == 0)
		{
			if (botDriver->thCloud != NULL)
			{
				badnessRecieveTimer = sdata->gGT->timer << 2;

				goto badEffectKartWiggle;
			}
		}
	}
	else
	{
	badEffectKartWiggle:
		int y = MATH_Sin(badnessRecieveTimer * 0xc);
		int x = MATH_Cos(badnessRecieveTimer * 0xc);

		//some GTE stuff TODO

		int uVar16 = 0, uVar12 = 0, uVar14 = 0; //no wiggle for now

		botDriver->botData.unk5bc.ai_turboMeter = 0;

		botDriver->rotCurr.x += uVar16;
		botDriver->rotCurr.z += uVar14;
		botDriver->rotCurr.y += uVar12;
	}

	if ((botDriver->botData.botFlags & 9) == 0)
	{
		short rot[3];
		rot[0] = navFrameOfConcern->rot[0] << 4;
		rot[1] = navFrameOfConcern->rot[1] << 4;
		rot[2] = navFrameOfConcern->rot[2] << 4;

		MATRIX m;

		ConvertRotToMatrix(&m, rot);

		botDriver->AxisAngle3_normalVec[0] = m.m[0][0];
		botDriver->AxisAngle3_normalVec[1] = m.m[0][1];
		botDriver->AxisAngle3_normalVec[2] = m.m[1][1];

		botInstance->bitCompressed_NormalVector_AndDriverIndex = (m.m[0][0] >> 6) & 0xff | m.m[0][1] & 0x3fc0 << 2 | ((m.m[1][1] >> 6) & 0xff) << 0x10 | (botDriver->driverID + 1) * 0x1000000;
	}

	ConvertRotToMatrix(&botInstance->matrix, &botDriver->rotCurr.x);

	//c is row-major (i.e., ticking the rightmost indeces has smaller memory address delta vs ticking the leftmost indeces)
	botDriver->AxisAngle2_normalVec[0] = botInstance->matrix.m[0][1];
	botDriver->AxisAngle2_normalVec[1] = botInstance->matrix.m[1][1];
	int uVar6 = botInstance->matrix.m[2][1];
	botDriver->angle = botDriver->rotCurr.y;

	botDriver->speedApprox = botDriver->botData.unk5bc.ai_speedLinear;

	botDriver->speed = botDriver->botData.unk5bc.ai_speedLinear;
	botDriver->jumpHeightPrev = botDriver->jumpHeightCurr;
	botDriver->axisRotationX = botDriver->botData.ai_rot4[1] & 0xfff;
	botDriver->AxisAngle2_normalVec[2] = uVar6;

	int iVar4_lifetime_2 = MATH_Cos(navFrameOfConcern->rot[3]);

	//bruh the jump is sinosuidal and not parabolic???
	botDriver->jumpHeightCurr = botDriver->botData.unk5bc.ai_speedY * iVar4_lifetime_2 >> 0xc;

	iVar4_lifetime_2 = MATH_Cos(botDriver->axisRotationX);

	botDriver->zSpeed = botDriver->botData.unk5bc.ai_speedLinear * iVar4_lifetime_2 >> 0xc;

	iVar4_lifetime_2 = MATH_Sin(botDriver->axisRotationX);

	int uVar11 = botDriver->rotCurr.z & 0xfff;

	botDriver->ySpeed = botDriver->botData.unk5bc.ai_speedY;
	botDriver->rotCurr.z = uVar11;

	botDriver->xSpeed = botDriver->botData.unk5bc.ai_speedLinear * iVar4_lifetime_2 >> 0xc;
	if (0x7ff < uVar11)
	{
		botDriver->rotCurr.z = uVar11 - 0x1000;
	}
	botDriver->rotCurr.y += botDriver->botData.unk5bc.ai_mulDrift + botDriver->turnAngleCurr;

	botDriver->posCurr.x = botDriver->botData.unk5bc.ai_velAxis[0] + botDriver->botData.ai_posBackup[0];
	botDriver->posCurr.y = botDriver->botData.unk5bc.ai_velAxis[1] + botDriver->botData.ai_posBackup[1];
	botDriver->posCurr.z = botDriver->botData.unk5bc.ai_velAxis[2] + botDriver->botData.ai_posBackup[2];

	botInstance->matrix.t[0] = botDriver->posCurr.x >> 8;
	botInstance->matrix.t[1] = botDriver->posCurr.y >> 8 + botDriver->Screen_OffsetY;
	botInstance->matrix.t[2] = botDriver->posCurr.z >> 8;

	badnessRecieveTimer = botDriver->clockReceive;

	if (badnessRecieveTimer == 0)
	{
		badnessRecieveTimer = botDriver->squishTimer;
		if (badnessRecieveTimer == 0)
		{
			if (0x100 < botDriver->speedApprox)
			{
				botDriver->hazardTimer -= elapsedMilliseconds;
			}

			int uVar11 = botDriver->hazardTimer & 0xfffe;
			botDriver->hazardTimer = uVar11;

			if (-1 < (uVar11 << 0x10))
			{
				botDriver->hazardTimer = 0xfffe;
			}
			goto LAB_8001686c;
		}
	}

	if ((botDriver->actionsFlagSet & 1) == 0)
	{
		int iVar4 = botDriver->speedApprox;
		if (iVar4 < 0)
		{
			iVar4 = -iVar4;
		}

		if (iVar4 < 0x101)
		{
			goto LAB_800167fc;
		}

		if (badnessRecieveTimer < 0)
		{
			badnessRecieveTimer = -badnessRecieveTimer;
		}
	LAB_8001680c:
		botDriver->hazardTimer = -badnessRecieveTimer;
	}
	else
	{
		int iVar4 = botDriver->speedApprox;

		if (iVar4 < 0)
		{
			iVar4 = -iVar4;
		}

		if (iVar4 < 0x101)
		{
		LAB_800167fc:
			badnessRecieveTimer = botDriver->hazardTimer;
			if (0 < badnessRecieveTimer)
			{
				goto LAB_8001680c;
			}
		}
		else
		{
			if (badnessRecieveTimer < 0)
			{
				badnessRecieveTimer = -badnessRecieveTimer;
			}
			botDriver->hazardTimer = badnessRecieveTimer;
		}
	}

	botDriver->hazardTimer |= 1; //increment it by 1 if even.

LAB_8001686c:

	if ((navFrameSpecialBits & 0x40) != 0 || (botDriver->botData.botFlags & 9) != 0)
	{
		DECOMP_BOTS_LevInstColl(botThread);
	}

	if ((navFrameFlags & 0x8000) != 0)
	{
		botInstance->flags |= 0x2000;
	}

	VehPhysForce_TranslateMatrix(botThread, botDriver);

	VehPhysForce_RotAxisAngle(&botDriver->matrixMovingDir, &botDriver->AxisAngle2_normalVec[0], botDriver->angle);

	VehFrameProc_Driving(botThread, botDriver);

	if ((botDriver->botData.botFlags & 2) != 0 && botDriver->botData.unk5ba == 2)
	{
		short rot[3];
		rot[0] = (*(short*)&botDriver->botData.unk5bc.rotXZ) << 8;
		rot[2] = 0;
		rot[1] = (*(short*)&botDriver->botData.unk5bc.rotXZ * 0xe0);

		ConvertRotToMatrix(&sdata->rotXZ, &rot[0]);

		MATH_MatrixMul(&sdata->rotXYZ, &botInstance->matrix, (VECTOR*)&sdata->rotXZ);

		MATH_MatrixMul(&botInstance->matrix, &sdata->rotXYZ, (VECTOR*)&sdata->arcadeDiff);

		//MATRIX is only 30 bytes, but is 32 because there's 2 bytes of padding (at the end?) this additional data is stored there?
		(*(int*)(((char*)botInstance) + 0x48)) += 0x20;
	}

	if ((botDriver->botData.botFlags & 4) == 0)
	{
		VehEmitter_DriverMain(botThread, botDriver);
	}

	if (botInstance->thread->modelIndex == DYNAMIC_PLAYER) //why doesn't the original code just use botThread???
	{
		EngineSound_Player(botDriver);
	}

	short camRot = botDriver->angle - (botDriver->botData.ai_rotY_608 & 0xfff);

	botDriver->rotCurr.w = -camRot;

	if (0x7ff < camRot) {
		camRot |= 0xf000;
	}

	botDriver->botData.ai_rotY_608 += (camRot >> 3) & 0xfff;

	if (botThread->modelIndex == DYNAMIC_PLAYER)
	{
		short posTop[3];
		short posBot[3];

		posTop[0] = (short)((botDriver->botData.ai_posBackup[0] + botDriver->botData.unk5bc.ai_velAxis[0]) >> 8);
		posBot[1] = (short)((botDriver->botData.ai_posBackup[1] + botDriver->botData.unk5bc.ai_velAxis[1]) >> 8);
		posTop[1] = posBot[1] - 0x100;
		posBot[1] += 0x40;
		posTop[2] = (short)((botDriver->botData.ai_posBackup[2] + botDriver->botData.unk5bc.ai_velAxis[2]) >> 8);
		posBot[0] = posTop[0];
		posBot[2] = posTop[2];

		sps->ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
		sps->Union.QuadBlockColl.qbFlagsWanted = 0x1000;
		sps->Union.QuadBlockColl.qbFlagsIgnored = 0;
		sps->Union.QuadBlockColl.searchFlags = 2;

		COLL_SearchBSP_CallbackQUADBLK((u_int*)&posTop[0], (u_int*)&posBot[0], sps, 0);

		if (sps->boolDidTouchQuadblock)
		{
			botDriver->underDriver = sps->Set2.ptrQuadblock;
		}
	}
}