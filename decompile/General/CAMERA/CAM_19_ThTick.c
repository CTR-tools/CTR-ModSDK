#include <common.h>

void DECOMP_CAM_ThTick(struct Thread *t)
{
	short sVar1;
	int bVar2;
	struct GameTracker *psVar3;
	u_short uVar4;
	short sVar5;
	short sVar6;
	int iVar7;
	int iVar8;
	u_int uVar9;
	u_int uVar10;
	struct PVS *psVar11;
	int *piVar12;
	struct Instance **ppsVar13;
	struct SpawnType1 *psVar14;
	struct CheckpointNode *psVar15;
	u_int uVar16;
	int iVar17;
	int iVar18;
	short *psVar19;
	short *psVar20;
	short *psVar21;
	u_int uVar22;
	struct CameraDC *cDC;
	struct TileView *tv;
	struct ZoomData *psVar23;
	struct Driver *d;
	short *scratchpad;
	int iVar24;
	int iVar25;
	short local_28;
	short local_26;
	short local_24;
	
	struct GameTracker* gGT = sdata->gGT;
	scratchpad = (short *)0x1f800108;
	cDC = (struct CameraDC *)t->inst;
	d = cDC->driverToFollow;
	tv = cDC->tileView;

	if ((cDC->flags & 0x8000) != 0)
	{
		return;
	}

	if
	(
		(
			(
				((gGT->gameMode1 & (PAUSE_ALL | START_OF_RACE | MAIN_MENU | GAME_CUTSCENE)) == 0) &&
				(d->instSelf->thread->funcThTick == 0)
			) && ((d->actionsFlagSet & 0x100000) == 0)
		) &&
		(
			(
				(d->kartState != WARP_PAD && (d->kartState != FREEZE)) &&
				(((gGT->gameMode2 & 4) == 0 && ((sdata->gGamepads->gamepad[cDC->cameraID].buttonsTapped & 0x80U) != 0)))
			)
		)
	)
	{
		uVar4 = cDC->unk92 + 1;
		cDC->unk92 = uVar4;
		if (1 < uVar4)
		{
			cDC->unk92 = 0;
		}
		if (cDC->unk92 == 2)
		{
			cDC->cameraMode = 0xf;
		}
		else
		{
			cDC->nearOrFar = cDC->unk92;
			cDC->cameraMode = 0;
		}
	}
	
	psVar23 = &data.NearCam4x3;
	if (gGT->numPlyrCurrGame == 2)
		psVar23 = &data.NearCam8x3;
	
	psVar23 = &psVar23[cDC->nearOrFar];

	if ((cDC->flags & 0x20) == 0) goto SkipNewCameraEOR;
	
	psVar14 = gGT->level1->ptrSpawnType1;
	
	psVar21 = 0;
	if (psVar14->count < 3) goto SkipNewCameraEOR;
	
	void** ptrs = ST1_GETPOINTERS(psVar14);
	psVar19 = ptrs[ST1_CAMERA_EOR];
	
	// number of EOR cameras
	sVar6 = *psVar19;
	
	local_28 = (short)((u_int)d->posCurr[0] >> 8);
	local_26 = (short)((u_int)d->posCurr[1] >> 8);
	local_24 = (short)((u_int)d->posCurr[2] >> 8);
	
	// advance to first EOR
	psVar20 = psVar19 + 1;

	if (sVar6 != 0)
	{
		uVar22 = (u_int)d->unknown_in_FUN_8005ca24[1];
		
		// pointer to modeID in EOR camera
		psVar19 += 2;
		
		for(; sVar6 != 0; sVar6--)
		{
			// camera mode
			iVar7 = (int)*psVar19;
			if (iVar7 < 0)
			{
				iVar7 = -iVar7;
			}
			
			// respawnPoint
			uVar16 = (u_int)*psVar20;
			
			// +2 to include respawnPoint and modeID
			psVar20 = (short *)((int)psVar19 + data.EndOfRace_Camera_Size[iVar7] + 2);
			
			psVar15 = gGT->level1->ptr_restart_points;
			if (
					(uVar22 == uVar16) || 
					(uVar22 == (u_char)psVar15[uVar16].nextIndex_forward) || 
					(uVar22 == (u_char)psVar15[uVar16].nextIndex_left) || 
					(uVar22 == (u_char)psVar15[uVar16].nextIndex_backward) || 
					(uVar22 == (u_char)psVar15[uVar16].nextIndex_right)
				)
			{
				psVar21 = psVar19;
			}
			psVar19 = psVar20 + 1;
		}
	}

	// if no EOR found, or EOR is already in-use
	if ((psVar21 == 0) || (psVar21 == cDC->currEOR)) goto SkipNewCameraEOR;

	cDC->currEOR = (int)psVar21;
	
	sVar6 = *psVar21;
	psVar19 = psVar21 + 1;
	sVar5 = sVar6;
	if (sVar6 < 0)
	{
		sVar5 = -sVar6;
	}
	cDC->cameraMode = sVar5;
	uVar22 = cDC->flags & 0xffffefff;
	cDC->flags = uVar22 | 9;
	if (sVar6 < 0)
	{
		cDC->flags = uVar22 | 0x1009;
	}
	cDC->flags = cDC->flags | 0x1000;

	switch(cDC->cameraMode)
	{
		case 0:
			tv->pos[0] = *(short *)(d->instSelf->matrix).t;
			tv->pos[1] = *(short *)((d->instSelf->matrix).t + 1);
			tv->pos[2] = *(short *)((d->instSelf->matrix).t + 2);
			tv->rot[0] = (d->rotCurr).x;
			tv->rot[1] = (d->rotCurr).y;
			tv->rot[2] = (d->rotCurr).z;
			*(u_short *)&cDC->unk_c0 = 0;
			break;
		case 3:
			tv->pos[0] = *psVar19;
			tv->pos[1] = psVar21[2];
			tv->pos[2] = psVar21[3];
			tv->rot[0] = psVar21[4];
			tv->rot[1] = psVar21[5];
			tv->rot[2] = psVar21[6];
			*(short *)&cDC->action = *psVar19;
			*(short *)((int)&cDC->action + 2) = psVar21[2];
			*(short *)&cDC->mode = psVar21[3];
			*(short *)&cDC->unk0xC = psVar21[4];
			*(short *)((int)&cDC->unk0xC + 2) = psVar21[5];
			cDC->desiredRot[0] = psVar21[6];
			break;
		case 4:
			tv->pos[0] = *psVar19;
			tv->pos[1] = psVar21[2];
			tv->pos[2] = psVar21[3];
			break;
		case 7:
			(cDC->transitionTo).pos[0] = *psVar19;
			sVar6 = psVar21[2];
			uVar22 = cDC->flags & 0xffffffbf;
			cDC->flags = uVar22;
			(cDC->transitionTo).pos[1] = sVar6;
			if (psVar21[3] != 0)
			{
				cDC->flags = uVar22 | 0x40;
			}
			break;
		case 8:
		case 14:
			cDC->driverOffset_CamEyePos[0] = *psVar19;
			sVar6 = cDC->driverOffset_CamEyePos[0];
			cDC->driverOffset_CamEyePos[1] = psVar21[2];
			sVar5 = cDC->driverOffset_CamEyePos[1];
			cDC->driverOffset_CamEyePos[2] = psVar21[3];
			sVar1 = cDC->driverOffset_CamEyePos[2];
			cDC->driverOffset_CamLookAtPos[0] = psVar21[4];
			cDC->driverOffset_CamLookAtPos[1] = psVar21[5];
			cDC->driverOffset_CamLookAtPos[2] = psVar21[6];
			iVar7 = MapToRange((int)sVar6 * (int)sVar6 + (int)sVar5 * (int)sVar5 + (int)sVar1 * (int)sVar1, 0x10000, 0x190000, 0x80, 0xf0);
			cDC->unk7A = (short)iVar7;
			break;
		case 9:
		case 13:
			sVar6 = *psVar19;
			psVar15 = gGT->level1->ptr_restart_points;
			cDC->unk94 = 0;
			cDC->unk88 = psVar15 + sVar6;
			(cDC->transitionTo).pos[0] = psVar21[2];
			(cDC->transitionTo).pos[1] = psVar21[3];
			(cDC->transitionTo).pos[2] = psVar21[4];
			(cDC->transitionTo).rot[0] = psVar21[5];
			(cDC->transitionTo).rot[1] = psVar21[6];
			(cDC->transitionTo).rot[2] = psVar21[7];
			*(short *)cDC->unk_b0 = psVar21[8];
			break;
		case 10:
			sVar6 = *psVar19;
			psVar19 = psVar21 + 2;
			goto LAB_8001b928;
		case 11:
			sVar6 = *(short *)&tv->distanceToScreen_CURR;
			tv->pos[0] = *psVar19;
			tv->pos[1] = psVar21[2];
			tv->pos[2] = psVar21[3];
			psVar19 = psVar21 + 5;
			sVar6 = psVar21[4] - sVar6;
LAB_8001b928:
			(cDC->transitionTo).pos[0] = sVar6;
			(cDC->transitionTo).pos[1] = *psVar19;
			(cDC->transitionTo).pos[2] = psVar19[1];
			break;
		case 12:
			(cDC->transitionTo).pos[0] = *psVar19;
			(cDC->transitionTo).pos[1] = psVar21[2];
			(cDC->transitionTo).pos[2] = psVar21[3];
			(cDC->transitionTo).rot[0] = psVar21[4];
			(cDC->transitionTo).rot[1] = psVar21[5];
			(cDC->transitionTo).rot[2] = psVar21[6];
			*(short *)cDC->unk_b0 = psVar21[7];
			*(short *)(cDC->unk_b0 + 2) = psVar21[8];
			*(short *)(cDC->unk_b0 + 4) = psVar21[9];
			*(short *)(cDC->unk_b0 + 6) = psVar21[10];
	}

SkipNewCameraEOR:

	tv->distanceToScreen_PREV = tv->distanceToScreen_CURR;
	sVar6 = cDC->cameraMode;

	if (sVar6 != 0)
	{
		sVar5 = cDC->cameraMode;
		*(u_short *)(cDC->data14 + 0x12) = 0;
		if (sVar6 != 0)
		{
			if (sVar6 == 4)
			{
LAB_8001c11c:
				CAM_LookAtPosition((int)scratchpad, d->posCurr, tv->pos, tv->rot);
				psVar21 = scratchpad;
LAB_8001c128:
				*(int *)(psVar21 + 0x120) = (int)tv->pos[0];
				*(int *)(psVar21 + 0x122) = (int)tv->pos[1];
				sVar6 = tv->pos[2];
				scratchpad = psVar21;
			}
			else
			{
				psVar21 = scratchpad;
				if (sVar6 == 10)
				{
					CAM_FollowDriver_Spin360(cDC, (u_int)0x1f800108, d, tv->pos, (u_int)tv->rot);
					goto LAB_8001c128;
				}
				if (sVar6 != 0xb)
				{
					if (sVar6 == 0xc)
					{
						if (cDC->cameraModePrev != 0xc)
						{
							cDC->unk8E = 0;
						}
						local_28 = (short)((u_int)d->posCurr[0] >> 8);
						local_26 = (short)((u_int)d->posCurr[1] >> 8);
						local_24 = (short)((u_int)d->posCurr[2] >> 8);
						iVar8 = CAM_MapRange_PosPoints((cDC->transitionTo).pos, (cDC->transitionTo).rot, &local_28);
						iVar17 = (int)*(short *)(cDC->unk_b0 + 6);
						local_28 = *(short *)cDC->unk_b0 - (cDC->transitionTo).rot[0];
						local_26 = *(short *)(cDC->unk_b0 + 2) - (cDC->transitionTo).rot[1];
						iVar7 = iVar17;
						if (iVar17 < 0)
						{
							iVar7 = -iVar17;
						}
						local_24 = *(short *)(cDC->unk_b0 + 4) - (cDC->transitionTo).rot[2];
						if (iVar17 < 0)
						{
							local_28 = -local_28;
							local_26 = -local_26;
							local_24 = -local_24;
						}
						iVar24 = SquareRoot0_stub((int)local_28 * (int)local_28 + (int)local_26 * (int)local_26 + (int)local_24 * (int)local_24);
						iVar18 = cDC->unk94 << 0xc;
						iVar25 = iVar18 / iVar24;
						/*
						if (iVar24 == 0)
						{
							trap(0x1c00);
						}
						if ((iVar24 == -1) && (iVar18 == -0x80000000))
						{
							trap(0x1800);
						}
						*/
						cDC->unk94 = cDC->unk94 + (((cDC->unk8E * 0x1000) / 0x1e) * iVar7 >> 0xc);
						if (iVar8 < 1)
						{
							if (iVar25 < 0x1001)
							{
								if (cDC->unk8E < 0x1e)
								{
									cDC->unk8E = cDC->unk8E + 1;
								}
							}
							else if (cDC->unk8E != 0)
							{
								cDC->unk8E = cDC->unk8E + -1;
							}
						}
						else
						{
							cDC->unk94 = 0;
							cDC->unk8E = 0;
						}
						psVar21 = (cDC->transitionTo).rot;
						if (iVar17 < 0)
						{
							psVar21 = (short *)cDC->unk_b0;
						}
						tv->pos[0] = *psVar21 + (short)(local_28 * iVar25 >> 0xc);
						tv->pos[1] = psVar21[1] + (short)(local_26 * iVar25 >> 0xc);
						tv->pos[2] = psVar21[2] + (short)(local_24 * iVar25 >> 0xc);
						goto LAB_8001c11c;
					}
					if (sVar6 == 7)
					{
						tv->pos[0] = (short)((u_int)d->posCurr[0] >> 8);
						tv->pos[1] = (cDC->transitionTo).pos[0] + (short)((u_int)d->posCurr[1] >> 8);
						tv->pos[2] = (short)((u_int)d->posCurr[2] >> 8);
						sVar6 = (cDC->transitionTo).pos[1];
						tv->rot[1] = 0;
						tv->rot[2] = 0;
						tv->rot[0] = sVar6 + 0x400;
						psVar21 = (short *)0x1f800108;
						if ((cDC->flags & 0x40) != 0)
						{
							tv->rot[1] = d->angle + 0x800;
						}
					}
					else if ((u_short)(sVar5 - 0xfU) < 2)
					{
						tv->pos[0] = sdata->FirstPersonCamera.posOffset[0] + (short)((u_int)d->posCurr[0] >> 8);
						tv->pos[1] = sdata->FirstPersonCamera.posOffset[1] + (short)((u_int)d->posCurr[1] >> 8);
						tv->pos[2] = sdata->FirstPersonCamera.posOffset[2] + (short)((u_int)d->posCurr[2] >> 8);
						if (cDC->cameraMode == 0x10)
						{
							tv->rot[0] = sdata->FirstPersonCamera.rotOffset[0] + (d->rotCurr).x;
							sVar6 = sdata->FirstPersonCamera.rotOffset[1] + d->angle;
						}
						else
						{
							tv->rot[0] = sdata->FirstPersonCamera.rotOffset[0] + (d->rotCurr).x;
							sVar6 = sdata->FirstPersonCamera.rotOffset[1] + (d->rotCurr).y;
						}
						tv->rot[1] = sVar6;
						tv->rot[2] = sdata->FirstPersonCamera.rotOffset[2] + (d->rotCurr).z;
					}
					else
					{
						if ((sVar6 == 8) || (sVar6 == 0xe))
						{
							if ((d->botFlags & 2U) == 0)
							{
								if ((cDC->driver5B0_prevFrame & 2) != 0)
								{
									cDC->flags = cDC->flags | 9;
								}
								CAM_FollowDriver_AngleAxis(cDC, d, (int)0x1f800108, tv->pos, tv->rot);
							}
							else
							{
								if ((cDC->driver5B0_prevFrame & 2) == 0)
								{
									cDC->flags = cDC->flags | 9;
								}
								CAM_FollowDriver_Normal(cDC, d, tv->pos, 0x1f800108, &psVar23->distMin);
							}
							cDC->driver5B0_prevFrame = d->botFlags;
							goto LAB_8001c150;
						}
						if ((cDC->cameraMode == 9) || (psVar21 = (short *)0x1f800108, cDC->cameraMode == 0xd))
						{
							if ((gGT->level1->cnt_restart_points != 0) && ((gGT->gameMode1 & 0xf) == 0))
							{
								uVar9 = CAM_FollowDriver_TrackPath(cDC, (short *)0x1f800390, (int)*(short *)cDC->unk_b0, 1);
								iVar7 = -0xc0;
								if (-1 < *(short *)cDC->unk_b0)
								{
									iVar7 = 0xc0;
								}
								uVar10 = CAM_FollowDriver_TrackPath(cDC, (short *)0x1f800398, iVar7, 0);
								iVar8 = ((uVar10 - uVar9) + 0x800 & 0xfff) - 0x800;
								*(short *)0x1f800314 = 0x800;
								*(short *)0x1f800316 = (short)uVar9 + (short)(iVar8 >> 1);
								*(short *)0x1f800318 = 0;
								*(short *)0x1f800390 = (short)((int)(*(short *)0x1f800390) + (int)(*(short *)0x1f800398) >> 1);
								*(short *)0x1f800392 = (short)((int)(*(short *)0x1f800392) + (int)(*(short *)0x1f80039a) >> 1);
								iVar7 = (int)(*(short *)0x1f80039c);
								*(short *)0x1f800394 = (short)((*(short *)0x1f800394) + iVar7 >> 1);
								ConvertRotToMatrix((MATRIX *)0x1f800328, (short *)0x1f800314);
								gte_SetRotMatrix((MATRIX *)0x1f800328);
								gte_ldv0((SVECTOR *)&cDC->transitionTo);
								gte_rtv0();

								// get the result
								#define read_mt(r0, r1, r2) 	__asm__ volatile( \
									"mfc2   %0, $25;"  \
									"mfc2   %1, $26;"  \
									"mfc2   %2, $27;"  \
									: : "r"(r0), "r"(r1), "r"(r2))

								read_mt(uVar9, iVar7, iVar8);

								tv->pos[0] = scratchpad[0x144] + (short)uVar9;
								tv->pos[1] = scratchpad[0x145] + (short)iVar7;
								tv->pos[2] = scratchpad[0x146] + (short)iVar8;
								tv->rot[0] = scratchpad[0x106] + (cDC->transitionTo).rot[0];
								tv->rot[1] = scratchpad[0x107] + (cDC->transitionTo).rot[1];
								tv->rot[2] = scratchpad[0x108] + (cDC->transitionTo).rot[2];
							}
							psVar21 = scratchpad;
							if (cDC->cameraMode == 0xd) goto LAB_8001c11c;
						}
					}
					goto LAB_8001c128;
				}
				CAM_LookAtPosition((int)0x1f800108, d->posCurr, tv->pos, tv->rot);
				iVar7 = SquareRoot0_stub((*(short *)0x1f800354) * (*(short *)0x1f800354) + (*(short *)0x1f80035c) * (*(short *)0x1f80035c));
				iVar17 = (int)(cDC->transitionTo).pos[0];
				iVar24 = (iVar7 - (cDC->transitionTo).pos[1]) * iVar17;
				iVar8 = (int)(cDC->transitionTo).pos[2];
				iVar7 = iVar24 / iVar8;
				/*
				if (iVar8 == 0)
				{
					trap(0x1c00);
				}
				if ((iVar8 == -1) && (iVar24 == -0x80000000))
				{
					trap(0x1800);
				}
				*/
				bVar2 = iVar17 < iVar7;
				if (iVar7 < 0)
				{
					iVar7 = 0;
					bVar2 = iVar17 < 0;
				}
				if (bVar2)
				{
					iVar7 = iVar17;
				}
				*(short *)0x1f800348 = (int)tv->pos[0];
				tv->distanceToScreen_PREV = tv->distanceToScreen_CURR + iVar7;
				*(short *)0x1f80034c = (int)tv->pos[1];
				sVar6 = tv->pos[2];
			}
			*(int *)(scratchpad + 0x124) = (int)sVar6;
			CAM_FindClosestQuadblock(scratchpad, cDC, d, (short *)((u_int)scratchpad | 0x240));
			goto LAB_8001c150;
		}
	}

	CAM_FollowDriver_Normal(cDC, d, &tv->pos[0], 0x1f800108, &psVar23->distMin);
	
