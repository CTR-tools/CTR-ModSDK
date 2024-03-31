#include <common.h>

// Draw various objects, like relic,
// key trophy, token, crystal, etc
void DECOMP_UI_ThTick_Reward(struct Thread * bucket)

{
  u_int flags;
  MATRIX* mat;
  struct GameTracker* gGT;
  struct UiElement3D* obj;
  struct Instance* inst;

  gGT = sdata->gGT;

  // Get instance
  inst = bucket->inst;

  // Get object
  obj = bucket->object;

  // Spin on the Y axis
  obj->rot[1] += FPS_HALF(0x40);

#ifndef REBUILD_PS1
  Vector_SpecLightSpin2D(inst,obj,obj->lightDir);
#endif

  // pointer to matrix
  mat = &inst->matrix;

  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(mat,obj);

#ifndef REBUILD_PS1
  MatrixRotate(mat,&obj->m.m[0][0],mat);
#endif
  
  if (
		// if hud is enabled, and this is not demo mode
		((*(int*)&gGT->bool_DrawOTag_InProgress & 0xff0100) == 0x100) &&
		
		// if any fade-in-from-black transition is over
		(0xfff < gGT->pushBuffer_UI.fadeFromBlack_currentValue)
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
