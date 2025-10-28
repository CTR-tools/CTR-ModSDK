#include <common.h>

typedef void (*VehicleFuncPtr)(struct Thread* thread, struct Driver* driver);

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
void RunVehicleThread(VehicleFuncPtr func, struct Thread* thread, struct Driver* driver);
#endif

void DECOMP_MainFrame_GameLogic(struct GameTracker* gGT, struct GamepadSystem* gGamepads)
{
	char boolPaused;
	short submitState;
	unsigned int msCount;
	char boolControllerIsValid;
	int timeElapsed;
	VehicleFuncPtr driverFuncPtrs;
	char numControllers;
	unsigned char boolRace_Battle;
	struct Driver* player1;
	struct Driver* currDriver;
	struct Driver* player1_backup;
	struct PushBuffer* pushBuffer;
	unsigned char i;
	unsigned int gameMode;
	unsigned char j;
	struct Thread* currThread;

	boolPaused = true;
	if ((gGT->gameMode1 & PAUSE_ALL) == 0)
	{
		boolPaused = false;
		pushBuffer = gGT->pushBuffer;
		for(currThread = gGT->threadBuckets[PLAYER].thread; currThread != 0; currThread = currThread->siblingThread)
		{
			currDriver = (struct Driver*)currThread->object;

			#ifdef USE_ONLINE
			currDriver = gGT->drivers[0];
			#endif

			if (currDriver->clockSend)
			{
				currDriver->clockSend--;
			}
			msCount = currDriver->clockFlash;
			if (msCount == 0)
			{
				if (currDriver->clockReceive == 0)
				{
					msCount = (u_int)currDriver->clockSend;
					if (msCount == 0)
					{
						if ((gGT->clockEffectEnabled & 1) == 0) goto LAB_80034e74;
						msCount = 10000;
					}
				}
				else
				{
					if ((currDriver->actionsFlagSet & 0x2000000) != 0)
					{
						currDriver->clockReceive = 0;
					}
					msCount = (u_int)currDriver->clockReceive;
				}

#ifndef REBUILD_PS1
				DISPLAY_Blur_Main(pushBuffer, msCount);
#endif
			}
			else
			{
#ifndef REBUILD_PS1
				DISPLAY_Blur_Main(pushBuffer, -msCount);
#endif
				currDriver->clockFlash--;
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

		timeElapsed = DECOMP_Timer_GetTime_Elapsed(gGT->clockFrameStart, &gGT->clockFrameStart);
		timeElapsed = (timeElapsed << 5) / 100;
		
		gGT->elapsedTimeMS = timeElapsed;
		if (timeElapsed < 0)
		{
			gGT->elapsedTimeMS = 0x20;
		}
		if (gGT->elapsedTimeMS > 0x40)
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
			if ((gGT->gameMode1 & DEBUG_MENU) == 0)
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
					timeElapsed = gGT->frozenTimeRemaining - gGT->elapsedTimeMS;
					gGT->frozenTimeRemaining = timeElapsed;
					if (timeElapsed < 0)
					{
						gGT->frozenTimeRemaining = 0;
					}
					else
					{
						msCount = gGT->timer;
						if (msCount == (msCount / FPS_DOUBLE(6)) * FPS_DOUBLE(6))
						{
							if (msCount == (msCount / FPS_DOUBLE(0xc)) * FPS_DOUBLE(0xc))
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

		DECOMP_CTR_CycleTex_AllModels(-1, sdata->PLYROBJECTLIST, gGT->timer);
		DECOMP_CTR_CycleTex_AllModels(gGT->level1->numModels, gGT->level1->ptrModelsPtrArray, gGT->timer);

		player1 = NULL;
		currDriver = NULL;

#ifndef REBUILD_PS1
		for(currThread = gGT->threadBuckets[PLAYER].thread; currThread != 0; currThread = currThread->siblingThread)
		{
			currDriver = (struct Driver*)currThread->object;
			player1_backup = currDriver;
			
			if (currDriver->driverID == 0)
			{
LAB_80035098:
				player1 = currDriver;
				currDriver = player1_backup;
			}
			else
			{

				player1_backup = player1;
				if ((u_char)currDriver->numTimesAttacking < (u_char)player1->numTimesAttacking) goto LAB_80035098;
			}
		}
#endif

		if
		(
			((player1 != NULL) && (currDriver != NULL)) &&
			(
				timeElapsed = (u_int)(u_char)currDriver->numTimesAttacking - (u_int)(u_char)player1->numTimesAttacking,
				player1->quip2 < timeElapsed
			)
		)
		{
			player1->quip2 = (short)timeElapsed;
		}
				
		for (j = 0; j < NUM_BUCKETS; j++)
		{			
			if
			(
				// This code was in OG, but not needed by retail game
				#ifdef USE_PROFILER
				(
					// if threads are not paused
					((gGT->gameMode1 & DEBUG_MENU) == 0) ||

					// if bucket can not be paused
					((gGT->threadBuckets[j].boolCantPause & 1U) != 0)
				) &&
				#endif

				// if threads exist
				(gGT->threadBuckets[j].thread != 0)
			)
			{
				#if defined(USE_ONLINE)
				// synchronize track hazards
				if(
					(j == STATIC) ||
					(j == SPIDER)
				)
				{
					if(gGT->trafficLightsTimer > 3600)
						continue;
				}
				#endif
				if (j == 0)
				{

					for(currThread = gGT->threadBuckets[j].thread; currThread != 0; currThread = currThread->siblingThread)
					{
						DECOMP_VehPickupItem_ShootOnCirclePress((struct Driver*)currThread->object);
					}

					#ifdef USE_HIGHMP
					int backupPlyrCount;
					#endif

					// run all driver funcPtrs,
					// all drivers must run the same stage (1-13)
					// at the same time, that's why the stages exist
					for(i = 0; i < 13; i++)
					{
						for(currThread = gGT->threadBuckets[j].thread; currThread != 0; currThread = currThread->siblingThread)
						{
							// if PLYR converted to robotcar at end of race,
							// dont run funcPtrs from inside driver struct
							if (currThread->funcThTick != 0) continue;

							currDriver = (struct Driver*)currThread->object;

							driverFuncPtrs = currDriver->funcPtrs[i];

							#ifdef USE_ONLINE
							RunVehicleThread(driverFuncPtrs, currThread, currDriver);
							#else
							if (driverFuncPtrs != NULL)
							{
								driverFuncPtrs(currThread, currDriver);
							}
							#endif

							#ifdef USE_60FPS
								#ifndef REBUILD_PS1
									// if this function just ran
									if(driverFuncPtrs == VehFrameProc_Driving)
									{
										// only if jumping animation,
										// otherwise wheelie gets bugged
										if(currDriver->instSelf->animIndex == 3)
										{
											currDriver->matrixIndex =
											currDriver->matrixIndex >> 1;
										}
									}
								#endif
							#endif
						}

						// rig collisions to high-poly,
						// wait until Stage 2 finishes, cause PhysLinear
						// uses gGT->numPlyrCurrGame for VehPhysGeneral_SetHeldItem
						#ifdef USE_HIGHMP
						if(i == 2)
						{
							backupPlyrCount = gGT->numPlyrCurrGame;
							gGT->numPlyrCurrGame = 1;
						}
						#endif
					}

					#ifdef USE_HIGHMP
					gGT->numPlyrCurrGame = backupPlyrCount;
					#endif

					#ifdef USE_ONLINE
					octr->readyToSend = 1;
					#endif
				}


#ifndef REBUILD_PS1
				ThTick_RunBucket(gGT->threadBuckets[j].thread);
#else
				TEST_ThTickRunBucket(gGT->threadBuckets[j].thread);
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
		currThread = gGT->threadBuckets[AKUAKU].thread;
		if (currThread != NULL)
		{
#ifndef REBUILD_PS1
			ThTick_RunBucket(currThread);
#else
			TEST_ThTickRunBucket(currThread);
#endif
		}
	}

	boolRace_Battle = DECOMP_LOAD_IsOpen_RacingOrBattle();
	if (boolRace_Battle != 0)
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
	numControllers = DECOMP_GAMEPAD_GetNumConnected(gGamepads);
	gameMode = gGT->gameMode1;

	if ((gameMode & END_OF_RACE) == 0)
	{
		if ((boolPaused) || ((gameMode & PAUSE_ALL) != 0))
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
			if ((gameMode & (GAME_CUTSCENE | END_OF_RACE | MAIN_MENU)) == 0)
				if (sdata->ptrActiveMenu == 0)
					if (sdata->AkuAkuHintState == 0)
						if (DECOMP_RaceFlag_IsFullyOnScreen() == 0)
			{
				for(j = 0; j < gGT->numPlyrCurrGame; j++)
				{
					if
					(
						(
							(
								(numControllers != 0) &&
								(
									(
#ifndef REBUILD_PS1
										boolControllerIsValid = MainFrame_HaveAllPads((u_short)(u_char)gGT->numPlyrNextGame),
										(boolControllerIsValid & 0xffff) == 0 &&
#endif
										((gGT->gameMode1 & PAUSE_ALL) == 0)
									)
								)
							) ||
							((gGamepads->gamepad[j].buttonsTapped & BTN_START) != 0)
						) &&
						(gGT->overlayIndex_Threads != -1)
					)
					{
						#if 0
						// But why? ND typo?
						gGT->gameModeEnd = (gGT->gameMode1 & 0x3e0020) | PAUSE_1;
						#endif

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
		gameMode = gGT->gameModeEnd;
		if ((gameMode & AKU_SONG) == 0)
		{
			if ((gameMode & CRYSTAL_CHALLENGE) == 0)
			{
				if (gGT->unk_timerCooldown_similarTo_1d36 == 0)
				{
					return;
				}
			}
			else if (gGT->unk_timerCooldown_similarTo_1d36 == 0)
			{
				if ((gameMode & PAUSE_2) == 0)
				{
					return;
				}

				submitState = DECOMP_SubmitName_DrawMenu(0x140);

				// if not done yet
				if (submitState == 0)
				{
					return;
				}


#ifndef REBUILD_PS1

				// if SAVE
				if (submitState == 1)
				{
					sdata->boolSaveCupProgress = 0;

					SelectProfile_ToggleMode(0x41);

					DECOMP_RECTMENU_Show(&data.menuWarning2);
					gGT->gameModeEnd |= NEW_NAME;

					return;
				}
#endif

				// if -1 (cancel)
				gGT->newHighScoreIndex = -1;
				gGT->gameModeEnd &= ~(NEW_BEST_LAP | NEW_HIGH_SCORE);
				return;
			}
			gGT->unk_timerCooldown_similarTo_1d36--;
		}
	}
	else if ((gameMode & ARCADE_MODE) == 0)
	{
		if (gGT->timerEndOfRaceVS < 0x96)
		{
#ifndef REBUILD_PS1
			UI_VsQuipDrawAll();
			UI_VsWaitForPressX();
#endif
		}
		if (gGT->timerEndOfRaceVS > 0x1e)
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