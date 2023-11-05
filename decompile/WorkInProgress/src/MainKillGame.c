#include <common.h>

void MainKillGame_StopCTR(void)
{
  // set callback and save callback
  EnterCriticalSection();
  DrawSyncCallback(sdata->MainDrawCb_DrawSyncPtr);
  ExitCriticalSection();

  StopCallback();

  MEMCARD_CloseCard();

  PadStopCom();
  ResetGraph(3);
  VSyncCallback(0);

  RCNT_Destroy();
}

void MainKillGame_LaunchSpyro2(void)
{
  CTR_ErrorScreen(0,0,0);

  Music_Stop();

  // clear backup, destroy music, destroy all fx
  howl_StopAudio(1,1,1);

  Bank_DestroyAll();

  howl_Disable();

  VSync(0x1e);

  MainKillGame_StopCTR();

  _96_remove();
  _96_init();

  LoadExec("cdrom:\\SPYRO2.EXE;1",0x801fff00,0);
}