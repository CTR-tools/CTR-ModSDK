// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "INSTANCE.h"

extern int func_8001D094(int modelID);

void func_80030ED4(int param_1, int param_2)
{
    int iVar1;
    int* puVar2;
    int iVar3;

    iVar3 = 0;
    if (0 < param_2)
    {
        puVar2 = (int*)(param_1 + 0x2C);
        do
        {
            iVar1 = func_8001D094((int)*(short*)(puVar2[-7] + 0x10));
            if (iVar1 != 0 && *(int*)(iVar1 + 4) != 0)
            {
                (*(void (**)(int))(iVar1 + 4))(*puVar2);
            }
            iVar3 = iVar3 + 1;
            puVar2 = puVar2 + 0x10;
        } while (iVar3 < param_2);
    }
}
