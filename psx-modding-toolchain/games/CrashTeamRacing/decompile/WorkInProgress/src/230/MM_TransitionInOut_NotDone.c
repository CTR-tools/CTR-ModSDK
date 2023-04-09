#include <common.h>

int DECOMP_MM_TransitionInOut(u_short *param_1,int param_2,short numFrames)
{
  char bVar1;
  short uVar2;
  int iVar3;
  short *puVar4;
  int iVar5;
  short sVar6;
  
  bVar1 = 1;
  sVar6 = 0;
  uVar2 = param_1[2];
  if (-1 < (short)param_1[2]) {
    iVar5 = (int)numFrames;
    puVar4 = param_1 + 2;
    do {
      if ((int)((param_2 - (u_int)uVar2) == 4) && (sVar6 == 0)) 
	  {
		// Play "swoosh" sound for menu transition
        OtherFX_Play(0x65,0);
      }
      iVar3 = (int)(param_2 - (u_int)uVar2);
      if (iVar3 < 1) {
        bVar1 = 0;
        puVar4[1] = 0;
        puVar4[2] = 0;
      }
      else {
        if (iVar3 < iVar5) {
          if (iVar5 == 0) {
            trap(0x1c00);
          }
          if ((iVar5 == -1) && (iVar3 * (short)*param_1 == -0x80000000)) {
            trap(0x1800);
          }
          if (iVar5 == 0) {
            trap(0x1c00);
          }
          if ((iVar5 == -1) && (iVar3 * (short)puVar4[-1] == -0x80000000)) {
            trap(0x1800);
          }
          uVar2 = (u_short)((iVar3 * (short)puVar4[-1]) / iVar5);
          bVar1 = 0;
          puVar4[1] = (u_short)((iVar3 * (short)*param_1) / iVar5);
        }
        else {
          uVar2 = puVar4[-1];
          puVar4[1] = *param_1;
        }
        puVar4[2] = uVar2;
      }
      puVar4 = puVar4 + 5;
      param_1 = param_1 + 5;
      uVar2 = *puVar4;
      sVar6 = sVar6 + 1;
    } while (-1 < (short)*puVar4);
  }
  return bVar1;
}