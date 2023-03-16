#include <common.h>

void MainFrame_RenderFrame(struct GameTracker *gGT)
{
	int *piVar1;
	u_char bVar2;
	struct Camera110 *psVar3;
	char cVar4;
	u_int uVar5;
	u_int uVar6;
	char *pcVar7;
	void *pvVar8;
	u_int *puVar9;
	short sVar10;
	int iVar10;
	u_int uVar11;
	int **ppiVar12;
	struct Thread *psVar13;
	DISPENV *env;
	short startX;
	struct Camera110 *psVar14;
	short startY;
	int iVar15;
	short sVar16;
	struct GameTracker *psVar17;
	int iVar23;
	int iVar18;
	int iVar19;
	int iVar20;
	struct GameTracker *psVar21;
	struct Level *level;
	struct mesh_info *playstationVar23;
	void *in_stack_ffffffb0;
	RECT local_40;
	short local_38;
	short local_36;
	RECT local_30;
	bool bool_menubox_mainMenuState;
	
	playstationVar23 = (struct mesh_info *)0x0;
	level = gGT->level1;
	bool_menubox_mainMenuState = false;
	uVar5 = LOAD_IsOpen_MainMenu();
	if ((uVar5 != 0) && (sdata->ptrActiveMenuBox == &OVR_230.menubox_mainMenu))
	{
		bool_menubox_mainMenuState = (OVR_230.menubox_mainMenu.state & 0x10) == 0;
	}
	if
	(
		(
			(
				((sdata_gGT->gameMode1 & 0x20000000U) == 0) &&
				(uVar6 = MainFrame_HaveAllPads((u_short)(u_char)sdata_gGT->numPlyrNextGame), 
				(uVar6 & 0xffff) == 0)
			) && (sdata_gGT->boolDemoMode == '\0')
		) &&
		(!bool_menubox_mainMenuState)
	)
	{
		sVar16 = data.errorPosY[sdata->errorMessagePosIndex];
		local_40.h = 0xe;
		if
		(
			(sdata->gGamepads->slotBuffer[0].meta[1] == -0x80) ||
			(sVar10 = 0, 2 < (u_char)sdata_gGT->numPlyrNextGame)
		)
		{
			sVar10 = 2;
		}
		iVar23 = 0;
		if (sdata_gGT->numPlyrNextGame != '\0') {
			iVar19 = 0;
			local_40.h = 0xe;
			do {
				pcVar7 = *(char **)(sdata->gGamepads->gamepad[0].data + iVar19 - 0xc);
				if ((pcVar7 == (char *)0x0) || (*pcVar7 != '\0')) {
					iVar15 = (int)sVar16;
					local_40.h = local_40.h + 8;
					sVar16 = sVar16 + 8;
					DecalFont_DrawLine(sdata->lngStrings[*(short *)((iVar23 + sVar10) * 2 - 0x7ff7bdbc)], 0x100, 
														 iVar15, 2, -0x8000);
				}
				iVar23 = iVar23 + 1;
				iVar19 = iVar19 + 0x50;
			} while (iVar23 < (int)(u_int)(u_char)sdata_gGT->numPlyrNextGame);
		}
		DecalFont_DrawLine(sdata->lngStrings[0x2b], 0x100, (int)sVar16, 2, -0x8000);
		local_40.x = -0x14;
		local_40.w = 0x228;
		local_40.y = data.errorPosY[sdata->errorMessagePosIndex] - 3;
		DrawTextBackground(&local_40, 1, (u_long *)(sdata_gGT->backBuffer->otMem).startPlusFour);
	}
	iVar15 = 0;
	iVar18 = 0;
	iVar20 = 0x168;
	iVar19 = iVar18;
	do {
		if (*(u_short *)((int)sdata->finalLapTextTimer + iVar15) != 0) {
			iVar10 = (int)((0x5a - (u_int)*(u_short *)((int)sdata->finalLapTextTimer + iVar15)) * 0x10000) >> 0x10;
			if (iVar10 < 0x51) {
				if (iVar10 < 0xb) {
					sVar16 = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20);
					startX = sVar16 + 100;
					startY = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20 + 2) >> 2;
					sVar16 = sVar16 >> 1;
				}
				else {
					iVar10 = iVar10 - 10;
					startX = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20) >> 1;
					startY = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20 + 2) >> 2;
					sVar16 = startX;
				}
			}
			else {
				iVar10 = iVar10 - 0x50;
				startX = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20) >> 1;
				startY = *(short *)((int)sdata_gGT->db[0].drawEnv.ofs + iVar20 + 2) >> 2;
				sVar16 = -100;
			}
			in_stack_ffffffb0 = (void *)0xa;
			InterpolatePosition2D_Linear(&local_38, startX, startY, sVar16, startY, iVar10, 10);
			DecalFont_DrawLineOT
								(sdata->lngStrings[0x233], (int)local_38, (int)local_36, 1, -0x8000, 
								 *(u_long **)(sdata_gGT->camera110[0].filler2 + iVar19 - 4));
			*(short *)((int)sdata->finalLapTextTimer + iVar15) = *(short *)((int)sdata->finalLapTextTimer + iVar15) - 1
			;
		}
		iVar15 = iVar15 + 2;
		iVar19 = iVar19 + 0x110;
		iVar18 = iVar18 + 1;
		iVar20 = iVar20 + 0x110;
	} while (iVar18 < 4);
	ElimBG_HandleState(sdata_gGT);
	if (level != (struct Level *)0x0) {
		playstationVar23 = level->ptr_mesh_info;
	}
	if ((gGT->renderFlags & 0x21) != 0) {
		MainFrame_VisMemFullFrame(gGT, level);
	}
	if ((((gGT->renderFlags & 1) != 0) && (sdata_gGT->visMem1 != (struct VisMem *)0x0)) &&
		 (level != (struct Level *)0x0)) {
		CTR_CycleTex_LEV((struct AnimTex *)level->ptr_anim_tex, gGT->timer);
	}
	if ((sdata->ptrActiveMenuBox != (struct MenuBox *)0x0) || ((sdata_gGT->gameMode1 & 0x200000U) != 0)) {
		MenuBox_CollectInput();
	}
	if ((sdata->ptrActiveMenuBox != (struct MenuBox *)0x0) && (sdata->Loading.stage == -1)) {
		MenuBox_ProcessState();
	}
	iVar19 = 0;
	if (gGT->numPlyrCurrGame != '\0') {
		iVar15 = 0x168;
		psVar17 = gGT;
		psVar21 = gGT;
		do {
			Camera110_UpdateFrustum((struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar15 - 0x20));
			iVar18 = *(int *)(psVar17->cameraDC[0].data40 + 0x18);
			if (iVar18 != 0) {
				uVar6 = (u_int)*(u_char *)(iVar18 + 0x39);
				uVar11 = (u_int)(u_char)gGT->numPlyrCurrGame;
				
				*(short *)&psVar21->rainBuffer[0].numParticles_max = (short)((uVar6 << 2) / uVar11);
				uVar6 = (u_int)*(u_char *)(*(int *)(psVar17->cameraDC[0].data40 + 0x18) + 0x3a);
				uVar11 = (u_int)(u_char)gGT->numPlyrCurrGame;
				
				*(short *)((int)&psVar21->rainBuffer[0].numParticles_max + 2) =
						 (short)((uVar6 << 2) / uVar11);
			}
			psVar21 = (struct GameTracker *)&psVar21->db[0].drawEnv.isbg;
			psVar17 = (struct GameTracker *)psVar17->db[1].drawEnv.dr_env.code;
			iVar19 = iVar19 + 1;
			iVar15 = iVar15 + 0x110;
		} while (iVar19 < (int)(u_int)(u_char)gGT->numPlyrCurrGame);
	}
	EffectSfxRain_MakeSound(gGT);
	uVar6 = sdata->frameCounter << 7;
	uVar5 = sdata->trigApprox[uVar6 & 0x3ff];
	if ((uVar6 & 0x400) == 0) {
		uVar5 = uVar5 << 0x10;
	}
	iVar19 = (int)uVar5 >> 0x10;
	if ((uVar6 & 0x800) != 0) {
		iVar19 = -iVar19;
	}
	iVar19 = (iVar19 << 6) >> 0xc;
	sdata->menuRowHighlight_Normal = (iVar19 + 0x40) * 0x100 | 0x80;
	sdata->menuRowHighlight_Green = (iVar19 + 0xa0) * 0x100 | 0x400040;
	if (((gGT->renderFlags & 2) != 0) && ((u_char)sdata_gGT->numPlyrCurrGame < 2)) {
		RenderWeather(sdata_gGT->camera110, &sdata_gGT->backBuffer->primMem, sdata_gGT->rainBuffer, 
									sdata_gGT->numPlyrCurrGame, sdata_gGT->gameMode1 & 0xf);
	}
	if (((gGT->renderFlags & 4) != 0) && (iVar19 = 0, 0 < (int)sdata_gGT->numWinners)) {
		iVar15 = 0;
		do {
			DrawConfetti(sdata_gGT->camera110 + *(int *)((int)sdata_gGT->winnerIndex + iVar15), 
									 &sdata_gGT->backBuffer->primMem, &sdata_gGT->confetti, 
									 sdata_gGT->frameTimer_Confetti, sdata_gGT->gameMode1 & 0xf);
			iVar19 = iVar19 + 1;
			iVar15 = iVar19 * 4;
		} while (iVar19 < (int)sdata_gGT->numWinners);
	}
	if (((gGT->renderFlags & 8) != 0) && (*(short *)&(sdata_gGT->stars).numStars != 0)) {
		RenderStars(sdata_gGT->camera110, &sdata_gGT->backBuffer->primMem, &sdata_gGT->stars, 
								sdata_gGT->numPlyrCurrGame);
	}
	if (((gGT->renderFlags & 0x100) != 0) && (1 < (u_char)sdata_gGT->numPlyrCurrGame)) {
		DecalMP_01(gGT);
	}
	if ((((sdata_gGT->hudFlags & 8U) == 0) || (sdata_gGT->numPlyrCurrGame != '\x01')) ||
		 ((sdata_gGT->gameMode1 & 0x40U) == 0)) {
		bVar2 = sdata_gGT->hudFlags;
		if ((bVar2 & 1) == 0) {
			if ((bVar2 & 4) != 0) {
				CupStandings_InputAndDraw();
			}
		}
		else {
			uVar6 = sdata_gGT->gameMode1;
			if ((uVar6 & 0x100000) == 0) {
				if (((uVar6 & 0x200000) == 0) || (sdata_gGT->timerEndOfRaceVS != 0)) {
					if ((uVar6 & 0x8000000) == 0) {
						DrawHUD_Racing();
					}
					else {
						DrawHUD_CrystalChallenge();
					}
				}
				else if (1 < sdata->Loading.stage + 5U) {
					if ((uVar6 & 0x8000000) == 0) {
						if ((uVar6 & 0x20000) == 0) {
							if ((uVar6 & 0x400000) == 0) {
								if ((uVar6 & 0x4000000) == 0) {
									if ((uVar6 & 0x80000) != 0) goto LAB_800367d4;
									if ((sdata_gGT->gameMode2 & 0x10U) == 0) {
										VB_EndEvent_DrawMenu();
									}
									else {
										sdata_gGT->hudFlags = bVar2 & 0xfe;
										sdata_gGT->hudFlags = sdata_gGT->hudFlags | 4;
									}
								}
								else {
									RR_EndEvent_DrawMenu();
								}
							}
							else {
LAB_800367d4:
								AA_EndEvent_DrawMenu();
							}
						}
						else {
							TT_EndEvent_DrawMenu();
						}
					}
					else {
						CC_EndEvent_DrawMenu();
					}
				}
			}
			else {
				if ((1 < sdata_gGT->overlayTransition) &&
					 (sdata_gGT->overlayTransition = sdata_gGT->overlayTransition - 1, 
					 sdata_gGT->overlayTransition == '\x01')) {
					LOAD_OvrThreads(2);
				}
				uVar5 = LOAD_IsOpen_AdvHub();
				if (uVar5 == 0) {
					if (0xfff < (sdata_gGT->camera110_UI).fadeFromBlack_currentValue) {
						DrawHUD_AdvStrings();
					}
				}
				else {
					if ((0xfff < (sdata_gGT->camera110_UI).fadeFromBlack_currentValue) &&
						 (AH_Map_Main(), sdata->AkuHint_RequestedHint != -1)) {
						AH_MaskHint_Start(sdata->AkuHint_RequestedHint, sdata->AkuHint_boolInterruptWarppad);
						sdata->AkuHint_RequestedHint = -1;
						sdata->AkuHint_boolInterruptWarppad = 0;
					}
					if (sdata_gGT->overlayTransition != '\0') {
						INSTANCE_LevRestartLInBs(gGT->level1->ptrInstDefs, gGT->level1->numInstances);
						psVar17 = sdata_gGT;
						piVar1 = &sdata_gGT->gameMode2;
						sdata_gGT->overlayTransition = '\0';
						psVar21 = sdata_gGT;
						psVar17->gameMode2 = *piVar1 & 0xfffffeff;
						(psVar21->camera110_UI).fadeFromBlack_desiredResult = 0x1000;
						(psVar21->camera110_UI).fade_step = 0x2aa;
					}
				}
			}
		}
	}
	else {
		DrawIntroRaceText_1P();
	}
	if (((gGT->renderFlags & 0x10) != 0) && ((u_char)sdata_gGT->numPlyrCurrGame < 3)) {
		RedBeaker_RenderRain
							(gGT->camera110, &gGT->backBuffer->primMem, &(sdata_gGT->JitPools).rain, 
							 sdata_gGT->numPlyrCurrGame, sdata_gGT->gameMode1 & 0xf);
	}
	uVar5 = LOAD_IsOpen_Podiums();
	if ((uVar5 != 0) && (sdata_gGT->levelID == NAUGHTY_DOG_CRATE)) {
		CS_BoxScene_InstanceSplitLines();
	}
	if ((gGT->renderFlags & 0x20) != 0) {
		uVar6 = (u_char)sdata_gGT->numPlyrCurrGame - 1;
		if ((sdata_gGT->gameMode1 & 0x4000000U) != 0) {
			uVar6 = uVar6 | 4;
		}
		pvVar8 = RenderBucket_QueueLevInstances
											 (gGT->cameraDC, (u_long *)&sdata_gGT->backBuffer->otMem, 
												sdata_gGT->ptrRenderBucketInstance, 
												(char *)(u_int)(u_char)sdata->LOD[uVar6], sdata_gGT->numPlyrCurrGame, 
												sdata_gGT->gameMode1 & 0xf);
		uVar6 = (u_char)sdata_gGT->numPlyrCurrGame - 1;
		if ((sdata_gGT->gameMode1 & 0x4000000U) != 0) {
			uVar6 = uVar6 | 4;
		}
		puVar9 = (u_int *)
						 RenderBucket_QueueNonLevInstances
											 ((sdata_gGT->JitPools).instance.taken.first, 
												(u_long *)&sdata_gGT->backBuffer->otMem, pvVar8, 
												(char *)(u_int)(u_char)sdata->LOD[uVar6], sdata_gGT->numPlyrCurrGame, 
												sdata_gGT->gameMode1 & 0xf);
		*puVar9 = 0;
	}
	if ((gGT->renderFlags & 0x200) != 0) {
		cVar4 = gGT->numPlyrCurrGame;
		iVar19 = 0;
		if (cVar4 == '\0') goto code_r0x800369d8;
		iVar15 = 0x168;
		do {
			iVar18 = iVar15 - 0x20;
			iVar15 = iVar15 + 0x110;
			Particle_RenderList((struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar18), 
													sdata_gGT->particleList_ordinary);
			iVar19 = iVar19 + 1;
		} while (iVar19 < (int)(u_int)(u_char)gGT->numPlyrCurrGame);
	}
	cVar4 = gGT->numPlyrCurrGame;
