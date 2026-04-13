#include <common.h> 

void DECOMP_RB_Warpball_Start(struct TrackerWeapon* tw)
{
  tw->ptrNodeCurr = RB_Warpball_NewPathNode(tw->ptrNodeCurr,tw->driverTarget);
  tw->ptrNodeNext = RB_Warpball_NewPathNode(tw->ptrNodeCurr,tw->driverTarget);
  return;
}
 