#include <common.h>

int DECOMP_CAM_Path_GetNumPoints(void)
{
  struct GameTracker *gGT = sdata->gGT;
  struct SpawnType1 *ptrSpawnType1;
  short sVar1;
  short *introCam;
  unsigned short uVar4;

  uVar4 = 0;

  // If LEV exists
  if (gGT->level1 != NULL)
  {
    ptrSpawnType1 = gGT->level1->ptrSpawnType1;

    if (// not enough ptrs
        (ptrSpawnType1->count < 3) ||
        (
            // get ptr_intro_cam
            introCam = ptrSpawnType1->pointers[ST1_CAMERA_PATH],

            // ptr_intro_cam is nullptr
            introCam == NULL))
      goto LAB_80018b98;

    for (;introCam[0] == NULL; introCam += 2 + introCam[0] * 6)
    {
      uVar4 += introCam[0];
    }
    sVar1 = (short)uVar4;
  }
  LAB_80018b98:
    return (int)sVar1;
}