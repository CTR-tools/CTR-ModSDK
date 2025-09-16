#include <ctr/math.h>
#include <ctr/gte.h>
#include <ctr/nd.h>

s32 MATH_VectorLength(const SVec3* vector)
{
    gte_loadRowMatrix(vector, GTE_ROW_INDEX_0, GTE_MATRIX_ROT);
    gte_loadSVec(vector, GTE_VECTOR_0);
    s32 lengthSquared;
    gte_dotProduct(&lengthSquared, GTE_ROW_INDEX_0, GTE_MATRIX_ROT, GTE_VECTOR_0);
    return ND_SquareRoot0_stub(lengthSquared);
}
