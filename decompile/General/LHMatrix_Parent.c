#include <common.h>

/// @brief Link Hierarchal Matrix (like weapon relative to kart)
/// @param pDst - destination instance
/// @param pSrc - source instance
/// @param transVec - transform vector (x,y,z)
/// 0x800313c8
void LHMatrix_Parent(struct Instance* pDst, struct Instance* pSrc, SVECTOR* transVec)
{
  //copy source matrix values to destination (both m and t)
  memcpy(&pDst->matrix, &pSrc->matrix, sizeof(pSrc->matrix));

  //load dst matrix and transform vector to GTE
  SetRotMatrix(&pDst->matrix.m);
  SetTransMatrix(&pDst->matrix.m);
  gte_ldv0(transVec);

  //rotate on GTE
  gte_rt();

  //store translated vector from GTE to dest matrix
  gte_stlvnl(&pDst->matrix.t);
}