#include <common.h>

typedef void (*whateverThisIs)(struct Thread* thread, struct Driver* driver);

void DECOMP_MainFrame_GameLogic(struct GameTracker* gGT2, struct GamepadSystem* gGamepads2)
{
	char bVar1;
	short sVar2;
	u_int uVar3;
	int iVar4;
	whateverThisIs pcVar5;
	u_int uVar5;
	u_int uVar6;
	int* piVar7;
	struct Driver* pvVar9;
	struct Driver* psVar8;
	struct Driver* psVar9;
	struct Driver* psVar10;
	struct Driver* pvVar12;
	struct TileView* tileView;
	int iVar11;
	struct Thread* psVar12;
	int iVar13;
	int iVar14;
	struct GameTracker* gGT3;
	struct GamepadSystem* gGamepads3;
	
	bVar1 = true;
	if ((gGT2->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
	{
		bVar1 = false;
		tileView = sdata->gGT->tileView;
		for(psVar12 = sdata->gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
		{
			pvVar12 = (struct Driver*)psVar12->object;
			if (pvVar12->clockSend)
			{
				pvVar12->clockSend += 0xff;
			}
			uVar3 = (u_int)*(u_char*)((u_int)&pvVar12->forcedJump_trampoline + 1);
			if (uVar3 == 0)
			{
				if (pvVar12->clockReceive == 0)
				{
					uVar3 = (u_int)pvVar12->clockSend;
					if (uVar3 == 0)
					{
						if ((sdata->gGT->clockEffectEnabled & 1) == 0) goto LAB_80034e74;
						uVar3 = 10000;
					}
				}
				else
				{
					if ((pvVar12->actionsFlagSet & 0x2000000) != 0)
					{
						pvVar12->clockReceive = 0;
					}
					uVar3 = (u_int)pvVar12->clockReceive;
				}
				DISPLAY_Blur_Main(tileView, uVar3);
			}
			else
			{
				DISPLAY_Blur_Main(tileView, -uVar3);
				*(char*)((u_int)&pvVar12->forcedJump_trampoline + 1) = *(char*)((u_int)&pvVar12->forcedJump_trampoline + 1) - 1;
			}
LAB_80034e74:
			tileView = tileView + 1;
		}
		gGT2->timer = gGT2->timer + 1;
		gGT3 = sdata->gGT;
		gGT2->framesInThisLEV = gGT2->framesInThisLEV + 1;
		gGT3->unk1cc4[4] = 0;
		iVar4 = RCNT_GetTime_Elapsed(gGT2->anotherTimer, &gGT2->anotherTimer);
		iVar4 = (iVar4 << 5) / 100;
		gGT2->elapsedTimeMS = iVar4;
		if (iVar4 < 0)
		{
			gGT2->elapsedTimeMS = 0x20;
		}
		if (0x40 < gGT2->elapsedTimeMS)
		{
			gGT2->elapsedTimeMS = 0x40;
		}
		if ((sdata->gGT->gameMode1_prevFrame & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) != 0)
		{
			gGT2->elapsedTimeMS = 0x20;
		}
		gGT2->BoxSceneTimer += gGT2->elapsedTimeMS;
		gGT3 = sdata->gGT;
		if (gGT2->trafficLightsTimer < 1)
		{
			if ((sdata->gGT->gameMode1 & PAUSE_THREADS) == 0)
			{
				if (gGT2->frozenTimeRemaining < 1)
				{
					if ((sdata->gGT->gameMode1 & END_OF_RACE) == 0)
					{
						gGT2->elapsedEventTime += gGT2->elapsedTimeMS;
					}
				}
				else
				{
					iVar4 = gGT2->frozenTimeRemaining - gGT2->elapsedTimeMS;
					gGT2->frozenTimeRemaining = iVar4;
					if (iVar4 < 0)
					{
						gGT2->frozenTimeRemaining = 0;
					}
					else
					{
						uVar3 = gGT3->timer;
						if (uVar3 == (uVar3 / 6) * 6)
						{
							if (uVar3 == (uVar3 / 0xc) * 0xc)
							{
								OtherFX_Play_LowLevel(0x40, '\0', 0x8c9080);
							}
							else
							{
								OtherFX_Play_LowLevel(0x40, '\0', 0x8c8880);
							}
						}
					}
				}
			}
		}
		else
		{
			gGT2->elapsedEventTime = 0;
		}
		CTR_CycleTex_AllModels(-1, (struct Model*)sdata->PLYROBJECTLIST, gGT2->timer);
		CTR_CycleTex_AllModels(gGT2->level1->numModels, (struct Model*)gGT2->level1->ptrModelsPtrArray, gGT2->timer);
		psVar8 = 0;
		psVar9 = 0;
		for(psVar12 = sdata->gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
		{
			pvVar9 = (struct Driver*)psVar12->object;
			psVar10 = psVar9;
			if (pvVar9->driverID == 0)
			{
LAB_80035098:
				psVar8 = pvVar9;
				psVar9 = psVar10;
			}
			else
			{
				if (pvVar9->driverID == 1)
				{
					psVar9 = pvVar9;
				}
				psVar10 = psVar8;
				if ((u_char)pvVar9->numTimesAttacking < (u_char)psVar8->numTimesAttacking) goto LAB_80035098;
			}
		}
		if
		(
			((psVar8 != 0) && (psVar9 != 0)) &&
			(
				iVar4 = (u_int)(u_char)psVar9->numTimesAttacking - (u_int)(u_char)psVar8->numTimesAttacking, 
				*(short*)(psVar8->unk_4F0_4F8 + 2) < iVar4
			)
		)
		{
			*(short*)(psVar8->unk_4F0_4F8 + 2) = (short)iVar4;
		}
		iVar14 = 0;
		iVar4 = 0;
		iVar13 = 0x1b2c;
		gGT3 = gGT2;
		do
		{
			piVar7 = (int*)((u_int)gGT2->db[0].drawEnv.ofs + iVar13 - 0x20);
			if ((((sdata->gGT->gameMode1 & PAUSE_THREADS) == 0) || ((piVar7[3] & 1U) != 0)) && (*piVar7 != 0))
			{
				if (iVar4 == 0)
				{
					for(psVar12 = sdata->gGT->threadBuckets[PLAYER].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
					{
						Weapon_Shoot_OnCirclePress((struct Driver*)psVar12->object);
					}
					for(iVar11 = 0; iVar11 < 13; iVar11++)
					{
						for(psVar12 = sdata->gGT->threadBuckets[PLAYER].thread; psVar12 != 0; psVar12 = psVar12->childThread)
						{
							if
							(
								(psVar12->funcThTick == 0) &&
								(
									pcVar5 = ((struct Driver*)psVar12->object)->funcPtrs[iVar11], 
									pcVar5 != 0
								)
							)
							{
								pcVar5(psVar12, (struct Driver*)psVar12->object);
							}
							psVar12 = psVar12->siblingThread;
						}
					}
				}
				ThreadBucketTickAll(gGT3->threadBuckets[0].thread);
			}
			gGT3 = (struct GameTracker*)&gGT3->frontBuffer;
			iVar14 = iVar14 + 0x14;
			iVar4 = iVar4 + 1;
			iVar13 = iVar13 + 0x14;
		} while (iVar4 < 17);
		BOTS_UpdateGlobals();
		GhostBuffer_RecordStats(0);
		sdata->gGT->unk1cc4[4] = (u_int)(sdata->gGT->unk1cc4[4] * 10000) / 0x147e;
		Particle_UpdateAllParticles();
	}
	else
	{
		psVar12 = gGT2->threadBuckets[AKUAKU].thread;
		if (psVar12 != 0)
		{
			ThreadBucketTickAll(psVar12);
		}
	}
	uVar5 = LOAD_IsOpen_RacingOrBattle();
	if (uVar5 != 0)
	{
		if ((sdata->gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
		{
			RB_Bubbles_RoosTubes();
		}
		if (sdata->gGT->threadBuckets[BURST].thread != 0)
		{
			RB_Burst_DrawAll(sdata->gGT);
		}
	}
	THREAD_CheckAllForDead();
	if ((sdata->gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
	{
		Audio_Update1();
	}
	gGamepads3 = sdata->gGamepads;
	gGT2->gameMode1_prevFrame = gGT2->gameMode1;
	uVar5 = GAMEPAD_GetNumConnected(gGamepads3);
	uVar3 = sdata->gGT->gameMode1;
	if ((uVar3 & END_OF_RACE) == 0)
	{
		if ((bVar1) || ((gGT2->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) != 0))
		{
			if (sdata->gGT->cooldownfromPauseUntilUnpause == '\0')
			{
				if
				(
					(
						(sdata->ptrActiveMenuBox != &data.menuBox_optionsMenu_racingWheel) &&
						(sdata->ptrActiveMenuBox != (struct MenuBox*)0x800b518c)
					) &&
					((sdata->AnyPlayerTap & 0x1000) != 0)
				)
				{
					MenuBox_ClearInput();
					sdata->gGT->gameMode1 = sdata->gGT->gameMode1 & (0xffffffff ^ PAUSE_1);
					MainFrame_TogglePauseAudio(0);
					OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate(sdata->gGT);
					MenuBox_Hide(sdata->ptrActiveMenuBox);
					sdata->gGT->cooldownFromUnpauseUntilPause = 5;
				}
			}
			else
			{
				sdata->gGT->cooldownfromPauseUntilUnpause--;
			}
		}
		else if (sdata->gGT->cooldownFromUnpauseUntilPause == 0)
		{
			if
			(
				(((uVar3 & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0) && (sdata->ptrActiveMenuBox == 0)) &&
				(
					(
						sdata->AkuAkuHintState == 0 &&
						(
							(
								uVar6 = TitleFlag_IsFullyOnScreen(), uVar6 == 0 &&
								(iVar4 = 0, gGT2->numPlyrCurrGame != 0)
					 		)
						)
					)
				)
			)
			{
				do
				{
					if
					(
						(
							(
								(uVar5 != 0) &&
								(
									(
										uVar3 = MainFrame_HaveAllPads((u_short)(u_char)sdata->gGT->numPlyrNextGame),
										(uVar3 & 0xffff) == 0 && ((gGT2->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
									)
								)
							) ||
							((gGamepads2->gamepad[0].buttonsTapped & 0x1000U) != 0)
						) &&
						(sdata->gGT->overlayIndex_Threads != -1)
					)
					{
						sdata->gGT->unknownFlags_1d44 = sdata->gGT->gameMode1 & 0x3e0020U | PAUSE_1;
						MainFreeze_IfPressStart();
						sdata->gGT->cooldownfromPauseUntilUnpause = 5;
					}
					iVar4 = iVar4 + 1;
					gGamepads2 = (struct GamepadSystem*)(gGamepads2->gamepad + 1);
				} while (iVar4 < (int)(u_int)(u_char)gGT2->numPlyrCurrGame);
			}
		}
		else
		{
			sdata->gGT->cooldownFromUnpauseUntilPause--;
		}
	}
	else if (sdata->gGT->timerEndOfRaceVS == 0)
	{
		uVar3 = sdata->gGT->unknownFlags_1d44;
		if ((uVar3 & AKU_SONG) == 0)
		{
			if ((uVar3 & CRYSTAL_CHALLENGE) == 0)
			{
				if (sdata->gGT->unk_timerCooldown_similarTo_1d36 == 0)
				{
					return;
				}
			}
			else if (sdata->gGT->unk_timerCooldown_similarTo_1d36 == 0)
			{
				if ((uVar3 & PAUSE_2) == 0)
				{
					return;
				}
				sVar2 = TitleOSK_DrawMenu(0x140);
				if (sVar2 == 0)
				{
					return;
				}
				if (sVar2 == 1)
				{
					*(u_short*)&sdata->unk_saveGame_related = 0;
					LoadSave_ToggleMode(0x41);
					MenuBox_Show(&data.menuBox_warning2);
					sdata->gGT->unknownFlags_1d44 |= AKU_SONG;
					return;
				}
				sdata->gGT->newHighScoreIndex = -1;
				sdata->gGT->unknownFlags_1d44 &= 0xf3ffffff;
				return;
			}
			sdata->gGT->unk_timerCooldown_similarTo_1d36--;
		}
	}
	else if ((uVar3 & ARCADE_MODE) == 0)
	{
		if (sdata->gGT->timerEndOfRaceVS < 0x96)
		{
			UI_VsQuipDrawAll();
			UI_VsWaitForPressX();
		}
		if (0x1e < sdata->gGT->timerEndOfRaceVS)
		{
			sdata->gGT->timerEndOfRaceVS--;
		}
	}
	else
	{
		sdata->gGT->timerEndOfRaceVS = 0;
	}
	return;
}