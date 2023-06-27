#include <common.h>

void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);

void DECOMP_UI_JumpMeter_Draw(short posX, short posY, struct Driver* driver)
{
	struct GameTracker *gGT;
	u_int colorAndCode;
	short jumpMeter;
	struct DB* backDB;
	int iVar5;
	u_long *primmemCurr;
	POLY_F4 *p;
	int iVar8;
	short sVar9;
	int iVar10;
	int iVar11;
	RECT box;
	u_int auStack64 [2];
	RECT box2;
	u_int auStack48 [2];
	int jumpMeterHeight;
	int whateverThisIs;
	
	gGT = sdata->gGT;

	iVar5 = ((int)driver->jumpMeter / 0x3c0) * 0x10000 >> 0x10;
	whateverThisIs = (int)driver->jumpMeter + iVar5 * -0x3c0;
	iVar10 = ((whateverThisIs / 6 + (whateverThisIs >> 0x1f) >> 4) - (whateverThisIs >> 0x1f)) * 0x10000 >> 0x10;
	iVar11 = (int)posX;
	iVar8 = (int)posY + -0x2b;

	// === widescreen ===
	// instead of -0x10, -4, +4,
	// use -0x10, -6, +0
	DebugFont_DrawNumbers(iVar5, iVar11 - 0x10, iVar8);
	DebugFont_DrawNumbers(iVar10, iVar11 + -6, iVar8);
	DebugFont_DrawNumbers((((whateverThisIs + iVar10 * -0x60) * 100) / 0x3c0) * 0x10000 >> 0x10, iVar11 + 0, iVar8);

	sVar9 = posX + -0x14;
	jumpMeter = posY + -0x2d;
	
	// === widescreen ===
	// use 0x1D(29) instead of 0x22(34)
	box.w = 0x1D;
	
	box.h = 10;
	box.x = sVar9;
	box.y = jumpMeter;
	memset(auStack64, 0, 4);

	CTR_Box_DrawWireBox(&box, auStack64, gGT->tileView_UI.ptrOT, &gGT->backBuffer->primMem);

	backDB = gGT->backBuffer;
	primmemCurr = backDB->primMem.curr;
	p = 0;

	// if there is room left for more
	if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
	{
		// add primitives
		backDB->primMem.curr = &primmemCurr[6];
		p = (POLY_F4 *)primmemCurr;
	}

	if (p != 0)
	{
		*(u_int *)&p->r0 = 0x28ffffff;
		p->x1 = posX + 0xe * 750/1000;
		p->x3 = posX + 0xe * 750/1000;
		p->x0 = sVar9;
		p->y0 = jumpMeter;
		p->y1 = jumpMeter;
		p->x2 = sVar9;
		p->y2 = posY - 0x23;
		p->y3 = posY - 0x23;

		// pointer to OT memory
		primmemCurr = gGT->tileView_UI.ptrOT;

		*(int*)p = *primmemCurr | 0x5000000;
		*primmemCurr = (u_int)p & 0xffffff;

		box2.y = posY - 0x26;
		box2.w = 0xc * 750 / 1000; // === widescreen ===
		box2.h = 0x26;
		box2.x = posX;
		memset(auStack48, 0, 4);

		CTR_Box_DrawWireBox(&box2, auStack48, gGT->tileView_UI.ptrOT, &gGT->backBuffer->primMem);

		backDB = gGT->backBuffer;
		primmemCurr = backDB->primMem.curr;
		p = 0;

		if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
		{
			backDB->primMem.curr = &primmemCurr[6];
			p = (POLY_F4 *)primmemCurr;
		}

		if (p != 0)
		{
			jumpMeter = driver->jumpMeter;
			sVar9 = driver->jumpMeter;
			colorAndCode = 0x28ff0000;
			if (0x27f < jumpMeter)
			{
				if (jumpMeter < 0x3c0)
				{
					colorAndCode = 0x2800ff00;
				}
				else
				{
					if (jumpMeter < 0x5a0)
					{
						colorAndCode = 0x2800ffff;
					}
					else
					{
						colorAndCode = 0x280000ff;
					}
				}
			}
			*(u_int *)&p->r0 = colorAndCode;
			jumpMeterHeight = (int)sVar9 * 0x26;
			sVar9 = posX + 0xc * 750 / 1000; // === widescreen ===
			p->x0 = posX;
			p->x1 = sVar9;
			p->x2 = posX;
			p->y2 = posY;
			p->x3 = sVar9;
			p->y3 = posY;
			jumpMeter = posY - ((short)(jumpMeterHeight / 0x960) - (short)(jumpMeterHeight / 0x80000000));
			p->y0 = jumpMeter;
			p->y1 = jumpMeter;

			primmemCurr = gGT->tileView_UI.ptrOT;

			*(int*)p = *primmemCurr | 0x5000000;
			*primmemCurr = (u_int)p & 0xffffff;

			backDB = gGT->backBuffer;
			primmemCurr = backDB->primMem.curr;
			p = 0;

			// If there is room to add more
			if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
			{
				// Add more primitives
				backDB->primMem.curr = &primmemCurr[6];
				p = (POLY_F4 *)primmemCurr;
			}

			if (p != 0)
			{
				*(u_int *)&p->r0 = 0x28808080;
				p->x0 = posX;
				p->y0 = posY - 0x26;
				p->x1 = sVar9;
				p->y1 = posY - 0x26;
				p->x2 = posX;
				p->y2 = posY;
				p->x3 = sVar9;
				p->y3 = posY;

				// pointer to OT memory
				primmemCurr = gGT->tileView_UI.ptrOT;

				*(int*)p = *primmemCurr | 0x5000000;
				*primmemCurr = (u_int)p & 0xffffff;
			}
		}
	}
	return;
}