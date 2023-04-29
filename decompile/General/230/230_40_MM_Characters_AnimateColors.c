#include <common.h>

void DECOMP_MM_Characters_AnimateColors(unsigned char *colorData, short playerID, short flag)
{
  unsigned char bVar1;
  unsigned int uVar3;
  unsigned int iVar4;
  
  // access int RGBA as a char array,
  // for editing components of color
  unsigned char* ptrColor;
  ptrColor = (unsigned char*)data.ptrColor[playerID + PLAYER_BLUE];

  iVar4 = 0;

  if (flag == 0) {
    uVar3 = sdata->frameCounter * 0x100 + playerID * 0x400;

    // approximate trigonometry
    iVar4 = data.trigApprox[uVar3 & 0x3ff];

    if ((uVar3 & 0x400) == 0) {
      iVar4 = iVar4 << 0x10;
    }
    iVar4 = iVar4 >> 0x10;

    if ((uVar3 & 0x800) != 0)
      iVar4 = -(int)iVar4;
  }

  bVar1 = 0;
  if (0xc00 < (int)iVar4) {
    bVar1 = ((iVar4 << 7) >> 0xc);
  }
  
  colorData[0] = ptrColor[0] | bVar1;
  colorData[1] = ptrColor[1] | bVar1;
  colorData[2] = ptrColor[2] | bVar1;
  colorData[3] = 0;
  
  return;
}