#include <common.h>

void DECOMP_MainLoadVLC_Callback();

void DECOMP_MainLoadVLC(void)
{
  // VLC is not loaded
  sdata->bool_IsLoaded_VlcTable = 0;

  struct BigHeader* bh = sdata->ptrBigfileCdPos_2;
  struct BigEntry* entry = BIG_GETENTRY(bh);
  int size = entry[0x1e0].size;

  sdata->ptrVlcTable = MEMPACK_AllocMem(size);//,"VlcTable");

  // This table is passed as parameter to DecDCTvlc2
  LOAD_AppendQueue(bh, LT_RAW ,0x1e0,sdata->ptrVlcTable, DECOMP_MainLoadVLC_Callback);
}