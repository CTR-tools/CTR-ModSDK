#include <common.h>

void DECOMP_MainStats_ClearBattleVS(void)

{
  int iVar1;
  int iVar3 = 0;
    
  // loop for 4 players
  for (int iVar4 = 0; iVar4 < 4; iVar4++)
  {
    iVar1 = iVar3;
    // loop for 3 positions (1st, 2nd, 3rd)
    for (int iVar2 = 0; iVar2 < 3; iVar2++)
    {
        sdata->gGT->standingsPoints[iVar1] = 0;
        iVar1 = iVar1 + 4;
    }
    iVar3 += 0xc;
  }
return;
}
