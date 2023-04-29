#include <common.h>

void DECOMP_RB_Warpball_SeekDriver(struct TrackerWeapon* tw,unsigned int param_2,struct Driver* d)
{
  int iVar1;

  if (
		// if driver is valid
		(d != NULL) && 
		
		// if path node index is valid
		((param_2 & 0xff) != 0xff)
	  ) 
  {
	// pointer to path node
    iVar1 = sdata->gGT->level1->ptr_restart_points[param_2 & 0xff];
    
	while (
			// driver distanceToFinish < pathNode -> distanceToFinish
			(d->distanceToFinish_curr <= (int)((unsigned int)*(unsigned short *)(iVar1 + 6) << 3) &&
           
			// node is not first node
			(iVar1 != sdata->gGT->level1->ptr_restart_points[0])
			)
		   ) 
	{
      iVar1 = RB_Warpball_NewPathNode(iVar1,tw->driverTarget);
    }
	
	// path index = pathPtr2 - pathPtr1
    *(char *)(tw + 0x11) = (char)((iVar1 - sdata->gGT->level1->ptr_restart_points[0]) * -0x55555555 >> 2);
  }
  return;
}
 