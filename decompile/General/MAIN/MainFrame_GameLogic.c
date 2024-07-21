#include <common.h>

typedef void (*VehicleFuncPtr)(struct Thread* thread, struct Driver* driver);

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
void RunVehicleThread(VehicleFuncPtr func, struct Thread* thread, struct Driver* driver);
#endif

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
	struct PushBuffer* pushBuffer;
	int iVar11;
	struct Thread* psVar12;

	bVar1 = true;
	if ((gGT->gameMode1 & PAUSE_ALL) == 0)
	{
		bVar1 = false;
		pushBuffer = gGT->pushBuffer;
		for(psVar12 = gGT->threadBuckets[0].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
		{
			psVar9 = (struct Driver*)psVar12->object;

			#ifdef USE_ONLINE
			psVar9 = gGT->drivers[0];
			#endif

			if (psVar9->clockSend)
			{
				psVar9->clockSend--;
			}
			uVar3 = psVar9->clockFlash;
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
				DISPLAY_Blur_Main(pushBuffer, uVar3);
#endif
			}
			else
			{
#ifndef REBUILD_PS1
				DISPLAY_Blur_Main(pushBuffer, -uVar3);
#endif
				psVar9->clockFlash--;
			}
LAB_80034e74:
			pushBuffer = pushBuffer + 1;

			#ifdef USE_ONLINE
			break;
			#endif
		}
		gGT->timer = gGT->timer + 1;
		gGT->framesInThisLEV = gGT->framesInThisLEV + 1;
		gGT->unk1cc4[4] = 0;

#ifndef REBUILD_PS1
		iVar4 = Timer_GetTime_Elapsed(gGT->anotherTimer, &gGT->anotherTimer);
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
				psVar8->quip2 < iVar4
			)
		)
		{
			psVar8->quip2 = (short)iVar4;
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

// online multiplayer
#ifdef USE_ONLINE

				// synchronize track hazards
				if(
					(iVar4 == STATIC) ||
					(iVar4 == SPIDER)
				)
				{
					if(gGT->trafficLightsTimer > 3600)
						continue;
				}

				if (iVar4 == 0)
				{
					struct Driver* dOnline = gGT->drivers[0];
					if(dOnline != 0)
					{
						struct Thread* dThread = dOnline->instSelf->thread;

						DECOMP_VehPickupItem_ShootOnCirclePress(dOnline);

						RunVehicleSet13(dThread, dOnline);
						octr->desiredFPS = FPS_DOUBLE(30);
					}

					for(int other = 1; other < 8; other++)
					{
						dOnline = gGT->drivers[other];
						if(dOnline == 0) continue;

						struct Thread* dThread = dOnline->instSelf->thread;

						RunVehicleSet13(dThread, dOnline);
					}
				}

// offline
#else
				if (iVar4 == 0)
				{

					for(psVar12 = gGT->threadBuckets[iVar4].thread; psVar12 != 0; psVar12 = psVar12->siblingThread)
					{
						DECOMP_VehPickupItem_ShootOnCirclePress((struct Driver*)psVar12->object);
					}

					#ifdef USE_HIGHMP
					int backupPlyrCount;
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

							#ifdef USE_ONLINE
							RunVehicleThread(pcVar5, psVar12, psVar9);
							#else
							if (pcVar5 != 0)
							{
								pcVar5(psVar12, psVar9);
							}
							#endif

							#ifdef USE_60FPS
								#ifndef REBUILD_PS1
									// if this function just ran
									if(pcVar5 == VehFrameProc_Driving)
									{
										// only if jumping animation,
										// otherwise wheelie gets bugged
										if(psVar9->instSelf->animIndex == 3)
										{
											psVar9->matrixIndex =
											psVar9->matrixIndex >> 1;
										}
									}
								#endif
							#endif
						}

						// rig collisions to high-poly,
						// wait until Stage 2 finishes, cause PhysLinear
						// uses gGT->numPlyrCurrGame for VehPhysGeneral_SetHeldItem
						#ifdef USE_HIGHMP
						if(iVar11 == 2)
						{
							backupPlyrCount = gGT->numPlyrCurrGame;
							gGT->numPlyrCurrGame = 1;
						}
						#endif
					}

					#ifdef USE_HIGHMP
					gGT->numPlyrCurrGame = backupPlyrCount;
					#endif
				}
