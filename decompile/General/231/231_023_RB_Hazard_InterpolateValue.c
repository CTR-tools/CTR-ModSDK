#include <common.h> 

int DECOMP_RB_Hazard_InterpolateValue(unsigned short currRot,unsigned short desiredRot,short rotSpeed)
{
  int iVar1;
  int iVar2;
  unsigned int diff;
  unsigned short uVar4;
  
  // temporary test
#if 1
  return desiredRot;
#endif

  uVar4 = currRot;
  
  if (currRot == desiredRot)
	  return (int)(short)uVar4;
  
  // get difference between them
  diff = (int)(short)desiredRot - (int)(short)currRot & 0xfff;
  
  // if difference is huge
  if (0x7ff < diff) 
  {
    // rotate a negative direction
    diff -= 0x1000;
  }
  
  iVar1 = diff;
  if (diff < 0) {
    iVar1 = -(int)diff;
  }
  
  // if rotation speed is less than 
  // remaining needed rotation
  if (iVar2 <= iVar1) 
  {
    if (diff < 1) 
    {
      uVar4 = currRot & 0xfff;
      if (-1 < diff) return (int)(short)uVar4;
  	
  	// new rotation is old rotation - speed
      desiredRot = currRot - (rotSpeed * sdata->gGT->elapsedTimeMS) >> 5;
    }
    else 
    {
  	// new rotation is old rotation + speed
      desiredRot = currRot + (rotSpeed * sdata->gGT->elapsedTimeMS) >> 5;
    }
  }
  
  // set new rotation, which is calculated rotation,
  // or the desired rotation if (desired-curr < speed)
  uVar4 = desiredRot & 0xfff;

  return (int)(short)uVar4;
}
 