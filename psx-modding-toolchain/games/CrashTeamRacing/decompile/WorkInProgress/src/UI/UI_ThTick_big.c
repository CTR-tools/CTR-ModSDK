#include <common.h>

void DECOMP_UI_ThTick_big1(struct Thread * bucket)

{
  short uVar1;
  u_int flags;
  void* obj;
  struct Instance* inst;

  // Get object from thread
  obj = bucket->object;

  // Get instance from thread
  inst = bucket->inst;

  uVar1 = obj.rot[3];
  inst->matrix.m[0][1] = 0;
  inst->matrix.m[0][2] = 0;
  inst->matrix.m[1][0] = 0;
  inst->matrix.m[1][1] = uVar1;
  uVar1 = obj.rot[3];
  inst->matrix.m[1][2] = 0;
  inst->matrix.m[2][0] = 0;
  inst->matrix.m[2][1] = 0;
  inst->matrix.m[1][1] = uVar1;
  inst->matrix.m[2][2] = obj.rot[3];
  
  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  MatrixRotate(inst->matrix,obj.rot[4],inst->matrix);

  // if hud is enabled, and this is not demo mode
  if ((sdata->gGT->bool_DrawOTag_InProgress & 0xff0100) == 0x100) {
    flags = inst->flags & 0xffffff7f; // make visible
  } else {
    flags = inst->flags | 0x80; // make invisible
  }
  inst->flags = flags;
  return;
}
