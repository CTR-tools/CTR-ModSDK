#include <common.h>

void DECOMP_LOAD_Callback_MaskHints3D(struct LoadQueueSlot * lqs)
{
  sdata->load_inProgress = 0;
  sdata->modelMaskHints3D = lqs->ptrDestination;
  return;
}