#include <common.h>

#ifndef REBUILD_PC

#define JMP(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)

#ifdef USE_60FPS

int BoolCheckExhaust(struct Driver* d)
{
	// 30fps PASS conditions:
	// 	humans:
	// 		1P:   every frame
	// 		2P:   driverID == gGT->timer&1
	// 		3P4P: driverID == gGT->timer&3
	//	bots:
	//		driverID&3 == gGT->timer&3

	// 60fps FAIL conditions:
	//	humans:
	//		1P:   gGT->timer&1
	//		2P:   gGT->timer&2
	//		3P4P: gGT->timer&4
	//	bots:
	//		gGT->timer&4

	struct GameTracker* gGT = sdata->gGT;
	int numPlyr = gGT->numPlyrCurrGame;
	int timer = gGT->timer;

	// human
	if(d->driverID < numPlyr)
	{
		if(numPlyr == 1)
		{
			if((timer&1) != 0)
				return 0;
		}

		else if(numPlyr == 2)
		{
			if((timer&2) != 0)
				return 0;
		}

		// 3p/4p
		else
		{
			if((timer&4) != 0)
				return 0;
		}
	}

	// AI
	else
	{
		if((timer&4) != 0)
			return 0;
	}

	return 1;
}

// This executes one time, before the
// Crash Team Racing exe boots
void ui60_entryHook()
{
	u_int i;

	// replace call to LIST_RemoveFront inside Particle_Init,
	// this alternative version is stored in Mods7.c
	struct Particle* NewParticleInit(struct LinkedList* param_1);
	*(unsigned int*)0x80040348 = JAL(NewParticleInit);

	// Gravity
	{
		#ifndef USE_ONLINE
		// decrease from 900 to xxx,
		// otherwise Hot Air Skyway C-T-R token is impossible,
		// and some shortcuts are impossible (HAS USF jump to startline)
		for(int i = 0; i < NUM_CLASSES; i++)
			data.metaPhys[0].value[i] = 850;
		#else
		// Online Multiplayer doesnt need C-T-R token letters,
		// make the rest of the game feel more accurate
		for(int i = 0; i < NUM_CLASSES; i++)
			data.metaPhys[0].value[i] = 875;
		#endif
	}

	// SelectProfile flashing orange/red
	// for strings SAVE/LOAD/WARNING
	{
		*(short*)0x8004A5C8 = FPS_DOUBLE(4);
	}

	// Starting line
	{
		// Intro Camera Fly-in
		// Need to fix camera zoom to player

		// these are in FollowDriver_Normal
		*(unsigned short*)0x8001AF6C = 0x14A;
		*(unsigned short*)0x8001AF80 = 0x12D;
		*(unsigned short*)0x8001AF8C = 0x12C;
		*(unsigned short*)0x8001AF90 = 0x12C;
	}

	// AI cooldown
	{
		// nextDriver->weaponCooldown
		*(short*)0x800412ac = FPS_DOUBLE(0xFF);
		*(short*)0x800412b0 = FPS_DOUBLE(0xF0);

		// nextDriver->weaponCooldown (same func, different place)
		*(short*)0x8004149c = FPS_DOUBLE(0xFF);
		*(short*)0x800414a0 = FPS_DOUBLE(0xF0);

		// BOTS_GotoStartingLine cooldown
		*(short*)0x80017144 = FPS_DOUBLE(0xFF);
		*(short*)0x80017148 = FPS_DOUBLE(0x12c);
	}

	// Boss cooldown
	{
		// 8008d8e4 needs to be doubled, after being set

		struct MetaDataBOSS* x;

		for(
				x = &data.BossWeaponOxide[0];
				x < &data.bossWeaponMetaPtr[0];
				x++
			)
		{
			// double min cooldown
			x->weaponCooldown = FPS_DOUBLE(x->weaponCooldown);
		}

		// double & 0x10
		// double + 0xc
		// double <<2 to <<4
		*(unsigned short*)0x80040c24 = FPS_DOUBLE(0x10);
		*(unsigned short*)0x80040c40 = FPS_DOUBLE(0xC);
		*(int*)0x80040c50 = 0x31900;

		// double & 0x10
		// double + 0xc
		// double <<2 to <<4
		*(unsigned short*)0x80040f4c = FPS_DOUBLE(0x10);
		*(unsigned short*)0x80040f68 = FPS_DOUBLE(0xC);
		*(int*)0x80040f78 = 0x31900;
	}

	// Inject new hooks, these are stored in Mods7.c
	void NewCallback231();
	void NewCallback233();
	data.overlayCallbackFuncs[1] = NewCallback231;
	data.overlayCallbackFuncs[3] = NewCallback233;
	return;
}

// USE_60FPS
#endif

// ifndef REBULD_PC
#endif

#ifdef USE_BOOSTBAR
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
#endif