#include <common.h>

void DECOMP_RB_Blowup_ThTick(struct Thread *t)
{
  short animFrame, numFrames;
  struct Instance *inst;
  char i;
  int *blowup;

  // get object from thread, not in header yet?
  blowup = t->object;

  for (i = 0; i < 2; i++)
  {
    // get instance pointer
    inst = blowup[i];

    if (inst == NULL) break;
    animFrame = inst->animFrame;

    numFrames = INSTANCE_GetNumAnimFrames(inst, 0);

    // if animation is not done
    if (animFrame < numFrames - 1)
    {
      // increment animation frame
      inst->animFrame += 1;
    }
    // if animation is done
    else
    {
      INSTANCE_Death(inst);
      inst = NULL;
    }
  }

  // if either instance has been erased
  if ((blowup[1] == NULL) && (blowup[0] == NULL))
  {
    // This thread is now dead
    t->flags |= 0x800;
  }

  // this skips $RA backup/restore, faster than JR $RA
  ThTick_FastRET(t);
}
 