#include <common.h>

struct Driver* DECOMP_VehInit_Player(int index)
{
	struct Thread* t =
		DECOMP_THREAD_BirthWithObject(0x62c0100, 0, 0, 0);
		
	struct Driver* d = t->object;
	memset(d, 0, 0x62c);
	
	// My bad, this wasn't safe to relocate -- Niko
	// Patch call to VehPtr_Crashing_Init from COLL
	#ifndef REBUILD_PC
	#define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
	*(int*)0x800214bc = JAL(DECOMP_VehPtr_Crashing_Init);
	#endif
	
	DECOMP_VehInit_NonGhost(t, index);
	
	d->funcPtrs[0] = DECOMP_VehPtr_Driving_Init;
	
	d->BattleHUD.teamID = 
		sdata->gGT->battleSetup.teamOfEachPlayer[index];

	return d;
}