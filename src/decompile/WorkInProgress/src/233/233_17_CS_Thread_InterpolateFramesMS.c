#include <common.h>

void CS_Thread_InterpolateFramesMS(struct Thread *t)
{
    struct GameTracker *gGT;
    int in_zero;
    int in_at;
    void *endMin100;
    u_int uVar3;
    void *primmemCurr;
    struct Instance *inst;
    int iVar6;
    int local_20;
    u_int local_1c;
    int local_18;
    u_int local_14;

    // instance from thread
    inst = t->inst;

    // CS_Instance_GetFrameData (curr frame)
    CS_Instance_GetFrameData(inst, inst->animIndex, inst->animFrame, &local_20, 0, 0);

    // CS_Instance_GetFrameData (next frame)
    CS_Instance_GetFrameData(inst, inst->animIndex, inst->animFrame, &local_18, 0, 1);

    local_20 = CONCAT22((local_20 >> 0x10) + inst->matrix.t[1], local_20 + inst->matrix.t[0]);
    local_1c &= 0xffff0000 | (local_1c + inst->matrix.t[2]);
    local_18 = CONCAT22((local_18 >> 0x10) + inst->matrix.t[1], local_18 + inst->matrix.t[0]);
    local_14 &= 0xffff0000 | (local_14 + inst->matrix.t[2]);

    primmemCurr = gGT->backBuffer->primMem.curr;

    endMin100 = gGT->backBuffer->primMem.endMin100;

    // if there is room in primMem
    if (primmemCurr + 6 < endMin100)
    {
        // pushBuffer offset 0x28 (400 = 0x190 = 0x168+0x28)
        setCopControlWord(2, 0, gGT->pushBuffer[0].matrix_ViewProj.m[0][0]);
        setCopControlWord(2, 0x800, gGT->pushBuffer[0].matrix_ViewProj.m[0][2]);
        setCopControlWord(2, 0x1000, gGT->pushBuffer[0].matrix_ViewProj.m[1][1]);
        setCopControlWord(2, 0x1800, gGT->pushBuffer[0].matrix_ViewProj.m[2][0]);
        setCopControlWord(2, 0x2000, gGT->pushBuffer[0].matrix_ViewProj.m[2][2]);
        setCopControlWord(2, 0x2800, gGT->pushBuffer[0].matrix_ViewProj.t[0]);
        setCopControlWord(2, 0x3000, gGT->pushBuffer[0].matrix_ViewProj.t[1]);
        setCopControlWord(2, 0x3800, gGT->pushBuffer[0].matrix_ViewProj.t[2]);
        setCopReg(2, in_zero, local_20);
        setCopReg(2, in_at, local_1c);
        setCopReg(2, &local_20, local_18);
        setCopReg(2, endMin100, local_14);

        // Perspective Transformation (Triple)
        copFunction(2, 0x280030);

        primmemCurr[4] = getCopReg(2, 0xc);
        primmemCurr[5] = getCopReg(2, 0xd);
        iVar6 = getCopReg(2, 0x8800);

        if (iVar6 - 1U < 0x11ff)
        {
            uVar3 = 0x3f;
            primmemCurr[1] = 0xe1000a20;
            primmemCurr[2] = 0;
            if (0xa00 < iVar6)
            {
                iVar6 = (0x1200 - iVar6) * 0x3f;
                uVar3 = iVar6 >> 0xb;
                if (iVar6 < 0)
                {
                    uVar3 = iVar6 + 0x7ff >> 0xb;
                }
            }
            primmemCurr[3] = uVar3 | uVar3 << 8 | uVar3 << 0x10 | 0x42000000;
            iVar6 = getCopReg(2, 0x8800) >> 6;
            if (0x3ff < iVar6)
            {
                iVar6 = 0x3ff;
            }
            endMin100 = gGT->pushBuffer[0].ptrOT[iVar6];
            uVar3 = (u_int)primmemCurr & 0xffffff;
            *primmemCurr = *endMin100 | 0x5000000;
            primmemCurr += 6;
            *endMin100 = uVar3;
        }

        // backBuffer->primMem.curr
        gGT->backBuffer->primMem.curr = primmemCurr;
    }
}