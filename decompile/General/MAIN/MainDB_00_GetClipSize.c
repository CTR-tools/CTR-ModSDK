#include <common.h>

// Debug clip space
#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
void RunHook226();

int DECOMP_MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{
#if 0
    // jal 800aa790 (can breakpoint to see regs)
	if (*(int*)0x800a0eac == 0xC02A9e4)
		*(int*)0x800a0eac = JAL(RunHook226);
#endif
	
	// Take a risk for levels that
	// are very low on free RAM
	if (numPlyrCurrGame > 2)
	{
		if(levelID == PAPU_PYRAMID || levelID == POLAR_PASS)
			return 2500;
		
		// New to our decomp
		// Increase later when we save more heap
		if(levelID == OXIDE_STATION)
			return 1200;
	}
	
	if(levelID == SEWER_SPEEDWAY) 	return 1500;	// down from 6000
	if(levelID == MYSTERY_CAVES) 	return 2500;	// same
	if(levelID == MAIN_MENU_LEVEL) 	return 1; 		// down from 16
	if(levelID == ADVENTURE_GARAGE)	return 6000; 	// down from 24000

	return 3000;
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