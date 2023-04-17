#include <common.h>

void DECOMP_RB_Player_ToggleInvisible(void)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Driver* d;
  struct Thread* t;
  char i;

  // loop through player threads
  for (t = gGT->threadBuckets[PLAYER]; t != NULL; t = t->siblingThread)
  {
    // driver object
    d = t->object;

    if (
        // if driver is invisible
        (d->invisibleTimer != 0) &&
        // player exists
        (gGT->numPlyrCurrGame))
    {
      // loop through InstanceDrawPerPlayer
      for (i = 0; i < gGT->numPlyrCurrGame; i++)
      {
        // if this is not the screen of the invisible driver
        if (i != d->driverID)
        {
          // make driver instance invisible on this screen
          d->instSelf->idpp[i].unkb8 &= 0xffffffbf;
        }
      }
    }
  }
  return;
}
 