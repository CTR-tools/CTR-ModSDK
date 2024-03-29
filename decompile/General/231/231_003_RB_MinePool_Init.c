#include <common.h>

// LinkedList, and MinePool data,
// comes between last RB Weapon func (ClosestTracker),
// and first RB Hazard func (Baron_ThTick)

void DECOMP_RB_MinePool_Init(void)
{
	int i;
	int numMines;
	unsigned int addr;
	int gameMode;
	
	// clear taken
	LIST_Clear((struct LinkedList*)0x800b2e9c);
	
	// clear free
	LIST_Clear((struct LinkedList*)0x800b2ea8);
	
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
	
	// empty buffer of 50(dec) * 0xC
	addr = 0x800b2eb4;
	
	// add all mines
	for(i = 0; i < numMines; i++)
	{
		LIST_AddFront((struct LinkedList*)0x800b2ea8, (struct Item*)addr);
		
		addr += 0xC;
	}
}