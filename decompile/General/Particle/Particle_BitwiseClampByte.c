#include <common.h>

int DECOMP_Particle_BitwiseClampByte(int *param_1)
{
  int iVar1 = *param_1;

  if (iVar1 < 0) iVar1 = 0;    
  else if (iVar1 > 0xff00) iVar1 = 0xff00;
  
  *param_1 = iVar1;

  // shift down a byte
  return iVar1 >> 8;
}