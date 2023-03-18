
void CAM_SkyboxGlow(short *param_1,struct Camera110 *camera,struct PrimMem *primMem,u_long *ptrOT)

{
	int sin;
	int cos;
	int iVar1;
	u_int uVar2;
	u_int uVar3;
	int iVar4;
	int iVar5;
	structLevel_clearColor sVar6;
	int iVar7;
	u_int *puVar8;
	u_int uVar9;
	int iVar10;
	u_int uVar11;
	u_int uVar12;
	u_int uVar13;
	int iVar14;
	
	sin = MATH_Sin((int)camera->rot[2]);
	cos = MATH_Cos((int)camera->rot[2]);
	if (cos == 0)
	{
		cos = 1;
	}
	iVar7 = (camera->rot[0] - 0x800) * 0x78;
	sin = -(((sin << 0xc) / cos << 8) >> 0xc) / 2;
	if (iVar7 < 0)
	{
		iVar7 = iVar7 + 0x3ff;
	}
	cos = (u_int)(u_short)(camera->rect).h << 0x10;
	DAT_1f800014 = (iVar7 >> 10) + ((cos >> 0x10) - (cos >> 0x1f) >> 1);
	cos = (camera->rot[0] - 0x800) * 0x78;
	iVar7 = 0;
	if (cos < 0)
	{
		cos = cos + 0x3ff;
	}
	iVar1 = (u_int)(u_short)(camera->rect).h << 0x10;
	DAT_1f800018 = (cos >> 10) + ((iVar1 >> 0x10) - (iVar1 >> 0x1f) >> 1);
	uVar13 = (u_int)(camera->rect).w;
	uVar12 = uVar13 & 0xffff;
	do
	{
		uVar11 = (DAT_1f800018 - param_1[1]) - sin;
		uVar9 = ~uVar11 >> 0x1f;
		cos = (DAT_1f800018 - param_1[1]) + sin;
		uVar2 = *(u_int *)(param_1 + 2);
		DAT_1f800000 = uVar2 & 0xffffff;
		uVar3 = *(u_int *)(param_1 + 4);
		DAT_1f800008 = uVar3 & 0xffffff;
		iVar10 = (DAT_1f800014 - *param_1) - sin;
		iVar1 = (DAT_1f800014 - *param_1) + sin;
		if (-1 < cos)
		{
			uVar9 = uVar9 | 2;
		}
		if (-1 < iVar10)
		{
			uVar9 = uVar9 | 4;
		}
		if (-1 < iVar1)
		{
			uVar9 = uVar9 | 8;
		}
		DAT_1f800008._1_1_ = (byte)(DAT_1f800008 >> 8);
		DAT_1f800008._2_1_ = (byte)(DAT_1f800008 >> 0x10);
		DAT_1f800000._1_1_ = (byte)(DAT_1f800000 >> 8);
		DAT_1f800000._2_1_ = (byte)(DAT_1f800000 >> 0x10);
		DAT_1f800004 = DAT_1f800000;
		DAT_1f80000c = DAT_1f800008;
		switch(uVar9)
		{
			case 1:
				iVar1 = iVar10 - uVar11;
				iVar4 = (iVar10 * 0x1000) / iVar1;
				cos = uVar11 - cos;
				iVar1 = (int)(uVar11 * 0x1000) / cos;
				DAT_1f800000._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ + (char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar4) >> 0xc),
					(char)DAT_1f800000 + (char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar4) >> 0xc)
				);
				DAT_1f800000._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ + (char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar4) >> 0xc),
					(u_short)DAT_1f800000
				);
				DAT_1f80000c._0_3_ =
				CONCAT12
				(
					DAT_1f800008._2_1_ + (char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800008._2_1_) * iVar1) >> 0xc),
					CONCAT11
					(
						DAT_1f800008._1_1_ + (char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800008._1_1_) * iVar1) >> 0xc),
						(char)DAT_1f800008 + (char)((int)(((uVar3 & 0xff) - (uVar3 & 0xff)) * iVar1) >> 0xc)
					)
				);
				DAT_1f80000c = (u_int)(u_int3)DAT_1f80000c;
				puVar8 = (u_int *)primMem->curr;
				uVar2 = (u_int)(u_int3)DAT_1f800000;
				puVar8[1] = (u_int3)DAT_1f800000 | 0x30000000;
				DAT_1f800000 = uVar2;
				puVar8[3] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				puVar8[2] = 0;
				puVar8[4] = uVar11 * 0x10000;
				puVar8[5] = uVar2;
				puVar8[6] = (int)(uVar13 * iVar1) >> 0xc & 0xffff;
				*puVar8 = *ptrOT | 0x6000000;
				uVar2 = (u_int)puVar8 & 0xffffff;
				puVar8 = puVar8 + 7;
				goto LAB_80017cb4;
			case 2:
				iVar10 = iVar1 - cos;
				iVar4 = (iVar1 * 0x1000) / iVar10;
				iVar1 = uVar11 - cos;
				iVar10 = (int)(uVar11 * 0x1000) / iVar1;
				DAT_1f800004._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ + (char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar4) >> 0xc),
					(char)DAT_1f800000 + (char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar4) >> 0xc)
				);
				DAT_1f800004 =
				(u_int)CONCAT12
				(
					DAT_1f800000._2_1_ + (char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar4) >> 0xc),
					(u_short)DAT_1f800004
				);
				DAT_1f800008._0_3_ =
				CONCAT12
				(
					DAT_1f800008._2_1_ + (char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800008._2_1_) * iVar10) >> 0xc),
					CONCAT11
					(
						DAT_1f800008._1_1_ + (char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800008._1_1_) * iVar10) >> 0xc),
						(char)DAT_1f800008 + (char)((int)(((uVar3 & 0xff) - (uVar3 & 0xff)) * iVar10) >> 0xc)
					)
				);
				puVar8 = (u_int *)primMem->curr;
				uVar2 = (u_int)(u_int3)DAT_1f800008;
				puVar8[1] = (u_int3)DAT_1f800008 | 0x30000000;
				DAT_1f800008 = uVar2;
				puVar8[3] = DAT_1f800004;
				uVar2 = DAT_1f80000c;
				puVar8[4] = uVar12;
				puVar8[5] = uVar2;
				puVar8[2] = (int)(uVar13 * iVar10) >> 0xc & 0xffff;
				puVar8[6] = uVar12 | cos * 0x10000;
				*puVar8 = *ptrOT | 0x6000000;
				uVar2 = (u_int)puVar8 & 0xffffff;
				puVar8 = puVar8 + 7;
				goto LAB_80017cb4;
			case 3:
				iVar4 = iVar10 - uVar11;
				iVar5 = (iVar10 * 0x1000) / iVar4;
				iVar10 = iVar1 - cos;
				iVar4 = (iVar1 * 0x1000) / iVar10;
				DAT_1f800000._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ + (char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar5) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar5) >> 0xc));
				DAT_1f800000._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ +
											(char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar5) >> 0xc),(u_short)DAT_1f800000);
				DAT_1f800000 = (u_int)(u_int3)DAT_1f800000;
				DAT_1f800004._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ +
											(char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar4) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar4) >> 0xc));
				DAT_1f800004._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ +
											(char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar4) >> 0xc),(u_short)DAT_1f800004);
				DAT_1f800004 = (u_int)(u_int3)DAT_1f800004;
				puVar8 = (u_int *)primMem->curr;
				puVar8[1] = DAT_1f800000 | 0x38000000;
				puVar8[3] = DAT_1f800004;
				puVar8[5] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				puVar8[6] = uVar11 * 0x10000;
				puVar8[2] = 0;
				puVar8[4] = uVar12;
				puVar8[8] = uVar12 | cos * 0x10000;
				puVar8[7] = uVar2;
				*puVar8 = *ptrOT | 0x8000000;
				uVar2 = (u_int)puVar8 & 0xffffff;
				puVar8 = puVar8 + 9;
	LAB_80017cb4:
				*ptrOT = uVar2;
				primMem->curr = puVar8;
				break;
			case 5:
				iVar1 = iVar10 - iVar1;
				cos = uVar11 - cos;
				puVar8 = (u_int *)primMem->curr;
				puVar8[1] = DAT_1f800000 | 0x38000000;
				uVar3 = (int)(uVar13 * ((iVar10 * 0x1000) / iVar1)) >> 0xc & 0xffff;
				puVar8[3] = DAT_1f800004;
				puVar8[5] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				puVar8[2] = iVar10 * 0x10000;
				puVar8[6] = uVar11 * 0x10000;
				puVar8[4] = uVar3;
				puVar8[7] = uVar2;
				puVar8[8] = (int)(uVar13 * ((int)(uVar11 * 0x1000) / cos)) >> 0xc & 0xffff;
				*puVar8 = *ptrOT | 0x8000000;
				*ptrOT = (u_int)puVar8 & 0xffffff;
				primMem->curr = puVar8 + 9;
				if ((iVar7 == 0) && (gameTracker->level1->clearColor[2].enable != '\0'))
				{
					sVar6 = gameTracker->level1->clearColor[2];
					puVar8[0xb] = uVar3;
					puVar8[0xc] = 0;
					puVar8[0xd] = iVar10 * 0x10000;
					puVar8[10] = (u_int)sVar6 & 0xffffff | 0x20000000;
					puVar8[9] = *ptrOT | 0x4000000;
					*ptrOT = (u_int)(puVar8 + 9) & 0xffffff;
					puVar8 = puVar8 + 0xe;
	LAB_800185d8:
					primMem->curr = puVar8;
				}
				break;
			case 7:
				iVar4 = iVar10 - iVar1;
				iVar5 = (iVar10 * 0x1000) / iVar4;
				iVar4 = iVar1 - cos;
				iVar14 = (iVar1 * 0x1000) / iVar4;
				DAT_1f800010._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ +
											(char)((int)(((u_int)DAT_1f800000._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar5) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar2 & 0xff) - (uVar2 & 0xff)) * iVar5) >> 0xc));
				uVar9 = iVar10 * 0x10000;
				DAT_1f800010._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ +
											(char)((int)(((u_int)DAT_1f800000._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar5) >> 0xc),(u_short)DAT_1f800010);
				DAT_1f800010 = DAT_1f800010 & 0xff000000 | (u_int)(u_int3)DAT_1f800010;
				DAT_1f800004._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ +
											(char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar14) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar14) >> 0xc));
				DAT_1f800004._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ +
											(char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar14) >> 0xc),(u_short)DAT_1f800004);
				DAT_1f800004 = (u_int)(u_int3)DAT_1f800004;
				puVar8 = (u_int *)primMem->curr;
				puVar8[1] = DAT_1f800000 | 0x30000000;
				puVar8[3] = DAT_1f800010;
				uVar2 = DAT_1f800004;
				uVar3 = (int)(uVar13 * iVar5) >> 0xc & 0xffff;
				puVar8[2] = uVar9;
				puVar8[4] = uVar3;
				puVar8[6] = uVar12;
				puVar8[5] = uVar2;
				*puVar8 = *ptrOT | 0x6000000;
				*ptrOT = (u_int)puVar8 & 0xffffff;
				uVar2 = DAT_1f800000;
				primMem->curr = puVar8 + 7;
				puVar8[8] = uVar2 & 0xffffff | 0x38000000;
				puVar8[10] = DAT_1f800004;
				puVar8[0xc] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				puVar8[0xd] = uVar11 * 0x10000;
				puVar8[9] = uVar9;
				puVar8[0xb] = uVar12;
				puVar8[0xf] = uVar12 | cos * 0x10000;
				puVar8[0xe] = uVar2;
				puVar8[7] = *ptrOT | 0x8000000;
				*ptrOT = (u_int)(puVar8 + 7) & 0xffffff;
				primMem->curr = puVar8 + 0x10;
				if ((iVar7 == 0) && (gameTracker->level1->clearColor[2].enable != '\0'))
				{
					sVar6 = gameTracker->level1->clearColor[2];
					puVar8[0x12] = uVar3;
					puVar8[0x13] = 0;
					puVar8[0x14] = uVar9;
					puVar8[0x11] = (u_int)sVar6 & 0xffffff | 0x20000000;
					puVar8[0x10] = *ptrOT | 0x4000000;
					*ptrOT = (u_int)(puVar8 + 0x10) & 0xffffff;
					puVar8 = puVar8 + 0x15;
					goto LAB_800185d8;
				}
				break;
			case 10:
				iVar4 = iVar10 - iVar1;
				iVar5 = uVar11 - cos;
				puVar8 = (u_int *)primMem->curr;
				puVar8[1] = DAT_1f800000 | 0x38000000;
				uVar3 = (int)(uVar13 * ((iVar10 * 0x1000) / iVar4)) >> 0xc & 0xffff;
				puVar8[3] = DAT_1f800004;
				puVar8[5] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				uVar9 = uVar12 | iVar1 * 0x10000;
				puVar8[4] = uVar9;
				puVar8[8] = uVar12 | cos * 0x10000;
				puVar8[2] = uVar3;
				puVar8[7] = uVar2;
				puVar8[6] = (int)(uVar13 * ((int)(uVar11 * 0x1000) / iVar5)) >> 0xc & 0xffff;
				*puVar8 = *ptrOT | 0x8000000;
				*ptrOT = (u_int)puVar8 & 0xffffff;
				primMem->curr = puVar8 + 9;
				if ((iVar7 == 0) && (gameTracker->level1->clearColor[2].enable != '\0'))
				{
					sVar6 = gameTracker->level1->clearColor[2];
					puVar8[0xb] = uVar3;
					puVar8[0xc] = uVar12;
					puVar8[0xd] = uVar9;
					puVar8[10] = (u_int)sVar6 & 0xffffff | 0x20000000;
					puVar8[9] = *ptrOT | 0x4000000;
					*ptrOT = (u_int)(puVar8 + 9) & 0xffffff;
					puVar8 = puVar8 + 0xe;
					goto LAB_800185d8;
				}
				break;
			case 0xb:
				iVar5 = iVar10 * 0x1000;
				iVar4 = iVar10 - iVar1;
				iVar14 = iVar5 / iVar4;
				iVar10 = iVar10 - uVar11;
				iVar4 = iVar5 / iVar10;
				DAT_1f800010._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ +
											(char)((int)(((u_int)DAT_1f800000._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar14) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar2 & 0xff) - (uVar2 & 0xff)) * iVar14) >> 0xc));
				DAT_1f800010 = DAT_1f800010 & 0xff000000 |
											 (u_int)(byte)(DAT_1f800000._2_1_ +
																	 (char)((int)(((u_int)DAT_1f800000._2_1_ - (u_int)DAT_1f800000._2_1_)
																							 * iVar14) >> 0xc)) << 0x10 | (u_int)(u_short)DAT_1f800010
				;
				DAT_1f800000._0_2_ =
				CONCAT11
				(
					DAT_1f800000._1_1_ +
											(char)((int)(((u_int)DAT_1f800008._1_1_ - (u_int)DAT_1f800000._1_1_) * iVar4) >> 0xc),
											(char)DAT_1f800000 +
											(char)((int)(((uVar3 & 0xff) - (uVar2 & 0xff)) * iVar4) >> 0xc));
				DAT_1f800000._0_3_ =
				CONCAT12
				(
					DAT_1f800000._2_1_ +
											(char)((int)(((u_int)DAT_1f800008._2_1_ - (u_int)DAT_1f800000._2_1_) * iVar4) >> 0xc),(u_short)DAT_1f800000);
				puVar8 = (u_int *)primMem->curr;
				uVar2 = (u_int)(u_int3)DAT_1f800000;
				puVar8[1] = (u_int3)DAT_1f800000 | 0x30000000;
				DAT_1f800000 = uVar2;
				puVar8[3] = DAT_1f800010;
				uVar2 = DAT_1f800004;
				uVar3 = uVar12 | iVar1 * 0x10000;
				uVar9 = (int)(uVar13 * iVar14) >> 0xc & 0xffff;
				puVar8[2] = 0;
				puVar8[4] = uVar9;
				puVar8[6] = uVar3;
				puVar8[5] = uVar2;
				*puVar8 = *ptrOT | 0x6000000;
				*ptrOT = (u_int)puVar8 & 0xffffff;
				uVar2 = DAT_1f800000;
				primMem->curr = puVar8 + 7;
				puVar8[8] = uVar2 & 0xffffff | 0x38000000;
				puVar8[10] = DAT_1f800004;
				puVar8[0xc] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				puVar8[0xd] = uVar11 * 0x10000;
				puVar8[9] = 0;
				puVar8[0xb] = uVar3;
				puVar8[0xf] = uVar12 | cos * 0x10000;
				puVar8[0xe] = uVar2;
				puVar8[7] = *ptrOT | 0x8000000;
				*ptrOT = (u_int)(puVar8 + 7) & 0xffffff;
				primMem->curr = puVar8 + 0x10;
				if ((iVar7 == 0) && (gameTracker->level1->clearColor[2].enable != '\0'))
				{
					sVar6 = gameTracker->level1->clearColor[2];
					puVar8[0x12] = uVar9;
					puVar8[0x13] = uVar12;
					puVar8[0x14] = uVar3;
					puVar8[0x11] = (u_int)sVar6 & 0xffffff | 0x20000000;
					puVar8[0x10] = *ptrOT | 0x4000000;
					*ptrOT = (u_int)(puVar8 + 0x10) & 0xffffff;
					puVar8 = puVar8 + 0x15;
					goto LAB_800185d8;
				}
				break;
			case 0xf:
				puVar8 = (u_int *)primMem->curr;
				puVar8[1] = DAT_1f800000 | 0x38000000;
				puVar8[3] = DAT_1f800004;
				puVar8[5] = DAT_1f800008;
				uVar2 = DAT_1f80000c;
				uVar3 = uVar12 | iVar1 * 0x10000;
				puVar8[6] = uVar11 * 0x10000;
				puVar8[2] = iVar10 * 0x10000;
				puVar8[4] = uVar3;
				puVar8[8] = uVar12 | cos * 0x10000;
				puVar8[7] = uVar2;
				*puVar8 = *ptrOT | 0x8000000;
				*ptrOT = (u_int)puVar8 & 0xffffff;
				primMem->curr = puVar8 + 9;
				if ((iVar7 == 0) && (gameTracker->level1->clearColor[2].enable != '\0'))
				{
					sVar6 = gameTracker->level1->clearColor[2];
					puVar8[0xb] = 0;
					puVar8[0xc] = uVar12;
					puVar8[0xd] = iVar10 * 0x10000;
					puVar8[0xe] = uVar3;
					puVar8[10] = (u_int)sVar6 & 0xffffff | 0x28000000;
					puVar8[9] = *ptrOT | 0x5000000;
					*ptrOT = (u_int)(puVar8 + 9) & 0xffffff;
					puVar8 = puVar8 + 0xf;
					goto LAB_800185d8;
				}
		}
		iVar7 = iVar7 + 1;
		param_1 = param_1 + 6;
		if (2 < iVar7)
		{
			return;
		}
	} while( true );
}

