#ifndef CTR_GTE_H
#define CTR_GTE_H

#include <ctr_math.h>
#include <psn00bsdk/include/inline_c.h>

typedef enum GTE_ROW_INDEX
{
    GTE_ROW_INDEX_0,
    GTE_ROW_INDEX_1,
    GTE_ROW_INDEX_2,
} GTE_ROW_INDEX;

typedef enum GTE_MATRIX
{
    GTE_MATRIX_ROT,
    GTE_MATRIX_LIGHT,
    GTE_MATRIX_COLOR,
    GTE_MATRIX_NONE,
} GTE_MATRIX;

typedef enum GTE_VECTOR
{
    GTE_VECTOR_0, /* SVec */
    GTE_VECTOR_1, /* SVec */
    GTE_VECTOR_2, /* SVec */
    GTE_VECTOR_IR, /* Vec */
} GTE_VECTOR;

typedef enum GTE_MAC
{
    GTE_MAC_0,
    GTE_MAC_1,
    GTE_MAC_2,
    GTE_MAC_3,
    GTE_MAC_VEC, /* 1-3, Vec */
} GTE_MAC;

/* HELPERS */
#define _CAT(a, b) a##b
#define CAT(a, b)  _CAT(a, b)
#define CAT3(a, b, c) CAT(CAT(a, b), c)

/* Private definitions */
#define _gte_loadSVecMatrix_GTE_MATRIX_ROT_GTE_ROW_INDEX_0(v) gte_ldsvrtrow0(v)
#define _gte_loadSVecMatrix_GTE_MATRIX_LIGHT_GTE_ROW_INDEX_0(v) gte_ldsvllrow0(v)
#define _gte_loadSVecMatrix_GTE_MATRIX_COLOR_GTE_ROW_INDEX_0(v) gte_ldsvlcrow0(v)
#define _gte_loadVec_GTE_VECTOR_0(v) gte_ldv0(v)
#define _gte_loadVec_GTE_VECTOR_1(v) gte_ldv1(v)
#define _gte_loadVec_GTE_VECTOR_2(v) gte_ldv2(v)
#define _gte_loadVec_GTE_VECTOR_IR(v) gte_ldsv(v)
#define _gte_readMac_GTE_MAC_0(out) gte_stopz(out)
#define _gte_readMac_GTE_MAC_1(out) gte_stlvnl0(out)
#define _gte_readMac_GTE_MAC_2(out) gte_stlvnl1(out)
#define _gte_readMac_GTE_MAC_3(out) gte_stlvnl2(out)
#define _gte_readMac_GTE_MAC_VEC(out) gte_stlvnl(out)
#define _gte_dotProduct_GTE_ROW_INDEX_0(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_1(out)
#define _gte_dotProduct_GTE_ROW_INDEX_1(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_2(out)
#define _gte_dotProduct_GTE_ROW_INDEX_2(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_3(out)
#define _gte_mulMatrixVec(out, matrixType, vecType, shift) gte_mvmva(shift, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_VEC(out)

/* API */
#define gte_readMac(out, macType) CAT(_gte_readMac_, macType)(out)
#define gte_loadVec(v, vecType) CAT(_gte_loadVec_, vecType)(v)
#define gte_loadRowMatrix(v, rowIndex, matrixType) CAT3(_gte_loadSVecMatrix_, matrixType, _##rowIndex)(v)
#define gte_mulMatrixVec(out, matrixType, vecType) _gte_mulMatrixVec(out, matrixType, vecType, 1)
#define gte_dotProduct(out, rowIndex, matrixType, vecType) CAT(_gte_dotProduct_, rowIndex)(out, matrixType, vecType)
#endif