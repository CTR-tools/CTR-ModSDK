#include <common.h>

u_char DECOMP_CAM_Path_Move(int frameIndex, short *position, short *rotation, short *param_4)
{
  short currPos;
  u_int uVar3;
  short index;
  short *ptrCam;
  short *move;
  short uVar7;

  // frame index
  index = (short)frameIndex;

  // get number of position on track
  currPos = CAM_Path_GetNumPoints();

  if (index < 0)
    return 0;

  if (index < currPos)
  {
    ptrCam = sdata->gGT->level1->ptrSpawnType1->pointers[3];

    uVar3 = (u_int)ptrCam[0];
    uVar7 = ptrCam[1];
    move = ptrCam + 2;
    if (ptrCam[0] <= index)
    {
      do
      {
        frameIndex = frameIndex - uVar3;
        move = move + (int)uVar3 * 6;
        uVar3 = (u_int)move[0];
        uVar7 = move[1];
        move = move + 2;
      } while ((int)uVar3 <= (int)frameIndex);
    }

    // advance pointer to pos+rot
    move += (int)index * 6;

    param_4[0] = uVar7;

    // position of frame
    position[0] = move[0];
    position[1] = move[1];
    position[2] = move[2];

    // rotation of frame
    rotation[0] = ((short)move[3] >> 4) + 0x800U & 0xfff;
    rotation[1] = move[4] >> 4;
    rotation[2] = move[5] >> 4;
    return 1;
  }
  return 0;
}