#include <common.h>

void DECOMP_RB_Warpball_Death(struct Thread* t)
{
  struct TrackerWeapon* tw;
  
  // get object from thread
  tw = t->object;
  
  *(unsigned short *)((int)tw + 0x38) = *(unsigned short *)(*(int *)((int)t + 0x34) + 0x48);
  *(unsigned short *)(*(short*)((int)tw + 0xC) + 0x10) = 0;
  *(unsigned short *)((int)tw + 0x30) = 0;
  
  // play sound of warpball death
  PlaySound3D(0x4f);
  
  // stop audio of moving
  OtherFX_RecycleMute(tw->audioPtr);
  
  ThTick_SetAndExec(t,&RB_Warpball_FadeAway);
  return;
}
 