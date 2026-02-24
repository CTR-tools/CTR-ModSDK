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

// inline Sine operation
// drops clock from ~130 to
force_inline
int MathSinInline(u_int param_1)
{
  int iVar1;

  // approximate trigonometry
  iVar1 = *(int*)&data.trigApprox[param_1 & 0x3ff];

  if ((param_1 & 0x400) == 0)
  {
    iVar1 = iVar1 << 0x10;
  }

  iVar1 = iVar1 >> 0x10;

  if ((param_1 & 0x800) != 0)
  {
	// make negative
    iVar1 = -iVar1;
  }
  return iVar1;
}

void DECOMP_RaceFlag_DrawSelf()
{
	int i, j;
	int column, row;
	int toggle;
	
	short flagPos;
	u_long *ot;
	u_int *scratchpad;
	u_int screenlimit;
	u_int dimensions;
	
	int var2;
	int var3;
	u_int var1;
	
	POLY_G4 *p;
	struct GameTracker *gGT = sdata->gGT;

	int time;
	int lightL;
	int lightR;
	
	// scratchpad
	u_int *posL;
	u_int *posR;
	int* local;
	SVECTOR* pos;
	

	if (sdata->RaceFlag_CanDraw == 0)
		return;

	if (sdata->RaceFlag_LoadingTextAnimFrame < 0)
	{
		if (
		
			(sdata->Loading.stage > LOADING_STORE_MPK_DATA) &&
			(sdata->Loading.stage < LOADING_SET_AUDIO_STATE)
			
		   )
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

	toggle = 0;
	
	// === First Loop Iteration ===
	// Remove 36*10 branching instructions,
	// Reduces clock from ~150 to ~130
	{
#ifdef REBUILD_PC
		posL = &scratchpadBuf[(toggle * 0x78 / 4) - 1];
		toggle = toggle ^ 1;
		posR = &scratchpadBuf[(toggle * 0x78 / 4)];
		local = &scratchpadBuf[0xF0/4];
		pos = &scratchpadBuf[0x108/4];
#else
		posL = (u_int *)(0x1f800000 + toggle * 0x78 - 4);
		toggle = toggle ^ 1;
		posR = (u_int *)(0x1f800000 + toggle * 0x78);
		local = (u_int *)(0x1f8000F0);
		pos = (u_int *)(0x1f800108);
#endif

		local[0] = data.checkerFlagVariables[0];
		local[1] = data.checkerFlagVariables[1];
		local[2] = data.checkerFlagVariables[2];
		local[3] = data.checkerFlagVariables[3];
		local[4] = data.checkerFlagVariables[4];

		// === Step 1 ===
		int stepRate = gGT->elapsedTimeMS;
		local[4] += local[3] * stepRate;
		var1 = (int)local[4] >> 5;
		
		// === Step 2 ===
		if (0xfff < var1)
		{
			// reset counter
			local[4] &= 0x1ffff;
			var1 = (int)local[4] >> 5;

			local[0] += 0x200;
			local[2] += 200;
			
			int sin0 = MathSinInline(local[0]) + 0xfff;
			int sin2 = MathSinInline(local[2]) + 0xfff;
			
			// reset based on trig
			local[1] = (sin0 * 0x20 >> 0xd) + 0x96;
			local[3] = (sin2 * 0x40 >> 0xd) + 0xb4;
		}

		// === Step 3 ===
		var2 = MathSinInline(var1) + 0xfff;
		var2 = var2 * local[1];
		var2 = (var2 >> 0xd) + 0x280;

		// === Step 4 ===
		var1 += 0xc80;
		lightL = MathSinInline(var1) + 0xfff;

		// === Step 5 ===
		pos[0].vy = 0xfc72;
		pos[1].vy = 0xfcd0;
		pos[2].vy = 0xfd2e;

		// === Step 6 ===
		data.checkerFlagVariables[0] = local[0];
		data.checkerFlagVariables[1] = local[1];
		data.checkerFlagVariables[2] = local[2];
		data.checkerFlagVariables[3] = local[3];
		data.checkerFlagVariables[4] = local[4];
		
		time = sdata->RaceFlag_ElapsedTime >> 5;
		var1 = time;

		flagPos = sdata->RaceFlag_Position;
		flagPos = -0xbbe - flagPos;
		pos[0].vx = flagPos;
		pos[1].vx = flagPos;
		pos[2].vx = flagPos;

		i = 0;
		// === Step 7 ===
		for (row = 0; row < 10; row++)
		{
			SVECTOR* vect;
			for (
				vect = &pos[0];
				vect < &pos[3];
				vect++)
			{
				// Range: [1.0, 2.0]
				var3 = MathSinInline(var1) + 0xfff;
				var1 += 300;

				// change all vector posZ
				vect->vz = (short)var2 + (short)(var3 * 0x20 >> 0xd);
			}

			gte_ldv3(&pos[0], &pos[1], &pos[2]);
			gte_rtpt();
			
			pos[0].vy += 0x11a;
			pos[1].vy += 0x11a;
			pos[2].vy += 0x11a;
			
			gte_stsxy3((long *)(posL + 1), (long *)(posL + 2), (long *)(posL + 3));
			posL += 3;
		}

		lightR = lightL;
	}
		

	// === Rest of Iterations ===
	// Now executing without branching
	for (column = 1; column < 36; column++)
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
		local[4] += local[3] * stepRate;
		var1 = (int)local[4] >> 5;
		
		// === Step 2 ===
		if (0xfff < var1)
		{
			// reset counter
			local[4] &= 0x1ffff;
			var1 = (int)local[4] >> 5;

			local[0] += 0x200;
			local[2] += 200;
			
			int sin0 = MathSinInline(local[0]) + 0xfff;
			int sin2 = MathSinInline(local[2]) + 0xfff;
			
			// reset based on trig
			local[1] = (sin0 * 0x20 >> 0xd) + 0x96;
			local[3] = (sin2 * 0x40 >> 0xd) + 0xb4;
		}

		// === Step 3 ===
		var2 = MathSinInline(var1) + 0xfff;
		var2 = var2 * local[1];
		var2 = (var2 >> 0xd) + 0x280;

		// === Step 4 ===
		var1 += 0xc80;
		lightL = MathSinInline(var1) + 0xfff;

		// === Step 5 ===
		pos[0].vy = 0xfc72;
		pos[1].vy = 0xfcd0;
		pos[2].vy = 0xfd2e;

		// === Step 6 ===
		time += 0x100;
		var1 = time;

		pos[0].vx += 100;
		pos[1].vx += 100;
		pos[2].vx += 100;

		i = 0;
		// === Step 7 ===
		for (row = 0; row < 10; row++)
		{
			SVECTOR* vect;
			for (
				vect = &pos[0];
				vect < &pos[3];
				vect++)
			{
				// Range: [1.0, 2.0]
				var3 = MathSinInline(var1) + 0xfff;
				var1 += 300;

				// change all vector posZ
				vect->vz = (short)var2 + (short)(var3 * 0x20 >> 0xd);
			}

			gte_ldv3(&pos[0], &pos[1], &pos[2]);
			gte_rtpt();
			
			pos[0].vy += 0x11a;
			pos[1].vy += 0x11a;
			pos[2].vy += 0x11a;
			
			gte_stsxy3((long *)(posL + 1), (long *)(posL + 2), (long *)(posL + 3));
			
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
					// TRUE for gray, FALSE for white
					u_char boolDark = (((column >> 2) + (i >> 2) & 1U) != 0);

					u_char colorR = RaceFlag_CalculateBrightness(lightR, boolDark);
					setRGB0(p, colorR, colorR, colorR);
					*(int*)&p->r2 = *(int*)&p->r0;
					
					u_char colorL = RaceFlag_CalculateBrightness(lightL, boolDark);
					setRGB1(p, colorL, colorL, colorL);
					*(int*)&p->r3 = *(int*)&p->r1;

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