#include <common.h>

int ratan2(int x, int y);

void DECOMP_CAM_EndOfRace_Battle(struct CameraDC* cDC, struct Driver* d) {

  cDC->flags |= 4;
  
  cDC->transitionTo.pos[0] = 0xffe5;
  cDC->transitionTo.pos[1] = data.Spin360_heightOffset_cameraPos[sdata->gGT->numPlyrCurrGame];
  cDC->transitionTo.pos[2] = 0xc0;

  long dx = cDC->cam110->pos[0] - (d->posCurr[0] >> 8);
  long dz = cDC->cam110->pos[2] - (d->posCurr[2] >> 8);
  long direction = ratan2(dx, dz);

  cDC->unk90[0] = (short)direction;
  cDC->unk8C = 0;
  
  cDC->unk8E = 60;
  cDC->frameCounterTransition = 60;
  return;
}