#include <common.h> 

void DECOMP_Cutscene_VolumeBackup(void)
{
  // enter critical section
  Smart_EnterCriticalSection();

    // make another copy volume of FX and clamp to 0x100
    sdata->storedVolume = howl_VolumeGet(0) & 0xff;
    sdata->currentVolume = sdata->storedVolume;

    // copy exists
    sdata->boolStoringVolume = 1;

  // exit critical section
  Smart_ExitCriticalSection();

  return;
}