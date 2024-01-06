#include <common.h>

void DECOMP_COLL_TestQuadblock_TwoTris(struct ScratchpadStruct* sps,struct QuadBlock* quad)
{	
  COLL_ResetScratchpadCache(sps);

  // always 2 for low poly (big block)
  sps->dataOutput[7] = 2;
  
  sps->dataOutput[6] = quad->triNormalVecBitShift;
  
  // TriNormalVecDividend
  short* SPS_TNVD = &sps->dataOutput[4];
  short* QBL_TNVD = &quad->triNormalVecDividend[0];
  
  struct BspSearchVertex* bsv = &sps->bspSearchVert[0];
  
  if (sps->unk4C[0xA0] != sps->unk4C[0xA2]) {
    *SPS_TNVD = QBL_TNVD[9];
    COLL_TestTriangle_GetNormalVector(sps, &bsv[1], &bsv[3], &bsv[2]); // 1, 3, 2
  }
  *SPS_TNVD = QBL_TNVD[8];
  COLL_TestTriangle_GetNormalVector(sps, &bsv[0], &bsv[1], &bsv[2]); // 0, 1, 2
}