code_r0x800369d8:
	iVar19 = 0;
	if (cVar4 != '\0') {
		psVar14 = gGT->camera110;
		psVar17 = gGT;
		iVar15 = 0x168;
		do {
			psVar3 = psVar17->camera110;
			psVar17 = (struct GameTracker *)(psVar17->db[1].drawEnv.dr_env.code + 0xd);
			Camera110_SetDrawEnv_Normal(psVar3->ptrOT + 0x3ff, psVar14, gGT->backBuffer, (short *)0x0, '\0');
			iVar19 = iVar19 + 1;
			psVar14 = (struct Camera110 *)((int)gGT->camera110[0].pos + iVar15 - 0x58);
			iVar15 = iVar15 + 0x110;
		} while (iVar19 < (int)(u_int)(u_char)gGT->numPlyrCurrGame);
	}
	if (((gGT->renderFlags & 0x100) != 0) && (1 < (u_char)sdata_gGT->numPlyrCurrGame)) {
		DecalMP_02(gGT);
	}
	if ((gGT->renderFlags & 0x40) != 0) {
		uVar5 = LOAD_IsOpen_RacingOrBattle();
		if (uVar5 != 0) {
			RB_Player_ToggleInvisible();
			RB_Player_ToggleFlicker();
			RB_Burst_ProcessBucket(sdata_gGT->threadBuckets[7].thread);
			RB_Blowup_ProcessBucket(sdata_gGT->threadBuckets[8].thread);
			RB_Spider_DrawWebs(sdata_gGT->threadBuckets[10].thread, gGT->camera110);
			RB_Follower_ProcessBucket(sdata_gGT->threadBuckets[0xb].thread);
			RB_StartText_ProcessBucket(sdata_gGT->threadBuckets[0xc].thread);
		}
		uVar5 = LOAD_IsOpen_AdvHub();
		if ((uVar5 != 0) && ((sdata_gGT->gameMode1 & 0x100000U) != 0)) {
			AH_WarpPad_AllWarppadNum();
		}
		iVar19 = 0;
		Turbo_ProcessBucket(sdata_gGT->threadBuckets[9].thread);
		if (gGT->numPlyrCurrGame != '\0') {
			iVar15 = 0x168;
			do {
				psVar14 = (struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar15 - 0x20);
				DrawSkidMarks_Main(sdata_gGT->threadBuckets[0].thread, psVar14);
				iVar15 = iVar15 + 0x110;
				DrawSkidMarks_Main(sdata_gGT->threadBuckets[1].thread, psVar14);
				iVar19 = iVar19 + 1;
			} while (iVar19 < (int)(u_int)(u_char)gGT->numPlyrCurrGame);
		}
	}
	if (((sdata_gGT->gameMode1 & 0x2000U) != 0) && (uVar5 = LOAD_IsOpen_MainMenu(), uVar5 != 0)) {
		MM_Title_SetTrophyDPP();
	}
	if ((gGT->renderFlags & 0x20) != 0) {
		RenderBucket_Execute(sdata_gGT->ptrRenderBucketInstance, &sdata_gGT->backBuffer->primMem);
	}
	if ((gGT->renderFlags & 0x80) != 0) {
		psVar13 = sdata_gGT->threadBuckets[0].thread;
		if (psVar13 != (struct Thread *)0x0) {
			DrawTires_Solid(psVar13, &sdata_gGT->backBuffer->primMem, gGT->numPlyrCurrGame);
			DrawTires_Reflection
								(sdata_gGT->threadBuckets[0].thread, &sdata_gGT->backBuffer->primMem, 
								 gGT->numPlyrCurrGame);
		}
		if (sdata_gGT->numBotsNextGame != '\0') {
			DrawTires_Solid(sdata_gGT->threadBuckets[1].thread, &sdata_gGT->backBuffer->primMem, 
											gGT->numPlyrCurrGame);
			DrawTires_Reflection
								(sdata_gGT->threadBuckets[1].thread, &sdata_gGT->backBuffer->primMem, 
								 gGT->numPlyrCurrGame);
		}
		psVar13 = sdata_gGT->threadBuckets[2].thread;
		if (psVar13 != (struct Thread *)0x0) {
			DrawTires_Solid(psVar13, &sdata_gGT->backBuffer->primMem, gGT->numPlyrCurrGame);
			DrawTires_Reflection
								(sdata_gGT->threadBuckets[2].thread, &sdata_gGT->backBuffer->primMem, 
								 gGT->numPlyrCurrGame);
		}
	}
	if ((gGT->renderFlags & 0x400) != 0) {
		DrawShadows_Main();
	}
	if ((gGT->renderFlags & 0x800) != 0) {
		DrawHeat_Main(sdata_gGT->particleList_heatWarp, gGT->camera110, &sdata_gGT->backBuffer->primMem, 
									gGT->numPlyrCurrGame, sdata_gGT->swapchainIndex * 0x128);
	}
	Camera110_FadeAllWindows();
	if (((gGT->renderFlags & 1) != 0) && (playstationVar23 != (struct mesh_info *)0x0)) {
		bVar2 = sdata_gGT->numPlyrCurrGame;
		if (bVar2 == 2) {
			CTR_ClearRenderLists_1P2P(gGT, 2);
			if ((level->configFlags & 4U) == 0) {
				AnimateWater2P(gGT->timer, level->count_water, level->ptr_water, level->ptr_tex_waterEnvMap, 
											 gGT->visMem1->visOVertList[0], gGT->visMem1->visOVertList[1]);
			}
			iVar15 = 0;
			VisData_CopyJMPsToScratchpad();
			gGT->numVisDataLinks = 0;
			iVar18 = 0x1808;
			iVar19 = 0x168;
			do {
				iVar20 = iVar19 - 0x20;
				ppiVar12 = gGT->visMem1->visLeafList + iVar15;
				iVar10 = iVar18 - 0x20;
				iVar18 = iVar18 + 0x30;
				iVar19 = iVar19 + 0x110;
				iVar20 = CreateRenderLists_1P2P
													 ((struct VisData *)(&playstationVar23->ptrVertexArray)[2], *ppiVar12, 
														(struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar20), 
														(int)gGT->db[0].drawEnv.ofs + iVar10, ppiVar12[0x20], gGT->numPlyrCurrGame
													 );
				iVar15 = iVar15 + 1;
				gGT->numVisDataLinks = gGT->numVisDataLinks + iVar20;
			} while (iVar15 < 2);
			iVar19 = 0;
			iVar15 = 0x168;
			DrawLevelOvr2P
								(gGT->LevRenderLists, gGT->camera110, (struct VisData *)playstationVar23, 
								 &gGT->backBuffer->primMem, gGT->visMem1->visFaceList[0], gGT->visMem1->visFaceList[1]
								 , level->ptr_tex_waterEnvMap);
			psVar17 = gGT;
			do {
				iVar18 = iVar15 - 0x20;
				psVar14 = psVar17->camera110;
				psVar17 = (struct GameTracker *)(psVar17->db[1].drawEnv.dr_env.code + 0xd);
				iVar15 = iVar15 + 0x110;
				iVar19 = iVar19 + 1;
				CAM_SkyboxGlow(&level->glowGradient[0].pointFrom, 
											 (struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar18), 
											 &gGT->backBuffer->primMem, psVar14->ptrOT + 0x3ff);
			} while (iVar19 < 2);
		}
		else if (bVar2 < 3) {
			if (bVar2 == 1) {
				CTR_ClearRenderLists_1P2P(gGT, 1);
				if (((level->configFlags & 4U) == 0) && (level != (struct Level *)0x0)) {
					AnimateWater1P(gGT->timer, level->count_water, level->ptr_water, level->ptr_tex_waterEnvMap, 
												 gGT->visMem1->visOVertList[0]);
				}
				else {
					AnimateQuad(gGT->timer << 7, level->numSCVert, level->ptrSCVert, 
											(int *)gGT->visMem1->visSCVertList[0]);
				}
				iVar19 = sdata_gGT->camera110[0].distanceToScreen_PREV;
				if ((sdata_gGT->levelID == ADVENTURE_CHARACTER_SELECT) ||
					 (((sdata_gGT->gameMode1 & 0x20000000U) != 0 && (sdata_gGT->levelID != INTRO_CRASH)))) {
					DAT_1f800014 = 0x1e00;
					DAT_1f800018 = 0x640;
					DAT_1f80001c = 0x640;
					DAT_1f800020 = 0x500;
					DAT_1f800024 = 0x280;
					DAT_1f800028 = 0x140;
					DAT_1f80002c = 0x780;
				}
				else {
					iVar15 = iVar19 * 0x2080;
					if (iVar15 < 0) {
						iVar15 = iVar15 + 0xff;
					}
					DAT_1f800024 = iVar19 * 7;
					iVar18 = iVar19 * 0x380;
					DAT_1f800014 = iVar15 >> 8;
					DAT_1f800020 = iVar19 * 0xc;
					DAT_1f800018 = iVar19 * 0x1a;
					DAT_1f80001c = iVar19 * 0x18;
					if (iVar18 < 0) {
						iVar18 = iVar18 + 0xff;
					}
					DAT_1f800028 = iVar18 >> 8;
					DAT_1f80002c = DAT_1f800018 + 0x140;
				}
				VisData_CopyJMPsToScratchpad();
				psVar14 = gGT->camera110;
				iVar19 = CreateRenderLists_1P2P
													 ((struct VisData *)(&playstationVar23->ptrVertexArray)[2], 
														gGT->visMem1->visLeafList[0], psVar14, (u_int)gGT->LevRenderLists, 
														gGT->visMem1->bspList[0], gGT->numPlyrCurrGame);
				gGT->numVisDataLinks = iVar19;
				DrawLevelOvr1P
									(gGT->LevRenderLists, psVar14, (struct VisData *)level->ptr_mesh_info, 
									 &gGT->backBuffer->primMem, gGT->visMem1->visFaceList[0], 
									 (int *)level->ptr_tex_waterEnvMap, in_stack_ffffffb0);
				DrawSky_Full(level->ptr_skybox, psVar14, &gGT->backBuffer->primMem);
				if ((level->configFlags & 1U) != 0) {
					CAM_SkyboxGlow(&level->glowGradient[0].pointFrom, psVar14, &gGT->backBuffer->primMem, 
												 gGT->camera110[0].ptrOT + 0x3ff);
				}
			}
		}
		else if (bVar2 == 3) {
			CTR_ClearRenderLists_3P4P(gGT, 3);
			if ((level->configFlags & 4U) == 0) {
				AnimateWater3P(gGT->timer, level->count_water, level->ptr_water, level->ptr_tex_waterEnvMap, 
											 gGT->visMem1->visOVertList[0], gGT->visMem1->visOVertList[1], 
											 gGT->visMem1->visOVertList[2]);
			}
			iVar15 = 0;
			VisData_CopyJMPsToScratchpad();
			gGT->numVisDataLinks = 0;
			iVar18 = 0x1808;
			iVar19 = 0x168;
			do {
				iVar20 = iVar19 - 0x20;
				iVar10 = iVar18 - 0x20;
				ppiVar12 = gGT->visMem1->visLeafList + iVar15;
				iVar18 = iVar18 + 0x30;
				iVar19 = iVar19 + 0x110;
				iVar20 = CreateRenderLists_3P4P
													 ((struct VisData *)(&playstationVar23->ptrVertexArray)[2], *ppiVar12, 
														(struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar20), 
														(int)gGT->db[0].drawEnv.ofs + iVar10, ppiVar12[0x20]);
				iVar15 = iVar15 + 1;
				gGT->numVisDataLinks = gGT->numVisDataLinks + iVar20;
			} while (iVar15 < 3);
			iVar19 = 0;
			iVar15 = 0x168;
			DrawLevelOvr3P
								(gGT->LevRenderLists, gGT->camera110, (struct VisData *)playstationVar23, 
								 &gGT->backBuffer->primMem, gGT->visMem1->visFaceList[0], gGT->visMem1->visFaceList[1]
								 , gGT->visMem1->visFaceList[2]);
			psVar17 = gGT;
			do {
				iVar18 = iVar15 - 0x20;
				psVar14 = psVar17->camera110;
				psVar17 = (struct GameTracker *)(psVar17->db[1].drawEnv.dr_env.code + 0xd);
				iVar15 = iVar15 + 0x110;
				iVar19 = iVar19 + 1;
				CAM_SkyboxGlow(&level->glowGradient[0].pointFrom, 
											 (struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar18), 
											 &gGT->backBuffer->primMem, psVar14->ptrOT + 0x3ff);
			} while (iVar19 < 3);
		}
		else if (bVar2 == 4) {
			CTR_ClearRenderLists_3P4P(gGT, 4);
			if ((level->configFlags & 4U) == 0) {
				AnimateWater4P(gGT->timer, level->count_water, level->ptr_water, level->ptr_tex_waterEnvMap, 
										 gGT->visMem1->visOVertList[0], gGT->visMem1->visOVertList[1], 
										 gGT->visMem1->visOVertList[2], gGT->visMem1->visOVertList[3]);
			}
			iVar15 = 0;
			VisData_CopyJMPsToScratchpad();
			gGT->numVisDataLinks = 0;
			iVar18 = 0x1808;
			iVar19 = 0x168;
			do {
				iVar20 = iVar19 - 0x20;
				iVar10 = iVar18 - 0x20;
				ppiVar12 = gGT->visMem1->visLeafList + iVar15;
				iVar18 = iVar18 + 0x30;
				iVar19 = iVar19 + 0x110;
				iVar20 = CreateRenderLists_3P4P
													 ((struct VisData *)(&playstationVar23->ptrVertexArray)[2], *ppiVar12, 
														(struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar20), 
														(int)gGT->db[0].drawEnv.ofs + iVar10, ppiVar12[0x20]);
				iVar15 = iVar15 + 1;
				gGT->numVisDataLinks = gGT->numVisDataLinks + iVar20;
			} while (iVar15 < 4);
			iVar19 = 0;
			iVar15 = 0x168;
			DrawLevelOvr4P
								(gGT->LevRenderLists, gGT->camera110, (struct VisData *)playstationVar23, 
								 &gGT->backBuffer->primMem, gGT->visMem1->visFaceList[0], gGT->visMem1->visFaceList[1]
								 , gGT->visMem1->visFaceList[2]);
			psVar17 = gGT;
			do {
				iVar18 = iVar15 - 0x20;
				psVar14 = psVar17->camera110;
				psVar17 = (struct GameTracker *)(psVar17->db[1].drawEnv.dr_env.code + 0xd);
				iVar15 = iVar15 + 0x110;
				iVar19 = iVar19 + 1;
				CAM_SkyboxGlow(&level->glowGradient[0].pointFrom, 
											 (struct Camera110 *)((int)gGT->db[0].drawEnv.ofs + iVar18), 
											 &gGT->backBuffer->primMem, psVar14->ptrOT + 0x3ff);
			} while (iVar19 < 4);
		}
		iVar19 = 0;
		if (gGT->numPlyrCurrGame != '\0') {
			psVar14 = gGT->camera110;
			psVar17 = gGT;
			iVar15 = 0x168;
			do {
				psVar3 = psVar17->camera110;
				psVar17 = (struct GameTracker *)(psVar17->db[1].drawEnv.dr_env.code + 0xd);
				Camera110_SetDrawEnv_Normal(psVar3->ptrOT + 0x3ff, psVar14, gGT->backBuffer, (short *)0x0, '\0')
				;
				iVar19 = iVar19 + 1;
				psVar14 = (struct Camera110 *)((int)gGT->camera110[0].pos + iVar15 - 0x58);
				iVar15 = iVar15 + 0x110;
			} while (iVar19 < (int)(u_int)(u_char)gGT->numPlyrCurrGame);
		}
		if (((sdata_gGT->hudFlags & 1U) != 0) && (1 < (u_char)sdata_gGT->numPlyrCurrGame)) {
			DrawHUD_Wumpa3D_2P3P4P(gGT);
		}
		if (((gGT->renderFlags & 0x100) != 0) && (1 < (u_char)sdata_gGT->numPlyrCurrGame)) {
			DecalMP_03(gGT);
		}
		if (((gGT->gameMode1 & 0x20102000U) == 0) && (sdata->Loading.stage != -4)) {
			DotLights_AudioAndVideo(gGT);
		}
		if ((sdata_gGT->renderFlags & 0x8000) != 0) {
			if ((((sdata_gGT->gameMode1 & 0x20U) != 0) && (2 < (u_char)sdata_gGT->numPlyrCurrGame)) &&
				 (iVar19 = 0, sdata_gGT->numPlyrCurrGame != '\0')) {
				iVar15 = 0;
				do {
					local_30.x = *(short *)((int)sdata_gGT->camera110[0].matrix_ViewProj.m[-2] + iVar15);
					local_30.y = *(short *)((int)sdata_gGT->camera110[0].matrix_ViewProj.m[-2] + iVar15 + 2);
					local_30.w = *(short *)((int)sdata_gGT->camera110[0].matrix_ViewProj.m[-2] + iVar15 + 4);
					local_30.h = *(short *)((int)sdata_gGT->camera110[0].matrix_ViewProj.m[-1] + iVar15);
					DrawBoxOutline_LowLevel
										(&local_30, 4, 2, 
										 data.ptrColor[(sdata_gGT->drivers[iVar19]->BattleHUD).teamID + 0x18], 0, 
										 (sdata_gGT->camera110_UI).ptrOT + 3);
					iVar19 = iVar19 + 1;
					iVar15 = iVar15 + 0x110;
				} while (iVar19 < (int)(u_int)(u_char)sdata_gGT->numPlyrCurrGame);
			}
			if (1 < (u_char)sdata_gGT->numPlyrCurrGame) {
				pvVar8 = (sdata_gGT->backBuffer->primMem).curr;
				*(u_char *)((int)pvVar8 + 3) = 5;
				*(u_char *)((int)pvVar8 + 7) = 0x28;
				*(u_char *)((int)pvVar8 + 6) = 0;
				*(u_char *)((int)pvVar8 + 5) = 0;
				*(u_char *)((int)pvVar8 + 4) = 0;
				psVar17 = sdata_gGT;
				*(u_short *)((int)pvVar8 + 10) = 0x6a;
				*(u_short *)((int)pvVar8 + 0xe) = 0x6a;
				*(u_short *)((int)pvVar8 + 8) = 0;
				*(u_short *)((int)pvVar8 + 0xc) = 0x200;
				*(u_short *)((int)pvVar8 + 0x10) = 0;
				*(u_short *)((int)pvVar8 + 0x12) = 0x6e;
				*(u_short *)((int)pvVar8 + 0x14) = 0x200;
				*(u_short *)((int)pvVar8 + 0x16) = 0x6e;
				AddPrim((psVar17->camera110_UI).ptrOT + 3, pvVar8);
				(sdata_gGT->backBuffer->primMem).curr =
						 (void *)((int)(sdata_gGT->backBuffer->primMem).curr + 0x18);
			}
			if (2 < (u_char)sdata_gGT->numPlyrCurrGame) {
				pvVar8 = (sdata_gGT->backBuffer->primMem).curr;
				*(u_char *)((int)pvVar8 + 3) = 5;
				*(u_char *)((int)pvVar8 + 7) = 0x28;
				*(u_char *)((int)pvVar8 + 6) = 0;
				*(u_char *)((int)pvVar8 + 5) = 0;
				*(u_char *)((int)pvVar8 + 4) = 0;
				psVar17 = sdata_gGT;
				*(u_short *)((int)pvVar8 + 8) = 0xfd;
				*(u_short *)((int)pvVar8 + 0x10) = 0xfd;
				*(u_short *)((int)pvVar8 + 10) = 0;
				*(u_short *)((int)pvVar8 + 0xc) = 0x103;
				*(u_short *)((int)pvVar8 + 0xe) = 0;
				*(u_short *)((int)pvVar8 + 0x12) = 0xd8;
				*(u_short *)((int)pvVar8 + 0x14) = 0x103;
				*(u_short *)((int)pvVar8 + 0x16) = 0xd8;
				AddPrim((psVar17->camera110_UI).ptrOT + 3, pvVar8);
				(sdata_gGT->backBuffer->primMem).curr =
						 (void *)((int)(sdata_gGT->backBuffer->primMem).curr + 0x18);
			}
			if (sdata_gGT->numPlyrCurrGame == '\x03') {
				pvVar8 = (sdata_gGT->backBuffer->primMem).curr;
				*(u_char *)((int)pvVar8 + 3) = 5;
				*(u_char *)((int)pvVar8 + 7) = 0x28;
				*(u_char *)((int)pvVar8 + 6) = 0;
				*(u_char *)((int)pvVar8 + 5) = 0;
				*(u_char *)((int)pvVar8 + 4) = 0;
				*(u_short *)((int)pvVar8 + 8) = 0x100;
				*(u_short *)((int)pvVar8 + 0x10) = 0x100;
				psVar17 = sdata_gGT;
				*(u_short *)((int)pvVar8 + 10) = 0x6c;
				*(u_short *)((int)pvVar8 + 0xe) = 0x6c;
				*(u_short *)((int)pvVar8 + 0xc) = 0x200;
				*(u_short *)((int)pvVar8 + 0x12) = 0xd8;
				*(u_short *)((int)pvVar8 + 0x14) = 0x200;
				*(u_short *)((int)pvVar8 + 0x16) = 0xd8;
				AddPrim((psVar17->camera110_UI).ptrOT + 3, pvVar8);
				(sdata_gGT->backBuffer->primMem).curr =
						 (void *)((int)(sdata_gGT->backBuffer->primMem).curr + 0x18);
			}
		}
		if (sdata->Loading.stage == -1) {
			if ((sdata_gGT->gameMode1 & 0xfU) == 0) {
				RobotcarWeapons_Update();
			}
			StartLine_Update();
		}
	}
	if ((sdata_gGT->gameMode1 & 0x302000U) != 0) {
		unk80047d64();
	}
	if (((sdata_gGT->renderFlags & 0x2000) != 0) &&
		 ((gGT->level1->clearColor[0].enable != '\0' || (gGT->level1->clearColor[1].enable != '\0')))) {
		CAM_ClearScreen(gGT);
	}
	if ((sdata_gGT->renderFlags & 0x1000) != 0) {
		CheckeredFlag_DrawSelf();
	}
	Camera110_SetDrawEnv_Normal
						((gGT->camera110_UI).ptrOT + 4, &gGT->camera110_UI, gGT->backBuffer, (short *)0x0, '\0');
	iVar19 = RCNT_GetTime_Total();
	psVar17 = sdata_gGT;
	gGT->countTotalTime = iVar19;
	if ((psVar17->renderFlags & 0x1000) != 0) {
		VSync(0);
	}
	cVar4 = sdata_gGT->bool_DrawOTag_InProgress;
	while( true ) {
		if ((cVar4 == '\0') && (sdata->vsyncTillFlip < 1)) goto LAB_800378d0;
		if (6 < (u_int)sdata_gGT->vSync_between_drawSync) break;
		cVar4 = sdata_gGT->bool_DrawOTag_InProgress;
	}
	BreakDraw();
