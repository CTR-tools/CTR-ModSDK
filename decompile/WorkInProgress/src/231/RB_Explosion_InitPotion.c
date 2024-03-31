#include <common.h>

void DECOMP_RB_Explosion_InitPotion(struct Instance* inst)
{
  struct Instance* shatterInst;
  struct Instance* iVar2;
  struct Particle* p;
  char i;
  int shatterColor;
  
  // green explosion
  shatterColor = 0x45;
  
  // if red beaker, red explosion
  if (inst->model->id == 0x46) shatterColor = 0x44;
  
  // create thread for shatter
  shatterInst = INSTANCE_BirthWithThread(shatterColor, sdata->s_shatter1, SMALL, OTHER, RB_Explosion_ThTick, 0,0);
  
  shatterInst->flags |= 0xa00;
  
  // copy position and rotation from one instance to the other
  shatterInst->matrix.m[0][0] = inst->matrix.m[0][0];
  shatterInst->matrix.m[0][2] = inst->matrix.m[0][2];
  shatterInst->matrix.m[1][1] = inst->matrix.m[1][1];
  shatterInst->matrix.m[2][0] = inst->matrix.m[2][0];
  shatterInst->matrix.m[2][2] = inst->matrix.m[2][2];
  shatterInst->matrix.t[0] = inst.matrix.t[0];
  shatterInst->matrix.t[1] = inst.matrix.t[1];
  shatterInst->matrix.t[2] = inst.matrix.t[2];
  
  // set funcThDestroy to remove instance from instance pool
  shatterInst->thread->funcThDestroy = PROC_DestroyInstance;
  
  // set scale
  shatterInst->scale[0] = 0x800;
  shatterInst->scale[1] = 0x800;
  shatterInst->scale[2] = 0x800;
  
  // particles for potion shatter
  for (i = 0; i < 5; i++)
  {
	// DAT_800b2d58
	// Unk, emset for shatter?
	  
	// Create instance in particle pool
    p = Particle_Init(0,gGT->iconGroup[1],&DAT_800b2d58);
	
    if (p != NULL) {
      p->axis[0]->startVal += shatterInst->matrix.t[0] * 0x100;
      p->axis[1]->startVal += shatterInst->matrix.t[1] * 0x100;
      p->axis[2]->startVal += shatterInst->matrix.t[2] * 0x100;
      if (shatterColor == 0x45) {
        p->axis[7].startVal = 1;
        p->axis[8].startVal = 0xc800;
      }
      else {
        p->axis[7].startVal = 0xc800;
        p->axis[8].startVal = 1;
      }
      p->axis[9].startVal = 1;
	  
      p->funcPtr = Particle_FuncPtr_PotionShatter;
      
	  p->modelID = shatterColor;
    }
  } 
  
  RB_Potion_OnShatter_TeethSearch(inst);
  
  return;
}
 