#endif


#ifndef REBUILD_PS1
				ThTick_RunBucket(gGT->threadBuckets[iVar4].thread);
#else
				TEST_ThTickRunBucket(gGT->threadBuckets[iVar4].thread);
#endif
			}
		}

#ifndef REBUILD_PS1
		BOTS_UpdateGlobals();
#endif
		DECOMP_GhostTape_WriteMoves(0);
		gGT->unk1cc4[4] = (u_int)(gGT->unk1cc4[4] * 10000) / 0x147e;

#ifndef REBUILD_PS1

		#ifdef USE_60FPS

		// This does not fix Underwater, or particles with function pointers
		for(struct Particle* p = gGT->particleList_ordinary; p != 0; p = p->next)
		{
			// if TireAxis is in use
			if((p->flagsAxis & (0x1<<0xA)) != 0)
			{
				// use ColorB axis, guaranteed not in use,
				// check here for patching, 4 divides to 2 in FOR-loop
				if (p->axis[0x9].startVal != 0) continue;
					p->axis[0x9].startVal = 4;
			}

			// TireAxis is not in use
			else
			{
				// check here for patching, 4 divides to 2 in FOR-loop
				if (p->axis[0xA].startVal != 0) continue;
					p->axis[0xA].startVal = 4;
			}

			// === If unpatched particle ===

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

		#endif // 60fps

		Particle_UpdateAllParticles();

#endif // rebuildps1
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

	uVar5 = DECOMP_LOAD_IsOpen_RacingOrBattle();
	if (uVar5 != 0)
	{
#ifndef REBUILD_PS1
		if ((gGT->gameMode1 & PAUSE_ALL) == 0)
		{
			DECOMP_RB_Bubbles_RoosTubes();
		}
		if (gGT->threadBuckets[BURST].thread != 0)
		{
			RB_Burst_DrawAll(gGT);
		}
#endif
	}

	DECOMP_PROC_CheckAllForDead();

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
						(sdata->ptrActiveMenu != &data.menuRacingWheelConfig) &&
						(sdata->ptrActiveMenu != &D232.menuHintMenu) // in 232
					) &&
					((sdata->AnyPlayerTap & BTN_START) != 0)
				)
				{
					DECOMP_RECTMENU_ClearInput();
					gGT->gameMode1 &= ~PAUSE_1;

					DECOMP_MainFrame_TogglePauseAudio(0);
					DECOMP_OtherFX_Play(1, 1);

					DECOMP_MainFreeze_SafeAdvDestroy();
					DECOMP_ElimBG_Deactivate(gGT);

					DECOMP_RECTMENU_Hide(sdata->ptrActiveMenu);
					gGT->cooldownFromUnpauseUntilPause = FPS_DOUBLE(5);
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
				if (sdata->ptrActiveMenu == 0)
					if (sdata->AkuAkuHintState == 0)
						if (DECOMP_RaceFlag_IsFullyOnScreen() == 0)
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

						DECOMP_MainFreeze_IfPressStart();

						gGT->cooldownfromPauseUntilUnpause = FPS_DOUBLE(5);
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

				sVar2 = DECOMP_SubmitName_DrawMenu(0x140);

				// if not done yet
				if (sVar2 == 0)
				{
					return;
				}


#ifndef REBUILD_PS1

				// if SAVE
				if (sVar2 == 1)
				{
					*(u_short*)&sdata->unk_saveGame_related = 0;

					SelectProfile_ToggleMode(0x41);

					DECOMP_RECTMENU_Show(&data.menuWarning2);
					gGT->unknownFlags_1d44 |= AKU_SONG;

					return;
				}
#endif

				// if -1 (cancel)
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