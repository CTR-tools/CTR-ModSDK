#include <common.h>

void DECOMP_RB_Follower_ThTick(struct Thread* t)
{
  char state;
  int iVar2;
  int *obj;
  struct Instance* inst;
  struct Driver* d;
  
  obj = t->object;
  
  d = obj[1];
  
  // something from object
  iVar2 = obj[0];
  
  state = d->kartState;
  
  // reduce life by one frame
  obj[0] = iVar2 + -1;
  
  if (
		(
			(0 < iVar2 + -1) &&
			((
				// driver state
				(state == 0 || (state == 2)) && 
				
				// aren't these always equal?
				(*(int *)(obj[2] + 0x20) == obj[3])
			))

		) && (-1 < d->speedApprox) 
    )
  {
    inst = t->inst;
	
	// if scale is small
    if (inst->scale[0] < 0x800) 
	{
	  // double the scale (x, y, z)
      inst->scale[0] = inst->scale[0] << 1;
      inst->scale[1] = inst->scale[1] << 1;
      inst->scale[2] = inst->scale[2] << 1;
    }
	
	// Change X, Y, Z, of mine, to the 
	// midpoint between the current driver position,
	// and the position where the driver "was" at time of firing weapon
	
	// Ghidra syntax might be wrong:
    inst->matrix.t[0] = (int)*(short *)((int)obj + 0x10) + (d->posCurr[0] >> 8) >> 1;
    inst->matrix.t[1] = (int)*(short *)((int)obj + 0x12) + (d->posCurr[1] >> 8) >> 1;
    inst->matrix.t[2] = (int)*(short *)((int)obj + 0x14) + (d->posCurr[2] >> 8) >> 1;
    return;
  }
  
  // This thread is now dead
  t->flags |= 0x800;
  
  return;
}