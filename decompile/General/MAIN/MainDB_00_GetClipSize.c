#include <common.h>

// Debug clip space
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
void RunHook226();

static char clipSizeArr[20] =
{
	// from Discord testers, plus padding,
	// multiply all these numbers by 100
	
	25,	// DINGO_CANYON
	28,	// DRAGON_MINES
	25,	// BLIZZARD_BLUFF
	20,	// CRASH_COVE
	20,	// TIGER_TEMPLE
	18,	// PAPU_PYRAMID
	25,	// ROO_TUBES
	20,	// HOT_AIR_SKYWAY
	25,	// SEWER_SPEEDWAY
	24,	// MYSTERY_CAVES
	25,	// CORTEX_CASTLE
	30,	// N_GIN_LABS
	22,	// POLAR_PASS
	20,	// OXIDE_STATION
	16,	// COCO_PARK
	20,	// TINY_ARENA
	28,	// SLIDE_COLISEUM
	28,	// TURBO_TRACK

	// padding
	0, 0
};

int DECOMP_MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{
#if 0
    // jal 800aa790 (can breakpoint to see regs)
	if (*(int*)0x800a0eac == 0xC02A9e4)
		*(int*)0x800a0eac = JAL(RunHook226);
#endif
	
	if(levelID == OXIDE_STATION)
		if (numPlyrCurrGame > 2)
			return 1200;

	if (levelID >= CREDITS_CRASH) 		return 1;		// 44 - 64
	if (levelID >= OXIDE_ENDING)		return 2700;	// 42, 43
	if (levelID == NAUGHTY_DOG_CRATE)	return 1;		// 41
	if (levelID == ADVENTURE_GARAGE)	return 4500; 	// 40
	if (levelID == MAIN_MENU_LEVEL) 	return 1; 		// 39
	if (levelID >= INTRO_RACE_TODAY)	return 2800;	// 30-38
	if (levelID >= GEM_STONE_VALLEY)	return 2750;	// 25-29
	if (levelID >= NITRO_COURT)			return 2400;	// 18-24
	
	// 0 - 17
	return (int)clipSizeArr[levelID] * 100;
}

#if 0
void RunHook226()
{
	// ra = 0x8000c000;
	asm("lui $ra, 0x8000");
	asm("ori $ra, $ra, 0xc000");
	
	// Save start(s7) and end(t8)
	asm("sw $s7, 0x0($ra)");
	asm("sw $t8, 0x4($ra)");
	asm("nop");
	
	// ra = 0x800a0eb4;
	asm("lui $ra, 0x800a");
	asm("ori $ra, $ra, 0xeb4");
	
	asm("j 0x800aa790");
	asm("nop");
}
#endif