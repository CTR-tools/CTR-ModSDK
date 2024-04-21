#include <common.h>

void DECOMP_CAM_StartLine_FlyIn_FixY(short* posRot) 
{
  int iVar1;
  int iVar2;
  short local_26;
  short sVar3;
  short local_20;
  short local_1e;
  short local_1c;
  short local_18;
  short local_16;
  short local_14;

  // lev -> mesh_info
  sdata->scratchpadStruct.ptr_mesh_info = sdata->gGT->level1->ptr_mesh_info;
  sdata->scratchpadStruct.Union.QuadBlockColl.searchFlags = 2;
  sdata->scratchpadStruct.Union.QuadBlockColl.qbFlagsWanted = 0x3000; // ground and wall
  sdata->scratchpadStruct.Union.QuadBlockColl.qbFlagsIgnored = 0;

  local_20 = posRot[0];
  local_26 = posRot[1];
  local_1c = posRot[2];
  
  for (iVar2 = 0; iVar2 < 8; iVar2++)
  {
    iVar1 = 0x400 * iVar2;
    local_1e = local_26 - (iVar1 + 0x400);
    local_16 = local_26 - (iVar1 - 0x100);
    local_18 = local_20;
    local_14 = local_1c;

    COLL_SearchTree_FindQuadblock_Touching(&local_20,&local_18,&sdata->scratchpadStruct,0,local_20,local_1c);

    sVar3 = sdata->scratchpadStruct.Union.QuadBlockColl.unk1E;
    if (sdata->scratchpadStruct.boolDidTouchQuadblock != 0) break;
    sVar3 = local_26;
  }
  
  posRot[1] = sVar3;
}