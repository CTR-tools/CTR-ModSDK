#include <common.h>

void DECOMP_RB_Warpball_Death(struct Thread* t)
{
  struct TrackerWeapon* tw;
  
  tw = t->object;
  tw->ptrParticle->framesLeftInLife = 0;
  tw->fadeAway_frameCount5 = 0;
  
  // play sound of warpball death
  struct Instance* inst = t->inst;
  tw->distFromGround = inst->matrix.t[1];
  PlaySound3D(0x4f, inst);
  
  // stop audio of moving
  OtherFX_RecycleMute(&tw->audioPtr);
  
  void RB_Warpball_FadeAway();
  ThTick_SetAndExec(t,&RB_Warpball_FadeAway);
  return;
}
 