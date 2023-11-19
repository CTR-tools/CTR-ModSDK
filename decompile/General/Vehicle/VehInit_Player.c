#include <common.h>

void VehPtr_Driving_Init();

struct Driver* DECOMP_VehInit_Player(int index)
{
	struct Thread* t =
		DECOMP_THREAD_BirthWithObject(0x62c0100, 0, 0, 0);
		
	struct Driver* d = t->object;
	memset(d, 0, 0x62c);
	
	DECOMP_VehInit_NonGhost(t, index);
	
	#ifndef REBUILD_PS1
	d->funcPtrs[0] = VehPtr_Driving_Init;
	#endif
	
	d->BattleHUD.teamID = 
		sdata->gGT->battleSetup.teamOfEachPlayer[index];

	return d;
}