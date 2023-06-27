#include <common.h> 

void DECOMP_Cutscene_VolumeRestore(void)
{
  // enter critical section
  Smart_EnterCriticalSection();

    // copy does not exist
    sdata->boolStoringVolume = 0;

    // Set volume of FX
    howl_VolumeSet(0,sdata->storedVolume);

  // exit critical section
  Smart_ExitCriticalSection();

  return;
}