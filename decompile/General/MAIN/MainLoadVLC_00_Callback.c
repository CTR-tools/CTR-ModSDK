#include <common.h>

void DECOMP_MainLoadVLC_Callback(struct LoadQueueSlot* param_1)
{
  // VLC is now loaded
  sdata->bool_IsLoaded_VlcTable = 1;
}