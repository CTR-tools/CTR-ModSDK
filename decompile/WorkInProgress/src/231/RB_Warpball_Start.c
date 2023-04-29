#include <common.h> 

void DECOMP_RB_Warpball_Start(struct TrackerWeapon* tw)
{
  short* psVar1;
  int iVar2;
  
  iVar2 = 0;
  psVar1 = (short*)((int)tw + 0x3c);
  // There was a loop here that iterates only once for some reason.
  psVar1 = RB_Warpball_NewPathNode(psVar1,tw->driverTarget);
  (short*)((int)tw + 0x3c) = psVar1;
  
  psVar1 = RB_Warpball_NewPathNode(psVar1,tw->driverTarget);
  (short*)((int)tw + 0x40) = psVar1;
  
  return;
}
 