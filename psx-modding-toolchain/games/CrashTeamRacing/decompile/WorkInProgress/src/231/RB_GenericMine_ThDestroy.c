#include <common.h>

void DECOMP_RB_GenericMine_ThDestroy(struct Thread* t, struct Instance* inst, struct MineWeapon* mw)
{
  short model;
  unsigned short soundId;

  model = inst->model->id;

  // if Nitro
  if (model == 6)
  {
    // glass shatter sound
    soundId = 0x3f;
  }
  else
  {
    // if not TNT
    if (model != 0x27)
    {
      // play sound of glass shatter
      PlaySound3D(0x3f, inst);

      RB_Explosion_InitPotion(inst);

      goto LAB_800ad2c8;
    }
    // explosion sound
    soundId = 0x3d;
  }

  PlaySound3D(soundId, inst);

  RB_Blowup_Init(inst);

LAB_800ad2c8:

  // Set scale (x, y, z) to zero
  inst->scale[0] = 0;
  inst->scale[1] = 0;
  inst->scale[2] = 0;

  // make invisible
  inst->flags |= 0x80;

  RB_MinePool_Remove(mw);

  // this thread is now dead
  t->flags |= 0x800;

  return;
}
