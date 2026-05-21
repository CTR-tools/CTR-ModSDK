// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

extern struct GameTracker* D_8008D2AC;
extern short func_80058F54(int, int, int);
extern void func_8005F89C(int, int, int);

void VehPhysProc_SpinStop_PhysAngular(u32 param_1, struct Driver* d)
{
    struct GameTracker* puVar1;
    short new_var2;
    short* new_var;
    u16 uVar2;
    int new_var3;
    short uVar3;

    new_var3 = ((int)d->ampTurnState) * D_8008D2AC->elapsedTimeMS;
    new_var = &d->angle;
    puVar1 = D_8008D2AC;
    uVar2 = ((*new_var) + ((short)(new_var3 >> 0xd))) & 0xfff;
    *((u16*)new_var) = uVar2;
    d->rotCurr.y = (uVar2 + d->turnAngleCurr) + d->unk3D4[0];
    uVar3 = func_80058F54((int)d->rotCurr.w, (puVar1->elapsedTimeMS << 5) >> 5, 0);
    puVar1 = D_8008D2AC;
    d->rotCurr.w = uVar3;
    uVar3 = func_80058F54((int)d->turnAngleCurr, (puVar1->elapsedTimeMS << 7) >> 5, 0);
    d->turnAngleCurr = uVar3;
    func_8005F89C((int)&d->matrixMovingDir, (int)&d->AxisAngle1_normalVec, (int)(new_var2 = *new_var));
    return;
}
