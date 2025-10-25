#include <common.h>

void DECOMP_RB_MinePool_Init(void)
{
	int i;
	int numMines;
	unsigned int addr;
	struct GameTracker* gGT;
	
	gGT = sdata->gGT; 

	DECOMP_LIST_Clear(&D231.minePoolTaken);
	DECOMP_LIST_Clear(&D231.minePoolFree);
	
	
	// default
	numMines = 10;
	
	if ((gGT->gameMode1 & CRYSTAL_CHALLENGE) != 0)
	{
		// naughty dog bug, should be 50,
		// this caused nitro court challenge bug
		numMines = 40;
	}
	
	// boss race
	if ((gGT->gameMode1 & ADVENTURE_BOSS) != 0)
	{
		if (gGT->levelID == DRAGON_MINES) numMines = 3;
		if (gGT->levelID == ROO_TUBES) numMines = 7;
	}
		
	// add all mines
	for(i = 0; i < numMines; i++)
	{
		DECOMP_LIST_AddFront(&D231.minePoolFree, (struct Item*)&D231.minePoolItem[i]);
	}
	
	return;
}