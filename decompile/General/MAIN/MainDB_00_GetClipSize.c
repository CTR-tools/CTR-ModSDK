#include <common.h>

int DECOMP_MainDB_GetClipSize(u_int levelID, int numPlyrCurrGame)
{

  /*
	Breakpoint 800aa790
	$s7/r23 is pointer to start Clip Buffer (buffer start)
	$t8/r24 is pointer to curr Clip Buffer (last write)
  */
	
	if(levelID == PAPU_PYRAMID || levelID == POLAR_PASS)
		if (2 < numPlyrCurrGame)
			return 2500;
		
	if(levelID == SEWER_SPEEDWAY) return 6000;
	if(levelID == MYSTERY_CAVES) return 2500;
	if(levelID == MAIN_MENU_LEVEL) return 1; // down from 16
	if(levelID == ADVENTURE_CHARACTER_SELECT) return 6000; // down from 24000

	return 3000;
}