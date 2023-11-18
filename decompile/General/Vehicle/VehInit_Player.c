#include <common.h>

void VehPtr_Driving_Init();

struct Driver* DECOMP_VehInit_Player(int index)
{
	struct Thread* t =
		THREAD_BirthWithObject(0x62c0100, 0, 0, 0);
		
	struct Driver* d = t->object;
	memset(d, 0, 0x62c);
	
	VehInit_NonGhost(d, index);
	
	d->funcPtrs[0] = VehPtr_Driving_Init;
	
	d->BattleHUD.teamID = 
		sdata->gGT->battleSetup.teamOfEachPlayer[index];

	return d;
}