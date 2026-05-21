// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "UI.h"

u32 func_80054A08(int param_1, int param_2, int param_3)
{
    switch (param_3)
    {
    case 1:
        return (u32)*(u8*)(param_1 + param_2);
    case 2:
        return (int)*(short*)(param_1 + param_2);
    case 4:
        return *(u32*)(param_1 + param_2);
    }
    return 0;
}
