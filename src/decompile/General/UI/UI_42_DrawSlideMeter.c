#include <common.h>

void DECOMP_UI_DrawSlideMeter(short posX, short posY, struct Driver* driver)
{
	const struct GameTracker * gGT = sdata->gGT;
	#ifdef USE_ONLINE
	const int xOffset = 2;
	const int barWidth = 39;
	int barHeight = 10;
	posX += xOffset;
	#else
	const int barWidth = WIDE_34(49);
	int barHeight = gGT->numPlyrCurrGame > 2 ? 3 : 7;
	#endif

	int meterLength = 0;
	if (driver->turbo_MeterRoomLeft != 0) {
		int currentRoomRemaining = driver->turbo_MeterRoomLeft * barWidth;
		int maxRoom = driver->const_turboMaxRoom * ELAPSED_MS;
		meterLength = barWidth - (currentRoomRemaining / maxRoom);
	}

	RECT box;
	short topX = posX - barWidth;
	short topY = posY - barHeight;
	box.x = topX;
	box.y = topY;
	box.w = barWidth;
	box.h = barHeight;
	DECOMP_CTR_Box_DrawWireBox(&box, MakeColor(0, 0, 0), gGT->pushBuffer_UI.ptrOT);

	#ifdef USE_ONLINE
	if (driver->driverID == 0 && driver->meterGradeTimer > 0)
	{
		driver->meterGradeTimer -= gGT->elapsedTimeMS;
		DECOMP_DecalFont_DrawLine(driver->meterGrade, topX, topY - 8, FONT_SMALL, driver->gradeColor);
	}
	#endif

	const PrimCode primCode = { .poly = { .quad = 1, .renderCode = RenderCode_Polygon } };
	ColorCode colorCode = MakeColorCode(0xFF, 0, 0, primCode); // red color, ready to boost

	if (driver->const_turboLowRoomWarning * ELAPSED_MS < driver->turbo_MeterRoomLeft) {
		colorCode = MakeColorCode(0, 0xFF, 0, primCode); // green color, no boost yet
	}

	for(int i = 0; i < 2; i++)
	{
		PolyF4 * p;
		GetPrimMem(p);
		if (p == nullptr) { return; }

		p->colorCode = colorCode;

		p->v[0].pos.y = topY;
		p->v[1].pos.y = topY;
		p->v[2].pos.y = posY;
		p->v[3].pos.y = posY;

		p->v[0].pos.x = posX - meterLength;
		p->v[1].pos.x = posX;
		p->v[2].pos.x = posX - meterLength;
		p->v[3].pos.x = posX;

		AddPrimitive(p, gGT->pushBuffer_UI.ptrOT);
		colorCode = MakeColorCode(0x80, 0x80, 0x80, primCode); // Gray color for background bar
		meterLength = barWidth;
	}

	#ifdef USE_BOOSTBAR
	void DrawBoostBar(short posX, short posY, struct Driver* driver);
	#ifdef USE_ONLINE
	DrawBoostBar(posX - xOffset, posY + 5, driver);
	#else
	DrawBoostBar(posX, posY + 5, driver);
	#endif
	#endif
}