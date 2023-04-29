#include <common.h>

void DECOMP_RB_Burst_ThTick(struct Thread *t)
{
  char i;
  short animFrame;
  short numFrames;
  struct Instance* inst;
  int *burst;

  burst = t->object;

  for (i = 0; i < 3; i++)
  {
    // get instance pointer
    inst = burst[i];

    if (inst == NULL) break;

    animFrame = inst->animFrame;

    numFrames = INSTANCE_GetNumAnimFrames(inst, 0);

    // if animation is not done
    if (animFrame < numFrames - 1)
    {
      // increment animation frame
      inst->animFrame++;
    }

    // if animation is done
    else
    {
      INSTANCE_Death(inst);
      inst = NULL;
    }
  }

  // if all instances have been erased
  if (burst[0] == burst[1] == burst[2] == 0)
  {
    // This thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 