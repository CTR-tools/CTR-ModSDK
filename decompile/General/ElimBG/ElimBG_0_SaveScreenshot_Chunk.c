#include <common.h>

void DECOMP_ElimBG_SaveScreenshot_Chunk(u_short *param_1, u_short *param_2, int param_3)
{
  u_short uVar1;
  u_short* puVar2;

  if (param_3 == 0) return;

  puVar2 = param_2 + 3;
  
  for(; param_3 > 0; param_3 -= 4, param_2 += 4, puVar2 += 4, param_1++) {
    uVar1 = (u_short)((param_2[0] & 0x3e0) >> 6);
    uVar1 |= puVar2[-2] >> 2 & 0xf0;
    uVar1 |= (u_short)((puVar2[-1] & 0x3c0) << 2);
    uVar1 |= (u_short)((*puVar2 & 0x3c0) << 6);
    *param_1 = uVar1;
  };
}