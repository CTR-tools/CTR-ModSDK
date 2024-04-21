#include <common.h>

void DECOMP_RB_Player_ToggleInvisible(void)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Driver* d;
  struct Thread* t;
  char i;

  // loop through player threads
  for (t = gGT->threadBuckets[PLAYER].thread; t != NULL; t = t->siblingThread)
  {
    // driver object
    d = t->object;

	// if driver is invisible
    if (d->invisibleTimer != 0)
    {
      // loop through InstanceDrawPerPlayer
      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        // if this is not the screen of the invisible driver
        if (i != d->driverID)
        {
		  struct InstDrawPerPlayer* idpp =
			INST_GETIDPP(d->instSelf);
			
          // make driver instance invisible on this screen
          idpp[i].instFlags &= 0xffffffbf;
        }
      }
    }
  }
  return;
}
 