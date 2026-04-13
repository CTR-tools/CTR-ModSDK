#include <common.h>
void DECOMP_MM_Characters_AnimateColors(unsigned char *colorData, short playerID, short flag)
{
  u_char colorAdjustmentValue;
  u_int trigApproximationIndex;
  u_int trigApprox;

  // access int RGBA as a char array,
  // for editing components of color
  u_char* ptrColor;
  ptrColor = (u_char*)data.ptrColor[playerID + PLAYER_BLUE];

  trigApprox = 0;

  // if player has not selected character yet
  // see MM_Characters_MenuProc
  if (flag == 0) {
    trigApproximationIndex = FPS_HALF(sdata->frameCounter) * 0x100 + playerID * 0x400;

    // approximate trigonometry
    trigApprox = *(u_int*)&data.trigApprox[trigApproximationIndex & 0x3ff];

    if ((trigApproximationIndex & 0x400) == 0) {
      trigApprox = trigApprox << 0x10;
    }
    trigApprox = trigApprox >> 0x10;

    if ((trigApproximationIndex & 0x800) != 0)
      trigApprox = -(int)trigApprox;
  }

  colorAdjustmentValue = 0;
  if (0xc00 < (int)trigApprox) {
    colorAdjustmentValue = ((trigApprox << 7) >> 0xc);
  }

  colorData[0] = ptrColor[0] | colorAdjustmentValue;
  colorData[1] = ptrColor[1] | colorAdjustmentValue;
  colorData[2] = ptrColor[2] | colorAdjustmentValue;
  colorData[3] = 0;

  return;
}