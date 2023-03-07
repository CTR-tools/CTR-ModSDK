#include <common.h>

u_int MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{
	if(levelID == PAPU_PYRAMID || levelID == POLAR_PASS)
		if (2 < numPlyrCurrGame)
			return 2500;
		
	if(levelID == SEWER_SPEEDWAY) return 6000;
	if(levelID == MYSTERY_CAVES) return 2500;
	if(levelID == MAIN_MENU) return 0x10;
	if(levelID == ADVENTURE_CHARACTER_SELECT) return 24000;

	return 3000;
}