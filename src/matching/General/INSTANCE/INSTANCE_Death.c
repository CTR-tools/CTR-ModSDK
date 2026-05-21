// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "INSTANCE.h"

extern char* D_8008D2AC;
void func_8003112C(void* pool, u32 instance);

void func_80030AA8(u32 param_1)
{
    func_8003112C(D_8008D2AC + 0x18F8, param_1);
}
