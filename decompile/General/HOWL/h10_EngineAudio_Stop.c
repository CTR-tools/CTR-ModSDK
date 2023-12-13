#include <common.h>

void DECOMP_EngineAudio_Stop(u_int soundID)
{
  if (sdata->boolAudioEnabled == 0) return;
	
  soundID = soundID & 0xffff;
  if (sdata->ptrHowlHeader->numEngineFX <= soundID) return;
  
  // 0 - engineFX
  DECOMP_Smart_EnterCriticalSection();
  DECOMP_Channel_SearchFX_Destroy(0,soundID,0xffffffff);
  DECOMP_Smart_ExitCriticalSection();
  
  return;
}