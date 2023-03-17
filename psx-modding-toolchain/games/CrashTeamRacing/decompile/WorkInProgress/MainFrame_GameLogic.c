#include <common.h>

void MainFrame_GameLogic(struct GameTracker* sdata->gGT, struct GamepadSystem* gGamepads)
{
	bool bVar1;
	struct GamepadSystem* gGamepads_00;
	short sVar2;
	u_int uVar3;
	int iVar4;
	code* pcVar5;
	u_int uVar6;
	u_int uVar7;
	int* piVar8;
	struct Driver* pvVar9;
	struct Driver* psVar9;
	struct Driver* psVar10;
	struct Driver* psVar11;
	struct Driver* pvVar12;
	int iVar12;
	struct TileView* tileView;
	int iVar13;
	struct Thread* psVar14;
	int iVar15;
	int iVar16;
	struct GameTracker* psVar17;
	
	bVar1 = true;
	if ((sdata->gGT->gameMode1 & 0xfU) == 0)
	{
		bVar1 = false;
		tileView = ::sdata->gGT->tileView;
		for (psVar14 = ::sdata->gGT->threadBuckets[0].thread; psVar14 != (struct Thread*)0x0; psVar14 = psVar14->siblingThread)
		{
			pvVar12 = (struct Driver*)psVar14->object;
			if (pvVar12->clockSend)
			{
				pvVar12->clockSend += 0xff;
			}
			uVar3 = (u_int)*(u_char*)((int)&pvVar12->forcedJump_trampoline + 1);
			if (uVar3 == 0)
			{
				if (pvVar12->clockReceive == 0)
				{
					uVar3 = (u_int)pvVar12->clockSend;
					if (uVar3 == 0)
					{
						if ((::sdata->gGT->clockEffectEnabled & 1) == 0) goto LAB_80034e74;
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
				*(char*)((int)&pvVar12->forcedJump_trampoline + 1) = *(char*)((int)&pvVar12->forcedJump_trampoline + 1) - 1;
			}
LAB_80034e74:
			tileView = tileView + 1;
		}
		sdata->gGT->timer = sdata->gGT->timer + 1;
		psVar17 = ::sdata->gGT;
		sdata->gGT->framesInThisLEV += 1;
		psVar17->unk1cc4[4] = 0;
		iVar4 = RCNT_GetTime_Elapsed(sdata->gGT->anotherTimer, &sdata->gGT->anotherTimer);
		iVar4 = (iVar4 << 5) / 100;
		sdata->gGT->elapsedTimeMS = iVar4;
		if (iVar4 < 0)
		{
			sdata->gGT->elapsedTimeMS = 0x20;
		}
		if (0x40 < sdata->gGT->elapsedTimeMS)
		{
			sdata->gGT->elapsedTimeMS = 0x40;
		}
		if ((::sdata->gGT->gameMode1_prevFrame & 0xfU) != 0)
		{
			sdata->gGT->elapsedTimeMS = 0x20;
		}
		sdata->gGT->BoxSceneTimer = sdata->gGT->BoxSceneTimer + sdata->gGT->elapsedTimeMS;
		psVar17 = ::sdata->gGT;
		if (sdata->gGT->trafficLightsTimer < 1)
		{
			if ((::sdata->gGT->gameMode1 & 0x10U) == 0)
			{
				if (sdata->gGT->frozenTimeRemaining < 1)
				{
					if ((::sdata->gGT->gameMode1 & 0x200000U) == 0)
					{
						sdata->gGT->elapsedEventTime = sdata->gGT->elapsedEventTime + sdata->gGT->elapsedTimeMS;
					}
				}
				else
				{
					iVar4 = sdata->gGT->frozenTimeRemaining - sdata->gGT->elapsedTimeMS;
					sdata->gGT->frozenTimeRemaining = iVar4;
					if (iVar4 < 0)
					{
						sdata->gGT->frozenTimeRemaining = 0;
					}
					else
					{
						uVar3 = psVar17->timer;
						if (uVar3 == (uVar3 / 6)*  6)
						{
							if (uVar3 == (uVar3 / 0xc)*  0xc)
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
			sdata->gGT->elapsedEventTime = 0;
		}
		CTR_CycleTex_AllModels(-1, sdata->PLYROBJECTLIST, sdata->gGT->timer);
		CTR_CycleTex_AllModels(sdata->gGT->level1->numModels, (struct Model*)sdata->gGT->level1->ptrModelsPtrArray, sdata->gGT->timer);
		psVar9 = (struct Driver*)0x0;
		psVar10 = (struct Driver*)0x0;
		for (psVar14 = ::sdata->gGT->threadBuckets[0].thread; psVar14 != (struct Thread*)0x0; psVar14 = psVar14->siblingThread)
		{
			pvVar9 = (struct Driver*)psVar14->object;
			psVar11 = psVar10;
			if (pvVar9->driverID == '\0')
			{
LAB_80035098:
				psVar9 = pvVar9;
				psVar10 = psVar11;
			}
			else
			{
				if (pvVar9->driverID == 1)
				{
					psVar10 = pvVar9;
				}
				psVar11 = psVar9;
				if ((u_char)pvVar9->numTimesAttacking < (u_char)psVar9->numTimesAttacking) goto LAB_80035098;
			}
		}
		if
		(
			((psVar9 != (struct Driver*)0x0) && (psVar10 != (struct Driver*)0x0)) &&
			(
				iVar4 = (u_int)(u_char)psVar10->numTimesAttacking - (u_int)(u_char)psVar9->numTimesAttacking, 
				*(short*)(psVar9->unk_4F0_4F8 + 2) < iVar4
			)
		)
		{
			*(short*)(psVar9->unk_4F0_4F8 + 2) = (short)iVar4;
		}
		iVar16 = 0;
		iVar4 = 0;
		iVar15 = 0x1b2c;
		psVar17 = sdata->gGT;
		do
		{
			piVar8 = (int*)((int)sdata->gGT->db[0].drawEnv.ofs + iVar15 - 0x20);
			if ((((::sdata->gGT->gameMode1 & 0x10U) == 0) || ((piVar8[3] & 1U) != 0)) && (*piVar8 != 0))
			{
				if (iVar4 == 0)
				{
					for (psVar14 = ::sdata->gGT->threadBuckets[0].thread; psVar14 != (struct Thread*)0x0; psVar14 = psVar14->siblingThread)
					{
						Weapon_Shoot_OnCirclePress((struct Driver*)psVar14->object);
					}
										
					iVar13 = 0;
					do
					{
						iVar12 =* (int*)((int)&::sdata->gGT->threadBuckets[0].thread + iVar16);
						if (iVar12 != 0)
						{
							do
							{
								if
								(
									(*(int*)(iVar12 + 0x2c) == 0) &&
									(
										pcVar5 =* (code* *)(*(int*)(iVar12 + 0x30) + iVar13*  4 + 0x54), 
										pcVar5 != (code*)0x0
									)
								)
								{
									(*pcVar5)(iVar12);
								}
								iVar12 = *(int*)(iVar12 + 0x10);
							} while (iVar12 != 0);
						}
						iVar13 = iVar13 + 1;
					} while (iVar13 < 0xd);
				}
				ThreadBucketTickAll(psVar17->threadBuckets[0].thread);
			}
			psVar17 = (struct GameTracker*)&psVar17->frontBuffer;
			iVar16 = iVar16 + 0x14;
			iVar4 = iVar4 + 1;
			iVar15 = iVar15 + 0x14;
		} while (iVar4 < 0x11);
		BOTS_UpdateGlobals();
		GhostBuffer_RecordStats(0);
		::sdata->gGT->unk1cc4[4] = (u_int)(::sdata->gGT->unk1cc4[4]*  10000) / 0x147e;
		Particle_UpdateAllParticles();
	}
	else
	{
		psVar14 = sdata->gGT->threadBuckets[0xe].thread;
		if (psVar14 != (struct Thread*)0x0)
		{
			ThreadBucketTickAll(psVar14);
		}
	}
	uVar6 = LOAD_IsOpen_RacingOrBattle();
	if (uVar6 != 0)
	{
		if ((::sdata->gGT->gameMode1 & 0xfU) == 0)
		{
			RB_Bubbles_RoosTubes();
		}
		if (::sdata->gGT->threadBuckets[7].thread != (struct Thread*)0x0)
		{
			RB_Burst_DrawAll((int)::sdata->gGT);
		}
	}
	THREAD_CheckAllForDead();
	if ((::sdata->gGT->gameMode1 & 0xfU) == 0)
	{
		Audio_Update1();
	}
	gGamepads_00 = ::gGamepads;
	sdata->gGT->gameMode1_prevFrame = sdata->gGT->gameMode1;
	uVar6 = GAMEPAD_GetNumConnected(gGamepads_00);
	uVar3 = ::sdata->gGT->gameMode1;
	if ((uVar3 & 0x200000) == 0)
	{
		if ((bVar1) || ((sdata->gGT->gameMode1 & 0xfU) != 0))
		{
			if (::sdata->gGT->cooldownfromPauseUntilUnpause == '\0')
			{
				if
				(
					(
						(sdata->ptrActiveMenuBox != (struct MenuBox*)0x80084190) &&
						(sdata->ptrActiveMenuBox != (struct MenuBox*)&DAT_800b518c)
					) &&
					((sdata->AnyPlayerTap & 0x1000) != 0)
				)
				{
					MenuBox_ClearInput();
					::sdata->gGT->gameMode1 = ::sdata->gGT->gameMode1 & 0xfffffffe;
					MainFrame_TogglePauseAudio(0);
					OtherFX_Play(1, 1);
					MainFreeze_SafeAdvDestroy();
					ElimBG_Deactivate((int)::sdata->gGT);
					MenuBox_Hide(sdata->ptrActiveMenuBox);
					::sdata->gGT->cooldownFromUnpauseUntilPause = '\x05';
				}
			}
			else
			{
				::sdata->gGT->cooldownfromPauseUntilUnpause = ::sdata->gGT->cooldownfromPauseUntilUnpause - 1;
			}
		}
		else if (::sdata->gGT->cooldownFromUnpauseUntilPause == '\0')
		{
			if
			(
				(((uVar3 & 0x20202000) == 0) && (sdata->ptrActiveMenuBox == (struct MenuBox*)0x0)) &&
				(
					(
						sdata->AkuAkuHintState == 0 &&
						(
							(
								uVar7 = CheckeredFlag_IsFullyOnScreen(), uVar7 == 0 &&
								(iVar4 = 0,  sdata->gGT->numPlyrCurrGame != '\0')
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
								(uVar6 != 0) &&
							 	(
							 		(
							 			uVar3 = MainFrame_HaveAllPads((ushort)(u_char)::sdata->gGT->numPlyrNextGame), 
										(uVar3 & 0xffff) == 0 && ((sdata->gGT->gameMode1 & 0xfU) == 0)
									)
							 	)
							) ||
							((gGamepads->gamepad[0].buttonsTapped & 0x1000U) != 0)
						) &&
						(::sdata->gGT->overlayIndex_Threads != -1)
					)
					{
						::sdata->gGT->unknownFlags_1d44 = ::sdata->gGT->gameMode1 & 0x3e0020U | 1;
						MainFreeze_IfPressStart();
						::sdata->gGT->cooldownfromPauseUntilUnpause = '\x05';
					}
					iVar4 = iVar4 + 1;
					gGamepads = (struct GamepadSystem*)(gGamepads->gamepad + 1);
				} while (iVar4 < (int)(u_int)(u_char)sdata->gGT->numPlyrCurrGame);
			}
		}
		else
		{
			::sdata->gGT->cooldownFromUnpauseUntilPause = ::sdata->gGT->cooldownFromUnpauseUntilPause - 1;
		}
	}
	else if (::sdata->gGT->timerEndOfRaceVS == 0)
	{
		uVar3 = ::sdata->gGT->unknownFlags_1d44;
		if ((uVar3 & 0x1000000) == 0)
		{
			if ((uVar3 & 0x8000000) == 0)
			{
				if (::sdata->gGT->unk_timerCooldown_similarTo_1d36 == 0)
				{
					return;
				}
			}
			else if (::sdata->gGT->unk_timerCooldown_similarTo_1d36 == 0)
			{
				if ((uVar3 & 2) == 0)
				{
					return;
				}
				sVar2 = OSK_DrawMenu(0x140);
				if (sVar2 == 0)
				{
					return;
				}
				if (sVar2 == 1)
				{
					*(u_short*)&sdata->unk_saveGame_related = 0;
					LoadSave_ToggleMode(0x41);
					MenuBox_Show((struct MenuBox*)&DAT_80085be0);
					::sdata->gGT->unknownFlags_1d44 = ::sdata->gGT->unknownFlags_1d44 | 0x1000000;
					return;
				}
				::sdata->gGT->newHighScoreIndex = -1;
				::sdata->gGT->unknownFlags_1d44 = ::sdata->gGT->unknownFlags_1d44 & 0xf3ffffff;
				return;
			}
			::sdata->gGT->unk_timerCooldown_similarTo_1d36 = ::sdata->gGT->unk_timerCooldown_similarTo_1d36 - 1;
		}
	}
	else if ((uVar3 & 0x400000) == 0)
	{
		if (::sdata->gGT->timerEndOfRaceVS < 0x96)
		{
			EndOfRace_DrawAllComments();
			EndOfRace_Battle();
		}
		if (0x1e < ::sdata->gGT->timerEndOfRaceVS)
		{
			::sdata->gGT->timerEndOfRaceVS = ::sdata->gGT->timerEndOfRaceVS - 1;
		}
	}
	else
	{
		::sdata->gGT->timerEndOfRaceVS = 0;
	}
	return;
}