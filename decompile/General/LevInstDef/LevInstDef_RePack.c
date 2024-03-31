#include <common.h>

void DECOMP_LevInstDef_RePack(struct mesh_info* ptr_mesh_info, int boolAdvHub)
{
	int i;
	int numQuadBlock;
	struct QuadBlock* ptrQuadBlockArray;
	struct QuadBlock* qbCurr;
	struct Instance** visInstSrc;
	struct Level* level1;
	struct Thread* th;
	 
	numQuadBlock = ptr_mesh_info->numQuadBlock;
	ptrQuadBlockArray = ptr_mesh_info->ptrQuadBlockArray;
	
	// loop through all quadblocks
	for(i = 0; i < numQuadBlock; i++)
	{
		qbCurr = &ptrQuadBlockArray[i];
		
		if(qbCurr->pvs != 0)
		{
			// loop through all instance pointers visible on quadblock
			for(
					visInstSrc = qbCurr->pvs->visInstSrc; 
					visInstSrc[0] != 0; 
					visInstSrc++
				)
			{
				visInstSrc[0] = visInstSrc[0]->instDef;
			}
		}
	}
	
	level1 = sdata->gGT->level1;
	
	if(level1->numInstances != 0)
	{
		// loop through all instDef pointers in the LEV
		for(
				visInstSrc = level1->ptrInstDefPtrArray; 
				visInstSrc[0] != 0; 
				visInstSrc++
			)
		{
			// if on adv hub
			if(boolAdvHub != 0)
			{
				// kill thread if it exists
				th = visInstSrc[0]->thread;
				if(th != 0) th->flags |= 0x800;
			}
			
			// erase instance in pool
			DECOMP_LIST_AddFront(
				&sdata->gGT->JitPools.instance.free, 
				visInstSrc[0]);
			
			// go back to instDef
			visInstSrc[0] = visInstSrc[0]->instDef;
		}
	}
	
	DECOMP_PROC_CheckAllForDead();
}