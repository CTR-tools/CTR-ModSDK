#include <ctr/test.h>

#ifdef TEST_COLL_IMPL

void TEST_COLL_ProjectPointToEdge(const SVec3* v1, const SVec3* v2, const SVec3* point, const SVec3* ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_ProjectPointToEdge));
    SVec3 expected;
    typedef void (*Func)(SVec3* out, const SVec3* v1, const SVec3* v2, const SVec3* point);
    Func func = (Func) TEST_WRAPPER;
    func(&expected, v1, v2, point);
    PrintSVectorDiff("COLL_ProjectPointToEdge", &expected, ret);
    PatchFunction_End(index);
}


void TEST_COLL_BarycentricTest(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3, const SVec3* pos, s32 ret)
{
    const u32 index = PatchFunction_Beg((u32*)(&ND_COLL_BarycentricTest));
    typedef s32 (*Func)(TestVertex* t, const CollVertex* v1, const CollVertex* v2, const CollVertex* v3);
    Func func = (Func) TEST_WRAPPER;
    const s32 expected = func(t, v1, v2, v3);
    PrintSVectorDiff("COLL_BarycentricTest", &t->pos, pos);
    if (expected != ret) { ND_printf("[COLL_BarycentricTest] Test Failed:\nExpected: %d\nResult: %d\n", expected, ret); }
    PatchFunction_End(index);
}

#endif // TEST_COLL_IMPL