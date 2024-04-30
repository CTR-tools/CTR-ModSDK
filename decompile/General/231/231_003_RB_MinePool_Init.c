#include <common.h>

extern struct WeaponSlot231 minePoolItem[40];
extern struct LinkedList minePoolTaken;
extern struct LinkedList minePoolFree;

void DECOMP_RB_MinePool_Init(void)
{
	int i;
	int numMines;
	unsigned int addr;
	int gameMode;
	
	DECOMP_LIST_Clear(&minePoolTaken);
	DECOMP_LIST_Clear(&minePoolFree);
	
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
		DECOMP_LIST_AddFront(
			&minePoolFree, (struct Item*)&minePoolItem[i]);
	}
}