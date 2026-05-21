// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "UI.h"

void func_8004EC18(short* param_1, short param_2, short param_3, short param_4, short param_5, int param_6, short param_7)
{
    int iVar1;
    int iVar2;
    iVar2 = param_6 * (((int)param_2) - ((int)param_4));
    iVar1 = (int)param_7;
    ;
    *param_1 = param_4 + ((short)(iVar2 / iVar1));
    param_1[1] = param_5 + ((short)((param_6 * (((int)param_3) - ((int)param_5))) / iVar1));
}
