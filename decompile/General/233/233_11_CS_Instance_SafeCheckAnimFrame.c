#include <common.h>

int DECOMP_CS_Instance_SafeCheckAnimFrame(struct Instance *inst, int unused1, int unused2, int desiredFrame)
{
  // Default return value
  int animFrame = desiredFrame;

  // Check if instance exists and desired frame is positive
  if (inst != NULL && desiredFrame > 0)
  {
    int numFrames = CS_Instance_GetNumAnimFrames();

    // if negative
    if (numFrames < 1)
    {
      animFrame = 0;
    }
    // if more than 1 and out of bounds
    else if (numFrames <= desiredFrame)
    {
      animFrame = numFrames - 1;
    }
  }

  // Return adjusted animFrame
  return animFrame;
}
