#include <common.h>

void DECOMP_COLL_TestQuadblock_TwoTris(struct ScratchpadStruct* sps,struct QuadBlock* quad)
{
  COLL_ResetScratchpadCache(0x1f800108);
  
  // always 2 for low poly (big block)
  sps->dataOutput[7] = 2;
  
  sps->dataOutput[6] = quad->triNormalVecBitShift;;
  
  // calculate normal vectors for two triangles,
  // no collision detection here
  
  if (sps->unk4C[0xA0] != sps->unk4C[0xA2]) {
    sps->dataOutput[4] = quad->triNormalVecDividend[9];
    COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f80020c, 0x1f800234, 0x1f800220); // 1, 3, 2
  }
  sps->dataOutput[4] = quad->triNormalVecDividend[8];
  COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f8001f8, 0x1f80020c, 0x1f800220); // 0, 1, 2
}