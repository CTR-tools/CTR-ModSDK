#include <common.h>

// all buttons fit in one byte
// except triangle, which overrides

#define LETTER_N (BTN_UP    & 0xff)
#define LETTER_U (BTN_UP    & 0xff)
#define LETTER_S (BTN_DOWN  & 0xff)
#define LETTER_D (BTN_DOWN  & 0xff)
#define LETTER_W (BTN_LEFT  & 0xff)
#define LETTER_L (BTN_LEFT  & 0xff)
#define LETTER_E (BTN_RIGHT & 0xff)
#define LETTER_R (BTN_RIGHT & 0xff)

#define LETTER_A 0x80 // BTN_TRIANGLE overrides to 0x80
#define LETTER_O (BTN_CIRCLE & 0xff)
#define LETTER_X (BTN_CROSS  & 0xff)

void MainKillGame_LaunchSpyro2();

struct Cheat
{
	// 0x0
	int length;
	
	// 0x4, 0x8, 0xC
	char buttons[12];
	
	// 0x10
	int* writeAddr;
	
	// 0x14
	int addBits;
	
	// 0x18 - size
};

struct Cheat cheats[22] =
{
	// Spyro2 - "soar"
	{
		.length = 4,
		.buttons =
		{
			LETTER_S,
			LETTER_O,
			LETTER_A,
			LETTER_R,
			0,0,0,0,0,0
		},
		
		.writeAddr = 0,
		.addBits = 0,
	},
	
	// MaxWumpa - "seeds"
	{
		.length = 5,
		.buttons = 
		{
			LETTER_S,
			LETTER_E,
			LETTER_E,
			LETTER_D,
			LETTER_S,
			0,0,0,0,0
		},
				
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x200,
	},
	
