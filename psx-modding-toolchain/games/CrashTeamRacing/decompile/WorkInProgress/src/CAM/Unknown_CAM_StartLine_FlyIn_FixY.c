#include <common.h>

struct BspSearchData* DECOMP_CAM_StartLine_FlyIn_FixY(struct {
    short pos[3];
    short rot[3];
} *DriverSpawn) {
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
  *(u_int*)0x8008db48 = &sdata->gGT->level1;

  *(u_int*)0x8008db3e = 2;
  // search flags
  *(u_int*)0x8008db40 = 0x3000; // ground and wall
  *(u_int*)0x8008db44 = 0;

  local_20 = DriverSpawn->pos[0];
  local_26 = DriverSpawn->pos[1];
  local_1c = DriverSpawn->pos[2];
  for (iVar2 = 0; iVar2 < 8; iVar2++)
  {
    iVar1 = 0x400 * iVar2;
    local_1e = local_26 - (iVar1 + 0x400);
    local_16 = local_26 - (iVar1 - 0x100);
    local_18 = local_20;
    local_14 = local_1c;

    COLL_SearchTree_FindQuadblock_Touching(&local_20,&local_18,&sdata->bspSearchData,0,local_20,local_1c);

    sVar3 = *(short*)0x8008db3a;
    if (*(int*)0x8008db5a != 0) break;
    sVar3 = local_26;
  }
  DriverSpawn->pos[1] = sVar3;
  return &sdata->bspSearchData;
}