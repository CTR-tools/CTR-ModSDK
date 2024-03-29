#include <common.h>

void DECOMP_UI_ThTick_CountPickup(struct Thread * bucket)
{

  struct GameTracker * gGT;
  short rotSpd;
  u_int flags;
  MATRIX* mat;

  gGT = sdata->gGT;

  // object from thread
  struct UiElement3D * obj = bucket->object;

  // instance from thread
  struct Instance * inst = bucket->inst;

  // instance color
  inst->colorRGBA = 0xffff0000;

  // if numPlyrCurrGame is 1
  if (gGT->numPlyrCurrGame == 1) {
    // if instance->model->modelID is not timebox
    if (inst->model->id != STATIC_TIME_CRATE_01) {
      // If player's wumpa is less than 10
      if (gGT->drivers[0]->numWumpas < 10) {
        // no shine
        inst->alphaScale = 0;
      } else {
        // wumpaShineResult
        inst->alphaScale = ((short) sdata->wumpaShineResult + -0x80) * 0x10;
      }
      goto LAB_8004c7a4;
    }
  }

  // if numPlyrCurrGame is not 1
  else {
    LAB_8004c7a4:

      // if HUD item is not timecrate
      if (inst->model->id != STATIC_TIME_CRATE_01) {
        // rotation speed 0x80
        rotSpd = obj->rot[1] + FPS_HALF(0x80);
        goto LAB_8004c7d4;
      }
  }

  // if wumpa or crystal,
  // rotation speed 0x40
  rotSpd = obj->rot[1] + FPS_HALF(0x40);

  LAB_8004c7d4:

  obj->rot[1] = rotSpd;
  mat = &inst->matrix.m[0][0];

  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(mat,obj);

#ifndef REBUILD_PS1  
  MatrixRotate(mat, &obj->m.m[0][0], mat);
#endif

  // if hud is enabled, and this is not demo mode
  if ((*(int*)&gGT->bool_DrawOTag_InProgress & 0xff0100) == 0x100) 
  {
    // make visible
    flags = inst->flags & 0xffffff7f;
  } 
  
  else 
  {
    // make invisible
    flags = inst->flags | 0x80;
  }
  
  inst->flags = flags;
  return;
}
