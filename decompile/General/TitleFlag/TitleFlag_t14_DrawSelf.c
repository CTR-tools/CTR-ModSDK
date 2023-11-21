#include <common.h>

#ifdef REBUILD_PC
int scratchpadBuf[0x1000];
#endif

typedef struct Color
{
	u_char R;
	u_char G;
	u_char B;
} Color;

void TitleFlag_DrawSelf()
{
	char i, j;
	char column, row;
	u_char toggle;
	short flagPos;
	u_long *ot;
	long *scratchpad;
	u_int screenlimit;
	u_int dimensions;
	int approx[2];
	int colorSine[2];
	u_char brightnessRight;
	u_char brightnessLeft;
	u_char rightRGB[3];
	u_char leftRGB[3];
	u_int angle[2];
	u_int *top;
	u_int *bottom;
	POLY_G4 *p;
	SVECTOR *vect;
	struct DB *backDB;
	struct GameTracker *gGT = sdata->gGT;

	// 0x10, 0x18, 0x20
	SVECTOR pos[3];

	// 0x28, 0x2C, 0x30, 0x34, 0x38
	// copies of data.checkeredFlag[X]
	int unk1;
	int unk2;
	int waveAngle;
	int unk3;
	int unk4;
	int time;

	if (sdata->TitleFlag_CanDraw == 0)
		return;

	if (sdata->TitleFlag_LoadingTextAnimFrame < 0)
	{
		if ((5 < sdata->Loading.stage) && (sdata->Loading.stage < 8))
		{
			sdata->TitleFlag_LoadingTextAnimFrame = 0;
		}

		if (sdata->TitleFlag_LoadingTextAnimFrame < 0)
			goto SKIP_LOADING_TEXT;
	}

	TitleFlag_DrawLoadingString();

SKIP_LOADING_TEXT:

	sdata->TitleFlag_CopyLoadStage = sdata->Loading.stage;
	ot = (u_long *)TitleFlag_GetOT();

	gte_SetRotMatrix(&data.matrixTitleFlag);
	gte_SetTransMatrix(&data.matrixTitleFlag);
	gte_SetGeomOffset(0x100, 0x78);
	gte_SetGeomScreen(0x100);

	p = NULL;

#ifdef REBUILD_PC
	scratchpad = &scratchpadBuf[0];
	memset(&scratchpadBuf[0], 0, 0x1000 * 4);
#else
	scratchpad = (long *)0x1f800000;
#endif
	toggle = 1;
	data.checkerFlagVariables[4] += data.checkerFlagVariables[3] * gGT->elapsedTimeMS;
	angle[0] = (int)data.checkerFlagVariables[4] >> 5;

	if (0xfff < angle[0])
	{
		data.checkerFlagVariables[4] &= 0x1ffff;
		angle[0] = (int)data.checkerFlagVariables[4] >> 5;

		// += 45 degrees
		data.checkerFlagVariables[0] += 0x200;

		// Range: [1.0, 2.0]
		approx[0] = MATH_Sin(data.checkerFlagVariables[0]) + 0xfff;

		// Range: [16, 32] + 0x96
		data.checkerFlagVariables[1] = (approx[0] * 0x20 >> 0xd) + 0x96;

		// += 18 degrees
		data.checkerFlagVariables[2] = data.checkerFlagVariables[2] + 200;

		// Range: [1.0, 2.0]
		approx[0] = MATH_Sin(data.checkerFlagVariables[2]) + 0xfff;

		// Range: [32, 64] + 0xb4
		data.checkerFlagVariables[3] = (approx[0] * 0x40 >> 0xd) + 0xb4;
	}

	// Range: [1.0, 2.0]
	approx[0] = MATH_Sin(angle[0]) + 0xfff;
	approx[0] = approx[0] * data.checkerFlagVariables[1];
	approx[0] = (approx[0] >> 0xd) + 0x280;

	// 280 degrees (3/4 of 360)
	angle[0] += 0xc80;

	// Range: [1.0, 2.0]
	colorSine[0] = MATH_Sin(angle[0]) + 0xfff;
	FP(1.0);

	time = sdata->TitleFlag_ElapsedTime >> 5;
	angle[0] = time;

	pos[0].vy = 0xfc72;
	pos[1].vy = 0xfcd0;
	pos[2].vy = 0xfd2e;

	flagPos = sdata->TitleFlag_Position;
	flagPos = -0xbbe - flagPos;
	pos[0].vx = flagPos;
	pos[1].vx = flagPos;
	pos[2].vx = flagPos;

	for (i = 0; i < 10; i++)
	{
		for (
			j = 0, vect = &pos[0];
			j < 3;
			j++, vect++)
		{
			// Range: [1.0, 2.0]
			approx[1] = MATH_Sin(angle[0]) + 0xfff;
			angle[0] += 300;

			vect->vz = (short)approx[0] + (short)(approx[1] * 0x20 >> 0xd);
		}

		gte_ldv3(&pos[0], &pos[1], &pos[2]);
		gte_rtpt();
		pos[0].vy += 0x11a;
		pos[1].vy += 0x11a;
		pos[2].vy += 0x11a;
		gte_stsxy3(scratchpad, scratchpad + 1, scratchpad + 2);
		scratchpad += 3;
	}

	screenlimit = 0x80008000;

	// screen size
	dimensions = 0xd80200;

	unk1 = data.checkerFlagVariables[0];
	unk2 = data.checkerFlagVariables[1];
	waveAngle = data.checkerFlagVariables[2];
	unk3 = data.checkerFlagVariables[3];
	unk4 = data.checkerFlagVariables[4];

	// vertical strips
	for (column = 0; column < 35; column++)
	{
#ifdef REBUILD_PC
		top = &scratchpadBuf[(toggle * 0x78 / 4) - 1];
		toggle = toggle ^ 1;
		bottom = &scratchpadBuf[(toggle * 0x78 / 4) - 0];
#else
		top = (u_int *)((0x1f800000 + toggle * 0x78) - 4);
		toggle = toggle ^ 1;
		bottom = (u_int *)(0x1f800000 + toggle * 0x78);
#endif

		// increment
		unk4 += unk3 * 0x40;
		angle[0] = unk4;
		angle[1] = (int)angle[0] >> 5;

		if (0xfff < angle[1])
		{
			angle[1] = (int)(angle[0] & 0x1ffff) >> 5;
			unk4 = angle[0] & 0x1ffff;

			// increment
			unk1 += 0x200;
			angle[0] = unk1;

			// Range: [1.0, 2.0]
			approx[0] = MATH_Sin(angle[0]) + 0xfff;

			// Range: [16, 32] + 0x96
			unk2 = (approx[0] * 0x20 >> 0xd) + 0x96;

			// increment
			waveAngle += 200;
			angle[0] = waveAngle;

			// Range: [1.0, 2.0]
			approx[0] = MATH_Sin(angle[0]) + 0xfff;

			// Range: [32, 64] + 0xb4
			unk3 = (approx[0] * 0x40 >> 0xd) + 0xb4;
		}

		// Range: [1.0, 2.0]
		approx[0] = MATH_Sin(angle[1]) + 0xfff;
		approx[0] = (approx[0] * unk2 >> 0xd) + 0x280;

		// 280 degrees
		angle[1] += 0xc80;

		// range: [1.0, 2.0]
		colorSine[1] = MATH_Sin(angle[1]) + 0xfff;

		pos[0].vy = 0xfc72;
		pos[1].vy = 0xfcd0;
		pos[2].vy = 0xfd2e;
		pos[0].vx += 100;
		pos[1].vx += 100;
		pos[2].vx += 100;

		// increment
		time += 0x100;
		angle[0] = time;

		for (
			i = 0, vect = &pos[0];
			i < 3;
			i++, vect++)
		{
			// Range: [1.0, 2.0]
			approx[1] = MATH_Sin(angle[0]) + 0xfff;
			angle[0] += 300;

			// change all vector posZ
			vect->vz = (short)approx[0] + (short)(approx[1] * 0x20 >> 0xd);
		}

		gte_ldv3(&pos[0], &pos[1], &pos[2]);
		gte_rtpt();

		i = 0;

		// horizontal strips
		for (row = 0; row < 10; row++)
		{
			gte_stsxy3((long *)(top + 1), (long *)(top + 2), (long *)(top + 3));

			if (row < 9)
			{
				for (
					j = 0, vect = &pos[0];
					j < 3;
					j++, vect++)
				{
					// Range: [1.0, 2.0]
					approx[1] = MATH_Sin(angle[0]) + 0xfff;
					angle[0] += 300;

					// change all vector posZ
					vect->vz = (short)approx[0] + (short)(approx[1] * 0x20 >> 0xd);
				}

				pos[0].vy += 0x11a;
				pos[1].vy += 0x11a;
				pos[2].vy += 0x11a;
				gte_ldv3(&pos[0], &pos[1], &pos[2]);
				gte_rtpt();
			}

			if (i == 0)
			{
				top++;
			}

			for (j = (i == 0); j < 3; bottom++, top++, j++, i++)
			{
				if (
					((bottom[0] & bottom[1] & top[0] & top[1] & screenlimit) == 0) &&
					((dimensions - bottom[0] & dimensions - bottom[1] & dimensions - top[0] & dimensions - top[1] & screenlimit) == 0))
				{
					backDB = gGT->backBuffer;

					p = (POLY_G4 *)backDB->primMem.curr;
					if (p <= (POLY_G4 *)backDB->primMem.endMin100)
					{
						backDB->primMem.curr = p + 1;
					}

					if (p == 0)
						return;

					// Change this for custom tilecolors;
					Color lightTile = {255, 255, 255}; // default: white
					Color darkTile = {160, 160, 160};  // default: grey

					// dark tile
					Color CurrTile = darkTile;
					int positiveConstant = 0x69;
					int negativeConstant = -0x37;
					int something = 0xA0;

					// light tile
					if (((column >> 2) + (i >> 2) & 1U) == 0)
					{
						CurrTile = lightTile;
						positiveConstant = 0x82;
						negativeConstant = -0x7d;
						something = 0xFF;
					}

					// Calculate color brightness
					// You don't have to do use either dark/light tile calculations,
					// you can use the same calculation constants for both left and right
					brightnessRight = (u_char)((colorSine[0] * positiveConstant + (0x2000 - colorSine[0]) * something) >> 0xD);
					brightnessLeft = (u_char)((colorSine[1] * negativeConstant + (something << 0xD)) >> 0xD);

					rightRGB[0] = (CurrTile.R * brightnessRight) >> 8;
					rightRGB[1] = (CurrTile.G * brightnessRight) >> 8;
					rightRGB[2] = (CurrTile.B * brightnessRight) >> 8;

					leftRGB[0] = (CurrTile.R * brightnessLeft) >> 8;
					leftRGB[1] = (CurrTile.G * brightnessLeft) >> 8;
					leftRGB[2] = (CurrTile.B * brightnessLeft) >> 8;

					// positions
					*(int *)&p->x0 = bottom[0];
					*(int *)&p->x2 = bottom[1];
					*(int *)&p->x1 = top[0];
					*(int *)&p->x3 = top[1];

					// right corner
					setRGB0(p, rightRGB[0], rightRGB[1], rightRGB[2]);
					setRGB2(p, rightRGB[0], rightRGB[1], rightRGB[2]);

					// left corner
					setRGB1(p, leftRGB[0], leftRGB[1], leftRGB[2]);
					setRGB3(p, leftRGB[0], leftRGB[1], leftRGB[2]);

					// prim/code
					setPolyG4(p);

					// Prim/OT
					// addPrim(ot, p); works but uses more instructions.
					*(int *)p = *ot | 0x8000000;
					*ot = (u_int)p & 0xffffff;
				}
			}
		}
		colorSine[0] = colorSine[1];
	}
	sdata->TitleFlag_ElapsedTime += gGT->elapsedTimeMS * 100;
}