LAB_8001c150:
	cDC->cameraModePrev = cDC->cameraMode;
	psVar3 = gGT;

	if (cDC->ptrQuadBlock != 0)
	{
		psVar11 = cDC->ptrQuadBlock->pvs;
		if ((psVar11 != 0) && (piVar12 = psVar11->visLeafSrc, piVar12 != 0))
		{
			cDC->visLeafSrc = piVar12;
			psVar3->unk1cac[1] = ((int)cDC->ptrQuadBlock - (int)psVar3->level1->ptr_mesh_info->ptrQuadBlockArray) * -0x1642c859 >> 2;
		}
		if (cDC->ptrQuadBlock != 0)
		{
			psVar11 = cDC->ptrQuadBlock->pvs;
			if ((psVar11 != 0) && (piVar12 = psVar11->visFaceSrc, piVar12 != 0))
			{
				cDC->visFaceSrc = piVar12;
			}
			if (cDC->ptrQuadBlock != 0)
			{
				psVar11 = cDC->ptrQuadBlock->pvs;
				if ((psVar11 != 0) && (ppsVar13 = psVar11->visInstSrc, ppsVar13 != 0))
				{
					cDC->visInstSrc = ppsVar13;
				}
				if (((cDC->ptrQuadBlock != 0) && (psVar11 = cDC->ptrQuadBlock->pvs, psVar11 != 0)) && (piVar12 = psVar11->visExtraSrc, piVar12 != 0))
				{
					if ((gGT->level1->configFlags & 4) == 0)
					{
						cDC->visOVertSrc = piVar12;
					}
					else
					{
						cDC->visSCVertSrc = piVar12;
					}
				}
			}
		}
	}

	if (*(int *)(cDC->unk30fill + 8) == 0)
	{
		cDC->visLeafSrc = 0;
		cDC->visFaceSrc = 0;
	}

	psVar3 = gGT;

	if ((cDC->flags & 1) != 0)
	{
		gGT->rainBuffer[cDC->cameraID].cameraPos[0] = tv->pos[0];
		psVar3->rainBuffer[cDC->cameraID].cameraPos[1] = tv->pos[1];
		psVar3->rainBuffer[cDC->cameraID].cameraPos[2] = tv->pos[2];
		cDC->flags &= ~1;
	}
	cDC->flags &= ~0x88;
	
	return;
}