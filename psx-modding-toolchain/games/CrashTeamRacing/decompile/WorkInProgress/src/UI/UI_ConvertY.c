#include <common.h>

#define midpointY 0x6c

int DECOMP_UI_ConvertY_2(int oldPosY,int newPosY)
{
  newPosY = (oldPosY - midpointY) * newPosY;

  // If new posY is under the screen
  if (newPosY < 0) {
    newPosY += 0xff;
  }

  // divide by 256 (0x100)
  return newPosY >> 8;
}