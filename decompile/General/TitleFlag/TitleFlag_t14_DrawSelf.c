#include <common.h>

void DECOMP_TitleFlag_DrawSelf()
{
	char bVar1;
	short sVar2;
	u_long *puVar3;
	u_char uVar4;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	struct DB *psVar9;
	u_int uVar10;
	SVECTOR *pSVar11;
	u_int uVar12;
	int iVar13;
	u_int *puVar14;
	int iVar15;
	u_int uVar16;
	SVECTOR *r0;
	int iVar17;
	u_int uVar18;
	u_int uVar19;
	u_int *puVar20;
	long *r0_00;
	u_int *puVar21;
	u_int *puVar22;
	u_int *puVar23;
	int iVar24;
	u_int uVar25;
	u_char *puVar26;
	u_char *puVar27;
	int iVar28;
	u_char auStack_88 [96];
	struct GameTracker* gGT = sdata->gGT;
	
	puVar26 = &sdata->langBufferSize;
	puVar27 = auStack_88;

	if (sdata->TitleFlag_CanDraw == 0)
	{
		return;
	}

	if (sdata->TitleFlag_LoadingTextAnimFrame < 0)
	{
		if ((5 < sdata->Loading.stage) && (sdata->Loading.stage < 8))
		{
			sdata->TitleFlag_LoadingTextAnimFrame = 0;
		}
		if (sdata->TitleFlag_LoadingTextAnimFrame < 0) goto LAB_80044568;
	}

	TitleFlag_DrawLoadingString();
LAB_80044568:
	sdata->TitleFlag_CopyLoadStage = sdata->Loading.stage;
	puVar3 = (u_int *)TitleFlag_GetOT();
	
	gte_SetRotMatrix(&data.matrixTitleFlag);
	gte_SetTransMatrix(&data.matrixTitleFlag);
	gte_SetGeomOffset(0x100,0x78);
	
	#define gte_ldH( r0 ) __asm__ volatile ( \
		"lhu   $12, 0(  %0  );" \
		"ctc2  $12, $31;"       \
		:                       \
		: "r" ( r0 )            \
		: "$12" )

	gte_ldH(0x100);
	
	iVar28 = data.checkerFlagVariables[3] * gGT->elapsedTimeMS;
	puVar20 = 0;
	r0_00 = 0x1f800000;
	uVar25 = 1;
	uVar18 = *(int *)(puVar26 + 0x4ec) >> 5;
	*(u_int *)(puVar27 + 0x4c) = uVar18;
	data.checkerFlagVariables[4] = data.checkerFlagVariables[4] + iVar28;
	uVar16 = (int)data.checkerFlagVariables[4] >> 5;

	if (0xfff < uVar16)
	{
		data.checkerFlagVariables[4] = data.checkerFlagVariables[4] & 0x1ffff;
		uVar16 = (int)data.checkerFlagVariables[4] >> 5;
		data.checkerFlagVariables[0] = data.checkerFlagVariables[0] + 0x200;
		uVar10 = *(int*)&data.trigApprox[data.checkerFlagVariables[0] & 0x3ff];
		if ((data.checkerFlagVariables[0] & 0x400) == 0)
		{
			uVar10 = uVar10 << 0x10;
		}
		iVar28 = (int)uVar10 >> 0x10;
		if ((data.checkerFlagVariables[0] & 0x800) != 0)
		{
			iVar28 = -iVar28;
		}
		data.checkerFlagVariables[1] = ((iVar28 + 0xfff) * 0x20 >> 0xd) + 0x96;
		data.checkerFlagVariables[2] = data.checkerFlagVariables[2] + 200;
		uVar10 = *(int*)&data.trigApprox[data.checkerFlagVariables[2] & 0x3ff];
		if ((data.checkerFlagVariables[2] & 0x400) == 0)
		{
			uVar10 = uVar10 << 0x10;
		}
		iVar28 = (int)uVar10 >> 0x10;
		if ((data.checkerFlagVariables[2] & 0x800) != 0)
		{
			iVar28 = -iVar28;
		}
		data.checkerFlagVariables[3] = ((iVar28 + 0xfff) * 0x40 >> 0xd) + 0xb4;
	}

	uVar10 = *(int*)&data.trigApprox[uVar16 & 0x3ff];

	if ((uVar16 & 0x400) == 0)
	{
		uVar10 = uVar10 << 0x10;
	}

	iVar28 = (int)uVar10 >> 0x10;

	if ((uVar16 & 0x800) != 0)
	{
		iVar28 = -iVar28;
	}

	uVar16 = uVar16 + 0xc80;
	uVar10 = *(int*)&data.trigApprox[uVar16 & 0x3ff];

	if ((uVar16 & 0x400) == 0)
	{
		uVar10 = uVar10 << 0x10;
	}

	iVar5 = (int)uVar10 >> 0x10;
	if ((uVar16 & 0x800) != 0)
	{
		iVar5 = -iVar5;
	}

	iVar24 = 0;
	puVar22 = data.trigApprox;
	r0 = (SVECTOR *)(puVar27 + 0x10);
	*(int *)(puVar27 + 0x48) = iVar5 + 0xfff;
	iVar28 = (iVar28 + 0xfff) * data.checkerFlagVariables[1];
	*(u_short *)(puVar27 + 0x12) = 0xfc72;
	sVar2 = *(short *)(puVar26 + 0x4d8);
	*(u_short *)(puVar27 + 0x1a) = 0xfcd0;
	*(u_short *)(puVar27 + 0x22) = 0xfd2e;
	sVar2 = -0xbbe - sVar2;
	*(short *)(puVar27 + 0x10) = sVar2;
	*(short *)(puVar27 + 0x18) = sVar2;
	*(short *)(puVar27 + 0x20) = sVar2;
	iVar28 = (iVar28 >> 0xd) + 0x280;

	for(iVar5 = 0, pSVar11 = r0; iVar24 < 10; iVar24++, r0_00 += 3)
	{
		for(; iVar5 < 3; uVar18 += 300, iVar5++, pSVar11++)
		{
			uVar16 = puVar22[uVar18 & 0x3ff];

			if ((uVar18 & 0x400) == 0)
			{
				uVar16 = uVar16 << 0x10;
			}

			iVar6 = (int)uVar16 >> 0x10;

			if ((uVar18 & 0x800) != 0)
			{
				iVar6 = -iVar6;
			}

			pSVar11->vz = (short)iVar28 + (short)((iVar6 + 0xfff) * 0x20 >> 0xd);
		}

		gte_ldv3(r0,(SVECTOR *)(puVar27 + 0x18),(SVECTOR *)(puVar27 + 0x20));
		gte_rtpt();
		*(short *)(puVar27 + 0x12) = *(short *)(puVar27 + 0x12) + 0x11a;
		*(short *)(puVar27 + 0x22) = *(short *)(puVar27 + 0x22) + 0x11a;
		*(short *)(puVar27 + 0x1a) = *(short *)(puVar27 + 0x1a) + 0x11a;
		gte_stsxy3(r0_00,r0_00 + 1,r0_00 + 2);
	}

	iVar5 = 1;
	puVar22 = data.trigApprox;
	uVar16 = 0x80008000;
	iVar24 = *(int *)(puVar27 + 0x48);
	*(u_char **)(puVar27 + 0x50) = puVar27 + 0x48;
	*(u_char **)(puVar27 + 0x5c) = puVar27 + 0x10;
	iVar28 = 0xd80200;
	*(u_int *)(puVar27 + 0x28) = data.checkerFlagVariables[0];
	*(int *)(puVar27 + 0x2c) = data.checkerFlagVariables[1];
	*(u_int *)(puVar27 + 0x30) = data.checkerFlagVariables[2];
	*(int *)(puVar27 + 0x34) = data.checkerFlagVariables[3];
	*(u_int *)(puVar27 + 0x38) = data.checkerFlagVariables[4];

	do
	{
		puVar21 = (u_int *)(uVar25 * 0x78 + 0x1f7ffffc);
		uVar25 = uVar25 ^ 1;
		puVar23 = (u_int *)(uVar25 * 0x78 + 0x1f800000);
		uVar19 = *(int *)(puVar27 + 0x4c) + 0x100;
		uVar18 = *(int *)(puVar27 + 0x38) + *(int *)(puVar27 + 0x34) * 0x40;
		uVar10 = (int)uVar18 >> 5;
		*(u_int *)(puVar27 + 0x4c) = uVar19;
		*(u_int *)(puVar27 + 0x38) = uVar18;
		if (0xfff < uVar10)
		{
			uVar10 = (int)(uVar18 & 0x1ffff) >> 5;
			*(u_int *)(puVar27 + 0x38) = uVar18 & 0x1ffff;
			uVar18 = *(int *)(puVar27 + 0x28) + 0x200;
			*(u_int *)(puVar27 + 0x28) = uVar18;
			uVar12 = puVar22[uVar18 & 0x3ff];
			if ((uVar18 & 0x400) == 0)
			{
				uVar12 = uVar12 << 0x10;
			}
			iVar6 = (int)uVar12 >> 0x10;
			if ((uVar18 & 0x800) != 0)
			{
				iVar6 = -iVar6;
			}
			*(int *)(puVar27 + 0x2c) = ((iVar6 + 0xfff) * 0x20 >> 0xd) + 0x96;
			uVar18 = *(int *)(puVar27 + 0x30) + 200;
			*(u_int *)(puVar27 + 0x30) = uVar18;
			uVar12 = puVar22[uVar18 & 0x3ff];
			if ((uVar18 & 0x400) == 0)
			{
				uVar12 = uVar12 << 0x10;
			}
			iVar6 = (int)uVar12 >> 0x10;
			if ((uVar18 & 0x800) != 0)
			{
				iVar6 = -iVar6;
			}
			*(int *)(puVar27 + 0x34) = ((iVar6 + 0xfff) * 0x40 >> 0xd) + 0xb4;
		}
		uVar18 = puVar22[uVar10 & 0x3ff];
		if ((uVar10 & 0x400) == 0)
		{
			uVar18 = uVar18 << 0x10;
		}
		iVar6 = (int)uVar18 >> 0x10;
		if ((uVar10 & 0x800) != 0)
		{
			iVar6 = -iVar6;
		}
		uVar10 = uVar10 + 0xc80;
		uVar18 = puVar22[uVar10 & 0x3ff];
		if ((uVar10 & 0x400) == 0)
		{
			uVar18 = uVar18 << 0x10;
		}
		iVar7 = (int)uVar18 >> 0x10;
		if ((uVar10 & 0x800) != 0)
		{
			iVar7 = -iVar7;
		}
		iVar15 = 0;
		iVar17 = *(int *)(puVar27 + 0x5c);
		**(int **)(puVar27 + 0x50) = iVar7 + 0xfff;
		*(u_short *)(puVar27 + 0x12) = 0xfc72;
		*(u_short *)(puVar27 + 0x1a) = 0xfcd0;
		*(u_short *)(puVar27 + 0x22) = 0xfd2e;
		*(short *)(puVar27 + 0x10) = *(short *)(puVar27 + 0x10) + 100;
		*(short *)(puVar27 + 0x18) = *(short *)(puVar27 + 0x18) + 100;
		*(short *)(puVar27 + 0x20) = *(short *)(puVar27 + 0x20) + 100;
		iVar6 = ((iVar6 + 0xfff) * *(int *)(puVar27 + 0x2c) >> 0xd) + 0x280;
		
		for(; iVar15 < 3; uVar19 += 300, iVar15++, iVar17 += 8)
		{
			uVar18 = puVar22[uVar19 & 0x3ff];
			if ((uVar19 & 0x400) == 0)
			{
				uVar18 = uVar18 << 0x10;
			}
			iVar7 = (int)uVar18 >> 0x10;
			if ((uVar19 & 0x800) != 0)
			{
				iVar7 = -iVar7;
			}
			*(short *)(iVar17 + 4) = (short)iVar6 + (short)((iVar7 + 0xfff) * 0x20 >> 0xd);
			uVar19 = uVar19 + 300;
			iVar15 = iVar15 + 1;
			iVar17 = iVar17 + 8;
		}

		gte_ldv3(*(SVECTOR **)(puVar27 + 0x5c),(SVECTOR *)(puVar27 + 0x18),(SVECTOR *)(puVar27 + 0x20) );
		gte_rtpt();
		iVar15 = 0;
		iVar7 = 1;

		for(; iVar7 < 10; iVar7++)
		{
			if (iVar7 < 0xb)
			{
				gte_stsxy3((long *)(puVar21 + 1),(long *)(puVar21 + 2),(long *)(puVar21 + 3));
				iVar17 = 0;
				if (iVar7 < 10)
				{
					iVar13 = *(int *)(puVar27 + 0x5c);
					do
					{
						uVar18 = puVar22[uVar19 & 0x3ff];
						if ((uVar19 & 0x400) == 0)
						{
							uVar18 = uVar18 << 0x10;
						}
						iVar8 = (int)uVar18 >> 0x10;
						if ((uVar19 & 0x800) != 0)
						{
							iVar8 = -iVar8;
						}
						*(short *)(iVar13 + 4) = (short)iVar6 + (short)((iVar8 + 0xfff) * 0x20 >> 0xd);
						uVar19 = uVar19 + 300;
						iVar17 = iVar17 + 1;
						iVar13 = iVar13 + 8;
					} while (iVar17 < 3);

					*(short *)(puVar27 + 0x12) = *(short *)(puVar27 + 0x12) + 0x11a;
					*(short *)(puVar27 + 0x22) = *(short *)(puVar27 + 0x22) + 0x11a;
					*(short *)(puVar27 + 0x1a) = *(short *)(puVar27 + 0x1a) + 0x11a;
					gte_ldv3(*(SVECTOR **)(puVar27 + 0x5c),(SVECTOR *)(puVar27 + 0x18), (SVECTOR *)(puVar27 + 0x20));
					gte_rtpt();
				}
			}
			if (iVar15 == 0)
			{
				puVar21++;
			}
			uVar18 = (u_int)(iVar15 == 0);
			*(int *)(puVar27 + 0x58) = iVar24 * 0x69 + (0x2000 - iVar24) * 0xa0 >> 0xd;
			
			for(; (int)uVar18 < 3; puVar23++, puVar21++, uVar18++, iVar15++)
			{
				if
				(
					((*puVar23 & puVar23[1] & uVar16 & uVar16 & *puVar21 & uVar16 & puVar21[1]) == 0) &&
					(
						(iVar28 - *puVar23 & iVar28 - puVar23[1] & uVar16 & uVar16 & iVar28 - *puVar21 & uVar16
						& iVar28 - puVar21[1]) == 0
					)
				)
				{
					psVar9 = gGT->backBuffer;
					puVar14 = (u_int *)(psVar9->primMem).curr;
					if (puVar14 <= (psVar9->primMem).endMin100)
					{
						(psVar9->primMem).curr = puVar14 + 9;
						puVar20 = puVar14;
					}
					if (puVar20 == 0)
					{
						return;
					}
					if (((iVar5 >> 2) + (iVar15 >> 2) & 1U) == 0)
					{
						puVar27[0x40] = (char)(iVar24 * 0x82 + (0x2000 - iVar24) * 0xff >> 0xd);
						uVar4 = (u_char)(*(int *)(puVar27 + 0x48) * -0x7d + 0x1fe000 >> 0xd);
					}
					else
					{
						uVar4 = (u_char)(*(int *)(puVar27 + 0x48) * -0x37 + 0x140000 >> 0xd);
						puVar27[0x40] = puVar27[0x58];
					}
					puVar27[0x41] = uVar4;
					puVar20[2] = *puVar23;
					puVar20[6] = puVar23[1];
					puVar20[4] = *puVar21;
					puVar20[8] = puVar21[1];
					uVar10 = (u_int)(u_char)puVar27[0x40];
					uVar10 = uVar10 | uVar10 << 0x10 | uVar10 << 8;
					puVar20[1] = uVar10;
					puVar20[5] = uVar10;
					uVar10 = (u_int)(u_char)puVar27[0x41];
					*(u_char *)((int)puVar20 + 3) = 8;
					*(u_char *)((int)puVar20 + 7) = 0x38;
					uVar10 = uVar10 | uVar10 << 0x10 | uVar10 << 8;
					puVar20[3] = uVar10;
					puVar20[7] = uVar10;
					*puVar20 = *puVar20 & 0xff000000 | *puVar3 & 0xffffff;
					*puVar3 = *puVar3 & 0xff000000 | (u_int)puVar20 & 0xffffff;
				}
			}
		}

		iVar24 = *(int *)(puVar27 + 0x48);
		iVar5 = iVar5 + 1;
		if (0x22 < iVar5)
		{
			*(int *)(puVar26 + 0x4ec) = *(int *)(puVar26 + 0x4ec) + gGT->elapsedTimeMS * 100;
			return;
		}
	} while( true );
}