#include <common.h>

void DECOMP_CS_LoadBossCallback(struct LoadQueueSlot * lqs)
{
  sdata->load_inProgress = 0;
  
  // CTR Model File (head)
  *(int*)0x800b7778 = lqs->ptrDestination;
}