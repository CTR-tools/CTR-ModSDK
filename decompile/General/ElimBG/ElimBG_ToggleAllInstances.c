#include <common.h>

void DECOMP_ElimBG_ToggleAllInstances(struct GameTracker* gGT, int boolGameIsPaused)
{
	struct Level* lev;
	struct Instance* inst;
	struct InstDef* ptrInstDefs;
	
	lev = gGT->level1;
	
	// Loop through all instances in level
	for (
			ptrInstDefs = &lev->ptrInstDefs[0]; 
			ptrInstDefs < &lev->ptrInstDefs[lev->numInstances]; 
			ptrInstDefs++
		)
	{
		inst = ptrInstDefs->ptrInstance;
		
		if (inst != 0)
			DECOMP_ElimBG_ToggleInstance(inst, boolGameIsPaused);
	}
	
	// Loop through all instances in Instance Pool
	for(
			inst = gGT->JitPools.instance.taken.first;
			inst != 0;
			inst = inst->next
		)
	{
		DECOMP_ElimBG_ToggleInstance(inst, boolGameIsPaused);
	}
}