#include <common.h> 

int DECOMP_RB_Hazard_InterpolateValue(unsigned short currRot,unsigned short desiredRot,short rotSpeed)
{
  int iVar1;
  int iVar2;
  unsigned int diff;
  unsigned short uVar4;
  
  uVar4 = currRot;
  
  // if current rotation is not desired rotation
  if (currRot != desiredRot) 
  {
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
      iVar1 = -diff;
    }
	
	// if rotation speed is less than 
	// remaining needed rotation
    if (iVar2 <= iVar1) 
	{
      if (diff < 1) 
	  {
        uVar4 = currRot & 0xfff;
        if (-1 < diff) goto LAB_800adb44;
		
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
  }
LAB_800adb44:
  return (int)(short)uVar4;
}
 