// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

u32 VehCalc_FastSqrt(u32 param_1, u32 param_2)
{
    u32 uVar1;
    u32 uVar2;
    int new_var;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    u32 uVar6;

    uVar5 = 0;
    uVar3 = 1 << param_2;
    uVar4 = 1;
    uVar6 = 0;
    while ((uVar3 < param_1) && ((uVar3 << 2) != 0))
    {
        uVar4 = uVar4 + 1;
        uVar3 = uVar3 << 2;
    }

    new_var = param_2 - 1;
    uVar1 = 1 << (uVar4 + new_var);
    while (uVar3 != 0)
    {
        uVar2 = uVar5 << uVar4;
        if (((int)uVar4) < 0)
        {
            uVar2 = uVar5 >> (-uVar4);
        }
        uVar2 = (uVar6 + uVar3) + uVar2;
        if (uVar2 <= param_1)
        {
            uVar6 = uVar2;
            uVar5 = uVar5 + uVar1;
        }
        uVar1 = uVar1 >> 1;
        uVar3 = uVar3 >> 2;
        uVar4 = uVar4 - 1;
    }

    return uVar5;
}
