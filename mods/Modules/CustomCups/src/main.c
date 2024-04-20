#include <common.h>

#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
#define J(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define StoreLong(dest, val) (*(unsigned long *)(dest) = (unsigned long)(val))
#define ADDR_230 0x800AB9F0

void RECTMENU_DrawInnerRect(RECT *r, int flag, u_long *ot);
int Timer_GetTime_Total();
void MM_JumpTo_Scrapbook();

struct CustomCup
{
	char choiceX[4][4];

	char choiceY;
	char boolOpen;
	char modifiedCup;

	void *(*funcPtr)(int *);
};

register struct CustomCup *cc asm("k1");

RECT windowSel[4] = 
{
	[0] = {0x100, 0x25, 0xE0, 0x4E},	// top right
	[1] = {0x20, 0x25, 0xE0, 0x4E},		// top left
	[2] = {0x100, 0x79, 0xE0, 0x4E},	// bottom right
	[3] = {0x20, 0x79, 0xE0, 0x4E}		// bottom left
};

RECT windowText = {0x40, 0, 0x180, 0x50};

// base address of Single menu data,
// this is an awful method, I'll fix it later

// sep3
#if BUILD == SepReview
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xCB0) // 0x800b341c
#define SIN_SIZE 16
#define ICON_OFFSET 2

// usa retail
#elif BUILD == UsaRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xF08) // 0x800b53b0
#define SIN_SIZE 16
#define ICON_OFFSET 2
#define CUP_SELECT *(char *)(0x800b4746)

// store trial
#elif BUILD == JpnTrial
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0x14A4) // 0x800b4e40
#define SIN_SIZE 20
#define ICON_OFFSET 4

// europe
#elif BUILD == EurRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0xF88) // 0x800b5b8c
#define SIN_SIZE 20
#define ICON_OFFSET 4
#define CUP_SELECT *(char *)(0x800b4f1e)

// japan retail
#elif BUILD == JpnRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0x14cc) // 0x800b93ec
#define SIN_SIZE 20
#define ICON_OFFSET 4
#define CUP_SELECT *(char *)(0x800b81ca)

#else
#error HookCups needs a macro for addresses
#endif

// Transfer data from Single(SIN) menu to Cup(CUP) menu
#define CUP_TRACK(i, cup) data.ArcadeCups[cup].CupTrack[i].trackID
#define SIN_TRACK(i, cup) *(char *)(SIN_ADDR + SIN_SIZE * cc->choiceX[cup][i] + 0)
#define CUP_ICON(i, cup) data.ArcadeCups[cup].CupTrack[i].iconID
#define SIN_ICON(i, cup) *(char *)(SIN_ADDR + SIN_SIZE * cc->choiceX[cup][i] + ICON_OFFSET)

static char Repeat(int numTracksSet, int currTrack, int cupIndex)
{
	int i;

	// check if track is taken
	// previously (<)
	// or by self (=)
	for (i = 0; i <= numTracksSet; i++)
		if (cc->choiceX[cupIndex][i] == currTrack)
			return 1;

	return 0;
}

