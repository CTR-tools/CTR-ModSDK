// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "INSTANCE.h"

extern void* func_800309A4(int p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6, u32 p7);

void* func_80030A50(u32* param_1)
{
    return func_800309A4(*param_1, param_1[1], param_1[2], param_1[3], param_1[4], param_1[5], param_1[6]);
}
