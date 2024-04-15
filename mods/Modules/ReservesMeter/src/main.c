#include <common.h>

void CTR_Box_DrawWireBox(RECT* r, int* unk, u_long* ot, struct PrimMem* primMem);

void DrawReservesMeter(short posX, short posY, struct Driver* driver)
{
	u_int colorAndCode;
	short reservesMeter;
	struct DB* backDB;
	u_long *primmemCurr;
	POLY_F4 *p;
	short bottomY;
	RECT box2;
	u_int auStack48 [2];
	int reservesMeterWidth;

	reservesMeter = posY - 0x2d;

	backDB = sdata->gGT->backBuffer;
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
		box2.y = posY - 3;
		box2.w = 0x31;
		box2.h = 3;
		box2.x = posX - 0x31;
		memset(auStack48, 0, 4);

		CTR_Box_DrawWireBox(&box2, auStack48, sdata->gGT->pushBuffer_UI.ptrOT, &sdata->gGT->backBuffer->primMem);

		colorAndCode = 0x280000ff; // red
		if (driver->reserves > 1600)
		{
			if (driver->reserves < 3840)
			{
				colorAndCode = 0x2800ffff; // yellow
			}
			else
			{
				colorAndCode = 0x2800ff00; // green
			}
		}
		*(u_int *)&p->r0 = colorAndCode;
		reservesMeterWidth = driver->reserves * 0xE; //Meter maximum is 8000 reserves units
		bottomY = posY - 3;
		p->y0 = posY;
		p->y1 = posY;
		p->x1 = posX;
		p->y2 = bottomY;
		p->x3 = posX;
		p->y3 = bottomY;
		
		reservesMeter = posX - ((short)(reservesMeterWidth / 0x960));
		if(reservesMeter < (posX - 0x31))
		{
			reservesMeter = posX - 0x31;
			*(u_int *)&p->r0 = 0x28ff0000; // blue
		}
		p->x0 = reservesMeter;
		p->x2 = reservesMeter;

		primmemCurr = sdata->gGT->pushBuffer_UI.ptrOT;

		*(int*)p = *primmemCurr | 0x5000000;
		*primmemCurr = (u_int)p & 0xffffff;

		backDB = sdata->gGT->backBuffer;
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
			p->y0 = posY;
			p->y1 = posY;
			p->x1 = posX;
			p->y2 = bottomY;
			p->x3 = posX;
			p->y3 = bottomY;
			p->x0 = posX - 0x31;
			p->x2 = posX - 0x31;

			// pointer to OT memory
			primmemCurr = sdata->gGT->pushBuffer_UI.ptrOT;

			*(int*)p = *primmemCurr | 0x5000000;
			*primmemCurr = (u_int)p & 0xffffff;
		}
	}

	return;
}

void ICantBelieveItTookNearly23YearsToMakeThis()
{
	if(sdata->gGT->numPlyrCurrGame == 1)
	{
		DrawReservesMeter(data.hud_1P_P1[0x8].x, data.hud_1P_P1[0x8].y + 5, (struct Driver*)sdata->gGT->threadBuckets[0].thread->object);
	}
}

///// OLD RESERVES METER THAT IS VERTICAL


/*
void DrawReservesMeter(short posX, short posY, struct Driver* driver)
{
	u_int colorAndCode;
	short reservesMeter;
	struct DB* backDB;
	u_long *primmemCurr;
	POLY_F4 *p;
	short sVar9;
	RECT box2;
	u_int auStack48 [2];
	int reservesMeterHeight;

	sVar9 = posX - 0x14;
	reservesMeter = posY - 0x2d;

	backDB = sdata->gGT->backBuffer;
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
		box2.y = posY - 0x4C;
		box2.w = 0xc;
		box2.h = 0x4C;
		box2.x = posX;
		memset(auStack48, 0, 4);

		CTR_Box_DrawWireBox(&box2, auStack48, sdata->gGT->pushBuffer_UI.ptrOT, &sdata->gGT->backBuffer->primMem);

		reservesMeter = driver->reserves;
		sVar9 = driver->reserves;
		colorAndCode = 0x280000ff; // red
		if (reservesMeter > 0x27f)
		{
			if (reservesMeter < 0x3c0)
			{
				colorAndCode = 0x280080ff; // orange
			}
			else if (reservesMeter < 0x5a0)
			{
				colorAndCode = 0x2800ffff; // yellow
			}
			else if (reservesMeter < 0x81f)
			{
				colorAndCode = 0x2800ff00; // green
			}
			else
			{
				colorAndCode = 0x28ff0000; // blue
			}
		}
		*(u_int *)&p->r0 = colorAndCode;
		reservesMeterHeight = (int)sVar9 * 0x26;
		sVar9 = posX + 0xc;
		p->x0 = posX;
		p->x1 = sVar9;
		p->x2 = posX;
		p->y2 = posY;
		p->x3 = sVar9;
		p->y3 = posY;
		
		reservesMeter = posY - ((short)(reservesMeterHeight / 0x960));
		if(reservesMeter < (posY - 0x4C))
		{
			reservesMeter = posY - 0x4C;
			*(u_int *)&p->r0 = 0x28ff0080; // purple
		}
		p->y0 = reservesMeter;
		p->y1 = reservesMeter;

		primmemCurr = sdata->gGT->pushBuffer_UI.ptrOT;

		*(int*)p = *primmemCurr | 0x5000000;
		*primmemCurr = (u_int)p & 0xffffff;

		backDB = sdata->gGT->backBuffer;
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
			p->y0 = posY - 0x4C;
			p->x1 = sVar9;
			p->y1 = posY - 0x4C;
			p->x2 = posX;
			p->y2 = posY;
			p->x3 = sVar9;
			p->y3 = posY;

			// pointer to OT memory
			primmemCurr = sdata->gGT->pushBuffer_UI.ptrOT;

			*(int*)p = *primmemCurr | 0x5000000;
			*primmemCurr = (u_int)p & 0xffffff;
		}
	}
	return;
}
*/