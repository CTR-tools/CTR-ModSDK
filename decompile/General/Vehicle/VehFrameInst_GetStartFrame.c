#include <common.h>

int DECOMP_VehFrameInst_GetStartFrame(int animIndex, int numFrames)
{
  switch (animIndex)
  {
	// midpoint
    case 0: return numFrames >> 1; 
    
	// end
	case 4: return (numFrames - 1);
    
	// start
	default: return 0;
  }
}