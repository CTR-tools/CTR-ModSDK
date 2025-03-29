#include <common.h>

#ifdef REBUILD_PC
u_int scratchpadBuf[0x1000];
#endif

force_inline char RaceFlag_CalculateBrightness(u_int sine, u_char darkTile)
{
	if (darkTile)
	{
		return((sine * -55 + 0x140000) >> 0xD);
	}
	return((sine * -125 + 0x1fe000) >> 0xD);
}

void DECOMP_RaceFlag_DrawSelf()
{
	char i, j;
	char column, row;
	u_char toggle;
	short flagPos;
	u_long *ot;
	u_int *scratchpad;
	u_int screenlimit;
	u_int dimensions;
	int approx[2];
	u_int angle[2];
	POLY_G4 *p;
	SVECTOR *vect;
	struct GameTracker *gGT = sdata->gGT;

	int lightL;
	int lightR;
	
	u_int *posL;
	u_int *posR;

	// 0x10, 0x18, 0x20
	SVECTOR pos[3];

	// 0x28, 0x2C, 0x30, 0x34, 0x38
	// copies of data.checkeredFlag[X]
	int local0;
	int local1;
	int local2;
	int local3;
	int local4;
	
	int time;

	if (sdata->RaceFlag_CanDraw == 0)
		return;

	if (sdata->RaceFlag_LoadingTextAnimFrame < 0)
	{
		if ((5 < sdata->Loading.stage) && (sdata->Loading.stage < 8))
		{
			sdata->RaceFlag_LoadingTextAnimFrame = 0;
		}

		if (sdata->RaceFlag_LoadingTextAnimFrame < 0)
			goto SKIP_LOADING_TEXT;
	}

	DECOMP_RaceFlag_DrawLoadingString();

SKIP_LOADING_TEXT:

	sdata->RaceFlag_CopyLoadStage = sdata->Loading.stage;
	ot = (u_long *)DECOMP_RaceFlag_GetOT();

	gte_SetRotMatrix(&data.matrixTitleFlag);
	gte_SetTransMatrix(&data.matrixTitleFlag);
	gte_SetGeomOffset(0x100, 0x78);
	gte_SetGeomScreen(0x100);

	p = (POLY_G4 *)gGT->backBuffer->primMem.curr;

#ifdef REBUILD_PC
	scratchpad = &scratchpadBuf[0];
	memset(&scratchpadBuf[0], 0, 0x1000 * 4);
#else
	scratchpad = (u_int*)0x1f800000;
#endif
	
	dimensions = 0xd80200;
	screenlimit = 0x80008000;

	local0 = data.checkerFlagVariables[0];
	local1 = data.checkerFlagVariables[1];
	local2 = data.checkerFlagVariables[2];
	local3 = data.checkerFlagVariables[3];
	local4 = data.checkerFlagVariables[4];

	// vertical strips
	toggle = 0;
	for (column = 0; column < 36; column++)
	{
#ifdef REBUILD_PC
		posL = &scratchpadBuf[(toggle * 0x78 / 4) - 1];
		toggle = toggle ^ 1;
		posR = &scratchpadBuf[(toggle * 0x78 / 4)];
#else
		posL = (u_int *)((0x1f800000 + toggle * 0x78) - 4);
		toggle = toggle ^ 1;
		posR = (u_int *)(0x1f800000 + toggle * 0x78);
#endif

		// === Step 1 ===
		int stepRate = 0x40;
		if (column == 0)
			stepRate = gGT->elapsedTimeMS;
		
		local4 += local3 * stepRate;
		angle[0] = (int)local4 >> 5;
		
		// === Step 2 ===
		if (0xfff < angle[0])
		{
			// reset counter
			local4 &= 0x1ffff;
			angle[0] = (int)local4 >> 5;

			local0 += 0x200;
			local2 += 200;
			
			int sin0 = DECOMP_MATH_Sin(local0) + 0xfff;
			int sin2 = DECOMP_MATH_Sin(local2) + 0xfff;
			
			// reset based on trig
			local1 = (sin0 * 0x20 >> 0xd) + 0x96;
			local3 = (sin2 * 0x40 >> 0xd) + 0xb4;
		}

		// === Step 3 ===
		approx[0] = DECOMP_MATH_Sin(angle[0]) + 0xfff;
		approx[0] = approx[0] * local1;
		approx[0] = (approx[0] >> 0xd) + 0x280;

		// === Step 4 ===
		angle[0] += 0xc80;
		lightL = DECOMP_MATH_Sin(angle[0]) + 0xfff;

		// === Step 5 ===
		pos[0].vy = 0xfc72;
		pos[1].vy = 0xfcd0;
		pos[2].vy = 0xfd2e;

		// === Step 6 ===
		if(column == 0)
		{
			data.checkerFlagVariables[0] = local0;
			data.checkerFlagVariables[1] = local1;
			data.checkerFlagVariables[2] = local2;
			data.checkerFlagVariables[3] = local3;
			data.checkerFlagVariables[4] = local4;
			
			time = sdata->RaceFlag_ElapsedTime >> 5;
			angle[0] = time;

			flagPos = sdata->RaceFlag_Position;
			flagPos = -0xbbe - flagPos;
			pos[0].vx = flagPos;
			pos[1].vx = flagPos;
			pos[2].vx = flagPos;
		}
		
		else
		{
			time += 0x100;
			angle[0] = time;

			pos[0].vx += 100;
			pos[1].vx += 100;
			pos[2].vx += 100;
		}

		i = 0;
		// === Step 8 ===
		for (row = 0; row < 10; row++)
		{
			for (
				j = 0, vect = &pos[0];
				j < 3;
				j++, vect++)
			{
				// Range: [1.0, 2.0]
				approx[1] = DECOMP_MATH_Sin(angle[0]) + 0xfff;
				angle[0] += 300;

				// change all vector posZ
				vect->vz = (short)approx[0] + (short)(approx[1] * 0x20 >> 0xd);
			}

			gte_ldv3(&pos[0], &pos[1], &pos[2]);
			gte_rtpt();
			
			pos[0].vy += 0x11a;
			pos[1].vy += 0x11a;
			pos[2].vy += 0x11a;
			
			gte_stsxy3((long *)(posL + 1), (long *)(posL + 2), (long *)(posL + 3));
			
			if(column == 0)
			{
				posL += 3;
				continue;
			}
			
			// ============================
			
			j = 0;
			if (i == 0)
			{
				j++;
				posL++;
			}

			for (/**/; j < 3; posR++, posL++, j++, i++)
			{
				if (
					((posR[0] & posR[1] & posL[0] & posL[1] & screenlimit) == 0) &&
					((dimensions - posR[0] & dimensions - posR[1] & dimensions - posL[0] & dimensions - posL[1] & screenlimit) == 0))
				{
					// white tile
					u_char boolDark = false;

					// grey tile
					if (((column >> 2) + (i >> 2) & 1U) != 0)
					{
						boolDark = true;
					}

					u_char colorR = RaceFlag_CalculateBrightness(lightR, boolDark);
					u_int rgbR = (colorR) | (colorR << 8) | (colorR << 16);
					*(int*)&p->r0 = rgbR;
					*(int*)&p->r2 = rgbR;
					
					u_char colorL = RaceFlag_CalculateBrightness(lightL, boolDark);
					u_int rgbL = (colorL) | (colorL << 8) | (colorL << 16);
					*(int*)&p->r1 = rgbL;
					*(int*)&p->r3 = rgbL;

					// positions
					*(int *)&p->x0 = posR[0];
					*(int *)&p->x2 = posR[1];
					*(int *)&p->x1 = posL[0];
					*(int *)&p->x3 = posL[1];

					// prim/code
					setPolyG4(p);

					// Prim/OT
					// addPrim(ot, p); works but uses more instructions.
					*(int *)p = *ot | 0x8000000;
					*ot = (u_int)p & 0xffffff;
					
					p++;
				}
			}
		}
		
		lightR = lightL;
	}
	
	gGT->backBuffer->primMem.curr = p;
	sdata->RaceFlag_ElapsedTime += gGT->elapsedTimeMS * 100;
}