LAB_800378d0:
	if (sdata->boolPlayVideoSTR == 1) {
		MM_Video_CheckIfFinished(1);
		MoveImage((RECT *)&sdata->videoSTR_src_vramRect, sdata->videoSTR_dst_vramX, sdata->videoSTR_dst_vramY);
		DrawSync(0);
	}
	iVar19 = RCNT_GetTime_Elapsed(gGT->countTotalTime, (void *)0x0);
	gGT->countTotalTime = iVar19;
	if (gGT->frontBuffer != (struct DB *)0x0) {
		sdata->vsyncTillFlip = 2;
		uVar6 = sdata->boolDebugDispEnv & 1;
		sdata_gGT->unk1cc4[5] = sdata_gGT->unk1cc4[0];
		if (uVar6 == 0) {
			env = &gGT->frontBuffer->dispEnv;
		}
		else {
			env = (DISPENV *)&sdata->blank_debug_DispEnv;
		}
		PutDispEnv(env);
		PutDrawEnv(&gGT->frontBuffer->drawEnv);
		gGT->frontBuffer = (struct DB *)0x0;
	}
	psVar17 = sdata_gGT;
	gGT->frontBuffer = (struct DB *)((int)gGT - (gGT->swapchainIndex * 0xa4 - 0xbc));
	psVar17->bool_DrawOTag_InProgress = '\x01';
	DrawOTag(gGT->camera110[0].ptrOT + 0x3ff);
	gGT->frameTimer_notPaused = gGT->frameTimer_VsyncCallback;
	return;
}

