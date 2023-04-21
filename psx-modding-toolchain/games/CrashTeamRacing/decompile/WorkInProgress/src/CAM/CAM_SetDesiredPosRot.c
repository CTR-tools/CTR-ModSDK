#include <common.h>

void DECOMP_CAM_SetDesiredPosRot(struct CameraDC* cDC, short *desiredPos, short *desiredRot)
{
  // cDC->transitionTo.pos[0] = desiredPos[0];
  // cDC->transitionTo.pos[1] = desiredPos[1];
  // cDC->transitionTo.pos[2] = desiredPos[2];

  // cDC->transitionTo.rot[0] = desiredRot[0];
  // cDC->transitionTo.rot[1] = desiredRot[1];
  // cDC->transitionTo.rot[2] = desiredRot[2];

  // saves 12 bytes, if not then overbudget at 0x6c bytes
  memcpy(&cDC->transitionTo.pos, desiredPos, sizeof(short)*3);
  memcpy(&cDC->transitionTo.rot, desiredRot, sizeof(short)*3);

  // make transition last one second
  cDC->frameCounterTransition = 0x1e;

  cDC->unk8E = 0;
  cDC->unk8C = 0x1000;

  // begin transition by activating flag
  cDC->flags |= 0x200;
  return;
}