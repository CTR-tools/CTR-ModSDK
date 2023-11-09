#include <common.h>

#ifdef REBUILD_PC
u_char auStack_88[96];
int scratchpadBuf[0x1000];
#endif

void DECOMP_TitleFlag_DrawSelf()
{
	short sVar2;
	u_long* puVar3;
	int iVar5;
	int iVar6;
	int iVar7;
	int iVar8;
	struct DB* psVar9;
	u_int uVar10;
	SVECTOR* pSVar11;
	int iVar13;
	u_int* puVar14;
	int iVar15;
	u_int uVar16;
	int iVar17;
	u_int uVar18;
	u_int uVar19;
	u_int* puVar20;
	long* r0_00;
	u_int* puVar21;
	u_int* puVar23;
	int iVar24;
	u_int uVar25;
	u_char* puVar27;
	int iVar28;
	struct GameTracker* gGT = sdata->gGT;

#ifndef REBUILD_PC
	u_char auStack_88[96];
#endif

	// 0x10, 0x18, 0x20
	SVECTOR pos[3];

	// 0x28, 0x2C, 0x30, 0x34, 0x38
	// copies of data.checkeredFlag[X]
	// unk1, unk2, waveAngle, brightness, darkness
	int copy0;
	int copy1;
	int copy2;
	int copy3;
	int copy4;

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

		// temporary test for PC port "LOADING..."
#ifndef REBUILD_PS1
		if (sdata->TitleFlag_LoadingTextAnimFrame < 0) goto LAB_80044568;
#endif
	}

	DECOMP_TitleFlag_DrawLoadingString();
LAB_80044568:
	sdata->TitleFlag_CopyLoadStage = sdata->Loading.stage;
	puVar3 = (u_int*)DECOMP_TitleFlag_GetOT();

	gte_SetRotMatrix(&data.matrixTitleFlag);
	gte_SetTransMatrix(&data.matrixTitleFlag);
	gte_SetGeomOffset(0x100, 0x78);

#ifndef REBUILD_PC
#define gte_ldH( r0 ) __asm__ volatile ( \
		"lhu   $12, 0(  %0  );" \
		"ctc2  $12, $31;"       \
		:                       \
		: "r" ( r0 )            \
		: "$12" )

	gte_ldH(0x100);
#endif

	iVar28 = data.checkerFlagVariables[3] * gGT->elapsedTimeMS;
	puVar20 = 0;

#ifdef REBUILD_PC
	r0_00 = &scratchpadBuf[0];
	memset(&scratchpadBuf[0], 0, 0x1000 * 4);
	memset(&auStack_88[0], 0, 96);
#else
	r0_00 = 0x1f800000;
