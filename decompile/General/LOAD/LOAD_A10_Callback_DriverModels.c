#include <common.h>

void DECOMP_LOAD_Callback_DriverModels(struct LoadQueueSlot* lqs)
{
  sdata->load_inProgress = 0;
  sdata->ptrMPK = lqs->ptrDestination;
  return;
}