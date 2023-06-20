#include <common.h>

void CAM_ThTick(struct Thread *t)
{
	char bVar1;
	struct GameTracker *psVar2;
	u_short uVar3;
	short sVar4;
	short sVar5;
	int iVar6;
	u_int uVar7;
	u_int uVar8;
	int iVar9;
	int* piVar10;
	void* pvVar11;
	u_int uVar12;
	int iVar13;
	int iVar14;
	int iVar15;
	short* psVar16;
	short* psVar17;
	short* psVar18;
	long* plVar19;
	u_int uVar20;
	struct Instance* cDC;
	short* tileViewPos;
	short* psVar21;
	struct Driver* d;
	short* scratchpad;
	int iVar22;
	int iVar23;
	short local_28;
	short local_26;
	short local_24;
	
	scratchpad = &DAT_1f800108;
	cDC = t->inst;
	d = (struct Driver *)(cDC->matrix).t[0];
	tileViewPos = (short *)(cDC->matrix).t[1];
	if ((*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) & 0x8000) != 0)
	{
		return;
	}
	if
	(
		(
			(
				((sdata->gGT->gameMode1 & (GAME_CUTSCENE | MAIN_MENU | START_OF_RACE | PAUSE_ALL)) == 0) &&
				((((int)&d->instSelf->thread + 2) + 0x2c) == 0)
			) &&
			((d->actionsFlagSet & 0x100000) == 0)
		) &&
		(
			(
				(d->kartState != WARP_PAD && (d->kartState != FREEZE)) &&
				(
					(
						(sdata->gGT->gameMode2 & 4U) == 0 &&
						// watch this --Super
			 			((*(u_int *)((int)sdata->gGT + (int)cDC->next * 0x50 + 0x14) & 0x80) != 0)
			 		)
				)
			)
		)
	)
	{
		uVar3 = *(short *)(cDC->idpp[0].m1.t + 2) + 1;
		*(u_short *)(cDC->idpp[0].m1.t + 2) = uVar3;
		if (1 < uVar3)
		{
			*(u_short *)(cDC->idpp[0].m1.t + 2) = 0;
		}
		if (*(short *)(cDC->idpp[0].m1.t + 2) == 2)
		{
			cDC->idpp[0].m2.m[2] = 0xf;
		}
		else
		{
			*(u_short *)(cDC->name + 2) = *(u_short *)(cDC->idpp[0].m1.t + 2);
			cDC->idpp[0].m2.m[2] = 0;
		}
	}
	iVar9 = *(short *)(cDC->name + 2) * 0x24;
	psVar21 = (short *)(iVar9 + -0x7ff7f098);
	if (sdata->gGT->numPlyrCurrGame == '\x02')
	{
		psVar21 = (short *)(iVar9 + -0x7ff7f086);
	}
	if ((*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) & 0x20) == 0)
	goto switchD_8001b678_caseD_1;
	piVar10 = sdata->gGT->level1->ptrSpawnType1;
	psVar18 = 0;
	if (*piVar10 < 3) goto switchD_8001b678_caseD_1;
	psVar16 = (short *)piVar10[3];
	sVar5 = *psVar16;
	local_28 = (short)((u_int)d->posCurr[0] >> 8);
	local_26 = (short)((u_int)d->posCurr[1] >> 8);
	local_24 = (short)((u_int)d->posCurr[2] >> 8);
	psVar17 = psVar16 + 1;
	if (sVar5 != 0)
	{
		uVar20 = (u_int)d->unknown_in_FUN_8005ca24[1];
		psVar16 = psVar16 + 2;
		do
		{
			iVar9 = (int)*psVar16;
			if (iVar9 < 0)
			{
				iVar9 = -iVar9;
			}
			uVar12 = (u_int)*psVar17;
			psVar17 = (short *)((int)psVar16 + *(short *)(Data.data_ZoomData + ((iVar9 << 0x10) >> 0xf)) + 2);
			if
			(
				(
					(uVar20 == uVar12) ||
					(
						pvVar11 = sdata->gGT->level1->ptr_restart_points, 
						uVar20 == *(u_char *)((int)pvVar11 + uVar12 * 0xc + 8)
					)
				) ||
				(
					(
						uVar20 == *(u_char *)((int)pvVar11 + uVar12 * 0xc + 9) ||
						(
							(
								uVar20 == *(u_char *)((int)pvVar11 + uVar12 * 0xc + 10) ||
								(uVar20 == *(u_char *)((int)pvVar11 + uVar12 * 0xc + 0xb))
							)
						)
					)
				)
			)
			{
				psVar18 = psVar16;
			}
			sVar5 = sVar5 + -1;
			psVar16 = psVar17 + 1;
		} while (sVar5 != 0);
	}
	if ((psVar18 == (short *)0x0) || (psVar18 == *(short **)(cDC->idpp[0].m2.m[1] + 2)))
	goto switchD_8001b678_caseD_1;
	*(short **)(cDC->idpp[0].m2.m[1] + 2) = psVar18;
	sVar5 = *psVar18;
	psVar16 = psVar18 + 1;
	uVar20 = *(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2);
	sVar4 = sVar5;
	if (sVar5 < 0)
	{
		sVar4 = -sVar5;
	}
	cDC->idpp[0].m2.m[2] = sVar4;
	uVar20 = uVar20 & 0xffffefff;
	*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) = uVar20 | 9;
	if (sVar5 < 0)
	{
		*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) = uVar20 | 0x1009;
	}
	sVar5 = cDC->idpp[0].m2.m[2];
	*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) |= 0x1000;
	switch(sVar5)
	{
		case 0:
			*tileViewPos = *(short *)(d->instSelf->matrix).t;
			tileViewPos[1] = *(short *)((d->instSelf->matrix).t + 1);
			tileViewPos[2] = *(short *)((d->instSelf->matrix).t + 2);
			tileViewPos[3] = (d->rotCurr).x;
			tileViewPos[4] = (d->rotCurr).y;
			tileViewPos[5] = (d->rotCurr).z;
			*(u_short *)((int)cDC->idpp[0].unkc0 + 2) = 0;
			break;
		case 3:
			*tileViewPos = *psVar16;
			tileViewPos[1] = psVar18[2];
			tileViewPos[2] = psVar18[3];
			tileViewPos[3] = psVar18[4];
			tileViewPos[4] = psVar18[5];
			tileViewPos[5] = psVar18[6];
			*(short *)&cDC->prev = *psVar16;
			*(short *)((int)&cDC->prev + 2) = psVar18[2];
			*(short *)cDC->name = psVar18[3];
			*(short *)(cDC->name + 4) = psVar18[4];
			*(short *)(cDC->name + 6) = psVar18[5];
			*(short *)(cDC->name + 8) = psVar18[6];
			break;
		case 4:
			*tileViewPos = *psVar16;
			tileViewPos[1] = psVar18[2];
			tileViewPos[2] = psVar18[3];
			break;
		case 7:
			cDC->idpp[0].m2.m[2][1] = *psVar16;
			sVar5 = psVar18[2];
			uVar20 = *(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) & 0xffffffbf;
			*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) = uVar20;
			cDC->idpp[0].m2.m[2][2] = sVar5;
			if (psVar18[3] != 0) {
				*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) = uVar20 | 0x40;
			}
			break;
		case 8:
		case 0xe:
			*(short *)((int)&cDC->idpp[0].tileView + 2) = *psVar16;
			iVar9 = (int)*(short *)((int)&cDC->idpp[0].tileView + 2);
			cDC->idpp[0].m1.m[0] = psVar18[2];
			iVar6 = (int)cDC->idpp[0].m1.m[0];
			cDC->idpp[0].m1.m[1] = psVar18[3];
			iVar13 = (int)cDC->idpp[0].m1.m[1];
			cDC->idpp[0].m1.m[1][0] = psVar18[4];
			cDC->idpp[0].m1.m[1][1] = psVar18[5];
			cDC->idpp[0].m1.m[1][2] = psVar18[6];
			iVar9 = MapToRange(iVar9 * iVar9 + iVar6 * iVar6 + iVar13 * iVar13, 0x10000, 0x190000, 0x80, 0xf0);
			cDC->idpp[0].m1.m[2] = (short)iVar9;
			break;
		case 9:
		case 0xd:
			sVar5 = *psVar16;
			pvVar11 = sdata->gGT->level1->ptr_restart_points;
			*(u_int *)((int)cDC->idpp[0].m1.t + 10) = 0;
			*(void **)&cDC->idpp[0].m1.field_0x12 = (void *)((int)pvVar11 + sVar5 * 0xc);
			cDC->idpp[0].m2.m[2][1] = psVar18[2];
			cDC->idpp[0].m2.m[2][2] = psVar18[3];
			*(short *)&cDC->idpp[0].m2.field_0x12 = psVar18[4];
			*(short *)cDC->idpp[0].m2.t = psVar18[5];
			*(short *)((int)cDC->idpp[0].m2.t + 2) = psVar18[6];
			*(short *)(cDC->idpp[0].m2.t + 1) = psVar18[7];
			*(short *)((int)cDC->idpp[0].m2.t + 6) = psVar18[8];
			break;
		case 10:
			sVar5 = *psVar16;
			psVar16 = psVar18 + 2;
			goto LAB_8001b928;
		case 0xb:
			*tileViewPos = *psVar16;
			tileViewPos[1] = psVar18[2];
			tileViewPos[2] = psVar18[3];
			psVar16 = psVar18 + 5;
			sVar5 = psVar18[4] - tileViewPos[0x86];
