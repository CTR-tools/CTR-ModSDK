#include <common.h>

void MainLoadVLC_Callback(void)
{
  // VLC is now loaded
  sdata->bool_IsLoaded_VlcTable = 1;
}

void MainLoadVLC(void)
{
  // VLC is not loaded
  sdata->bool_IsLoaded_VlcTable = 0;

  int size = *(int *)(sdata->ptrBigfileCdPos_2 + 0xf0c) + 0x7ff;
  if (size < 0) {
    size = *(int *)(sdata->ptrBigfileCdPos_2 + 0xf0c) + 0xffe;
  }

  //this one is labeled vlctable, loads some file that looks like array
  //google hints it's something for video decoding?

  // MEMPACK_AllocMem
  sdata->ptrVlcTable = MEMPACK_AllocMem((size >> 0xb) << 0xb,"VlcTable");

  // This table is passed as parameter to DecDCTvlc2

  // '1' for readfile
  LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, 1 ,0x1e0,sdata->ptrVlcTable, MainLoadVLC_Callback);
}