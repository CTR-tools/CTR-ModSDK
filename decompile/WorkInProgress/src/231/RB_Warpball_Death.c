#include <common.h>

void DECOMP_RB_Warpball_Death(struct Thread* t)
{
  struct TrackerWeapon* tw;
  
  tw = t->object;
  tw->distFromGround = t->inst->matrix.t[1];
  tw->ptrParticle->framesLeftInLife = 0;
  tw->fadeAway_frameCount5 = 0;
  
  // play sound of warpball death
  PlaySound3D(0x4f);
  
  // stop audio of moving
  OtherFX_RecycleMute(&tw->audioPtr);
  
  ThTick_SetAndExec(t,&RB_Warpball_FadeAway);
  return;
}
 