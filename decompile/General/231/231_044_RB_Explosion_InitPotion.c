#include <common.h>

void DECOMP_RB_Explosion_InitPotion(struct Instance* inst)
{
  struct Instance* shatterInst;
  struct Particle* p;
  int shatterColor;
  unsigned char i;
  
  // green explosion
  shatterColor = STATIC_SHOCKWAVE_GREEN;
  
  // if red beaker, red explosion
  if (inst->model->id == STATIC_BEAKER_RED) 
	  shatterColor = STATIC_SHOCKWAVE_RED;
  
  // create instance for shatter
  shatterInst = INSTANCE_BirthWithThread(
	shatterColor, 0, SMALL, OTHER, 
	DECOMP_RB_Explosion_ThTick, 0,0);
  
  shatterInst->flags |= 0xa00;
  
  // set funcThDestroy to remove instance from instance pool
  shatterInst->thread->funcThDestroy = PROC_DestroyInstance;
  
  // copy position and rotation from one instance to the other
  *(int*)&shatterInst->matrix.m[0][0] = *(int*)&inst->matrix.m[0][0];
  *(int*)&shatterInst->matrix.m[0][2] = *(int*)&inst->matrix.m[0][2];
  *(int*)&shatterInst->matrix.m[1][1] = *(int*)&inst->matrix.m[1][1];
  *(int*)&shatterInst->matrix.m[2][0] = *(int*)&inst->matrix.m[2][0];
  shatterInst->matrix.m[2][2] = inst->matrix.m[2][2];
  

  //copy XYZ
  for (i = 0; i < 3; i++)
  {
	//scale
	shatterInst->scale[i] = 0x800;
	
	//pos
    shatterInst->matrix.t.v[i] = inst->matrix.t.v[i];
  }
	
	
  // particles for potion shatter
  for (i = 0; i < 5; i++)
  {  
	// Create instance in particle pool
    p = Particle_Init(0,sdata->gGT->iconGroup[1], (struct ParticleEmitter*)0x800b2d58);
	
    if (p == NULL)
		continue;
	
    p->axis[0].startVal += shatterInst->matrix.t.x * 0x100;
    p->axis[1].startVal += shatterInst->matrix.t.y * 0x100;
    p->axis[2].startVal += shatterInst->matrix.t.z * 0x100;

	p->modelID = shatterColor;
	
	if (shatterColor == STATIC_SHOCKWAVE_GREEN) 
	{
      p->axis[7].startVal = 1;
      p->axis[8].startVal = 0xc800;
    }
    
	else 
	{
      p->axis[7].startVal = 0xc800;
      p->axis[8].startVal = 1;
    }
	
    p->axis[9].startVal = 1;
	
	void Particle_FuncPtr_PotionShatter();
    p->funcPtr = Particle_FuncPtr_PotionShatter;
  } 
  
  DECOMP_RB_Potion_OnShatter_TeethSearch(inst);
  return;
}
 