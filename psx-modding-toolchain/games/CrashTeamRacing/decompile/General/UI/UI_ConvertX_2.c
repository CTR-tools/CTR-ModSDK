#include <common.h>

int DECOMP_UI_ConvertX_2(int oldPosX,int newPosX)
{
  #define midpointX 0x100
  newPosX = (oldPosX - midpointX) * newPosX;

  // If new posX is on the left of the screen
  if (newPosX < 0) {
    newPosX += 0xff;
  }

  // divide by 256 (0x100)
  return newPosX >> 8;
}