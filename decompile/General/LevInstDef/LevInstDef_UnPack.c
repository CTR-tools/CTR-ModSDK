#include <common.h>

void DECOMP_LevInstDef_UnPack(struct mesh_info* ptr_mesh_info)
{
	int i;
	int numQuadBlock;
	struct QuadBlock* ptrQuadBlockArray;
	struct QuadBlock* qbCurr;
	struct InstDef** visInstSrc;
	struct Level* level1;
	 
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
				visInstSrc[0] = visInstSrc[0]->ptrInstance;
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
			visInstSrc[0] = visInstSrc[0]->ptrInstance;
		}
	}
}