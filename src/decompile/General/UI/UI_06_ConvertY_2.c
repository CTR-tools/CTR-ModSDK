#include <common.h>

int DECOMP_UI_ConvertY_2(int oldPosY,int newPosY)
{
  #define midpointY 0x6c
  newPosY = (oldPosY - midpointY) * newPosY;

  // If new posY is under the screen
  if (newPosY < 0) {
    newPosY += 0xff;
  }

  // divide by 256 (0x100)
  return newPosY >> 8;
}