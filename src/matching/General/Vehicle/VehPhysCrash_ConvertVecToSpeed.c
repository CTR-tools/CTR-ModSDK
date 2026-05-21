// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

extern int func_80059070(int, int);
extern int func_8007173C(int, int);

void VehPhysCrash_ConvertVecToSpeed(struct Driver* d, int* param_2)
{
    int extraout_var_00;
    int extraout_var_01;
    int x;
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;

    iVar4 = func_80059070(((*param_2) * (*param_2)) + (param_2[2] * param_2[2]), 0x10);
    x = iVar4;
    d->speed = ((u32)func_80059070((((*param_2) * (*param_2)) + (param_2[1] * param_2[1])) + (param_2[2] * param_2[2]), 0x10)) >> 8;
    x = func_8007173C(param_2[1] << 8, x);
    d->axisRotationY = (short)x;
    x = func_8007173C(*param_2, param_2[2]);
    d->axisRotationX = (short)x;
    iVar4 = ((((*param_2) * ((int)d->matrixMovingDir.m[0][1])) + (param_2[1] * ((int)d->matrixMovingDir.m[1][1]))) + (param_2[2] * ((int)d->matrixMovingDir.m[2][1]))) >> 0xc;
    iVar1 = (((int)d->matrixMovingDir.m[0][1]) * iVar4) >> 0xc;
    iVar2 = (((int)d->matrixMovingDir.m[1][1]) * iVar4) >> 0xc;
    iVar3 = (((int)d->matrixMovingDir.m[2][1]) * iVar4) >> 0xc;
    extraout_var_00 = ((u32)func_80059070(((iVar1 * iVar1) + (iVar2 * iVar2)) + (iVar3 * iVar3), 0x10)) >> 8;
    d->jumpHeightCurr = extraout_var_00;
    if (iVar4 < 0)
    {
        d->jumpHeightCurr = -extraout_var_00;
    }
    iVar1 = (*param_2) - iVar1;
    iVar2 = param_2[1] - iVar2;
    iVar3 = param_2[2] - iVar3;
    extraout_var_01 = ((u32)func_80059070(((iVar1 * iVar1) + (iVar2 * iVar2)) + (iVar3 * iVar3), 0x10)) >> 8;
    d->speedApprox = extraout_var_01;
    if ((((iVar1 * d->matrixMovingDir.m[0][2]) + (iVar2 * d->matrixMovingDir.m[1][2])) + (iVar3 * d->matrixMovingDir.m[2][2])) < 0)
    {
        d->speedApprox = -extraout_var_01;
    }
    return;
}
