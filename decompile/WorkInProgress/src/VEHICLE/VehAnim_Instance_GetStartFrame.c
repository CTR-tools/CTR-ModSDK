#include <common.h>

int VehAnim_Instance_GetStartFrame(int animIndex, int numFrames)
{
  switch (animIndex)
  {
    case 0:
      // midpoint
      return numFrames >> 1; 
    case 4:
        // start
      return 0;
    default:
        // end
      return (numFrames - 1);
  }
}