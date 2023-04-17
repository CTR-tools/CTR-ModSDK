#include <common.h>

void DECOMP_RB_Explosion_InitGeneric(struct Instance* inst)
{
  struct Instance* explosion;
  unsigned short color;
  
  // create thread for explosion
  explosion = INSTANCE_BirthWithThread(0x26, sdata->s_explosion1, SMALL, OTHER, RB_Explosion_ThTick, 0,0);
  
  // copy position and rotation from one instance to the other
  explosion->matrix.m[0][0] = inst->matrix.m[0][0];
  explosion->matrix.m[0][2] = inst->matrix.m[0][2];
  explosion->matrix.m[1][1] = inst->matrix.m[1][1];
  explosion->matrix.m[2][0] = inst->matrix.m[2][0];
  explosion->matrix.m[2][2] = inst->matrix.m[2][2];
  explosion->matrix.t[0] = inst->matrix.t[0];
  explosion->matrix.t[1] = inst->matrix.t[1];
  explosion->matrix.t[2] = inst->matrix.t[2];
  
  // instance -> model -> modelID == TNT
  if ((inst->model->id) == 0x27) {
    
	// red
	color = 0xad10000;
  }
  
  // not TNT
  else 
  {
	// green
    color = 0x1eac000;
  }
  
  // set color
  explosion->colorRGBA = color;
  
  // set scale
  explosion->alphaScale = 0x1000;
  
  // set funcThDestroy to remove instance from instance pool
  explosion->thread->funcThDestroy = THREAD_DestroyInstance;
  return;
}