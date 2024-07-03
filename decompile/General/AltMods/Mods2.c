// used for 16x9 (part 1)
// used for oxide
#include <common.h>

#ifdef USE_ONLINE
Color HsvToRgb(int h, int s, int v);

void FixReservesIncrement(struct Driver * driver, int reserves)
{
	if (driver->reserves > 30000) { driver->uncappedReserves += reserves; }
	else { driver->reserves += reserves; }
}
#endif

#ifdef USE_BOOSTBAR
void DrawBoostBar(short posX, short posY, struct Driver* driver)
{
	#ifdef USE_ONLINE
	const int numberBarDivisions = 5;
	const Color barEmptyColor = MakeColor(0x80, 0x80, 0x80);
	#endif

	struct GameTracker * gGT = sdata->gGT;
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
	short meterLength = ((driver->reserves * 0xE)/0x960);
	if ((meterLength > fullWidth) || (driver->reserves < 0)) { meterLength = fullWidth; }
	#endif

	RECT box;
	short topX = posX - fullWidth;
	short topY = posY - fullHeight;
	box.x = topX;
	box.y = topY;
	box.w = fullWidth;
	box.h = fullHeight;

	struct DB * backDB = gGT->backBuffer;

	DECOMP_CTR_Box_DrawWireBox(&box, MakeColor(0, 0, 0), gGT->pushBuffer_UI.ptrOT);

	#ifdef USE_ONLINE
	int spacing = fullWidth / numberBarDivisions;
	int remainder = fullWidth % numberBarDivisions;
	for (int i = 0; i < numberBarDivisions - 1; i++)
	{
		LineF2 * p;
		GetPrimMem(p);
		if (p == nullptr) { return; }

		const PrimCode primCode = { .line = { .renderCode = RenderCode_Line } };
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

	const PrimCode primCode = { .poly = { .quad = 1, .renderCode = RenderCode_Polygon } };

	#ifdef USE_ONLINE
	char s_barsCompleted[15];
	sprintf(s_barsCompleted, "%d", numFullBarsFilled);
	DECOMP_DecalFont_DrawLine(s_barsCompleted, topX - 2, topY - 3, FONT_SMALL, PENTA_WHITE | JUSTIFY_RIGHT);

	ColorCode colorCode;
	ColorCode bgBarColor = barEmptyColor;
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

		#ifdef USE_ONLINE
		colorCode = bgBarColor;
		#else
		colorCode = MakeColorCode(0x80, 0x80, 0x80, primCode); // Gray color for Prim #2
		#endif
		meterLength = fullWidth;
	}
}
#endif

#ifdef USE_16BY9
void ui16by9_ViewProj(struct PushBuffer* pb)
{
	// Y axis is already scaled 512/216 x 0x360/0x600 -> 4x3
	// X axis correction for 16x9 must be 9/16 x 4/3 -> 0.75
	// 16x9 is 0.75, 20x9 is 0.6, etc

	// 600  / 1000 for 20x9
	// 750  / 1000 for 16x9
	// 1000 / 1000 for 4x3

	pb->matrix_ViewProj.t[0] =
	pb->matrix_ViewProj.t[0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][0] =
	pb->matrix_ViewProj.m[0][0] * 750 / 1000;

	pb->matrix_ViewProj.m[0][1] =
	pb->matrix_ViewProj.m[0][1] * 750 / 1000;

	pb->matrix_ViewProj.m[0][2] =
	pb->matrix_ViewProj.m[0][2] * 750 / 1000;
}
#endif

#ifdef USE_OXIDE
void Oxide_HookAppendLoadingQueue()
{
	int loop;
	struct LoadQueueSlot* lqs_next;
	struct LoadQueueSlot* lqs_curr;
	int packIndex = DECOMP_LOAD_GetAdvPackIndex();

	// set pointers
	lqs_curr = &sdata->queueSlots[sdata->queueLength-1];
	lqs_next = &lqs_curr[1];

	// only continue if you tried to load oxide in 1st place
	if(sdata->gGT->podium_modelIndex_First != 0x8D) return;

	// quit if not this condition
	if(lqs_curr->callback.funcPtr != DECOMP_LOAD_Callback_Podiums) return;

	// if most recent addition to the queue, is the last append for podiums

	// shift the request
	for(loop = 0; loop < 0x18/4; loop++)
	{
		// shift down one
		*(int*)((int*)lqs_next + loop) =
		*(int*)((int*)lqs_curr + loop);
	}

	// add oxide request
	lqs_curr->subfileIndex = packIndex + 0xf*2 + 0x18D;
	lqs_curr->ptrDestination = (void*)&data.podiumModel_firstPlace;
	lqs_curr->callback.flags = 0xfffffffe;

	// increase size
	sdata->queueLength++;
}
#endif
