#include <common.h> 

void Cutscene_VolumeBackup(void)
{
  // enter critical section
  Smart_EnterCriticalSection();

    // make a copy of FX volume
    sdata->currentVolume = howl_VolumeGet(0);

    // make another copy volume of FX and clamp to 0x100
    sdata->storedVolume = sdata->currentVolume;
    sdata->currentVolume &= 0xff;

    // copy exists
    sdata->boolStoringVolume = 1;

  // exit critical section
  Smart_ExitCriticalSection();

  return;
}