void HookCups(int *param_1)
{
	int i;
	unsigned int buttonTap;
	int id;

	DecalFont_DrawLine(
		"PRESS SELECT FOR CUSTOM CUPS",
		0x100,
		0x4,
		FONT_SMALL,
		(JUSTIFY_CENTER | ORANGE));

	buttonTap = sdata->gGamepads->gamepad[0].buttonsTapped;

	if (buttonTap & BTN_SELECT)
	{
		cc->boolOpen = !cc->boolOpen;
		cc->modifiedCup = CUP_SELECT;
		cc->choiceY = 0;
	}

	if (cc->boolOpen)
	{
		CUP_SELECT = cc->modifiedCup;

		if (buttonTap & BTN_UP) cc->choiceY--;
		if (buttonTap & BTN_DOWN) cc->choiceY++;
		cc->choiceY &= 3;
		
		if (buttonTap & BTN_LEFT)
			cc->choiceX[cc->modifiedCup][cc->choiceY]--;
		if (buttonTap & BTN_RIGHT)
			cc->choiceX[cc->modifiedCup][cc->choiceY]++;

		// pressing Left on Crash Cove goes to Turbo Track,
		// pressing Right on Turbo Track goes to Crash Cove
		if (cc->choiceX[cc->modifiedCup][cc->choiceY] < 0)
			cc->choiceX[cc->modifiedCup][cc->choiceY] = 17;
		else
			cc->choiceX[cc->modifiedCup][cc->choiceY] = 
			cc->choiceX[cc->modifiedCup][cc->choiceY] % 18;

		if ((buttonTap & BTN_R1) != 0)
		{
			i = 0;

			while (i < 4)
			{
				// random
				MixRNG_Scramble();

				id = (
						 // system clock
						 (Timer_GetTime_Total() & 0xf)

						 +

						 // from RNG
						 (sdata->randomNumber >> 8)

							 ) %
					 18; // 18 tracks

				// avoid repeats
				if (Repeat(i, id, cc->modifiedCup))
					continue;

				// set value
				cc->choiceX[cc->modifiedCup][i] = id;
				i++;
			}
		}

		// Draw arrow
		DecalFont_DrawLine(
			"-\0",
			(cc->modifiedCup == 0 || cc->modifiedCup == 2) ? 0x108 : 0x28,
			((cc->modifiedCup == 0 || cc->modifiedCup == 1) ? 0x30 : 0x84) + 0x10 * cc->choiceY,
			FONT_SMALL,
			ORANGE);

		// set values of all cups
		for (i = 0; i < 4; i++)
		{
			// Set trackID
			CUP_TRACK(i, cc->modifiedCup) = SIN_TRACK(i, cc->modifiedCup);

			// set iconID
			CUP_ICON(i, cc->modifiedCup) = SIN_ICON(i, cc->modifiedCup);

			// Draw name of track
			DecalFont_DrawLine(
				sdata->lngStrings[CUP_TRACK(i, cc->modifiedCup) + 0x6e],
				(cc->modifiedCup == 0 || cc->modifiedCup == 2) ? 0x118 : 0x38,
				((cc->modifiedCup == 0 || cc->modifiedCup == 1) ? 0x30 : 0x84) + 0x10 * i,
				FONT_SMALL,
				ORANGE);
		}

		windowText.y = 0x25;
		if(cc->modifiedCup < 2)
			windowText.y = 0x79;

		DecalFont_DrawLine(
			"USE D-PAD TO CUSTOMIZE CUP",
			0x100,
			windowText.y + 0x18,
			FONT_SMALL,
			(JUSTIFY_CENTER | PERIWINKLE));

		DecalFont_DrawLine(
			"PRESS R1 TO RANDOMOMIZE",
			0x100,
			windowText.y + 0x30,
			FONT_SMALL,
			(JUSTIFY_CENTER | PERIWINKLE));

		struct DB *backBuffer = 
			sdata->gGT->backBuffer;

		RECTMENU_DrawInnerRect(
			&windowSel[cc->modifiedCup], 1, 
			backBuffer->otMem.startPlusFour);

		RECTMENU_DrawInnerRect(
			&windowText, 1, 
			backBuffer->otMem.startPlusFour);
	}

	// things drawn last are put underneath
	// earlier things, so now draw original cup menu
	cc->funcPtr(param_1);
}

void RunInitHook()
{
	cc = (struct CustomCup *)0x8000FFE0;

	// each choice is 0-18
	// Start with default tracks
	cc->choiceX[0][0] = 0;
	cc->choiceX[0][1] = 2;
	cc->choiceX[0][2] = 5;
	cc->choiceX[0][3] = 3;
	cc->choiceX[1][0] = 1;
	cc->choiceX[1][1] = 7;
	cc->choiceX[1][2] = 9;
	cc->choiceX[1][3] = 6;
	cc->choiceX[2][0] = 4;
	cc->choiceX[2][1] = 8;
	cc->choiceX[2][2] = 11;
	cc->choiceX[2][3] = 12;
	cc->choiceX[3][0] = 10;
	cc->choiceX[3][1] = 14;
	cc->choiceX[3][2] = 13;
	cc->choiceX[3][3] = 16;

	cc->choiceY = 0;
	cc->boolOpen = 0;
	cc->modifiedCup = 0;
}

void RunHook_Callback230()
{
	// cups menu
	struct RectMenu* menu = (struct RectMenu *)(MM_JumpTo_Scrapbook +

#if BUILD == SepReview
	0x2C4
#elif BUILD == UsaRetail
	0x284
#elif BUILD == JpnTrial
	0x270
#elif BUILD == EurRetail
	0x300
#elif BUILD == JpnRetail
	0x290
#else
#error RunHook_Callback230 needs a macro for Menu
#endif

	);

	// For now, this works without throwing off recompilers,
	// replace with a JMP hook when proper overlay file injection works
	cc->funcPtr = (void *)menu->funcPtr;
	menu->funcPtr = (void *)HookCups;

	return;
}
