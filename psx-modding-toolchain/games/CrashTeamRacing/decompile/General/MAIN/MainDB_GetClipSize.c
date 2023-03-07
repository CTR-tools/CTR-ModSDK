#include <common.h>

u_int MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{
	if(levelID == 5 || levelID == 0xC)
		if (2 < numPlyrCurrGame)
				return 2500;
		
	if(levelID == 8) return 6000;
	if(levelID == 9) return 2500;
	if(levelID == 0x27) return 0x10;
	if(levelID == 0x28) return 24000;

	return 3000;
}