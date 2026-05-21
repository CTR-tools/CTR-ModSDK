// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "INSTANCE.h"

extern char* D_8008D2AC;
extern int func_800310D4(void* pool);
extern void func_80030778(int inst, u32 model, u32 name, u32 thread, u32 flags);

int func_8003086C(u32 param_1, u32 param_2, u32 param_3)
{
    int iVar1;

    iVar1 = func_800310D4(D_8008D2AC + 0x18F8);
    if (iVar1 != 0)
    {
        func_80030778(iVar1, param_1, param_2, param_3, 0xF);
    }
    return iVar1;
}
