#include <common.h>

int DECOMP_LOAD_GetBigfileIndex(unsigned int levelID, int lod, int fileType)
{
	// === Wow we need a bigfile enum ===

	// race tracks
	if(levelID <= LAB_BASEMENT)
		return 0x0 + levelID*8 + sdata->levBigLodIndex[lod-1] + fileType;
	
	// adv hubs
	if(levelID <= CITADEL_CITY)
		return 0xc8 + (levelID-GEM_STONE_VALLEY)*3 + fileType;
	
	// cutscenes
	if(levelID <= INTRO_OXIDE)
		return 0x203 + (levelID-INTRO_RACE_TODAY)*3 + fileType;
	
	if(levelID <= ADVENTURE_CHARACTER_SELECT)
		return 0xd7 + (levelID-MAIN_MENU_LEVEL)*2 + fileType;
	
	if(levelID == NAUGHTY_DOG_CRATE)
		return 0x201 + fileType;
	
	// oxide endings
	if(levelID <= OXIDE_TRUE_ENDING)
		return 0x21e + (levelID-OXIDE_ENDING)*2 + fileType;
	
	if(levelID <= CREDITS_MEGUMI)
		return 0x222 + (levelID-CREDITS_CRASH)*3 + fileType;
	
	// SCRAPBOOK
	return 0x25e + fileType;
}