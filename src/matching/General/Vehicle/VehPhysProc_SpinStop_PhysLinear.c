// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

extern void func_8006181C(int, int);

void VehPhysProc_SpinStop_PhysLinear(u32 param_1, struct Driver* d)
{
    func_8006181C(param_1, (int)d);
    d->baseSpeed = 0;
    d->fireSpeed = 0;
    return;
}
