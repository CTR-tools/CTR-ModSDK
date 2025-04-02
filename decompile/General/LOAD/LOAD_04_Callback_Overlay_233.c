#include <common.h>

void DECOMP_LOAD_Callback_Overlay_233(void)
{
  sdata->gGT->overlayIndex_Threads = 3;
  
  // My bad, this wasn't safe to relocate -- Niko
  // Patch call to LOAD_Hub_ReadFile from CS_Thread_UseOpcode
  #ifndef REBUILD_PS1
  #define JAL(dest) (((unsigned long)dest & 0x3FFFFFF) >> 2 | 0xC000000)
  void DECOMP_LOAD_Hub_ReadFile();
  if(*(int*)0x800ad368 == 0xC00CBFF)
  *(int*)0x800ad368 = JAL(DECOMP_LOAD_Hub_ReadFile);
  #endif
  
  return;
}