LAB_8001b928:
			cDC->idpp[0].m2.m[2][1] = sVar5;
			cDC->idpp[0].m2.m[2][2] = *psVar16;
			*(short *)&cDC->idpp[0].m2.field_0x12 = psVar16[1];
			break;
		case 0xc:
			cDC->idpp[0].m2.m[2][1] = *psVar16;
			cDC->idpp[0].m2.m[2][2] = psVar18[2];
			*(short *)&cDC->idpp[0].m2.field_0x12 = psVar18[3];
			*(short *)cDC->idpp[0].m2.t = psVar18[4];
			*(short *)((int)cDC->idpp[0].m2.t + 2) = psVar18[5];
			*(short *)(cDC->idpp[0].m2.t + 1) = psVar18[6];
			*(short *)((int)cDC->idpp[0].m2.t + 6) = psVar18[7];
			*(short *)(cDC->idpp[0].m2.t + 2) = psVar18[8];
			*(short *)((int)cDC->idpp[0].m2.t + 10) = psVar18[9];
			*(short *)cDC->idpp[0].unkb8 = psVar18[10];
	}
switchD_8001b678_caseD_1:
	*(u_int *)(tileViewPos + 0xc) = *(u_int *)(tileViewPos + 0x86);
	sVar5 = cDC->idpp[0].m2.m[2];
	if (sVar5 != 0)
	{
		sVar4 = cDC->idpp[0].m2.m[2];
		*(u_short *)&cDC->idpp[0].mh = 0;
		if (sVar5 != 0)
		{
			if (sVar5 == 4)
			{
LAB_8001c11c:
				CAM_LookAtPosition((int)scratchpad, d->posCurr, tileViewPos, tileViewPos + 3);
				psVar18 = scratchpad;
LAB_8001c128:
				(psVar18 + 0x120) = (int)*tileViewPos;
				(psVar18 + 0x122) = (int)tileViewPos[1];
				sVar5 = tileViewPos[2];
				scratchpad = psVar18;
			}
			else
			{
				psVar18 = scratchpad;
				if (sVar5 == 10)
				{
					CAM_FollowDriver_Spin360((struct CameraDC *)cDC, (u_int)&DAT_1f800108, d, tileViewPos, (u_int)(tileViewPos + 3));
					goto LAB_8001c128;
				}
				if (sVar5 != 0xb)
				{
					if (sVar5 == 0xc)
					{
						if (cDC->idpp[0].m2.m[1][0] != 0xc)
						{
							*(u_short *)(cDC->idpp[0].m1.t + 1) = 0;
						}
						local_28 = (short)((u_int)d->posCurr[0] >> 8);
						local_26 = (short)((u_int)d->posCurr[1] >> 8);
						local_24 = (short)((u_int)d->posCurr[2] >> 8);
						iVar6 = CAM_MapRange_PosPoints(cDC->idpp[0].m2.m[2] + 1, (short *)cDC->idpp[0].m2.t, &local_28);
						iVar13 = (int)*(short *)cDC->idpp[0].unkb8;
						local_28 = *(short *)((int)cDC->idpp[0].m2.t + 6) - *(short *)cDC->idpp[0].m2.t;
						local_26 = *(short *)(cDC->idpp[0].m2.t + 2) - *(short *)((int)cDC->idpp[0].m2.t + 2);
						iVar9 = iVar13;
						if (iVar13 < 0)
						{
							iVar9 = -iVar13;
						}
						local_24 = *(short *)((int)cDC->idpp[0].m2.t + 10) - *(short *)(cDC->idpp[0].m2.t + 1);
						if (iVar13 < 0)
						{
							local_28 = -local_28;
							local_26 = -local_26;
							local_24 = -local_24;
						}
						iVar22 = SquareRoot0_stub((int)local_28 * (int)local_28 + (int)local_26 * (int)local_26 + (int)local_24 * (int)local_24);
						iVar14 = ((int)cDC->idpp[0].m1.t + 10);
						iVar15 = iVar14 << 0xc;
						iVar23 = iVar15 / iVar22;
						((int)cDC->idpp[0].m1.t + 10) = iVar14 + (((*(short *)(cDC->idpp[0].m1.t + 1) * 0x1000) / 0x1e) * iVar9 >> 0xc);
						if (iVar6 < 1)
						{
							if (iVar23 < 0x1001)
							{
								if (*(short *)(cDC->idpp[0].m1.t + 1) < 0x1e)
								{
									*(short *)(cDC->idpp[0].m1.t + 1) = *(short *)(cDC->idpp[0].m1.t + 1) + 1;
								}
							}
							else if (*(short *)(cDC->idpp[0].m1.t + 1) != 0)
							{
								*(short *)(cDC->idpp[0].m1.t + 1) = *(short *)(cDC->idpp[0].m1.t + 1) + -1;
							}
						}
						else
						{
							*(u_int *)((int)cDC->idpp[0].m1.t + 10) = 0;
							*(u_short *)(cDC->idpp[0].m1.t + 1) = 0;
						}
						plVar19 = cDC->idpp[0].m2.t;
						if (iVar13 < 0)
						{
							plVar19 = (long *)((int)cDC->idpp[0].m2.t + 6);
						}
						*tileViewPos = *(short *)plVar19 + (short)(local_28 * iVar23 >> 0xc);
						tileViewPos[1] = *(short *)((int)plVar19 + 2) + (short)(local_26 * iVar23 >> 0xc);
						tileViewPos[2] = *(short *)(plVar19 + 1) + (short)(local_24 * iVar23 >> 0xc);
						goto LAB_8001c11c;
					}
					if (sVar5 == 7)
					{
						*tileViewPos = (short)((u_int)d->posCurr[0] >> 8);
						tileViewPos[1] = cDC->idpp[0].m2.m[2][1] + (short)((u_int)d->posCurr[1] >> 8);
						tileViewPos[2] = (short)((u_int)d->posCurr[2] >> 8);
						sVar5 = cDC->idpp[0].m2.m[2][2];
						tileViewPos[4] = 0;
						tileViewPos[5] = 0;
						tileViewPos[3] = sVar5 + 0x400;
						psVar18 = &DAT_1f800108;
						if ((*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) & 0x40) != 0)
						{
							tileViewPos[4] = d->angle + 0x800;
						}
					}
					else if ((u_short)(sVar4 - 0xfU) < 2)
					{
						*tileViewPos = sdata->FirstPersonCamera.posOffset[0] + (short)((u_int)d->posCurr[0] >> 8);
						tileViewPos[1] = sdata->FirstPersonCamera.posOffset[1] + (short)((u_int)d->posCurr[1] >> 8);
						tileViewPos[2] = sdata->FirstPersonCamera.posOffset[2] + (short)((u_int)d->posCurr[2] >> 8);
						if (cDC->idpp[0].m2.m[2] == 0x10)
						{
							tileViewPos[3] = sdata->FirstPersonCamera.rotOffset[0] + (d->rotCurr).x;
							sVar5 = sdata->FirstPersonCamera.rotOffset[1] + d->angle;
						}
						else
						{
							tileViewPos[3] = sdata->FirstPersonCamera.rotOffset[0] + (d->rotCurr).x;
							sVar5 = sdata->FirstPersonCamera.rotOffset[1] + (d->rotCurr).y;
						}
						tileViewPos[4] = sVar5;
						tileViewPos[5] = sdata->FirstPersonCamera.rotOffset[2] + (d->rotCurr).z;
					}
					else
					{
						if ((sVar5 == 8) || (sVar5 == 0xe))
						{
							if ((*(u_int *)(d->no_mans_land + 0x18) & 2) == 0)
							{
								if ((*(u_int *)(cDC->idpp[0].m1.m[2] + 1) & 2) != 0)
								{
									*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) |= 9;
								}
								CAM_FollowDriver_AngleAxis((struct CameraDC *)cDC, d, (int)&DAT_1f800108, tileViewPos, tileViewPos + 3);
							}
							else
							{
								if ((*(u_int *)(cDC->idpp[0].m1.m[2] + 1) & 2) == 0)
								{
									*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) |= 9;
								}
								CAM_FollowDriver_Normal((struct CameraDC *)cDC, d, tileViewPos, 0x108, psVar21);
							}
							*(u_int *)(cDC->idpp[0].m1.m[2] + 1) = *(u_int *)(d->no_mans_land + 0x18);
							goto LAB_8001c150;
						}
						sVar5 = cDC->idpp[0].m2.m[2];
						if ((sVar5 == 9) || (psVar18 = &DAT_1f800108,  sVar5 == 0xd))
						{
							if
							(
								(sdata->gGT->level1->cnt_restart_points != 0) &&
								((sdata->gGT->gameMode1 & PAUSE_ALL) == 0)
							)
							{
								uVar7 = CAM_FollowDriver_TrackPath((struct CameraDC *)cDC, &DAT_1f800390, (int)*(short *)((int)cDC->idpp[0].m2.t + 6), 1);
								iVar9 = -0xc0;
								if (-1 < *(short *)((int)cDC->idpp[0].m2.t + 6))
								{
									iVar9 = 0xc0;
								}
								uVar8 = CAM_FollowDriver_TrackPath((struct CameraDC *)cDC, &DAT_1f800398, iVar9, 0);
								iVar6 = ((uVar8 - uVar7) + 0x800 & 0xfff) - 0x800;
								DAT_1f800314 = 0x800;
								DAT_1f800316 = (short)uVar7 + (short)(iVar6 >> 1);
								DAT_1f800318 = 0;
								DAT_1f800390 = (short)((int)DAT_1f800390 + (int)DAT_1f800398 >> 1);
								DAT_1f800392 = (short)((int)DAT_1f800392 + (int)DAT_1f80039a >> 1);
								iVar9 = (int)DAT_1f80039c;
								DAT_1f800394 = (short)(DAT_1f800394 + iVar9 >> 1);
								ConvertRotToMatrix((MATRIX *)&DAT_1f800328, &DAT_1f800314);
								gte_SetRotMatrix((MATRIX *)&DAT_1f800328);
								gte_ldv0((SVECTOR *)(cDC->idpp[0].m2.m[2] + 1));
								gte_rtv0();
								read_mt(uVar7, iVar9, iVar6);
								*tileViewPos = scratchpad[0x144] + (short)uVar7;
								tileViewPos[1] = scratchpad[0x145] + (short)iVar9;
								tileViewPos[2] = scratchpad[0x146] + (short)iVar6;
								tileViewPos[3] = scratchpad[0x106] + *(short *)cDC->idpp[0].m2.t;
								tileViewPos[4] = scratchpad[0x107] + *(short *)((int)cDC->idpp[0].m2.t + 2);
								tileViewPos[5] = scratchpad[0x108] + *(short *)(cDC->idpp[0].m2.t + 1);
							}
							psVar18 = scratchpad;
							if (cDC->idpp[0].m2.m[2] == 0xd) goto LAB_8001c11c;
						}
					}
					goto LAB_8001c128;
				}
				CAM_LookAtPosition((int)&DAT_1f800108, d->posCurr, tileViewPos, tileViewPos + 3);
				iVar9 = SquareRoot0_stub(DAT_1f800354 * DAT_1f800354 + DAT_1f80035c * DAT_1f80035c);
				iVar13 = (int)cDC->idpp[0].m2.m[2][1];
				iVar22 = (iVar9 - cDC->idpp[0].m2.m[2][2]) * iVar13;
				iVar6 = (int)*(short *)&cDC->idpp[0].m2.field_0x12;
				iVar9 = iVar22 / iVar6;
				bVar1 = iVar13 < iVar9;
				if (iVar9 < 0)
				{
					iVar9 = 0;
					bVar1 = iVar13 < 0;
				}
				if (bVar1)
				{
					iVar9 = iVar13;
				}
				DAT_1f800348 = (int)*tileViewPos;
				(tileViewPos + 0xc) = (tileViewPos + 0x86) + iVar9;
				DAT_1f80034c = (int)tileViewPos[1];
				sVar5 = tileViewPos[2];
			}
			(scratchpad + 0x124) = (int)sVar5;
			CAM_FindClosestQuadblock(scratchpad, (struct CameraDC *)cDC, d, (short *)((u_int)scratchpad | 0x240));
			goto LAB_8001c150;
		}
	}
	CAM_FollowDriver_Normal((struct CameraDC *)cDC, d, tileViewPos, 0x108, psVar21);
