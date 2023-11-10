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
			ElimBG_ToggleInstance(inst, boolGameIsPaused);
	}
	
	// Loop through all instances in Instance Pool
	inst = LIST_GetFirstItem(&gGT->JitPools.instance.taken);
	
	while(inst != 0)
	{
		ElimBG_ToggleInstance(inst, boolGameIsPaused);
		inst = LIST_GetNextItem(inst);
	}
}