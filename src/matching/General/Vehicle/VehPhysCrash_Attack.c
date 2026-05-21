// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

extern short D_80086E84[];
int D_8008D9F4 = 0;
extern void func_8002E760(u32, int);
extern void func_8002CBE8(int, int, int);
extern void func_80028468(int, int);

int VehPhysCrash_Attack(struct Driver* d1, struct Driver* d2, int param_3, int param_4)
{
    int iVar1;

    if ((d1->actionsFlagSet & 0x800000) == 0)
    {
        if ((d2->actionsFlagSet & 0x800000) != 0)
        {
            d1->ChangeState_param2 = 2;
            *(char*)&d1->ChangeState_param4 = 6;
            d1->ChangeState_param3 = (int)d2;
            if (((param_3 != 0) && (d1->kartState != '\x06')) &&
                (d1->invincibleTimer == 0))
            {
                func_8002E760((u32)((u16*)&d1->actionsFlagSet)[1] & 1, 0xff);
                func_8002CBE8(1, (int)(short)D_80086E84[d1->driverID], 0x10);
            }
        }
        if ((d2->instBubbleHold != 0) && (d1->instBubbleHold == 0))
        {
            iVar1 = *(int*)(*(int*)((char*)d2->instBubbleHold + 0x6c) + 0x30);
            *(u16*)(iVar1 + 6) = *(u16*)(iVar1 + 6) | 8;
            d2->instBubbleHold = 0;
            d1->ChangeState_param2 = 2;
            *(char*)&d1->ChangeState_param4 = 0;
            d1->ChangeState_param3 = (int)d2;
            if ((param_3 != 0) &&
                ((d1->kartState != '\x06' && (d1->invincibleTimer == 0))))
            {
                func_8002E760((u32)((u16*)&d1->actionsFlagSet)[1] & 1, 0xff);
                if (param_4 != 0)
                {
                    func_80028468(0x4f, 1);
                }
                func_8002CBE8(1, (int)(short)D_80086E84[d1->driverID], 0x10);
            }
        }
        if ((((0xa00 < D_8008D9F4) &&
              (d2->reserves != 0)) &&
             ((d2->actionsFlagSet & 0x200) != 0)) &&
            (d1->reserves == 0))
        {
            d2->forcedJump_trampoline = 2;
            d1->ChangeState_param2 = 3;
            *(char*)&d1->ChangeState_param4 = 5;
            d1->ChangeState_param3 = (int)d2;
        }
    }
    return param_3;
}
