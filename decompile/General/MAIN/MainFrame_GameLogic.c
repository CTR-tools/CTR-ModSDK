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
	struct Driver* psVar8;
	struct Driver* psVar9;
	struct Driver* psVar10;
	struct Driver* pvVar12;
	struct TileView* tileView;
	int iVar11;
	struct Thread* psVar12;
	
	bVar1 = true;
	if ((gGT->gameMode1 & PAUSE_ALL) == 0)
	{
		bVar1 = false;
		tileView = gGT->tileView;
		for(psVar12 = gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
		{
			psVar9 = (struct Driver*)psVar12->object;
			if (psVar9->clockSend)
			{
				psVar9->clockSend--;
			}
			uVar3 = psVar9->unk367;
			if (uVar3 == 0)
			{
				if (psVar9->clockReceive == 0)
				{
					uVar3 = (u_int)psVar9->clockSend;
					if (uVar3 == 0)
					{
						if ((gGT->clockEffectEnabled & 1) == 0) goto LAB_80034e74;
						uVar3 = 10000;
					}
				}
				else
				{
					if ((psVar9->actionsFlagSet & 0x2000000) != 0)
					{
						psVar9->clockReceive = 0;
					}
					uVar3 = (u_int)psVar9->clockReceive;
				}

#ifndef REBUILD_PS1
				DISPLAY_Blur_Main(tileView, uVar3);
#endif
			}
			else
			{
#ifndef REBUILD_PS1
				DISPLAY_Blur_Main(tileView, -uVar3);
#endif
				psVar9->unk367--;
			}
LAB_80034e74:
			tileView = tileView + 1;
		}
		gGT->timer = gGT->timer + 1;
		gGT->framesInThisLEV = gGT->framesInThisLEV + 1;
		gGT->unk1cc4[4] = 0;

#ifndef REBUILD_PS1
		iVar4 = RCNT_GetTime_Elapsed(gGT->anotherTimer, &gGT->anotherTimer);
		iVar4 = (iVar4 << 5) / 100;
#else
		iVar4 = FPS_HALF(0x20);
#endif

		gGT->elapsedTimeMS = iVar4;
		if (iVar4 < 0)
		{
			gGT->elapsedTimeMS = 0x20;
		}
		if (0x40 < gGT->elapsedTimeMS)
		{
			gGT->elapsedTimeMS = 0x40;
		}
		if ((gGT->gameMode1_prevFrame & PAUSE_ALL) != 0)
		{
			gGT->elapsedTimeMS = 0x20;
		}
		gGT->msInThisLEV += gGT->elapsedTimeMS;
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
						if (uVar3 == (uVar3 / FPS_DOUBLE(6)) * FPS_DOUBLE(6))
						{
							if (uVar3 == (uVar3 / FPS_DOUBLE(0xc)) * FPS_DOUBLE(0xc))
							{
								DECOMP_OtherFX_Play_LowLevel(0x40, '\0', 0x8c9080);
							}
							else
							{
								DECOMP_OtherFX_Play_LowLevel(0x40, '\0', 0x8c8880);
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
		
		DECOMP_CTR_CycleTex_AllModels(-1, (struct Model**)sdata->PLYROBJECTLIST, gGT->timer);
		DECOMP_CTR_CycleTex_AllModels(gGT->level1->numModels, gGT->level1->ptrModelsPtrArray, gGT->timer);
		
		psVar8 = 0;
		psVar9 = 0;

#ifndef REBUILD_PS1
		for(psVar12 = gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
		{
			psVar9 = (struct Driver*)psVar12->object;
			psVar10 = psVar9;
			if (psVar9->driverID == 0)
			{
LAB_80035098:
				psVar8 = psVar9;
				psVar9 = psVar10;
			}
			else
			{
				if (psVar9->driverID == 1)
				{
					psVar9 = psVar9;
				}
				psVar10 = psVar8;
				if ((u_char)psVar9->numTimesAttacking < (u_char)psVar8->numTimesAttacking) goto LAB_80035098;
			}
		}
#endif

		if
		(
			((psVar8 != 0) && (psVar9 != 0)) &&
			(
				iVar4 = (u_int)(u_char)psVar9->numTimesAttacking - (u_int)(u_char)psVar8->numTimesAttacking, 
				*(short*)(&psVar8->unk_4F0_4F8[2]) < iVar4
			)
		)
		{
			*(short*)(&psVar8->unk_4F0_4F8[2]) = (short)iVar4;
		}
		for (iVar4 = 0; iVar4 < NUM_BUCKETS; iVar4++)
		{
			if
			(
				(
					// if threads are not paused
					((gGT->gameMode1 & PAUSE_THREADS) == 0) || 
					
					// if bucket can not be paused
					((gGT->threadBuckets[iVar4].boolCantPause & 1U) != 0)
				) && 
				
				// if threads exist
				(gGT->threadBuckets[iVar4].thread != 0)
			)
			{
				if (iVar4 == 0)
				{
#ifndef REBUILD_PS1
					for(psVar12 = gGT->threadBuckets[iVar4].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
					{
						Weapon_Shoot_OnCirclePress((struct Driver*)psVar12->object);
					}
#endif
					
					// run all driver funcPtrs,
					// all drivers must run the same stage (1-13)
					// at the same time, that's why the stages exist
					for(iVar11 = 0; iVar11 < 13; iVar11++)
					{
						for(psVar12 = gGT->threadBuckets[iVar4].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
						{
							// if PLYR converted to robotcar at end of race,
							// dont run funcPtrs from inside driver struct
							if (psVar12->funcThTick != 0) continue;
						
							psVar9 = (struct Driver*)psVar12->object;
							
							pcVar5 = psVar9->funcPtrs[iVar11];
							
							if (pcVar5 != 0)
							{
								pcVar5(psVar12, psVar9);
							}
						}	
					}
				}
#ifndef REBUILD_PS1
				ThTick_RunBucket(gGT->threadBuckets[iVar4].thread);
#else
				TEST_ThTickRunBucket(gGT->threadBuckets[iVar4].thread);
#endif
			}
		}

#ifndef REBUILD_PS1
		BOTS_UpdateGlobals();
		GhostTape_WriteMoves(0);
		gGT->unk1cc4[4] = (u_int)(gGT->unk1cc4[4] * 10000) / 0x147e;
		
		#ifdef USE_60FPS
		
		// This does not fix Underwater, or particles with function pointers
		for(struct Particle* p = gGT->particleList_ordinary; p != 0; p = p->next)
		{
			// good thing PSX supports address mirroring,
			// use the top bit to determine if particle is patched
			unsigned int pointer = p->ptrIconGroup;
			unsigned int topBit = pointer & 0xC0000000;
			
			// topBit will be 00000000 (if null) or 80000000 (not null),
			// set the bit 40000000 to prove it was patched, and the 
			// pointer will behave as if it was never edited (thanks psx mirroring)
			if(topBit == 0x40000000) continue;
			
			pointer = pointer & 0xfffffff;
			pointer |= 0x40000000;
			p->ptrIconGroup = pointer;
			
			p->framesLeftInLife *= 2;
			
			for(int axis = 0; axis < 0xb; axis++)
			{
				p->axis[axis].velocity /= 2;
				p->axis[axis].accel /= 2;
			}
		}
		
		// For byte budget, forget heat warp,
		// it only draws in Tiger Temple anyway
		
		//for(struct Particle* p = gGT->particleList_heatWarp; p != 0; p = p->next)
		//{
		//	p->axis[7].velocity = 0x30;
		//}
		
		#endif

		Particle_UpdateAllParticles();
#endif
	}
	else
	{
		psVar12 = gGT->threadBuckets[AKUAKU].thread;
		if (psVar12 != 0)
		{
#ifndef REBUILD_PS1
			ThTick_RunBucket(psVar12);
#else
			TEST_ThTickRunBucket(psVar12);
#endif
		}
	}
	
#ifndef REBUILD_PS1
	uVar5 = LOAD_IsOpen_RacingOrBattle();
	if (uVar5 != 0)
	{
		if ((gGT->gameMode1 & PAUSE_ALL) == 0)
		{
			RB_Bubbles_RoosTubes();
		}
		if (gGT->threadBuckets[BURST].thread != 0)
		{
			RB_Burst_DrawAll(gGT);
		}
	}
#endif

	DECOMP_THREAD_CheckAllForDead();

	if ((gGT->gameMode1 & PAUSE_ALL) == 0)
	{
		DECOMP_Audio_Update1();
	}
	
	gGT->gameMode1_prevFrame = gGT->gameMode1;
	uVar5 = DECOMP_GAMEPAD_GetNumConnected(gGamepads);
	uVar3 = gGT->gameMode1;

	if ((uVar3 & END_OF_RACE) == 0)
	{
		if ((bVar1) || ((uVar3 & PAUSE_ALL) != 0))
		{
			if (gGT->cooldownfromPauseUntilUnpause == 0)
			{
				if
				(
					(
						(sdata->ptrActiveMenuBox != &data.menuBox_optionsMenu_racingWheel) &&
						(sdata->ptrActiveMenuBox != (struct MenuBox*)0x800b518c) // in 232
					) &&
					((sdata->AnyPlayerTap & BTN_START) != 0)
				)
				{
					DECOMP_MENUBOX_ClearInput();
					gGT->gameMode1 &= ~PAUSE_1;
					
#ifndef REBUILD_PS1
					MainFrame_TogglePauseAudio(0);
					DECOMP_OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate(gGT);
#endif

					DECOMP_MENUBOX_Hide(sdata->ptrActiveMenuBox);
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
			if ((uVar3 & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0)
				if (sdata->ptrActiveMenuBox == 0)
					if (sdata->AkuAkuHintState == 0)
						if (DECOMP_TitleFlag_IsFullyOnScreen() == 0)
			{
				for(iVar4 = 0; iVar4 < gGT->numPlyrCurrGame; iVar4++)
				{
					if
					(
						(
							(
								(uVar5 != 0) &&
								(
									(
#ifndef REBUILD_PS1
										uVar3 = MainFrame_HaveAllPads((u_short)(u_char)gGT->numPlyrNextGame),
										(uVar3 & 0xffff) == 0 && 
#endif
										((gGT->gameMode1 & PAUSE_ALL) == 0)
									)
								)
							) ||
							((gGamepads->gamepad[iVar4].buttonsTapped & BTN_START) != 0)
						) &&
						(gGT->overlayIndex_Threads != -1)
					)
					{
						gGT->unknownFlags_1d44 = (gGT->gameMode1 & 0x3e0020) | PAUSE_1;
						
#ifndef REBUILD_PS1
						MainFreeze_IfPressStart();
#endif

						gGT->cooldownfromPauseUntilUnpause = 5;
					}
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

#ifndef REBUILD_PS1
				sVar2 = TitleOSK_DrawMenu(0x140);
				if (sVar2 == 0)
				{
					return;
				}
				if (sVar2 == 1)
				{
					*(u_short*)&sdata->unk_saveGame_related = 0;
					
					LoadSave_ToggleMode(0x41);

					DECOMP_MENUBOX_Show(&data.menuBox_warning2);
					gGT->unknownFlags_1d44 |= AKU_SONG;

					return;
				}
#endif

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
#ifndef REBUILD_PS1
			UI_VsQuipDrawAll();
			UI_VsWaitForPressX();
#endif
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