#include <common.h>
void DECOMP_LOAD_Callback_LEV(struct LoadQueueSlot * lqs)
{
    // flags
    if ((lqs->flags & 2) == 0) 
    {
        sdata->load_inProgress = 0;
    }
    sdata->ptrLEV_DuringLoading = lqs->ptrDestination;
  return;
}