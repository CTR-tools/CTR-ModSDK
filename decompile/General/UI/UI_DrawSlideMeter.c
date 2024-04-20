#include <common.h>

void DECOMP_UI_DrawSlideMeter(short posX, short posY, struct Driver* driver)
{
	struct GameTracker *gGT;
	u_int colorAndCode;
	int maxRoom;
	struct DB* backDB;
	POLY_F4 *p;
	u_long* ptrOT;
	u_long* primmemCurr;
	int fullWidth;
	short fullHeight;
	short meterLength;
	RECT box;
	int currentRoomRemaining;
	
	gGT = sdata->gGT;

	fullHeight = 7;
	if (gGT->numPlyrCurrGame > 2)
		fullHeight = 3;

	// width of full bar
	fullWidth = WIDE_PICK(0x31, 0x25);

	// width of boost meter
	meterLength = 0;
	
	// if powerslide meter is not zero
	if ((int)driver->turbo_MeterRoomLeft != 0)
	{
		// current room remaining
		currentRoomRemaining = driver->turbo_MeterRoomLeft * fullWidth;

		// max amount of room in turbo
		maxRoom = (u_int)driver->const_turboMaxRoom << 5;

		// length of rectangle is currentRoom / maxRoom
		meterLength = fullWidth - (short)(currentRoomRemaining / maxRoom);
	}
	
	box.x = posX - fullWidth;
	box.y = posY - fullHeight;
	box.w = fullWidth;
	box.h = fullHeight;
	
	backDB = gGT->backBuffer;
	int boxColor = 0;
	
	DECOMP_CTR_Box_DrawWireBox(
		&box, &boxColor, 
		gGT->pushBuffer_UI.ptrOT, 
		&backDB->primMem);
		
	int topY = posY - fullHeight;

	// red color, ready to boost
	colorAndCode = 0x280000ff;

	// green color, no boost yet
	if ((int)((u_int)driver->const_turboLowRoomWarning << 5) < (int)driver->turbo_MeterRoomLeft)
		colorAndCode = 0x2800ff00;

	for(int i = 0; i < 2; i++)
	{
		primmemCurr = backDB->primMem.curr;
		p = 0;
	
		// if there is room remaining to draw
		if (primmemCurr <= (u_long *)backDB->primMem.endMin100)
		{
			p = (POLY_F4 *)primmemCurr;
			backDB->primMem.curr = p+1;
		}
	
		if (p == 0)
			return;
	
		*(int*)&p->r0 = colorAndCode;
		
		p->y0 = topY;
		p->y1 = topY;
		p->y2 = posY;
		p->y3 = posY;
		
		p->x0 = posX - meterLength;
		p->x1 = posX;
		p->x2 = posX - meterLength;
		p->x3 = posX;
	
		ptrOT = gGT->pushBuffer_UI.ptrOT;
		*(int*)p = *ptrOT | 0x5000000;
		*ptrOT = (u_int)p & 0xffffff;
		
		// Gray color for Prim #2
		colorAndCode = 0x28808080;
		
		// full length of meter
		meterLength = fullWidth;
	}
	
	#ifdef USE_BOOSTBAR
	void DrawBoostBar(short posX, short posY, struct Driver* driver);
	DrawBoostBar(posX, posY+5, driver);
	#endif
}