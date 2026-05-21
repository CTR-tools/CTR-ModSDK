// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "Vehicle.h"

void func_8005E104(struct Driver*, void*, s32);
void func_8005E214(struct Driver*, void*);

void func_8005EA60(void* arg0, struct Driver* d)
{
    s32 temp_a0;
    s32 temp_v1;
    struct QuadBlock* temp_v0;
    register s32 temp_a2 asm("a2");

    if (d->speed >= 0x6401)
    {
        d->speed = 0x6400;
    }
    asm volatile("lw     $12, 0(%0);lw     $13, 4(%0);ctc2   $12, $16;ctc2   $13, $17;lw     $12, 8(%0);lw     $13, 12(%0);lw     $14, 16(%0);ctc2   $12, $18;ctc2   $13, $19;ctc2   $14, $20" : : "r"(&d->matrixFacingDir) : "$12", "$13", "$14");
    temp_a2 = 0x190000;
    asm volatile("mtc2 %0, $0" : : "r"(temp_a2));
    temp_a2 = 0;
    asm volatile("mtc2 %0, $1" : : "r"(temp_a2));
    asm volatile("nop\n\tnop\n\t.word 0x4A4C6012");
    asm volatile("swc2 $25, 0(%0)" : : "r"(&d->originToCenter.v[0]) : "memory");
    asm volatile("swc2 $26, 0(%0)" : : "r"(&d->originToCenter.v[1]) : "memory");
    asm volatile("swc2 $27, 0(%0)" : : "r"(&d->originToCenter.v[2]) : "memory");
    func_8005E104(d, &d->velocity.v[0], temp_a2);
    temp_v0 = d->underDriver;
    if (temp_v0 != 0)
    {
        if (*((u8*)((char*)temp_v0 + 0x38)) == 0xE)
        {
            temp_a0 = d->posCurr.v[1];
            if (temp_a0 >= (-0xFFF))
            {
                temp_v1 = (-0x1000) - temp_a0;
                if (d->velocity.v[1] < temp_v1)
                {
                    d->velocity.v[1] = temp_v1;
                }
            }
        }
    }
    func_8005E214(d, &d->velocity.v[0]);
    *(s32*)&d->normalVecUP.v[0] = 0x10000000;
    d->currBlockTouching = (struct QuadBlock*)0;
    d->normalVecUP.v[2] = 0;
    d->AxisAngle1_normalVec.v[2] = 0;
    *(s32*)&d->AxisAngle1_normalVec.v[0] = 0x10000000;
    d->unkAA = 0;
    d->velocity.v[0] += d->accel.v[0];
    d->velocity.v[1] += d->accel.v[1];
    d->velocity.v[2] += d->accel.v[2];
}
