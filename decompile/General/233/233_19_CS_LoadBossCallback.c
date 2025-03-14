#include <common.h>

void DECOMP_CS_LoadBossCallback(struct LoadQueueSlot * lqs)
{
  sdata->load_inProgress = 0;
  OVR_233.ptrModelBossHead = lqs->ptrDestination;
}