#include <common.h>
// In air, after spamming L1 or R1,
// will explode on impact with ground
void DECOMP_RB_TNT_ThTick_ThrowOffHead(struct Thread* t)
{
  struct GameTracker* gGT = sdata->gGT;
  struct Instance* inst;
  struct MineWeapon* mw;
  
  inst = t->inst;
  
  //  object (tnt)
  mw = t->object;
  
  // do NOT use parenthesis
  inst->matrix.t[1] += (mw->velocity[1] * gGT->elapsedTimeMS) >> 5;

  if (mw->stopFallAtY == 0x3fff) 
    mw->stopFallAtY = mw->driverTarget->instSelf->matrix.t[1];
  
  if (inst->matrix.t[1] <= mw->stopFallAtY)
  {	  
    // plays tnt explosion sound 3D
    PlaySound3D(0x3d,inst);
    
    RB_Blowup_Init(inst);
    
    // Set scale (x, y, z) to zero
    inst->scale[0] = 0;
    inst->scale[1] = 0;
    inst->scale[2] = 0;
    
    // make invisible
    inst->flags |= 0x80;
    
    // this thread is now dead
    t->flags |= 0x800;
    
    mw->driverTarget->instTntRecv = 0;
  }
  
  // decrease velocity (artificial gravity)
  mw->velocity[1] -= ((gGT->elapsedTimeMS << 2) >> 5);
  if (mw->velocity[1] < -0x60) mw->velocity[1] = -0x60;
}
 