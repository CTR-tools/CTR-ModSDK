// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

u16 D_8008D9EC = 0;
u16 D_8008D9EE = 0;
u16 D_8008D9F0 = 0;
extern u16 D_8009AE38[3][3];
extern int D_8009AE28[3];
extern void func_8006C2A4(int*, int*);

void VehPhysCrash_AI(struct Driver* d, int* param_2)
{
    int iVar1;
    int iVar2;
    int* new_var;

    // NOTE: NavFrame pointer is reloaded each access to preserve match —
    // a local temp or `d->botData.botNavFrame` form prevents gcc from
    // emitting the same single-load + 3-byte-read sequence the target has.
    D_8008D9EC = ((u16)(*((u8*)((*((int*)((char*)d + 0x5a4))) + 6)))) << 4;
    D_8008D9EE = ((u16)(*((u8*)((*((int*)((char*)d + 0x5a4))) + 7)))) << 4;
    D_8008D9F0 = ((u16)(*((u8*)((*((int*)((char*)d + 0x5a4))) + 8)))) << 4;
    func_8006C2A4((int*)D_8009AE38, (int*)(&D_8008D9EC));
    D_8009AE28[0] = ((int)(((u32)D_8009AE38[0][2]) << 0x10)) >> 0x14;
    D_8009AE28[1] = ((int)(((u32)D_8009AE38[1][2]) << 0x10)) >> 0x14;
    D_8009AE28[2] = ((int)(((u32)D_8009AE38[2][2]) << 0x10)) >> 0x14;
    iVar1 = (((D_8009AE28[0] * (*param_2)) + (D_8009AE28[1] * param_2[1])) + (D_8009AE28[2] * param_2[2])) >> 8;
    d->botData.unk5bc.ai.ai_speedLinear = iVar1;
    d->botData.unk5bc.ai.ai_accelAxis[0] = (*param_2) - ((D_8009AE28[0] * (*(new_var = &iVar1))) >> 8);
    iVar1 = D_8009AE28[2] * iVar1;
    iVar2 = param_2[2];
    d->botData.botFlags = d->botData.botFlags | 8;
    d->botData.unk5bc.ai.ai_accelAxis[2] = iVar2 - (iVar1 >> 8);
    return;
}