	// UnlockRoo - "roodude"
	{
		.length = 7,
		.buttons = 
		{
			LETTER_R,
			LETTER_O,
			LETTER_O,
			LETTER_D,
			LETTER_U,
			LETTER_D,
			LETTER_E,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x80,
	},
	
	// UnlockPapu - "lardrolls"
	{
		.length = 9,
		.buttons =
		{
			LETTER_L,
			LETTER_A,
			LETTER_R,
			LETTER_D,
			LETTER_R,
			LETTER_O,
			LETTER_L,
			LETTER_L,
			LETTER_S,
			0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x100,
	},
	
	// UnlockJoe - "dollars"
	{
		.length = 7,
		.buttons = 
		{
			LETTER_D,
			LETTER_O,
			LETTER_L,
			LETTER_L,
			LETTER_A,
			LETTER_R,
			LETTER_S,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x200,
	},
	
	// UnlockPinstripe - "leaded"
	{
		.length = 6,
		.buttons =
		{
			LETTER_L,
			LETTER_E,
			LETTER_A,
			LETTER_D,
			LETTER_E,
			LETTER_D,
			0,0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x400,
	},
	
	// UnlockFakeCrash - "oddnoodle"
	{
		.length = 9,
		.buttons = 
		{
			LETTER_O,
			LETTER_D,
			LETTER_D,
			LETTER_N,
			LETTER_O,
			LETTER_O,
			LETTER_D,
			LETTER_L,
			LETTER_E,
			0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x800,
	},
	
	// UnlockPenta - "seaswan"
	{
		.length = 7,
		.buttons =
		{
			LETTER_S,
			LETTER_E,
			LETTER_A,
			LETTER_S,
			LETTER_W,
			LETTER_A,
			LETTER_N,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x40,
	},
	
	// UnlockTropy - "slender"
	{
		.length = 7,
		.buttons =
		{
			LETTER_S,
			LETTER_L,
			LETTER_E,
			LETTER_N,
			LETTER_D,
			LETTER_E,
			LETTER_R,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x20,
	},
	
	// UnlockScrapbook - "underwear"
	{
		.length = 9,
		.buttons =
		{
			LETTER_U,
			LETTER_N,
			LETTER_D,
			LETTER_E,
			LETTER_R,
			LETTER_W,
			LETTER_E,
			LETTER_A,
			LETTER_R,
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[1],
		.addBits = 0x10,
	},
	
	// UnlockTracks - "rewards"
	{
		.length = 7,
		.buttons = 
		{
			LETTER_R,
			LETTER_E,
			LETTER_W,
			LETTER_A,
			LETTER_R,
			LETTER_D,
			LETTER_S,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameProgress.unlocks[0],
		.addBits = 0x1e,
	},
	
	// InfiniteMasks - "warlords"
	{
		.length = 8,
		.buttons = 
		{
			LETTER_W,
			LETTER_A,
			LETTER_R,
			LETTER_L,
			LETTER_O,
			LETTER_R,
			LETTER_D,
			LETTER_S,
			0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x400,
	},
	
	// MaxTurbos - "axelwax"
	{
		.length = 7,
		.buttons =
		{
			LETTER_A,
			LETTER_X,
			LETTER_E,
			LETTER_L,
			LETTER_W,
			LETTER_A,
			LETTER_X,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x800,
	},
	
	// MaxInvisibility - "unseen"
	{
		.length = 7,
		.buttons = 
		{
			LETTER_U,
			LETTER_N,
			LETTER_S,
			LETTER_E,
			LETTER_E,
			LETTER_N,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x8000,
	},
	
	// MaxEngine - "unleaded" (also triggers pinstripe)
	{
		.length = 8,
		.buttons =
		{
			LETTER_U,
			LETTER_N,
			LETTER_L,
			LETTER_E,
			LETTER_A,
			LETTER_D,
			LETTER_E,
			LETTER_D,
			0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x10000,
	},
	
	// MaxBombs - "arsenal"
	{
		.length = 7,
		.buttons =
		{
			LETTER_A,
			LETTER_R,
			LETTER_S,
			LETTER_E,
			LETTER_N,
			LETTER_A,
			LETTER_L,
			0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x400000,
	},
	
	// AdvDifficulty - "endneo"
	{
		.length = 6,
		.buttons =
		{
			LETTER_E,
			LETTER_N,
			LETTER_D,
			LETTER_N,
			LETTER_E,
			LETTER_O,
			0,0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x40000,
	},
	
	// SuperHard - "deluxe"
	{
		.length = 6,
		.buttons =
		{
			LETTER_D,
			LETTER_E,
			LETTER_L,
			LETTER_U,
			LETTER_X,
			LETTER_E,
			0,0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x200000,
	},

	// IcyTracks - "sledroad"
	{
		.length = 8,
		.buttons = 
		{
			LETTER_S,
			LETTER_L,
			LETTER_E,
			LETTER_D,
			LETTER_R,
			LETTER_O,
			LETTER_A,
			LETTER_D,
			0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x80000,
	},
	
	// SuperTurboPads - "arrow"
	{
		.length = 5,
		.buttons =
		{
			LETTER_A,
			LETTER_R,
			LETTER_R,
			LETTER_O,
			LETTER_W,
			0,0,0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x100000,
	},
	
	// OneLap - "suddendead"
	{
		.length = 10,
		.buttons =
		{
			LETTER_S,
			LETTER_U,
			LETTER_D,
			LETTER_D,
			LETTER_E,
			LETTER_N,
			LETTER_D,
			LETTER_E,
			LETTER_A,
			LETTER_D
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x800000,
	},
	
	// TurboCounter - "addon"
	{
		.length = 5,
		.buttons =
		{
			LETTER_A,
			LETTER_D,
			LETTER_D,
			LETTER_O,
			LETTER_N,
			0,0,0,0,0
		},
		
		.writeAddr = &sdata_static.gameTracker.gameMode2,
		.addBits = 0x8000000,
	}
};

char inputButtons[12] = {0,0,0,0,0,0,0,0,0,0};

void DECOMP_MM_ParseCheatCodes()
{
	int i;
	int j;
	int tap;
	int boolPass;
	struct Cheat* cheat;
	struct GamepadBuffer* gpad;
	
	// there's extra room in here, 
	// so store this code here
	#if 1
	char* info = "Date/Time in CheatCodes.c";
	DecalFont_DrawLine(info, 		5, 197, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(__DATE__, 	5, 206, FONT_SMALL, ORANGE);
	DecalFont_DrawLine(__TIME__, 	170, 206, FONT_SMALL, ORANGE);
	DecalFont_DrawLine("30%", 		285, 206, FONT_SMALL, ORANGE);
	#endif
	
	#if 0
	DecalFont_DrawLine("No DotLights", 	325, 197, FONT_SMALL, RED);
	DecalFont_DrawLine("No RenderFrame",325, 206, FONT_SMALL, RED);
	#endif
	
	gpad = &sdata->gGamepads->gamepad[0];
	
	// if not holding L1 and R1
	if(
			gpad->buttonsHeldCurrFrame & (BTN_L1|BTN_R1) 
			!= 
			(BTN_L1|BTN_R1)
		) 
	{
		// skip function
		return;
	}
	
	tap = gpad->buttonsTapped;
	
	if(tap == 0) return;
	
	// at this point, must be holding L1 and R1,
	// and also must have tapped a buttons
	
	// shift the loop
	for(i = 9; i > 0; i--)
	{
		inputButtons[i] = inputButtons[i-1];
	}
	
	// override triangle to 0x80, for byte optimization
	if(tap & BTN_TRIANGLE) tap |= 0x80;
	
	// add to input
	inputButtons[0] = tap & 0xff;
	
	// loop through all cheats
	for(cheat = &cheats[0]; cheat < &cheats[22]; cheat++)
	{
		boolPass = 1;
		
		// check if buttons match this cheat
		for(i = 0; i < cheat->length; i++)
		{
			// remember, inputButtons is backward
			if(cheat->buttons[i] != inputButtons[cheat->length-i-1])
			{
				boolPass = 0;
				break;
			}
		}
		
		// skip to next cheat if needed
		if(!boolPass) continue;
		
		// if spyro 2 cheat
		if(cheat == &cheats[0])
		{
			MainKillGame_LaunchSpyro2();
			
			return;
		}
		
		// if not spyro 2 cheat...
		
		// play cheat sound
		OtherFX_Play(0x67, 1);
		
		// apply cheat
		*cheat->writeAddr |= cheat->addBits;
		
		// do NOT quit loop,
		// pinstripe and max engine overlap in cheat
	}
		
	return;
}