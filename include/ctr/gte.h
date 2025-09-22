#pragma once

#include <ctr/math.h>
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
    GTE_VECTOR_IR, /* SVec */
    GTE_VECTOR_MAC, /* Vec */
} GTE_VECTOR;

typedef enum GTE_IR
{
    GTE_IR_0, /* s16 */
    GTE_IR_1, /* s16 */
    GTE_IR_2, /* s16 */
    GTE_IR_3, /* s16 */
} GTE_IR;

typedef enum GTE_MAC
{
    GTE_MAC_0, /* s32 */
    GTE_MAC_1, /* s32 */
    GTE_MAC_2, /* s32 */
    GTE_MAC_3, /* s32 */
} GTE_MAC;

typedef enum GTE_INTERPOLATE
{
    GTE_INTERPOLATE_INT,
    GTE_INTERPOLATE_FLOATING_POINT,
} GTE_INTERPOLATE;

/* HELPERS */
#define _CAT(a, b) a##b
#define CAT(a, b)  _CAT(a, b)
#define CAT3(a, b, c) CAT(CAT(a, b), c)

/* Private definitions */
#define _gte_loadSVecMatrix_GTE_MATRIX_ROT_GTE_ROW_INDEX_0(v) gte_ldsvrtrow0(v)
#define _gte_loadSVecMatrix_GTE_MATRIX_LIGHT_GTE_ROW_INDEX_0(v) gte_ldsvllrow0(v)
#define _gte_loadSVecMatrix_GTE_MATRIX_COLOR_GTE_ROW_INDEX_0(v) gte_ldsvlcrow0(v)
#define _gte_loadSVec_GTE_VECTOR_0(v) gte_ldv0(v)
#define _gte_loadSVec_GTE_VECTOR_1(v) gte_ldv1(v)
#define _gte_loadSVec_GTE_VECTOR_2(v) gte_ldv2(v)
#define _gte_loadSVec_GTE_VECTOR_IR(v) gte_ldsv(v)
#define _gte_loadVec_GTE_VECTOR_IR(v) gte_ldlvl(v)
#define _gte_loadVec_GTE_VECTOR_MAC(v) __asm__ volatile ( \
	"lwc2	$25, 0( %0 );"	\
	"lwc2	$26, 4( %0 );"	\
	"lwc2	$27, 8( %0 );"	\
	:						\
	: "r"( v ) )
#define _gte_readMac_GTE_MAC_0(out) gte_stopz(out)
#define _gte_readMac_GTE_MAC_1(out) gte_stlvnl0(out)
#define _gte_readMac_GTE_MAC_2(out) gte_stlvnl1(out)
#define _gte_readMac_GTE_MAC_3(out) gte_stlvnl2(out)
#define _gte_readMac_GTE_VECTOR_MAC(out) gte_stlvnl(out)
#define _gte_loadIR_GTE_IR_0(in) gte_lddp(in)
#define _gte_dotProduct_GTE_ROW_INDEX_0(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_1(out)
#define _gte_dotProduct_GTE_ROW_INDEX_1(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_2(out)
#define _gte_dotProduct_GTE_ROW_INDEX_2(out, matrixType, vecType) gte_mvmva(0, matrixType, vecType, 3, 0); _gte_readMac_GTE_MAC_3(out)
#define _gte_mulMatrixVec(out, matrixType, vecType, shift) gte_mvmva(shift, matrixType, vecType, 3, 0); _gte_readMac_GTE_VECTOR_MAC(out)
#define _gte_interpolate_GTE_INTERPOLATE_INT() gte_gpl0()
#define _gte_interpolate_GTE_INTERPOLATE_FLOATING_POINT() gte_gpl12()
#define _gte_leadingZeroes(out, in) __asm__ volatile ( \
    "mtc2	%1, $30;" \
    "nop;" \
    "nop;" \
    "swc2	$31, 0( %0 );" \
    : \
    : "r"( out ), "r"( in ) \
    : "memory" \
    )

/* API */
#define gte_readMac(out, macType) CAT(_gte_readMac_, macType)(out)
#define gte_loadIR(in, irType) CAT(_gte_loadIR_, irType)(in)
#define gte_loadSVec(v, vecType) CAT(_gte_loadSVec_, vecType)(v)
#define gte_loadVec(v, vecType) CAT(_gte_loadVec_, vecType)(v)
#define gte_loadRowMatrix(v, rowIndex, matrixType) CAT3(_gte_loadSVecMatrix_, matrixType, _##rowIndex)(v)
#define gte_mulMatrixVec(out, matrixType, vecType) _gte_mulMatrixVec(out, matrixType, vecType, 1)
#define gte_dotProduct(out, rowIndex, matrixType, vecType) CAT(_gte_dotProduct_, rowIndex)(out, matrixType, vecType)
#define gte_leadingZeroes(out, in) _gte_leadingZeroes(out, in)
#define gte_interpolate(out, interpolationType) CAT(_gte_interpolate_, interpolationType)(); _gte_readMac_GTE_VECTOR_MAC(out)