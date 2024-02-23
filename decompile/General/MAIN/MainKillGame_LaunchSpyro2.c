#include <common.h>

void DECOMP_MainKillGame_LaunchSpyro2(void)
{
  DECOMP_CTR_ErrorScreen(0,0,0);

  DECOMP_Music_Stop();

  // clear backup, destroy music, destroy all fx
  DECOMP_howl_StopAudio(1,1,1);

  DECOMP_Bank_DestroyAll();

  DECOMP_howl_Disable();

  VSync(0x1e);

  DECOMP_MainKillGame_StopCTR();

  _96_remove();
  _96_init();

  LoadExec(&rdata.s_PathTo_SpyroExe[0],0x801fff00,0);
}