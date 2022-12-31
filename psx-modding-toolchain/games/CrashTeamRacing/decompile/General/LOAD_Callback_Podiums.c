#include <common.h>

void DECOMP_LOAD_Callback_Podiums(struct LoadQueueSlot * lqs)
{
  sdata->load_inProgress = 0;
  data.podiumModel_podiumStands = lqs->ptrDestination;
  return;
}