#endif
	uVar25 = 1;
	uVar18 = sdata->TitleFlag_ElapsedTime >> 5;
	*(u_int*)(puVar27 + 0x4c) = uVar18;
	data.checkerFlagVariables[4] = data.checkerFlagVariables[4] + iVar28;
	uVar16 = (int)data.checkerFlagVariables[4] >> 5;

	if (0xfff < uVar16)
	{
		data.checkerFlagVariables[4] = data.checkerFlagVariables[4] & 0x1ffff;
		uVar16 = (int)data.checkerFlagVariables[4] >> 5;

		// += 45 degrees
		data.checkerFlagVariables[0] += 0x200;
		iVar28 = DECOMP_MATH_Sin(data.checkerFlagVariables[0]);

		data.checkerFlagVariables[1] = ((iVar28 + 0xfff) * 0x20 >> 0xd) + 0x96;

		// += 18 degrees
		data.checkerFlagVariables[2] = data.checkerFlagVariables[2] + 200;
		iVar28 = DECOMP_MATH_Sin(data.checkerFlagVariables[2]);

		data.checkerFlagVariables[3] = ((iVar28 + 0xfff) * 0x40 >> 0xd) + 0xb4;
	}

	iVar28 = DECOMP_MATH_Sin(uVar16);

	// 280 degrees (3/4 of 360)
	uVar16 += 0xc80;

	iVar5 = DECOMP_MATH_Sin(uVar16);

	*(int*)(puVar27 + 0x48) = iVar5 + 0xfff;

	iVar28 = (iVar28 + 0xfff) * data.checkerFlagVariables[1];
	iVar28 = (iVar28 >> 0xd) + 0x280;
	
	pos[0].vy = 0xfc72;
	pos[1].vy = 0xfcd0;
	pos[2].vy = 0xfd2e;
	
	sVar2 = sdata->TitleFlag_Position;
	sVar2 = -0xbbe - sVar2;
	pos[0].vx = sVar2;
	pos[1].vx = sVar2;
	pos[2].vx = sVar2;

	iVar24 = 0;
	for (iVar5 = 0, pSVar11 = &pos[0]; iVar24 < 10; iVar24++, r0_00 += 3)
	{
		for (; iVar5 < 3; uVar18 += 300, iVar5++, pSVar11++)
		{
			iVar6 = DECOMP_MATH_Sin(uVar18);

			pSVar11->vz = (short)iVar28 + (short)((iVar6 + 0xfff) * 0x20 >> 0xd);
		}

		gte_ldv3(&pos[0], &pos[1], &pos[2]);
		gte_rtpt();
		pos[0].vy += 0x11a;
		pos[1].vy += 0x11a;
		pos[2].vy += 0x11a;
		gte_stsxy3(r0_00, r0_00 + 1, r0_00 + 2);
	}

	iVar5 = 1;
	uVar16 = 0x80008000;
	iVar24 = *(int*)(puVar27 + 0x48);
	*(u_char**)(puVar27 + 0x50) = puVar27 + 0x48;
	*(u_char**)(puVar27 + 0x5c) = &pos[0];

	// screen size
	iVar28 = 0xd80200;

	copy0 = data.checkerFlagVariables[0];
	copy1 = data.checkerFlagVariables[1];
	copy2 = data.checkerFlagVariables[2];
	copy3 = data.checkerFlagVariables[3];
	copy4 = data.checkerFlagVariables[4];

	do
	{

#ifdef REBUILD_PC
		puVar21 = &scratchpadBuf[(uVar25 * 0x78 / 4) - 1];
		uVar25 = uVar25 ^ 1;
		puVar23 = &scratchpadBuf[(uVar25 * 0x78 / 4) - 0];
#else
		puVar21 = (u_int*)((0x1f800000 + uVar25 * 0x78) - 4);
		uVar25 = uVar25 ^ 1;
		puVar23 = (u_int*)(0x1f800000 + uVar25 * 0x78);
#endif		

		uVar19 = *(int*)(puVar27 + 0x4c) + 0x100;
		uVar18 = copy4 + copy3 * 0x40;
		uVar10 = (int)uVar18 >> 5;
		*(u_int*)(puVar27 + 0x4c) = uVar19;
		copy4 = uVar18;
		if (0xfff < uVar10)
		{
			uVar10 = (int)(uVar18 & 0x1ffff) >> 5;
			copy4 = uVar18 & 0x1ffff;
			
			uVar18 = copy0 + 0x200;
			copy0 = uVar18;

			iVar6 = DECOMP_MATH_Sin(uVar18);

			copy1 = ((iVar6 + 0xfff) * 0x20 >> 0xd) + 0x96;

			uVar18 = copy2 + 200;
			copy2 = uVar18;

			iVar6 = DECOMP_MATH_Sin(uVar18);

			copy3 = ((iVar6 + 0xfff) * 0x40 >> 0xd) + 0xb4;
		}

		iVar6 = DECOMP_MATH_Sin(uVar10);

		// 280 degrees
		uVar10 += 0xc80;

		iVar7 = DECOMP_MATH_Sin(uVar10);

		iVar15 = 0;
		iVar17 = *(int*)(puVar27 + 0x5c);
		**(int**)(puVar27 + 0x50) = iVar7 + 0xfff;
		pos[0].vy = 0xfc72;
		pos[1].vy = 0xfcd0;
		pos[2].vy = 0xfd2e;
		pos[0].vx += 100;
		pos[1].vx += 100;
		pos[2].vx += 100;
		iVar6 = ((iVar6 + 0xfff) * copy1 >> 0xd) + 0x280;

		for (; iVar15 < 3; uVar19 += 300, iVar15++, iVar17 += 8)
		{
			iVar7 = DECOMP_MATH_Sin(uVar19);

			*(short*)(iVar17 + 4) = (short)iVar6 + (short)((iVar7 + 0xfff) * 0x20 >> 0xd);
			uVar19 = uVar19 + 300;
			iVar15 = iVar15 + 1;
			iVar17 = iVar17 + 8;
		}

		gte_ldv3(*(SVECTOR**)(puVar27 + 0x5c), &pos[1], &pos[2]);
		gte_rtpt();

		iVar15 = 0;
		for (iVar7 = 1; iVar7 < 10; iVar7++)
		{
			if (iVar7 < 0xb)
			{
				gte_stsxy3((long*)(puVar21 + 1), (long*)(puVar21 + 2), (long*)(puVar21 + 3));
				iVar17 = 0;
				if (iVar7 < 10)
				{
					iVar13 = *(int*)(puVar27 + 0x5c);
					do
					{
						iVar8 = DECOMP_MATH_Sin(uVar19);

						*(short*)(iVar13 + 4) = (short)iVar6 + (short)((iVar8 + 0xfff) * 0x20 >> 0xd);
						uVar19 = uVar19 + 300;
						iVar17 = iVar17 + 1;
						iVar13 = iVar13 + 8;
					} while (iVar17 < 3);

					pos[0].vy += 0x11a;
					pos[1].vy += 0x11a;
					pos[2].vy += 0x11a;
					gte_ldv3(*(SVECTOR**)(puVar27 + 0x5c), &pos[1], &pos[2]);
					gte_rtpt();
				}
			}
			if (iVar15 == 0)
			{
				puVar21++;
			}
			uVar18 = (u_int)(iVar15 == 0);
			*(int*)(puVar27 + 0x58) = iVar24 * 0x69 + (0x2000 - iVar24) * 0xa0 >> 0xd;

			for (; (int)uVar18 < 3; puVar23++, puVar21++, uVar18++, iVar15++)
			{
				if(
					((puVar23[0] & puVar23[1] & puVar21[0] & puVar21[1] & uVar16) == 0) &&
					((iVar28 - puVar23[0] & iVar28 - puVar23[1] & iVar28 - puVar21[0] & iVar28 - puVar21[1] & uVar16) == 0)
				  )
				{
					psVar9 = gGT->backBuffer;
					puVar14 = (u_int*)(psVar9->primMem).curr;
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
						puVar27[0x41] = (u_char)(*(int*)(puVar27 + 0x48) * -0x7d + 0x1fe000 >> 0xd);
					}
					else
					{
						puVar27[0x41] = (u_char)(*(int*)(puVar27 + 0x48) * -0x37 + 0x140000 >> 0xd);
						puVar27[0x40] = puVar27[0x58];
					}
					puVar20[2] = *puVar23;
					puVar20[6] = puVar23[1];
					puVar20[4] = *puVar21;
					puVar20[8] = puVar21[1];
					uVar10 = (u_int)(u_char)puVar27[0x40];
					uVar10 = uVar10 | uVar10 << 0x10 | uVar10 << 8;
					puVar20[1] = uVar10;
					puVar20[5] = uVar10;
					uVar10 = (u_int)(u_char)puVar27[0x41];
					*(u_char*)((int)puVar20 + 3) = 8;
					*(u_char*)((int)puVar20 + 7) = 0x38;
					uVar10 = uVar10 | uVar10 << 0x10 | uVar10 << 8;
					puVar20[3] = uVar10;
					puVar20[7] = uVar10;
					*puVar20 = *puVar20 & 0xff000000 | *puVar3 & 0xffffff;
					*puVar3 = *puVar3 & 0xff000000 | (u_int)puVar20 & 0xffffff;
				}
			}
		}

		iVar24 = *(int*)(puVar27 + 0x48);
		iVar5 = iVar5 + 1;
		if (0x22 < iVar5)
		{
			sdata->TitleFlag_ElapsedTime += gGT->elapsedTimeMS * 100;
			return;
		}
	} while (true);
}