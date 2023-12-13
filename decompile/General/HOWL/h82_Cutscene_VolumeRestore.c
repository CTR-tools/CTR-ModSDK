#include <common.h> 

void DECOMP_Cutscene_VolumeRestore(void)
{
  // enter critical section
  DECOMP_Smart_EnterCriticalSection();

  // copy does not exist
  sdata->boolStoringVolume = 0;
  
  // Set volume of FX
  DECOMP_howl_VolumeSet(0,sdata->storedVolume);

  // exit critical section
  DECOMP_Smart_ExitCriticalSection();

  return;
}