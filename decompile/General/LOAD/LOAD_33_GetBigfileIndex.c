#include <common.h>

int DECOMP_LOAD_GetBigfileIndex(unsigned int levelID, int lod)
{
	// === Wow we need a bigfile enum ===

#ifdef USE_HIGHMP
	lod = 1;
#endif

#ifdef USE_REAL60PS1
	lod = 4;
#endif

	if(levelID <= LAB_BASEMENT)
		return BI_ARCADETRACKS + levelID*8 + sdata->levBigLodIndex[lod-1];
	
	// adv hubs
	if(levelID <= CITADEL_CITY)
		return BI_ADVENTUREHUB + (levelID-GEM_STONE_VALLEY)*3;
	
	if(levelID <= INTRO_OXIDE)
		return BI_CUTSCENES_INTRO + (levelID-INTRO_RACE_TODAY)*3;
	
	if(levelID <= ADVENTURE_CHARACTER_SELECT)
		return BI_MAINMENUFILE + (levelID-MAIN_MENU_LEVEL)*2;
	
	if(levelID == NAUGHTY_DOG_CRATE)
		return BI_NDBOX;
	
	if(levelID <= OXIDE_TRUE_ENDING)
		return BI_CUTSCENES_OUTRO + (levelID-OXIDE_ENDING)*2;
	
	if(levelID <= CREDITS_MEGUMI)
		return BI_CREDITS + (levelID-CREDITS_CRASH)*3;
	
	// SCRAPBOOK
	return BI_SCRAPBOOK;
}