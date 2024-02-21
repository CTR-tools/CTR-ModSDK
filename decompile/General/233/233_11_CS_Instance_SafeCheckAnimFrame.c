#include <common.h>

int DECOMP_CS_Instance_SafeCheckAnimFrame(struct Instance *inst, int unused1, int unused2, int desiredFrame)
{
  // Default return value
  int animFrame = desiredFrame;

  if (inst == NULL)
	  return animFrame;
  
  if (desiredFrame <= 0)
	  return animFrame;

  int numFrames = CS_Instance_GetNumAnimFrames();
  
  // if negative
  if (numFrames < 1)
  	return 0;
	
  // if more than 1 and out of bounds
  if (numFrames <= desiredFrame)
    animFrame = numFrames - 1;

  // Return adjusted animFrame
  return animFrame;
}
