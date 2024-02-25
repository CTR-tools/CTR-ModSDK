#include <common.h>

struct Driver* DECOMP_VehInit_Player(int index)
{
	struct Thread* t =
		DECOMP_THREAD_BirthWithObject(0x62c0100, 0, 0, 0);
		
	struct Driver* d = t->object;
	memset(d, 0, 0x62c);
		
	DECOMP_VehInit_NonGhost(t, index);
	
	d->funcPtrs[0] = DECOMP_VehPtr_Driving_Init;
	
	d->BattleHUD.teamID = 
		sdata->gGT->battleSetup.teamOfEachPlayer[index];

	return d;
}