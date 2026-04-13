#include <common.h>

void DECOMP_RB_GenericMine_ThDestroy(struct Thread* t, struct Instance* inst, struct MineWeapon* mw)
{
  unsigned int model;
  unsigned short param;

  model = inst->model->id;

  // if model is green or red beaker
  if ((unsigned int)(model - 0x46) < 2) 
  {
      // play sound of glass shatter
      PlaySound3D(0x3f, inst);

      RB_Explosion_InitPotion(inst);
  }
  
  else
  {
    // if model is TNT
	// tnt explosion sound
	param = 0x3d;
  
	// if model is Nitro
	if (model == 6) 
	{
		// glass shatter
		param = 0x3f;
	}
	
	PlaySound3D(param, inst);

	RB_Blowup_Init(inst);
  }

  // Set scale (x, y, z) to zero
  inst->scale[0] = 0;
  inst->scale[1] = 0;
  inst->scale[2] = 0;

  // make invisible
  inst->flags |= 0x80;

  DECOMP_RB_MinePool_Remove(mw);

  // this thread is now dead
  t->flags |= 0x800;

  return;
}
