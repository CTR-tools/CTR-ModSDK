#include <common.h>

void DECOMP_CAM_StartOfRace(struct CameraDC* cDC)
{
  // if fly-in camera data exists and there is only one screen
  if (2 < sdata->gGT->level1->cnt_restart_points && (sdata->gGT->numPlyrCurrGame == 1)) {
    int flyInData = (int)sdata->gGT->level1->ptr_restart_points;
    cDC->unk90[4] = 0;
    cDC->unk8C = 0;

    // make transition to driver last one second
    cDC->frameCounterTransition = 0x1E;
    cDC->desiredRot[6] = 0;

    // when camera reaches player, be zoomed in
    cDC->cameraMode = 0;
    cDC->unk88[20] = flyInData + 0x18;

    // if 1 or less screens
	  // set fly-in to last 165 frames, (5.25 seconds)
    cDC->unk8E = 0xA5;
  }
  else {
    // set animation to last one frame
    cDC->unk8E = 1;
  }

  cDC->cameraMode = 0;

  // remove bit & 0x4 (battle end of race) and 0x1000 (idk)
  cDC->flags &= 0xFFFFEFFB;
  return;
}
