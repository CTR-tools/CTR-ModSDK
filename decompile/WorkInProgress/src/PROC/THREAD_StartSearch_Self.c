#include <common.h>

void DECOMP_PROC_StartSearch_Self(struct ScratchpadStruct* param)
{
  struct GameTracker* gGT = sdata->gGT;
  short sVar1;

  // box half-length
  sVar1 = param->hitRadius;

  // Make hitbox, min and max x,y,z
  param->Union.ThBuckColl.min[0] = param->Input1.pos[0] - sVar1;
  param->Union.ThBuckColl.min[1] = param->Input1.pos[1] - sVar1;
  param->Union.ThBuckColl.min[2] = param->Input1.pos[2] - sVar1;
  param->Union.ThBuckColl.max[0] = param->Input1.pos[0] + sVar1;
  param->Union.ThBuckColl.max[1] = param->Input1.pos[1] + sVar1;
  param->Union.ThBuckColl.max[2] = param->Input1.pos[2] + sVar1;

  COLL_SearchTree_FindX(
	gGT->level1->ptr_mesh_info->bspRoot,
	param->funcCallback,
	PROC_PerBspLeaf_CheckInstances);
  
  return;
}