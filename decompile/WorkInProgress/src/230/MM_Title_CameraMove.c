#include <common.h>

void DECOMP_MM_Title_CameraMove(struct Title *title, short frameIndex)
{
     struct GameTracker *gGT = sdata->gGT;
     int transition;
     short* introCam;

     // after frame 0xe6, make the intro models transition from the center
     // of the screen, to the left of the screen, over the course of 15 frames
     transition = TitleFlag_MoveModels((OVR_230.unkTimerMM - 230), 15);

     // pointer to intro-camera that flies around showing all drivers
     introCam = OVR_230.ptrIntroCam[frameIndex * 6];

     // camera posX
     gGT->tileView[0].pos[0] =
         title->cameraPosOffset[0] + introCam[0] + (short)(OVR_230.titleCameraPosRot[0] * transition >> 12);

     // camera posY
     gGT->tileView[0].pos[1] =
         title->cameraPosOffset[1] + introCam[1] + (short)(OVR_230.titleCameraPosRot[2] * transition >> 12);

     // camera posZ
     gGT->tileView[0].pos[2] =
         title->cameraPosOffset[2] + introCam[2] + (short)(OVR_230.titleCameraPosRot[4] * transition >> 12);

     // Camera Rotation X, Y, and Z
     gGT->tileView[0].rot[0] = introCam[3] + (short)(OVR_230.titleCameraPosRot[8] * transition >> 12);
     gGT->tileView[0].rot[1] = introCam[4] + (short)(OVR_230.titleCameraPosRot[10] * transition >> 12);
     gGT->tileView[0].rot[2] = introCam[5] + (short)(OVR_230.titleCameraPosRot[12] * transition >> 12);
}