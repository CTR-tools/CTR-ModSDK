#include <common.h>

struct Driver* DECOMP_VehBirth_Player(int index)
{
	struct Thread* t =
		DECOMP_PROC_BirthWithObject(0x62c0100, 0, 0, 0);
		
	struct Driver* d = t->object;
	memset(d, 0, 0x62c);
		
	DECOMP_VehBirth_NonGhost(t, index);
	
	d->funcPtrs[0] = DECOMP_VehPhysProc_Driving_Init;
	
	d->BattleHUD.teamID = 
		sdata->gGT->battleSetup.teamOfEachPlayer[index];

	return d;
}