LAB_8001c150:
	iVar9 = cDC->scale;
	cDC->idpp[0].m2.m[1][0] = cDC->idpp[0].m2.m[2];
	psVar2 = sdata->gGT;
	if (iVar9 != 0)
	{
		piVar10 = *(int **)(iVar9 + 0x44);
		if ((piVar10 != (int *)0x0) && (iVar9 = *piVar10,  iVar9 != 0))
		{
			(cDC->scale + 2) = iVar9;
			psVar2->unk1cac[1] = (cDC->scale - (int)psVar2->level1->ptr_mesh_info->ptrQuadBlockArray) * -0x1642c859 >> 2;
		}
		if (cDC->scale != 0)
		{
			iVar9 = (cDC->scale + 0x44);
			if ((iVar9 != 0) && (iVar9 = (iVar9 + 4),  iVar9 != 0))
			{
				cDC->colorRGBA = iVar9;
			}
			if (cDC->scale != 0)
			{
				iVar9 = (cDC->scale + 0x44);
				if ((iVar9 != 0) && (iVar9 = (iVar9 + 8),  iVar9 != 0))
				{
					cDC->flags = iVar9;
				}
				if
				(
					((cDC->scale != 0) && (iVar9 = (cDC->scale + 0x44),  iVar9 != 0)) &&
					(iVar9 = (iVar9 + 0xc),  iVar9 != 0)
				)
				{
					if ((sdata->gGT->level1->configFlags & 4U) == 0)
					{
						cDC->ptrInstDef = iVar9;
					}
					else
					{
						cDC->matrix.m[0][0] = iVar9;
					}
				}
			}
		}
	}
	if ((int)cDC->matrix.m[2] == 0)
	{
		cDC->scale[2] = 0;
		cDC->colorRGBA = 0;
	}
	psVar2 = sdata->gGT;
	if ((*(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) & 1) != 0)
	{
		sdata->gGT->rainBuffer[(int)cDC->next].cameraPos[0] = *tileViewPos;
		psVar2->rainBuffer[(int)cDC->next].cameraPos[1] = tileViewPos[1];
		psVar2->rainBuffer[(int)cDC->next].cameraPos[2] = tileViewPos[2];
		(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) &= 0xfffffffe;
	}
	(u_int *)((int)&cDC->bitCompressed_NormalVector_AndDriverIndex + 2) &= 0xffffff77;
	return;
}