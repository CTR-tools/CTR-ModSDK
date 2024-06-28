#include <common.h>

#ifdef USE_ONLINE
void StatsUpgrade()
{
	/*
		Stat 9 is acceleration,
		Stats 11 and 12 speed related
	*/
	for (int i = 9; i < 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data.metaPhys[i].value[j] = data.metaPhys[i].value[4]; // copy MAX
		}
	}
}
#endif

#ifdef USE_BOOSTBAR
void DrawBoostBar(short posX, short posY, struct Driver* driver)
{
	struct GameTracker * gGT = sdata->gGT;

	short fullHeight = 3;
	int fullWidth = WIDE_34(49);

	short meterLength = ((driver->reserves * 0xE)/0x960);
	if ((meterLength > fullWidth) || (driver->reserves < 0)) { meterLength = fullWidth; }

	RECT box;
	box.x = posX - fullWidth;
	box.y = posY - fullHeight;
	box.w = fullWidth;
	box.h = fullHeight;

	struct DB * backDB = gGT->backBuffer;

	DECOMP_CTR_Box_DrawWireBox(
		&box, MakeColor(0, 0, 0),
		gGT->pushBuffer_UI.ptrOT);

	int topY = posY - fullHeight;

	/* === BoostBar ===
		red: 0-2s
		yellow: 2s-4s
		green: 4s-full
		blue: full-saffi
		purple: saffi */

	PrimCode primCode = { .poly = { .quad = 1, .renderCode = RenderCode_Polygon } };
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

	for (int i = 0; i < 2; i++)
	{
		PolyF4 * p;
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

		// Gray color for Prim #2
		colorCode = MakeColorCode(0x80, 0x80, 0x80, primCode);
		meterLength = fullWidth;
	}
}
#endif