#include <common.h>

void DECOMP_RB_MovingExplosive_Explode(
	struct Thread* t,
	struct Instance* inst,
	struct TrackerWeapon* tw)
{
  short soundId;
  struct Driver* d;

  // bomb
  if (inst->model->id == 0x3b)
  {
    // bomb explode
    soundId = 0x49;
    tw->driverParent->instBombThrow = NULL;
  }
  
  // missile
  else 
  {
    d = tw->driverTarget;
    if (d != NULL)
    {
      // remove 2D square-target being drawn on the player's screen
      d->actionsFlagSet &= 0xfbffffff;
    }
    // missile explode
    soundId = 0x4c;
  }

#ifndef REBUILD_PS1
  // play explosion sound
  PlaySound3D(soundId,inst);
  
  // stop audio of rolling
  OtherFX_RecycleMute(&tw->audioPtr);
  
  DECOMP_RB_Burst_Init(inst);
#endif
  
  // This thread is now dead
  t->flags |= 0x800;
  return;
}