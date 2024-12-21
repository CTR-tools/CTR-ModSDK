#include <common.h>

int DECOMP_LOAD_GetAdvPackIndex()
{
	int levelID = sdata->gGT->levelID;
	
	if ((levelID != GEM_STONE_VALLEY) && (levelID != GLACIER_PARK)) return 1;
	
	return 2;
}