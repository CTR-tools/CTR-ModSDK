#include <common.h>

void CAM_ThTick(struct Thread *t)
{
	short sVar1;
	bool bVar2;
	struct GameTracker *psVar3;
	ushort uVar4;
	short sVar5;
	short sVar6;
	int iVar7;
	u_int uVar8;
	u_int uVar9;
	struct PVS *psVar10;
	int *piVar11;
	struct Instance **ppsVar12;
	int iVar13;
	struct SpawnType1 *psVar14;
	struct CheckpointNode *psVar15;
	uint uVar16;
	int iVar17;
	int iVar18;
	short *psVar19;
	short *psVar20;
	short *psVar21;
	uint uVar22;
	struct CameraDC *cDC;
	struct TileView *cam110Pos;
	short *psVar23;
	struct Driver *d;
	short *scratchpad;
	int iVar24;
	int iVar25;
	short local_28;
	short local_26;
	short local_24;
	
	scratchpad = &DAT_1f800108;
	cDC = (struct CameraDC *)t->inst;
	d = cDC->driverToFollow;
	cam110Pos = cDC->tileView;
	if ((cDC->flags & 0x8000) != 0) {
		return;
	}
	if (((((sdata->gGT->gameMode1 & 0x2000204f) == 0) && (d->instSelf->thread->funcThTick == (funcThTick *)0x0)) && ((d->actionsFlagSet & 0x100000) == 0)) && (((d->kartState != WARP_PAD && (d->kartState != FREEZE)) && (((sdata->gGT->gameMode2 & 4) == 0 && ((sdata->gGamepads->gamepad[cDC->cameraID].buttonsTapped & 0x80U) != 0)))))) {
		uVar4 = cDC->unk92 + 1;
		cDC->unk92 = uVar4;
		if (1 < uVar4) {
			cDC->unk92 = 0;
		}
		if (cDC->unk92 == 2) {
			cDC->cameraMode = 0xf;
		}
		else {
			*(short *)((int)&cDC->mode + 2) = cDC->unk92;
			cDC->cameraMode = 0;
		}
	}
	iVar13 = *(short *)((int)&cDC->mode + 2) * 0x24;
	psVar23 = (short *)(iVar13 + -0x7ff7f098);
	if (sdata->gGT->numPlyrCurrGame == '\x02') {
		psVar23 = (short *)(iVar13 + -0x7ff7f086);
	}
	if ((cDC->flags & 0x20) == 0) goto switchD_8001b678_caseD_1;
	psVar14 = sdata->gGT->level1->ptrSpawnType1;
	psVar21 = (short *)0x0;
	if (psVar14->count < 3) goto switchD_8001b678_caseD_1;
	psVar19 = (short *)psVar14[3].count;
	sVar6 = *psVar19;
	local_28 = (short)((uint)d->posCurr[0] >> 8);
	local_26 = (short)((uint)d->posCurr[1] >> 8);
	local_24 = (short)((uint)d->posCurr[2] >> 8);
	psVar20 = psVar19 + 1;
	if (sVar6 != 0) {
		uVar22 = (uint)d->unknown_in_FUN_8005ca24[1];
		psVar19 = psVar19 + 2;
		do {
			iVar13 = (int)*psVar19;
			if (iVar13 < 0) {
				iVar13 = -iVar13;
			}
			uVar16 = (uint)*psVar20;
			psVar20 = (short *)((int)psVar19 + *(short *)(&DAT_80080fb0 + ((iVar13 << 0x10) >> 0xf)) + 2);
			if (((uVar22 == uVar16) || (psVar15 = sdata->gGT->level1->ptr_restart_points, uVar22 == (byte)psVar15[uVar16].nextIndex_forward)) || ((uVar22 == (byte)psVar15[uVar16].nextIndex_left || ((uVar22 == (byte)psVar15[uVar16].nextIndex_backward || (uVar22 == (byte)psVar15[uVar16].nextIndex_right)))))) {
				psVar21 = psVar19;
			}
			sVar6 = sVar6 + -1;
			psVar19 = psVar20 + 1;
		} while (sVar6 != 0);
	}
	if ((psVar21 == (short *)0x0) || (psVar21 == (short *)cDC->unk_DC2)) goto switchD_8001b678_caseD_1;
	cDC->unk_DC2 = (int)psVar21;
	sVar6 = *psVar21;
	psVar19 = psVar21 + 1;
	sVar5 = sVar6;
	if (sVar6 < 0) {
		sVar5 = -sVar6;
	}
	cDC->cameraMode = sVar5;
	uVar22 = cDC->flags & 0xffffefff;
	cDC->flags = uVar22 | 9;
	if (sVar6 < 0) {
		cDC->flags = uVar22 | 0x1009;
	}
	cDC->flags = cDC->flags | 0x1000;
	switch(cDC->cameraMode) {
	case 0:
		cam110Pos->pos[0] = *(short *)(d->instSelf->matrix).t;
		cam110Pos->pos[1] = *(short *)((d->instSelf->matrix).t + 1);
		cam110Pos->pos[2] = *(short *)((d->instSelf->matrix).t + 2);
		cam110Pos->rot[0] = (d->rotCurr).x;
		cam110Pos->rot[1] = (d->rotCurr).y;
		cam110Pos->rot[2] = (d->rotCurr).z;
		*(undefined2 *)&cDC->unk_c0 = 0;
		break;
	case 3:
		cam110Pos->pos[0] = *psVar19;
		cam110Pos->pos[1] = psVar21[2];
		cam110Pos->pos[2] = psVar21[3];
		cam110Pos->rot[0] = psVar21[4];
		cam110Pos->rot[1] = psVar21[5];
		cam110Pos->rot[2] = psVar21[6];
		*(short *)&cDC->action = *psVar19;
		*(short *)((int)&cDC->action + 2) = psVar21[2];
		*(short *)&cDC->mode = psVar21[3];
		*(short *)&cDC->unk0xC = psVar21[4];
		*(short *)((int)&cDC->unk0xC + 2) = psVar21[5];
		cDC->desiredRot[0] = psVar21[6];
		break;
	case 4:
		cam110Pos->pos[0] = *psVar19;
		cam110Pos->pos[1] = psVar21[2];
		cam110Pos->pos[2] = psVar21[3];
		break;
	case 7:
		(cDC->transitionTo).pos[0] = *psVar19;
		sVar6 = psVar21[2];
		uVar22 = cDC->flags & 0xffffffbf;
		cDC->flags = uVar22;
		(cDC->transitionTo).pos[1] = sVar6;
		if (psVar21[3] != 0) {
			cDC->flags = uVar22 | 0x40;
		}
		break;
	case 8:
	case 0xe:
		cDC->driverOffset_CamEyePos[0] = *psVar19;
		sVar6 = cDC->driverOffset_CamEyePos[0];
		cDC->driverOffset_CamEyePos[1] = psVar21[2];
		sVar5 = cDC->driverOffset_CamEyePos[1];
		cDC->driverOffset_CamEyePos[2] = psVar21[3];
		sVar1 = cDC->driverOffset_CamEyePos[2];
		cDC->driverOffset_CamLookAtPos[0] = psVar21[4];
		cDC->driverOffset_CamLookAtPos[1] = psVar21[5];
		cDC->driverOffset_CamLookAtPos[2] = psVar21[6];
		iVar13 = MapToRange((int)sVar6 * (int)sVar6 + (int)sVar5 * (int)sVar5 + (int)sVar1 * (int)sVar1,0x10000,0x190000,0x80,0xf0);
		cDC->unk7A = (short)iVar13;
		break;
	case 9:
	case 0xd:
		sVar6 = *psVar19;
		psVar15 = sdata->gGT->level1->ptr_restart_points;
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
	case 0xb:
		sVar6 = *(short *)&cam110Pos->distanceToScreen_CURR;
		cam110Pos->pos[0] = *psVar19;
		cam110Pos->pos[1] = psVar21[2];
		cam110Pos->pos[2] = psVar21[3];
		psVar19 = psVar21 + 5;
		sVar6 = psVar21[4] - sVar6;
LAB_8001b928:
		(cDC->transitionTo).pos[0] = sVar6;
		(cDC->transitionTo).pos[1] = *psVar19;
		(cDC->transitionTo).pos[2] = psVar19[1];
		break;
	case 0xc:
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
switchD_8001b678_caseD_1:
	cam110Pos->distanceToScreen_PREV = cam110Pos->distanceToScreen_CURR;
	sVar6 = cDC->cameraMode;
	if (sVar6 != 0) {
		sVar5 = cDC->cameraMode;
		*(undefined2 *)(cDC->data14 + 0x12) = 0;
		if (sVar6 != 0) {
			if (sVar6 == 4) {
LAB_8001c11c:
				CAM_LookAtPosition((int)scratchpad,d->posCurr,cam110Pos->pos,cam110Pos->rot);
				psVar21 = scratchpad;
LAB_8001c128:
				*(int *)(psVar21 + 0x120) = (int)cam110Pos->pos[0];
				*(int *)(psVar21 + 0x122) = (int)cam110Pos->pos[1];
				sVar6 = cam110Pos->pos[2];
				scratchpad = psVar21;
			}
			else {
				psVar21 = scratchpad;
				if (sVar6 == 10) {
					CAM_FollowDriver_Spin360(cDC,0x1f800108,d,cam110Pos->pos,(u_int)cam110Pos->rot);
					goto LAB_8001c128;
				}
				if (sVar6 != 0xb) {
					if (sVar6 == 0xc) {
						if (cDC->cameraModePrev != 0xc) {
							cDC->unk8E = 0;
						}
						local_28 = (short)((uint)d->posCurr[0] >> 8);
						local_26 = (short)((uint)d->posCurr[1] >> 8);
						local_24 = (short)((uint)d->posCurr[2] >> 8);
						iVar7 = CAM_MapRange_PosPoints((cDC->transitionTo).pos,(cDC->transitionTo).rot,&local_28);
						iVar17 = (int)*(short *)(cDC->unk_b0 + 6);
						local_28 = *(short *)cDC->unk_b0 - (cDC->transitionTo).rot[0];
						local_26 = *(short *)(cDC->unk_b0 + 2) - (cDC->transitionTo).rot[1];
						iVar13 = iVar17;
						if (iVar17 < 0) {
							iVar13 = -iVar17;
						}
						local_24 = *(short *)(cDC->unk_b0 + 4) - (cDC->transitionTo).rot[2];
						if (iVar17 < 0) {
							local_28 = -local_28;
							local_26 = -local_26;
							local_24 = -local_24;
						}
						iVar24 = SquareRoot0_stub((int)local_28 * (int)local_28 + (int)local_26 * (int)local_26 + (int)local_24 * (int)local_24);
						iVar18 = cDC->unk94 << 0xc;
						iVar25 = iVar18 / iVar24;
						if (iVar24 == 0) {
							trap(0x1c00);
						}
						if ((iVar24 == -1) && (iVar18 == -0x80000000)) {
							trap(0x1800);
						}
						cDC->unk94 = cDC->unk94 + (((cDC->unk8E * 0x1000) / 0x1e) * iVar13 >> 0xc);
						if (iVar7 < 1) {
							if (iVar25 < 0x1001) {
								if (cDC->unk8E < 0x1e) {
									cDC->unk8E = cDC->unk8E + 1;
								}
							}
							else if (cDC->unk8E != 0) {
								cDC->unk8E = cDC->unk8E + -1;
							}
						}
						else {
							cDC->unk94 = 0;
							cDC->unk8E = 0;
						}
						psVar23 = (cDC->transitionTo).rot;
						if (iVar17 < 0) {
							psVar23 = (short *)cDC->unk_b0;
						}
						cam110Pos->pos[0] = *psVar23 + (short)(local_28 * iVar25 >> 0xc);
						cam110Pos->pos[1] = psVar23[1] + (short)(local_26 * iVar25 >> 0xc);
						cam110Pos->pos[2] = psVar23[2] + (short)(local_24 * iVar25 >> 0xc);
						goto LAB_8001c11c;
					}
					if (sVar6 == 7) {
						cam110Pos->pos[0] = (short)((uint)d->posCurr[0] >> 8);
						cam110Pos->pos[1] = (cDC->transitionTo).pos[0] + (short)((uint)d->posCurr[1] >> 8);
						cam110Pos->pos[2] = (short)((uint)d->posCurr[2] >> 8);
						sVar6 = (cDC->transitionTo).pos[1];
						cam110Pos->rot[1] = 0;
						cam110Pos->rot[2] = 0;
						cam110Pos->rot[0] = sVar6 + 0x400;
						psVar21 = &DAT_1f800108;
						if ((cDC->flags & 0x40) != 0) {
							cam110Pos->rot[1] = d->angle + 0x800;
						}
					}
					else if ((ushort)(sVar5 - 0xfU) < 2) {
						cam110Pos->pos[0] = DAT_8009cf94 + (short)((uint)d->posCurr[0] >> 8);
						cam110Pos->pos[1] = DAT_8009cf96 + (short)((uint)d->posCurr[1] >> 8);
						cam110Pos->pos[2] = DAT_8009cf98 + (short)((uint)d->posCurr[2] >> 8);
						if (cDC->cameraMode == 0x10) {
							cam110Pos->rot[0] = DAT_8009cf9c + (d->rotCurr).x;
							sVar6 = DAT_8009cf9e + d->angle;
						}
						else {
							cam110Pos->rot[0] = DAT_8009cf9c + (d->rotCurr).x;
							sVar6 = DAT_8009cf9e + (d->rotCurr).y;
						}
						cam110Pos->rot[1] = sVar6;
						cam110Pos->rot[2] = DAT_8009cfa0 + (d->rotCurr).z;
					}
					else {
						if ((sVar6 == 8) || (sVar6 == 0xe)) {
							if ((d->botFlags & 2U) == 0) {
								if ((cDC->driver5B0_prevFrame & 2) != 0) {
									cDC->flags = cDC->flags | 9;
								}
								CAM_FollowDriver_AngleAxis(cDC,d,0x1f800108,cam110Pos->pos,cam110Pos->rot);
							}
							else {
								if ((cDC->driver5B0_prevFrame & 2) == 0) {
									cDC->flags = cDC->flags | 9;
								}
								CAM_FollowDriver_Normal(cDC,d,cam110Pos->pos,0x108,psVar23);
							}
							cDC->driver5B0_prevFrame = d->botFlags;
							goto LAB_8001c150;
						}
						if ((cDC->cameraMode == 9) || (psVar21 = &DAT_1f800108, cDC->cameraMode == 0xd)) {
							if ((sdata->gGT->level1->cnt_restart_points != 0) && ((sdata->gGT->gameMode1 & 0xf) == 0)) {
								uVar8 = CAM_FollowDriver_TrackPath(cDC,&DAT_1f800390,(int)*(short *)cDC->unk_b0,1);
								iVar13 = -0xc0;
								if (-1 < *(short *)cDC->unk_b0) {
									iVar13 = 0xc0;
								}
								uVar9 = CAM_FollowDriver_TrackPath(cDC,&DAT_1f800398,iVar13,0);
								iVar7 = ((uVar9 - uVar8) + 0x800 & 0xfff) - 0x800;
								DAT_1f800314 = 0x800;
								DAT_1f800316 = (short)uVar8 + (short)(iVar7 >> 1);
								DAT_1f800318 = 0;
								DAT_1f800390 = (short)((int)DAT_1f800390 + (int)DAT_1f800398 >> 1);
								DAT_1f800392 = (short)((int)DAT_1f800392 + (int)DAT_1f80039a >> 1);
								iVar13 = (int)DAT_1f80039c;
								DAT_1f800394 = (short)(DAT_1f800394 + iVar13 >> 1);
								ConvertRotToMatrix((MATRIX *)&DAT_1f800328,&DAT_1f800314);
								gte_SetRotMatrix((MATRIX *)&DAT_1f800328);
								gte_ldv0((SVECTOR *)&cDC->transitionTo);
								gte_rtv0();
								read_mt(uVar8,iVar13,iVar7);
								cam110Pos->pos[0] = scratchpad[0x144] + (short)uVar8;
								cam110Pos->pos[1] = scratchpad[0x145] + (short)iVar13;
								cam110Pos->pos[2] = scratchpad[0x146] + (short)iVar7;
								cam110Pos->rot[0] = scratchpad[0x106] + (cDC->transitionTo).rot[0];
								cam110Pos->rot[1] = scratchpad[0x107] + (cDC->transitionTo).rot[1];
								cam110Pos->rot[2] = scratchpad[0x108] + (cDC->transitionTo).rot[2];
							}
							psVar21 = scratchpad;
							if (cDC->cameraMode == 0xd) goto LAB_8001c11c;
						}
					}
					goto LAB_8001c128;
				}
				CAM_LookAtPosition(0x1f800108,d->posCurr,cam110Pos->pos,cam110Pos->rot);
				iVar13 = SquareRoot0_stub(DAT_1f800354 * DAT_1f800354 + DAT_1f80035c * DAT_1f80035c);
				iVar17 = (int)(cDC->transitionTo).pos[0];
				iVar24 = (iVar13 - (cDC->transitionTo).pos[1]) * iVar17;
				iVar7 = (int)(cDC->transitionTo).pos[2];
				iVar13 = iVar24 / iVar7;
				if (iVar7 == 0) {
					trap(0x1c00);
				}
				if ((iVar7 == -1) && (iVar24 == -0x80000000)) {
					trap(0x1800);
				}
				bVar2 = iVar17 < iVar13;
				if (iVar13 < 0) {
					iVar13 = 0;
					bVar2 = iVar17 < 0;
				}
				if (bVar2) {
					iVar13 = iVar17;
				}
				DAT_1f800348 = (int)cam110Pos->pos[0];
				cam110Pos->distanceToScreen_PREV = cam110Pos->distanceToScreen_CURR + iVar13;
				DAT_1f80034c = (int)cam110Pos->pos[1];
				sVar6 = cam110Pos->pos[2];
			}
			*(int *)(scratchpad + 0x124) = (int)sVar6;
			CAM_FindClosestQuadblock(scratchpad,cDC,d,(short *)((uint)scratchpad | 0x240));
			goto LAB_8001c150;
		}
	}
	CAM_FollowDriver_Normal(cDC,d,cam110Pos->pos,0x108,psVar23);
LAB_8001c150:
	cDC->cameraModePrev = cDC->cameraMode;
	psVar3 = sdata->gGT;
	if (cDC->ptrQuadblock != (struct QuadBlock *)0x0) {
		psVar10 = cDC->ptrQuadblock->pvs;
		if ((psVar10 != (struct PVS *)0x0) && (piVar11 = psVar10->visLeafSrc, piVar11 != (int *)0x0)) {
			cDC->visLeafSrc = piVar11;
			psVar3->unk1cac[1] = ((int)cDC->ptrQuadblock - (int)psVar3->level1->ptr_mesh_info->ptrQuadBlockArray) * -0x1642c859 >> 2;
		}
		if (cDC->ptrQuadblock != (struct QuadBlock *)0x0) {
			psVar10 = cDC->ptrQuadblock->pvs;
			if ((psVar10 != (struct PVS *)0x0) && (piVar11 = psVar10->visFaceSrc, piVar11 != (int *)0x0)) {
				cDC->visFaceSrc = piVar11;
			}
			if (cDC->ptrQuadblock != (struct QuadBlock *)0x0) {
				psVar10 = cDC->ptrQuadblock->pvs;
				if ((psVar10 != (struct PVS *)0x0) && (ppsVar12 = psVar10->visInstSrc, ppsVar12 != (struct Instance **)0x0)) {
					cDC->visInstSrc = ppsVar12;
				}
				if (((cDC->ptrQuadblock != (struct QuadBlock *)0x0) && (psVar10 = cDC->ptrQuadblock->pvs, psVar10 != (struct PVS *)0x0)) && (piVar11 = psVar10->visExtraSrc, piVar11 != (int *)0x0)) {
					if ((sdata->gGT->level1->configFlags & 4) == 0) {
						cDC->visOVertSrc = piVar11;
					}
					else {
						cDC->visSCVertSrc = piVar11;
					}
				}
			}
		}
	}
	if (*(int *)(cDC->unk30fill + 8) == 0) {
		cDC->visLeafSrc = (int *)0x0;
		cDC->visFaceSrc = (int *)0x0;
	}
	psVar3 = sdata->gGT;
	if ((cDC->flags & 1) != 0) {
		sdata->gGT->rainBuffer[cDC->cameraID].cameraPos[0] = cam110Pos->pos[0];
		psVar3->rainBuffer[cDC->cameraID].cameraPos[1] = cam110Pos->pos[1];
		psVar3->rainBuffer[cDC->cameraID].cameraPos[2] = cam110Pos->pos[2];
		cDC->flags = cDC->flags & 0xfffffffe;
	}
	cDC->flags = cDC->flags & 0xffffff77;
										// WARNING: Read-only address (ram,0x8009cf94) is written
										// WARNING: Read-only address (ram,0x8009cf96) is written
										// WARNING: Read-only address (ram,0x8009cf98) is written
										// WARNING: Read-only address (ram,0x8009cf9c) is written
										// WARNING: Read-only address (ram,0x8009cf9e) is written
										// WARNING: Read-only address (ram,0x8009cfa0) is written
	return;
}

