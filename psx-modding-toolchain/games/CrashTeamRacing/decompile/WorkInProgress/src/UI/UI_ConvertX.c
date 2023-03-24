#include <common.h>

#define midpointX 0x100

int DECOMP_UI_ConvertX_2(int oldPosX,int newPosX)
{
  newPosX = (oldPosX - midpointX) * newPosX;

  // If new posX is on the left of the screen
  if (newPosX < 0) {
    newPosX += 0xff;
  }
  
  // divide by 256 (0x100)
  return newPosX >> 8;
}
