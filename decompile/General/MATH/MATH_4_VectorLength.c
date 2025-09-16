#include <ctr_gte.h>
#include <ctr_math.h>
#include <common.h>

int DECOMP_Math_VectorLength(SVec3* vector)
{
    gte_loadRowMatrix(vector, GTE_ROW_INDEX_0, GTE_MATRIX_ROT);
    gte_loadSVec(vector, GTE_VECTOR_0);
    int lengthSquared;
    gte_dotProduct(&lengthSquared, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0);
    return SquareRoot0_stub(lengthSquared);
}