#include <common.h>

void DECOMP_RB_ShieldDark_Pop(struct Thread* t)
{
  struct Shield* sh;
  struct Instance* inst;
  struct Instance* shInst;
  struct Driver* attacker;
  short local_18[3];
  
  inst = t->inst;
  
  // get object from thread from instance
  sh = inst->thread->object;
  shInst = (struct Instance*)sh[2];
  
  // rot? dir?
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  
  // get the driver that shot this weapon
  attacker = t->parentThread->object;
  
  // Copy matrices
  LHMatrix_Parent(inst,attacker->instSelf,&local_18);
  LHMatrix_Parent(shInst,attacker->instSelf,&local_18);
  
  // set rotation
  inst->matrix.m[0][0] = 0x1000;
  inst->matrix.m[0][2] = 0;
  inst->matrix.m[1][1] = 0x1000;
  inst->matrix.m[2][0] = 0;
  inst->matrix.m[2][2] = 0x1000;
  
  // set rotation
  shInst->matrix.m[0][0] = 0x1000;
  shInst->matrix.m[0][2] = 0;
  shInst->matrix.m[1][1] = 0x1000;
  shInst->matrix.m[2][0] = 0;
  shInst->matrix.m[2][2] = 0x1000;
  
  // if animation is not done, frame index?
  if (sh->unknown[0] < 0xb) 
  {
	// set scale
    inst->scale[0] = *(short *)0x800b2d14[sh->unknown[0]];
    inst->scale[1] = *(short *)0x800b2d16[sh->unknown[0]];
    inst->scale[2] = *(short *)0x800b2d14[sh->unknown[0]];
	
	// set scale
    shInst->scale[0] = *(short *)0x800b2d14[sh->unknown[0]];
    shInst->scale[1] = *(short *)0x800b2d16[sh->unknown[0]];
    shInst->scale[2] = *(short *)0x800b2d14[sh->unknown[0]];
	
    // next frame
    sh->unknown[0] += 1;
  }
  
  // if animation is done
  else 
  {
	// play 3D sound for "green shield fade away"
    PlaySound3D(0x58,inst);
	
    INSTANCE_Death(shInst);

    // another instance?
    INSTANCE_Death(sh[3]);
	
	// this thread is now dead
    t->flags |= 0x800;
  }
  return;
}
 