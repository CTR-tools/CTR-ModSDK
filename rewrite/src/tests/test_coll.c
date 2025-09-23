#include <ctr/test.h>

#ifdef TEST_COLL_IMPL

void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge));
    SVec3 expected;
    ND_COLL_ProjectPointToEdge(&expected, v1, v2, point);
    PrintSVectorDiff("COLL_ProjectPointToEdge", &expected, ret);
    PatchFunction_End(index);
}

#endif // TEST_COLL_IMPL