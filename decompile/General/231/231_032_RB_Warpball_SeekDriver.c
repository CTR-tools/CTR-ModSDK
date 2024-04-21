#include <common.h>

void DECOMP_RB_Warpball_SeekDriver(struct TrackerWeapon* tw,unsigned int param_2,struct Driver* d)
{
  int iVar1;
  
  param_2 &= 0xff;

  if(d == 0) return;
  if(param_2 == 0xff) return;

	struct CheckpointNode* first =
		&sdata->gGT->level1->ptr_restart_points[0];
	  
	// pointer to path node
	struct CheckpointNode* cn =
		&first[param_2];
    
	while (
			(d->distanceToFinish_curr <= (cn->distToFinish << 3)) &&
           
			// node is not first node
			(cn != first)
		   ) 
	{
      cn = RB_Warpball_NewPathNode(cn,tw->driverTarget);
    }
	
	// path index = pathPtr2 - pathPtr1
    tw->nodeCurrIndex = 
		(
			(unsigned int)cn -
			(unsigned int)first
		) / sizeof(struct CheckpointNode);

  return;
}
 