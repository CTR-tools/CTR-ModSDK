#include <common.h>

// Draw various objects, like relic,
// key trophy, token, crystal, etc
void DECOMP_UI_ThTick_Reward(struct Thread * bucket)

{
  u_int flags;
  struct UiElement3D * obj;
  MATRIX mat;
  struct Instance * inst;

  // Get instance
  inst = bucket->inst;

  // Get object
  obj = bucket->object;

  // Spin on the Y axis
  obj->rot[1] += 0x40;

  // instance, ptr rot[6], cop registers
  Vector_SpecLightSpin2D(inst,obj,obj->lightDir);

  // pointer to matrix
  mat = inst->matrix;

   // convert 3 rotation shorts into rotation matrix
  CovertRotToMatrix(mat,obj);

  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  MatrixRotate(mat,obj->m.m[0][0],mat);
  
  if (
		((sdata->gGT->bool_DrawOTag_InProgress & 0xff0100) == 0x100) &&

		// if any fade-in-from-black transition is over
		(0xfff < sdata->gGT->tileView_UI.fadeFromBlack_currentValue)
	 )
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
