#include <common.h>

void DECOMP_COLL_TestQuadblock_EightTris(struct ScratchpadStruct* sps,struct QuadBlock* quad)
{
  COLL_ResetScratchpadCache(0x1f800108);
   
  // always 0 for high poly (small block)
  sps->dataOutput[7] = 0;
  
  sps->dataOutput[6] = quad->triNormalVecBitShift;;
  
  // calculate normal vectors for eight triangles,
  // no collision detection here
  
  if (sps->unk4C[0xA0] != sps->unk4C[0xA2]) {  // Do we hit two quads? if then, check two quads.
    sps->dataOutput[4] = quad->triNormalVecDividend[4]; // triangle 4
    COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f800298, 0x1f800270, 0x1f800284); // 8, 6, 7
    sps->dataOutput[4] = quad->triNormalVecDividend[5]; // triangle 5
    COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f800284, 0x1f800234, 0x1f800298); // 7, 3, 8
    sps->dataOutput[4] = quad->triNormalVecDividend[6]; // triangle 6
    COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f80020c, 0x1f800284, 0x1f800270); // 1, 7, 6
    sps->dataOutput[4] = quad->triNormalVecDividend[7]; // triangle 7
    COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f800220, 0x1f800270, 0x1f800298); // 2, 6, 8
  }
  sps->dataOutput[4] = quad->triNormalVecDividend[0]; // triangle 0
  COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f8001f8, 0x1f800248, 0x1f80025c); // 0, 4, 5
  sps->dataOutput[4] = quad->triNormalVecDividend[1]; // triangle 1
  COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f800248, 0x1f800270, 0x1f80025c); // 4, 6, 5
  sps->dataOutput[4] = quad->triNormalVecDividend[2]; // triangle 2
  COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f800270, 0x1f800248, 0x1f80020c); // 6, 4, 1
  sps->dataOutput[4] = quad->triNormalVecDividend[3]; // triangle 3
  COLL_TestTriangle_GetNormalVector(0x1f800108, 0x1f80025c, 0x1f800270, 0x1f800220); // 5, 6, 2
}