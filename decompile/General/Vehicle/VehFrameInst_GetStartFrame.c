#include <common.h>

int DECOMP_VehFrameInst_GetStartFrame(int animIndex, int numFrames)
{
  switch (animIndex)
  {
	// midpoint
    case 0: return numFrames >> 1; 
    
	// start
	case 4: return 0;
    
	// end
	default: return (numFrames - 1);
  }
}