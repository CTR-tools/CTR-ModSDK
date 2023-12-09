#include <common.h>

int ratan2(int x, int y);

void DECOMP_CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d) {

  int dx;
  int dz;
  int height;
  struct TileView* tileView;

  // transition to the radius of 
  // the camera that spins around player
  height = data.Spin360_heightOffset_cameraPos[sdata->gGT->numPlyrCurrGame];
  cDC->transitionTo.pos[0] = 0xffe5;
  cDC->transitionTo.pos[1] = height;
  cDC->transitionTo.pos[2] = 0xc0;

  // use camera that spins around player
  cDC->flags |= 4;
  
  // transition should take two seconds
  cDC->unk8C = 0;
  cDC->unk8E = 60;
  cDC->frameCounterTransition = 60;

  // direction to face
  tileView = cDC->tileView;
  dx = tileView->pos[0] - (d->posCurr[0] >> 8);
  dz = tileView->pos[2] - (d->posCurr[2] >> 8);
  cDC->unk90 = ratan2(dx, dz);
  
  return;
}