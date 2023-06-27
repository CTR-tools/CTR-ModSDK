#include <common.h>

// Handle CTR letters in HUD
void DECOMP_UI_ThTick_CtrLetters(struct Thread * bucket)

{
  int endOfRaceTransition;
  struct Instance* inst;
  struct UiElement3D* obj;
  short rotY;
  short rotX;
  short rotZ;

  // thread->instance
  inst = bucket->inst;

  // thread->object
  obj = bucket->object;

  // I know they dont look like they rotate in HUD,
  // believe, me, there is "rotation" to some degree,
  // that's why the lighting changes in the HUD

  // Rotate on the Y axis
  obj->rot[1] += 0x40;

  // Vector_SpecLightSpin2D
  // instance, ptr rot[6], cop registers
  Vector_SpecLightSpin2D(inst,obj,obj->lightDir);

  if (
		// If you're in End-Of-Race menu
		((sdata->gGT->gameMode1 & END_OF_RACE) != 0) &&

		(
			// TitleFlag_IsTransitioning
			endOfRaceTransition = TitleFlag_IsTransitioning,
			endOfRaceTransition != 0
		)
	)
  {
	// Set Scale to zero, basically stop
	// drawing letters in the HUD
    inst->scale[0] = 0;
    inst->scale[1] = 0;
    inst->scale[2] = 0;
  }

  if (inst->scale[0] == 0x800) {
    rotX = 0;
  }
  else {
    endOfRaceTransition = (int)inst->scale[0] + -0x800;
    if (endOfRaceTransition < 0) {
      endOfRaceTransition = (int)inst->scale[0] + -0x401;
    }
    rotX = ((short)(endOfRaceTransition >> 10) + 1) * 0x200;
  }
  rotY = 0;
  rotZ = 0;
  inst = inst->matrix;

   // convert 3 rotation shorts into rotation matrix
  CovertRotToMatrix(inst,&rotY);

  // MatrixRotate (param_1 = param_2 matrix rotated by param_3 matrix)
  MatrixRotate(inst,obj->m.m[0][0],inst);
  
  return;
}
