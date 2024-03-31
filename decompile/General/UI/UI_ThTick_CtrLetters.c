#include <common.h>

// Handle CTR letters in HUD
void DECOMP_UI_ThTick_CtrLetters(struct Thread * bucket)

{
  int endOfRaceTransition;
  struct Instance* inst;
  struct UiElement3D* obj;
  short rot[3];

  // thread->instance
  inst = bucket->inst;

  // thread->object
  obj = bucket->object;

  // I know they dont look like they rotate in HUD,
  // believe, me, there is "rotation" to some degree,
  // that's why the lighting changes in the HUD

  // Rotate on the Y axis
  obj->rot[1] += FPS_HALF(0x40);

#ifndef REBUILD_PS1
  Vector_SpecLightSpin2D(inst,obj,obj->lightDir);
#endif

  if (
		// If you're in End-Of-Race menu
		((sdata->gGT->gameMode1 & END_OF_RACE) != 0) &&

		(DECOMP_RaceFlag_IsTransitioning() != 0)
	)
  {
	// Set Scale to zero, basically stop
	// drawing letters in the HUD
    inst->scale[0] = 0;
    inst->scale[1] = 0;
    inst->scale[2] = 0;
  }

  if (inst->scale[0] == 0x800) {
    rot[1] = 0;
  }
  else {
    endOfRaceTransition = (int)inst->scale[0] + -0x800;
    if (endOfRaceTransition < 0) {
      endOfRaceTransition = (int)inst->scale[0] + -0x401;
    }
    rot[1] = ((short)(endOfRaceTransition >> 10) + 1) * 0x200;
  }
  rot[0] = 0;
  rot[2] = 0;
  inst = &inst->matrix;

  // converted to TEST in rebuildPS1
  ConvertRotToMatrix(inst,&rot[0]);

#ifndef REBUILD_PS1
  MatrixRotate(inst,&obj->m.m[0][0],inst);
#endif
  
  return;
}
