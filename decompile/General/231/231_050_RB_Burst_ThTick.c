#include <common.h>

// Identical to Blowup, but except for i<x
void DECOMP_RB_Burst_ThTick(struct Thread *t)
{
  short animFrame;
  short numFrames;
  struct Instance* inst;
  int boolAlive;
  
  int *burst;
  burst = t->object;

  boolAlive = 0;
  for (int i = 0; i < 3; i++, burst++)
  {
    // get instance pointer
    inst = *burst;
	
    if (inst == NULL)
		continue;
    
	animFrame = inst->animFrame;
    numFrames = INSTANCE_GetNumAnimFrames(inst, 0);

    if (animFrame < numFrames - 1)
	{
	  boolAlive = 1;
      inst->animFrame++;
	}

    else
    {
      INSTANCE_Death(inst);
      *burst = NULL;
    }
  }

  if (!boolAlive)
  {
    // This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 