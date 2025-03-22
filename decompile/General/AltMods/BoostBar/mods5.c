void DrawBoostBar(short posX, short posY, struct Driver* driver)
{
#ifdef USE_ONLINE
	const int numberBarDivisions = 5;
	const Color barEmptyColor = MakeColor(0x80, 0x80, 0x80);
#endif

	struct GameTracker* gGT = sdata->gGT;
	short fullHeight = 3;
#ifdef USE_ONLINE
	short fullWidth = WIDE_34(96);
	int reserves = driver->reserves + driver->uncappedReserves;
	int numFullBarsFilled = reserves / SECONDS(5);
	int numBarsFilled = reserves / SECONDS(1);
	int reserveLength = reserves % SECONDS(5);
	int meterLength = (fullWidth * reserveLength) / SECONDS(5);
	posX += 35;
#else
	short fullWidth = WIDE_34(49);
	short meterLength = ((driver->reserves * 0xE) / 0x960);
	if ((meterLength > fullWidth) || (driver->reserves < 0)) { meterLength = fullWidth; }
#endif

	RECT box;
	short topX = posX - fullWidth;
	short topY = posY - fullHeight;
	box.x = topX;
	box.y = topY;
	box.w = fullWidth;
	box.h = fullHeight;

	struct DB* backDB = gGT->backBuffer;

	DECOMP_CTR_Box_DrawWireBox(&box, MakeColor(0, 0, 0), gGT->pushBuffer_UI.ptrOT);

#ifdef USE_ONLINE
	int spacing = fullWidth / numberBarDivisions;
	int remainder = fullWidth % numberBarDivisions;
	for (int i = 0; i < numberBarDivisions - 1; i++)
	{
		LineF2* p;
		GetPrimMem(p);
		if (p == nullptr) { return; }

		const PrimCode primCode = { .line = {.renderCode = RenderCode_Line } };
		const Color colorCode = MakeColorCode(0, 0, 0, primCode);
		p->colorCode = colorCode;
		s16 xPos = posX - (spacing * (i + 1));
		if (remainder > 0) { xPos--; remainder--; }
		p->v[0].pos.x = xPos;
		p->v[0].pos.y = topY;
		p->v[1].pos.x = xPos;
		p->v[1].pos.y = topY + fullHeight;
		AddPrimitive(p, gGT->pushBuffer_UI.ptrOT);
	}
#endif

	const PrimCode primCode = { .poly = {.quad = 1, .renderCode = RenderCode_Polygon } };

#ifdef USE_ONLINE
	char s_barsCompleted[15];
	sprintf(s_barsCompleted, "%d", numFullBarsFilled);
	DECOMP_DecalFont_DrawLine(s_barsCompleted, topX - 2, topY - 3, FONT_SMALL, PENTA_WHITE | JUSTIFY_RIGHT);

	ColorCode colorCode;
	ColorCode bgBarColor = barEmptyColor;
	Color HsvToRgb(int h, int s, int v);
	if (numFullBarsFilled > 0) { bgBarColor = HsvToRgb(5 * numberBarDivisions * (numFullBarsFilled - 1), (int)(255 * 0.5), (int)(255 * 0.5)); }
	colorCode = HsvToRgb(5 * numBarsFilled, (int)(255 * 0.9), (int)(255 * 1.0));
	colorCode.code = primCode;
	bgBarColor.code = primCode;
#else
	/* === BoostBar ===
		red: 0-2s
		yellow: 2s-4s
		green: 4s-full
		blue: full-saffi
		purple: saffi */
	ColorCode colorCode = MakeColorCode(0xFF, 0, 0, primCode); // red
	if (driver->reserves < 0) {
		colorCode = MakeColorCode(0xFF, 0x0, 0xFF, primCode); // purple
	}
	else if (meterLength == fullWidth) {
		colorCode = MakeColorCode(0, 0, 0xFF, primCode); // blue
	}
	else if (driver->reserves >= SECONDS(4)) {
		colorCode = MakeColorCode(0, 0xFF, 0, primCode); // green
	}
	else if (driver->reserves >= SECONDS(2)) {
		colorCode = MakeColorCode(0xFF, 0xFF, 0, primCode); // yellow
	}
#endif

	for (int i = 0; i < 2; i++)
	{
		PolyF4* p;
		GetPrimMem(p);
		if (p == nullptr) { return; }

		p->colorCode = colorCode;
		p->v[0].pos.x = posX - meterLength;
		p->v[0].pos.y = topY;
		p->v[1].pos.x = posX;
		p->v[1].pos.y = topY;
		p->v[2].pos.x = posX - meterLength;
		p->v[2].pos.y = posY;
		p->v[3].pos.x = posX;
		p->v[3].pos.y = posY;
		AddPrimitive(p, gGT->pushBuffer_UI.ptrOT);

#ifdef USE_ONLINE
		colorCode = bgBarColor;
#else
		colorCode = MakeColorCode(0x80, 0x80, 0x80, primCode); // Gray color for Prim #2
#endif
		meterLength = fullWidth;
	}
}
