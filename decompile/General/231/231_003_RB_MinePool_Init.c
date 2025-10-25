#include <common.h>

void DECOMP_RB_MinePool_Init(void)
{
	int i;
	int numMines;
	unsigned int addr;
	unsigned int gameMode;

	DECOMP_LIST_Clear(&D231.minePoolTaken);
	DECOMP_LIST_Clear(&D231.minePoolFree);
	
	gameMode = sdata->gGT->gameMode1;
	
	// default
	numMines = 10;
	
	if ((gameMode & CRYSTAL_CHALLENGE) != 0)
	{
		// naughty dog bug, should be 50,
		// this caused nitro court challenge bug
		numMines = 40;
	}
	
	// boss race
	if ((gameMode & ADVENTURE_BOSS) != 0)
	{
		if (sdata->gGT->levelID == DRAGON_MINES) numMines = 3;
		if (sdata->gGT->levelID == ROO_TUBES) numMines = 7;
	}
		
	// add all mines
	for(i = 0; i < numMines; i++)
	{
		DECOMP_LIST_AddFront(&D231.minePoolFree, (struct Item*)&D231.minePoolItem[i]);
	}
}