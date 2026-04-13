#include <common.h>

void DECOMP_COLL_FIXED_QUADBLK_GetNormVecs_HiLOD(struct ScratchpadStruct* sps, struct QuadBlock* quad)
{
  COLL_FIXED_QUADBLK_LoadScratchpadVerts(sps);
   
  // always 0 for high poly (small block)
  sps->dataOutput[7] = 0;
  
  sps->dataOutput[6] = quad->triNormalVecBitShift;
  
  // TriNormalVecDividend
  short* SPS_TNVD = &sps->dataOutput[4];
  short* QBL_TNVD = &quad->triNormalVecDividend[0];
  
  // calculate normal vectors for eight triangles,
  // no collision detection here
  struct BspSearchVertex* bsv = &sps->bspSearchVert[0];
  
  if (sps->unkVecE8[2] != sps->unkVecE8[3])
  {
    *SPS_TNVD = QBL_TNVD[4]; // triangle 4
    COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[8], &bsv[6], &bsv[7]); // 8, 6, 7
    
	*SPS_TNVD = QBL_TNVD[5]; // triangle 5
    COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[7], &bsv[3], &bsv[8]); // 7, 3, 8
    
	*SPS_TNVD = QBL_TNVD[6]; // triangle 6
    COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[1], &bsv[7], &bsv[6]); // 1, 7, 6
    
	*SPS_TNVD = QBL_TNVD[7]; // triangle 7
    COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[2], &bsv[6], &bsv[8]); // 2, 6, 8
  }
  
  *SPS_TNVD = QBL_TNVD[0]; // triangle 0
  COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[0], &bsv[4], &bsv[5]); // 0, 4, 5
  
  *SPS_TNVD = QBL_TNVD[1]; // triangle 1
  COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[4], &bsv[6], &bsv[5]); // 4, 6, 5
  
  *SPS_TNVD = QBL_TNVD[2]; // triangle 2
  COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[6], &bsv[4], &bsv[1]); // 6, 4, 1
  
  *SPS_TNVD = QBL_TNVD[3]; // triangle 3
  COLL_FIXED_TRIANGL_GetNormVec(sps, &bsv[5], &bsv[6], &bsv[2]); // 5, 6, 2
}