#include <common.h>

typedef void (*VehicleFuncPtr)(struct Thread* thread, struct Driver* driver);

void DECOMP_MainFrame_GameLogic(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	char bVar1;
	short sVar2;
	u_int uVar3;
	int iVar4;
	VehicleFuncPtr pcVar5;
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
	
	bVar1 = true;
	if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
	{
		bVar1 = false;
		tileView = gGT->tileView;
		for(psVar12 = gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
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
						if ((gGT->clockEffectEnabled & 1) == 0) goto LAB_80034e74;
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
		gGT->timer = gGT->timer + 1;
		gGT->framesInThisLEV = gGT->framesInThisLEV + 1;
		gGT->unk1cc4[4] = 0;
		iVar4 = RCNT_GetTime_Elapsed(gGT->anotherTimer, &gGT->anotherTimer);
		iVar4 = (iVar4 << 5) / 100;
		gGT->elapsedTimeMS = iVar4;
		if (iVar4 < 0)
		{
			gGT->elapsedTimeMS = 0x20;
		}
		if (0x40 < gGT->elapsedTimeMS)
		{
			gGT->elapsedTimeMS = 0x40;
		}
		if ((gGT->gameMode1_prevFrame & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) != 0)
		{
			gGT->elapsedTimeMS = 0x20;
		}
		gGT->BoxSceneTimer += gGT->elapsedTimeMS;
		if (gGT->trafficLightsTimer < 1)
		{
			if ((gGT->gameMode1 & PAUSE_THREADS) == 0)
			{
				if (gGT->frozenTimeRemaining < 1)
				{
					if ((gGT->gameMode1 & END_OF_RACE) == 0)
					{
						gGT->elapsedEventTime += gGT->elapsedTimeMS;
					}
				}
				else
				{
					iVar4 = gGT->frozenTimeRemaining - gGT->elapsedTimeMS;
					gGT->frozenTimeRemaining = iVar4;
					if (iVar4 < 0)
					{
						gGT->frozenTimeRemaining = 0;
					}
					else
					{
						uVar3 = gGT->timer;
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
			gGT->elapsedEventTime = 0;
		}
		CTR_CycleTex_AllModels(-1, (struct Model*)sdata->PLYROBJECTLIST, gGT->timer);
		CTR_CycleTex_AllModels(gGT->level1->numModels, (struct Model*)gGT->level1->ptrModelsPtrArray, gGT->timer);
		psVar8 = 0;
		psVar9 = 0;
		for(psVar12 = gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
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
		for (iVar4 = 0; iVar4 < 17; iVar4++)
		{
			if
			(
				(
					// if threads are not paused
					((gGT->gameMode1 & PAUSE_THREADS) == 0) || 
					
					// if bucket can not be paused
					((gGT->threadBuckets[PLAYER].boolCantPause & 1U) != 0)
				) && 
				
				// if threads exist
				(gGT->threadBuckets[PLAYER].thread != 0)
			)
			{
				if (iVar4 == 0)
				{
					for(psVar12 = gGT->threadBuckets[PLAYER].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
					{
						Weapon_Shoot_OnCirclePress((struct Driver*)psVar12->object);
					}
					for(iVar11 = 0; iVar11 < 13; iVar11++)
					{
						for(psVar12 = gGT->threadBuckets[PLAYER].thread; psVar12 != 0; psVar12 = psVar12->childThread)
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
				
				ThTick_RunBucket(gGT->threadBuckets[iVar4].thread);
			}
		}
		BOTS_UpdateGlobals();
		GhostBuffer_RecordStats(0);
		gGT->unk1cc4[4] = (u_int)(gGT->unk1cc4[4] * 10000) / 0x147e;
		Particle_UpdateAllParticles();
	}
	else
	{
		psVar12 = gGT->threadBuckets[AKUAKU].thread;
		if (psVar12 != 0)
		{
			ThTick_RunBucket(psVar12);
		}
	}
	uVar5 = LOAD_IsOpen_RacingOrBattle();
	if (uVar5 != 0)
	{
		if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
		{
			RB_Bubbles_RoosTubes();
		}
		if (gGT->threadBuckets[BURST].thread != 0)
		{
			RB_Burst_DrawAll(gGT);
		}
	}
	THREAD_CheckAllForDead();
	if ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
	{
		Audio_Update1();
	}
	
	gGT->gameMode1_prevFrame = gGT->gameMode1;
	uVar5 = GAMEPAD_GetNumConnected(gGamepads);
	uVar3 = gGT->gameMode1;
	if ((uVar3 & END_OF_RACE) == 0)
	{
		if ((bVar1) || ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) != 0))
		{
			if (gGT->cooldownfromPauseUntilUnpause == '\0')
			{
				if
				(
					(
						(sdata->ptrActiveMenuBox != &data.menuBox_optionsMenu_racingWheel) &&
						(sdata->ptrActiveMenuBox != (struct MenuBox*)0x800b518c)
					) &&
					((sdata->AnyPlayerTap & BTN_START) != 0)
				)
				{
					MenuBox_ClearInput();
					gGT->gameMode1 = gGT->gameMode1 & ~PAUSE_1;
					MainFrame_TogglePauseAudio(0);
					OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate(gGT);
					MenuBox_Hide(sdata->ptrActiveMenuBox);
					gGT->cooldownFromUnpauseUntilPause = 5;
				}
			}
			else
			{
				gGT->cooldownfromPauseUntilUnpause--;
			}
		}
		else if (gGT->cooldownFromUnpauseUntilPause == 0)
		{
			if
			(
				(((uVar3 & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0) && (sdata->ptrActiveMenuBox == 0)) &&
				(
					(
						sdata->AkuAkuHintState == 0 &&
						(
							(
								uVar6 = TitleFlag_IsFullyOnScreen(), uVar6 == 0
					 		)
						)
					)
				)
			)
			{
				for(iVar4 = 0; iVar4 <  gGT->numPlyrCurrGame; iVar4++)
				{
					if
					(
						(
							(
								(uVar5 != 0) &&
								(
									(
										uVar3 = MainFrame_HaveAllPads((u_short)(u_char)gGT->numPlyrNextGame),
										(uVar3 & 0xffff) == 0 && ((gGT->gameMode1 & (PAUSE_1 | PAUSE_2 | PAUSE_3 | PAUSE_4)) == 0)
									)
								)
							) ||
							((gGamepads->gamepad[iVar4].buttonsTapped & BTN_START) != 0)
						) &&
						(gGT->overlayIndex_Threads != -1)
					)
					{
						gGT->unknownFlags_1d44 = gGT->gameMode1 & 0x3e0020U | PAUSE_1;
						MainFreeze_IfPressStart();
						gGT->cooldownfromPauseUntilUnpause = 5;
					}
					iVar4 = iVar4 + 1;
				}
			}
		}
		else
		{
			gGT->cooldownFromUnpauseUntilPause--;
		}
	}
	else if (gGT->timerEndOfRaceVS == 0)
	{
		uVar3 = gGT->unknownFlags_1d44;
		if ((uVar3 & AKU_SONG) == 0)
		{
			if ((uVar3 & CRYSTAL_CHALLENGE) == 0)
			{
				if (gGT->unk_timerCooldown_similarTo_1d36 == 0)
				{
					return;
				}
			}
			else if (gGT->unk_timerCooldown_similarTo_1d36 == 0)
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
					gGT->unknownFlags_1d44 |= AKU_SONG;
					return;
				}
				gGT->newHighScoreIndex = -1;
				gGT->unknownFlags_1d44 &= ~(RELIC_RACE | CRYSTAL_CHALLENGE);
				return;
			}
			gGT->unk_timerCooldown_similarTo_1d36--;
		}
	}
	else if ((uVar3 & ARCADE_MODE) == 0)
	{
		if (gGT->timerEndOfRaceVS < 0x96)
		{
			UI_VsQuipDrawAll();
			UI_VsWaitForPressX();
		}
		if (0x1e < gGT->timerEndOfRaceVS)
		{
			gGT->timerEndOfRaceVS--;
		}
	}
	else
	{
		gGT->timerEndOfRaceVS = 0;
	}
	return;
}