#include <common.h>

void THREAD_PerVisData_CheckInstances();

void DECOMP_THREAD_StartSearch_Self(struct WeaponSearchData* param)
{
  struct GameTracker* gGT = sdata->gGT;
  short sVar1;

  // box half-length
  sVar1 = param->hitRadius;

  // position of object hitting
  // tiger temple teeth

  // param[0] = posX,
  // param[1] = posY,
  // param[2] = posZ,

  // Make hitbox, min and max x,y,z
  param->min[0] = param->pos[0] - sVar1;
  param->min[1] = param->pos[1] - sVar1;
  param->min[2] = param->pos[2] - sVar1;
  param->max[0] = param->pos[0] + sVar1;
  param->max[1] = param->pos[1] + sVar1;
  param->max[2] = param->pos[2] + sVar1;

  COLL_SearchTree_FindX(&gGT->level1->ptrModelsPtrArray,param->funcCallback,THREAD_PerVisData_CheckInstances);
  return;
}