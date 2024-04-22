#include <common.h>

// Identical to Burst, but except for i<x
void DECOMP_RB_Blowup_ThTick(struct Thread *t)
{
  short animFrame;
  short numFrames;
  struct Instance* inst;
  int boolAlive;
  
  int *blowup;
  blowup = t->object;

  boolAlive = 0;
  for (int i = 0; i < 2; i++, blowup++)
  {
    // get instance pointer
    inst = *blowup;
	
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
      *blowup = NULL;
    }
  }

  if (!boolAlive)
  {
    // This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 