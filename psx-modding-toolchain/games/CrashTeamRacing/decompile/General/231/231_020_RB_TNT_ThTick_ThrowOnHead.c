#include <common.h>

void RB_TNT_ThTick_SitOnHead();

void DECOMP_RB_TNT_ThTick_ThrowOnHead(struct Thread* t)
{
  short rng;
  struct MineWeapon* mw;
  struct Instance* inst;
  short* array;
  short rot[3];
  short auStack48 [32];
  
  inst = t->inst;
  
  // object
  mw = inst->thread->object;
  
  // alter height of TNT as it flies onto a driver's head
  mw->deltaPos[1] += mw->velocity[1] * (sdata->gGT->elapsedTimeMS >> 5);
  
  // if TNT is moving downward
  if (mw->velocity[1] < 0) 
  {
	// 0x800b2ac4
	// BSS before Baron_ThTick,
	// determines height of TNT for each player
	array = 0x800b2ac4;
    
	// if TNT landed on head
	if (
		(mw->deltaPos[1] < array[data.characterIDs[mw->driverTarget->driverID]]) &&
		(mw->deltaPos[1] = array[data.characterIDs[mw->driverTarget->driverID]],
		inst->scale[0] == 0x800)
	   )
	{
	  // Set TNT timer to 0, it blows up at 0x5a
      mw->numFramesOnHead = 0;
	  
      rng = (short)MixRNG_Scramble();
      
	  // Set number of required jumps to 8, with some RNG to mix it up
	  mw->jumpsRemaining = 8 - (rng + (rng / 2) * -2);
	  
	  // play sound that you hit a TNT
      PlaySound3D(0x51,inst);
	  
      inst->unk50 = mw->driverTarget->instSelf->unk50 + -1;
      inst->unk51 = mw->driverTarget->instSelf->unk51 + -1;
      
	  // assign 
	  ThTick_SetAndExec(t,RB_TNT_ThTick_SitOnHead);
    }
  }
  
  // CopyMatrix
  LHMatrix_Parent(inst,mw->driverTarget->instSelf,&mw->deltaPos[0]);
  
  // rotation
  rot[0] = 0;
  rot[1] = *(short *)((unsigned int)mw + 0x26);
  rot[2] = 0;
  
   // convert 3 rotation shorts into rotation matrix
  ConvertRotToMatrix(auStack48,&rot[0]);
  
  MatrixRotate(&inst->matrix,&inst->matrix,auStack48);
  
  // reduce time remaining until TNT lands on head
  mw->velocity[1] -= ((sdata->gGT->elapsedTimeMS << 2) >> 5);
  
   // set a minimum value (-0x60)
	if(mw->velocity[1] < -0x60) mw->velocity[1] = -0x60;
  
  // rotation
  *(short *)((unsigned int)mw + 0x26) += 0x100;
  
  // if scale is small
  if (inst->scale[0] < 0x801) 
  {
	// set min scale
    inst->scale [0] = 0x800;
    inst->scale [1] = 0x800;
    inst->scale [2] = 0x800;
  }
  
  // if scale is large
  else 
  {
	// reduce scale
    inst->scale [0] += -0x100;
    inst->scale [1] += -0x100;
    inst->scale [2] += -0x100;
  }
  return;
}