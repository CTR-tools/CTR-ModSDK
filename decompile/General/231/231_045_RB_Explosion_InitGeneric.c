#include <common.h>

void RB_Explosion_ThTick();

void DECOMP_RB_Explosion_InitGeneric(struct Instance* inst)
{
  struct Instance* explosion;
  unsigned short color;
  
  // create thread for explosion
  explosion = INSTANCE_BirthWithThread(
	0x26, 0, SMALL, OTHER, 
	RB_Explosion_ThTick, 0,0);
  
  // copy position and rotation from one instance to the other
  *(int*)&explosion->matrix.m[0][0] = *(int*)&inst->matrix.m[0][0];
  *(int*)&explosion->matrix.m[0][2] = *(int*)&inst->matrix.m[0][2];
  *(int*)&explosion->matrix.m[1][1] = *(int*)&inst->matrix.m[1][1];
  *(int*)&explosion->matrix.m[2][0] = *(int*)&inst->matrix.m[2][0];
  explosion->matrix.m[2][2] = inst->matrix.m[2][2];
  
  explosion->matrix.t[0] = inst->matrix.t[0];
  explosion->matrix.t[1] = inst->matrix.t[1];
  explosion->matrix.t[2] = inst->matrix.t[2];

  // green
  color = 0x1eac000;
  
  // instance -> model -> modelID == TNT
  if ((inst->model->id) == 0x27) 
  {  
	// red
	color = 0xad10000;
  }
  
  // set color
  explosion->colorRGBA = color;
  
  // set scale
  explosion->alphaScale = 0x1000;
  
  // set funcThDestroy to remove instance from instance pool
  explosion->thread->funcThDestroy = PROC_DestroyInstance;
  return;
}