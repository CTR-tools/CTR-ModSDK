#include <common.h>

#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
#define J(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0x8000000)
#define StoreLong(dest, val) (*(unsigned long*)(dest) = (unsigned long)(val))
#define ADDR_230 0x800AB9F0

void DrawTextBackground(RECT* r, int unk, void* ot);
void DecalFont_DrawLine(char*, int, int, int, int);
void RNG_Scramble();
int RCNT_GetTime_Total();
void MM_JumpTo_Scrapbook();

struct CustomCup
{
	char choiceX[4];

	char choiceY;
	char boolOpen;
	char padding[2];

	void *(*funcPtr)(int *);
};

register struct CustomCup* cc asm("k1");

//RECT window1 = {0x100, 37, 0xE0, 0xAC};
//RECT window2 = {0x40, 0x75, 0xC0, 0x5C};

// window with track names
RECT window1 = {0x100, 37, 0xE0, 0x4E};

// window with directions
RECT window2 = {0x20, 0x75, 0x1C0, 0x5C};

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

// japan retail
#elif BUILD == JpnRetail
#define SIN_ADDR (MM_JumpTo_Scrapbook + 0x14cc) // 0x800b93ec
#define SIN_SIZE 20
#define ICON_OFFSET 4

#else
#error HookCups needs a macro for addresses
#endif

// Transfer data from Single(SIN) menu to Cup(CUP) menu
#define CUP_TRACK(i) data.ArcadeCups[0].CupTrack[i].trackID
#define SIN_TRACK(i) *(char*)(SIN_ADDR + SIN_SIZE*cc->choiceX[i] + 0)
#define CUP_ICON(i) data.ArcadeCups[0].CupTrack[i].iconID
#define SIN_ICON(i) *(char*)(SIN_ADDR + SIN_SIZE*cc->choiceX[i] + ICON_OFFSET)

static char Repeat(int numTracksSet, int currTrack)
{
	int i;

	// check if track is taken
	// previously (<)
	// or by self (=)
	for(i = 0; i <= numTracksSet; i++)
		if(cc->choiceX[i] == currTrack)
			return 1;

	return 0;
}

void HookCups(int* param_1)
{
	int i;
	unsigned int buttonTap;
	int id;

    DecalFont_DrawLine("PRESS SELECT FOR CUSTOM CUPS",
                 0x100,
                 0x4,
				 2,0xffff8000);

	buttonTap = sdata.gamepadSystem.controller[0].buttonsTapped;

	if(buttonTap & BTN_SELECT) cc->boolOpen = !cc->boolOpen;

	if(cc->boolOpen)
	{
		if(buttonTap & BTN_UP) cc->choiceY--;
		if(buttonTap & BTN_DOWN) cc->choiceY++;

		if(cc->choiceY < 0) cc->choiceY = 0;
		else if(cc->choiceY > 3) cc->choiceY = 3;

		if(buttonTap & BTN_LEFT) cc->choiceX[cc->choiceY]--;
		if(buttonTap & BTN_RIGHT) cc->choiceX[cc->choiceY]++;

		// pressing Left on Crash Cove goes to Turbo Track,
		// pressing Right on Turbo Track goes to Crash Cove
		if(cc->choiceX[cc->choiceY] < 0) cc->choiceX[cc->choiceY] = 17;
		else cc->choiceX[cc->choiceY] = cc->choiceX[cc->choiceY] % 18;

		if((buttonTap & BTN_R1) != 0)
		{
			i = 0;

			while(i < 4)
			{
				// random
				RNG_Scramble();

				id = (
						// system clock
						(RCNT_GetTime_Total() & 0xf )

						+

						// from RNG
						(sdata.randomNumber >> 8)

					  ) % 18; // 18 tracks

				// avoid repeats
				if(Repeat(i, id)) continue;

				// set value
				cc->choiceX[i] = id;
				i++;
			}
		}

		// Draw arrow
		DecalFont_DrawLine("-\0",
			0x108,
			0x30 + 0x10*cc->choiceY,
			2,
			0);

		// set values of all cups
		for(i = 0; i < 4; i++)
		{
			// Set trackID
			CUP_TRACK(i) = SIN_TRACK(i);

			// set iconID
			CUP_ICON(i) = SIN_ICON(i);

			// Draw name of track
			DecalFont_DrawLine(sdata.lngStrings[CUP_TRACK(i) + 0x6e],
				0x118,
				0x30 + 0x10*i,
				2,
				0);
		}

		DecalFont_DrawLine("USE D-PAD TO CUSTOMIZE WUMPA CUP",
                 0x100,
                 0x88,
				 2,0xffff8001);

		DecalFont_DrawLine("PRESS R1 TO RANDOMOMIZE",
                 0x100,
                 0xA0,
				 2,0xffff8001);

		DecalFont_DrawLine("THEN PRESS SELECT AND PICK WUMPA",
                 0x100,
                 0xB8,
				 2,0xffff8001);

		// Draw background box ========================
		DrawTextBackground(&window1,1,sdata.gGT->backBuffer->otMem.startPlusFour);
		DrawTextBackground(&window2,1,sdata.gGT->backBuffer->otMem.startPlusFour);
	}

	// things drawn last are put underneath
	// earlier things, so now draw original cup menu
	cc->funcPtr(param_1);
}

void RunInitHook()
{
	cc = (struct CustomCup*)0x8000FFE0;

	// each choice is 0-18
	// Start with default tracks
	cc->choiceX[0] = 0;
	cc->choiceX[1] = 2;
	cc->choiceX[2] = 5;
	cc->choiceX[3] = 3;

	cc->choiceY = 0;
	cc->boolOpen = 0;
}

void RunHook_Callback230()
{
	// cups menuBox
	struct MenuBox* mb = (struct MenuBox*)(MM_JumpTo_Scrapbook +

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
		#error RunHook_Callback230 needs a macro for MenuBox
		#endif

	);

	// For now, this works without throwing off recompilers,
	// replace with a JMP hook when proper overlay file injection works
	cc->funcPtr = (void*)mb->funcPtr;
	mb->funcPtr = (void*)HookCups;

	return;
}