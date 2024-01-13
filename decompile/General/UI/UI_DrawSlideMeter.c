#include <common.h>

void DECOMP_UI_DrawSlideMeter(short posX, short posY, struct Driver* driver)
{
	struct GameTracker *gGT;
	u_int colorAndCode;
	int maxRoom;
	struct DB* backDB;
	POLY_F4 *p;
	u_long *primmemCurr;
	short meterHeight;
	short meterLength;
	RECT box;
	u_int auStack40 [2];
	int currentRoomRemaining;
	
	gGT = sdata->gGT;

	meterLength = 0;

	// height of bar in 1P or 2P
	meterHeight = 7;

	// if numPlyrCurrGame is more than 2 (3P or 4P)
	if (2 < gGT->numPlyrCurrGame)
	{
		// Make the bar shorter
		meterHeight = 3;
	}

	// if powerslide meter is not zero
	if ((int)driver->turbo_MeterRoomLeft != 0)
	{
		// current room remaining
		currentRoomRemaining = driver->turbo_MeterRoomLeft * WIDE_PICK(0x31, 0x25);

		// max amount of room in turbo
		maxRoom = (u_int)driver->const_turboMaxRoom << 5;

		/*
		// max turbo meter size must be more than zero
		if (driver->const_turboMaxRoom == 0)
		{
			trap(0x1c00);
		}
		if ((maxRoom == -1) && (backDB == -0x80000000))
		{
			trap(0x1800);
		}
		*/

		// length of rectangle is currentRoom / maxRoom
		meterLength = WIDE_PICK(0x31, 0x25) - (short)(currentRoomRemaining / maxRoom);
	}
	box.x = posX - WIDE_PICK(0x31, 0x25);
	box.y = posY - meterHeight;
	box.w = WIDE_PICK(0x31, 0x25);
	box.h = meterHeight;
	memset(auStack40, 0, 4);

	DECOMP_CTR_Box_DrawWireBox(&box, auStack40, gGT->tileView_UI.ptrOT, &gGT->backBuffer->primMem);

	backDB = gGT->backBuffer;
	primmemCurr = backDB->primMem.curr;
	p = 0;

	// if there is room remaining to draw
	if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
	{
		// increment "curr" for next draw after powerslide meter
		backDB->primMem.curr = &primmemCurr[6];

		// set pointer for where to draw powerslide meter primMem
		p = (POLY_F4 *)primmemCurr;
	}

	// if we are definitely drawing the powerslide meter
	if (p != 0)
	{
		// if remaining room is more than the "low warning"
		if ((int)((u_int)driver->const_turboLowRoomWarning << 5) < (int)driver->turbo_MeterRoomLeft)
		{
			// set color to green
			colorAndCode = 0x2800ff00;
		}

		// if room remaining is lower than "low warning"
		else
		{
			// set color to red
			colorAndCode = 0x280000ff;
		}

		*(u_int *)&p->r0 = colorAndCode;
		gGT = gGT;
		meterHeight = posY - meterHeight;
		p->x0 = posX - meterLength;
		p->y0 = meterHeight;
		p->x1 = posX;
		p->y1 = meterHeight;
		p->y2 = posY;
		p->x3 = posX;
		p->y3 = posY;
		p->x2 = posX - meterLength;

		// pointer to OT memory
		primmemCurr = gGT->tileView_UI.ptrOT;

		*(int*)p = *primmemCurr | 0x5000000;
		*primmemCurr = (u_int)p & 0xffffff;

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
			*(u_int *)&p->r0 = 0x28808080;
			gGT = gGT;
			p->x0 = posX - WIDE_PICK(0x31, 0x25);
			p->y0 = meterHeight;
			p->x1 = posX;
			p->y1 = meterHeight;
			p->y2 = posY;
			p->x3 = posX;
			p->y3 = posY;
			p->x2 = posX - WIDE_PICK(0x31, 0x25);

			// pointer to OT memory
			primmemCurr = gGT->tileView_UI.ptrOT;

			*(int*)p = *primmemCurr | 0x5000000;
			*primmemCurr = (u_int)p & 0xffffff;
		}
	}
	return;
}