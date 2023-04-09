#include <common.h>

void DECOMP_MM_Title_CameraMove(struct Title* title,short frameIndex)
{
  struct GameTracker* gGT = sdata->gGT;
  int iVar2;
  short *introCam;
  
  // after frame 0xe6, make the intro models transition from the center
  // of the screen, to the left of the screen, over the course of 15 frames
  iVar2 = TitleFlag_MoveModels((*(int*)0x800b5a14 - 0xe6),0xf);
  
  // pointer to intro-camera that flies around showing all drivers
  introCam = ((short *)0x800b5a34)[frameIndex * 3];
  
  // camera posX
  gGT->tileView[0].pos[0] =
       title->cameraPosOffset[0] + introCam[0] + (short)(OVR_230.titleCameraPosRot[0] * iVar2 >> 0xc);
  
  // camera posY
  gGT->tileView[0].pos[1] =
       title->cameraPosOffset[1] + introCam[1] + (short)(OVR_230.titleCameraPosRot[2] * iVar2 >> 0xc);
  
  // camera posZ
  gGT->tileView[0].pos[2] =
       title->cameraPosOffset[2]+ introCam[2] + (short)(OVR_230.titleCameraPosRot[4] * iVar2 >> 0xc);
  
  // Camera Rotation X, Y, and Z
  gGT->tileView[0].rot[0] = introCam[3] + (short)(OVR_230.titleCameraPosRot[8] * iVar2 >> 0xc);
  gGT->tileView[0].rot[1] = introCam[4] + (short)(OVR_230.titleCameraPosRot[10] * iVar2 >> 0xc);
  gGT->tileView[0].rot[2] = introCam[5] + (short)(OVR_230.titleCameraPosRot[12] * iVar2 >> 0xc);
  return;
} 