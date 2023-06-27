#include <common.h>

void DECOMP_EngineAudio_Stop(u_int soundID)
{
  if ((sdata->boolAudioEnabled != 0) &&
	((soundID & 0xffff) < (sdata->ptrHowlHeader + 0x18)))
  {
    Smart_EnterCriticalSection();

	// 0 - engineFX
    Channel_SearchFX_Destroy(0,soundID & 0xffff,0xffffffff);

    Smart_ExitCriticalSection();
  }
  return;
}