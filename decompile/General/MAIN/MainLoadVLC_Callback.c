#include <common.h>

void DECOMP_MainLoadVLC_Callback(void)
{
  // VLC is now loaded
  sdata->bool_IsLoaded_VlcTable = 1;
}