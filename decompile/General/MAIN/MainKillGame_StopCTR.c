#include <common.h>

void DECOMP_MainKillGame_StopCTR(void)
{
  // set callback and save callback
  EnterCriticalSection();
  DrawSyncCallback(sdata->MainDrawCb_DrawSyncPtr);
  ExitCriticalSection();

  StopCallback();

  #ifndef REBUILD_PC
  MEMCARD_CloseCard();
  #endif

  PadStopCom();
  ResetGraph(3);
  VSyncCallback(0);

  DECOMP_Timer_Destroy();
}