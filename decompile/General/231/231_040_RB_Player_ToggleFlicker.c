#include <common.h>

void DECOMP_RB_Player_ToggleFlicker(void)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Thread* t;
  struct Driver* d;
  char i;

  for (t = gGT->threadBuckets[PLAYER].thread; t != NULL; t = t->siblingThread)
  {
    // driver object
    d = t->object;

    if (
            // invincible timer
            (0x2a0 < d->invincibleTimer) &&

            // odd number frames
            ((gGT->timer & FPS_DOUBLE(1)) != 0)
		)
    {
	  struct InstDrawPerPlayer* idpp =
		INST_GETIDPP(d->instSelf);
		
      // on all screens
      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        // make driver invisible
        idpp[i].instFlags &= 0xffffffbf;
      }
    }
  }
  return;
}
 