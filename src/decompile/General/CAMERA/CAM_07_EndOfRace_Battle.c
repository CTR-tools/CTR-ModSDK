#include <common.h>

int ratan2(int x, int y);

void DECOMP_CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d) {

  int dx;
  int dz;
  int height;
  struct PushBuffer* pb;

  // This is NOT TransitionTo,
  // spin360's spinSpeed (missing union)
  // and spinHeight, spinDistance, etc
  height = data.Spin360_heightOffset_cameraPos[sdata->gGT->numPlyrCurrGame];
  cDC->transitionTo.pos[0] = FPS_HALF(0xffe5);
  cDC->transitionTo.pos[1] = height;
  cDC->transitionTo.pos[2] = 0xc0;

  // use camera that spins around player
  cDC->flags |= 4;

  // transition should take two seconds
  cDC->unk8C = 0;
  cDC->unk8E = 60;
  cDC->frameCounterTransition = 60;

  // direction to face
  pb = cDC->pushBuffer;
  dx = pb->pos[0] - (d->posCurr.x >> 8);
  dz = pb->pos[2] - (d->posCurr.z >> 8);
  cDC->unk90 = ratan2(dx, dz);

  return;
}