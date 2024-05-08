// used for boost bar

#ifdef USE_BOOSTBAR
void uibb_entryHook()
{
	struct UiElement2D* ptrHudData;
	
	// This is already 206
	// data.hud_1P_P1[8].y
	
	// Change all these, should be
	// same value as hud_1P_P1.y 
	data.hud_2P_P1[8].y -= 6;
	data.hud_2P_P2[8].y -= 6;
	data.hud_4P_P1[8].y -= 6;
	data.hud_4P_P2[8].y -= 6;
	data.hud_4P_P3[8].y -= 6;
	data.hud_4P_P4[8].y -= 6;
	
	// lapcount that draws above bootbar
	data.hud_2P_P1[1].y -= 6;
	data.hud_2P_P2[1].y -= 6;
	data.hud_4P_P1[1].y -= 6;
	data.hud_4P_P2[1].y -= 6;
	data.hud_4P_P3[1].y -= 6;
	data.hud_4P_P4[1].y -= 6;
}

void DrawBoostBar(short posX, short posY, struct Driver* driver)
{
	// Copies code from UI_DrawSlideMeter
	
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

	// === BoostBar ===
	// always height of 3
	fullHeight = 3;

	// width of full bar
	fullWidth = WIDE_PICK(0x31, 0x25);

	// === BoostBar ===
	// length depends on reserves
	meterLength = ((driver->reserves * 0xE)/0x960);
	if((meterLength > fullWidth) || (driver->reserves < 0))
		meterLength = fullWidth;
	
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

	// === BoostBar ===
	// red: 0-1599
	// yellow: 1600-3839
	// green: 3840-full
	// blue: full-inf
	// purple: inf
	
	colorAndCode = 0x280000ff; // red
	if (driver->reserves >= 1600)
		colorAndCode = 0x2800ffff; // yellow
		if (driver->reserves >= 3840)
			colorAndCode = 0x2800ff00; // green

	if (meterLength == fullWidth)
		colorAndCode = 0x28ff0000; // blue
		
	if (driver->reserves < 0)
		colorAndCode = 0x28ff00ff; // purple

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
}
#endif