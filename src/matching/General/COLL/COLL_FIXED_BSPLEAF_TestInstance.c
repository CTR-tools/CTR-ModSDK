// ===================================================
// Should be score 0, needs types analysis/replacement
// ===================================================

#include "COLL.h"

void func_8001D0C4(struct ScratchpadStruct*, struct BSP*);

void fun_8001d610(struct BSP* node, struct ScratchpadStruct* sps)
{
    int iVar1;
    int iVar2;
    struct BSP* piVar3;
    struct BSP* piVar4;
    struct BSP* temp;

    temp = node->data.leaf.bspHitboxArray;
    if (temp == ((struct BSP*)0x0)) return;

    piVar3 = temp;
    piVar4 = piVar3 + 1;

    // Sentinel check reads flag+id as a single u32 — matching the
    // target's `lw` (not `lhu` for flag alone).
    while (*((int*)piVar3) != 0)
    {
        iVar1 = sps->numInstHitboxesHit + (-1);
        if ((-1) < iVar1)
        {
            iVar2 = (iVar1 * 4) + (int)sps;
            do
            {
                iVar1 = iVar1 + (-1);
                do { if (piVar3 == (*((struct BSP**)(iVar2 + 0x88)))) { goto LAB_8001d750; } iVar2 = iVar2 + (-4); } while (0);
            }
            while ((-1) < iVar1);
        }
        if ((((((((*((u8*)piVar3)) & 0x80) == 0) || (piVar3->data.hitbox.instDef == ((struct InstDef*)0))) || (((*((u32*)((*((int*)((char*)piVar3->data.hitbox.instDef + 0x2c))) + 0x28))) & 0xf) != 0)) && ((sps->bbox.min[0] <= piVar3->box.max[0]) && (piVar3->box.min[0] <= sps->bbox.max[0]))) && ((sps->bbox.min[1] <= piVar3->box.max[1]) && ((piVar3->box.min[1] <= sps->bbox.max[1]) && (sps->bbox.min[2] <= piVar3->box.max[2])))) && (piVar3->box.min[2] <= sps->bbox.max[2]))
        {
            func_8001D0C4(sps, piVar3);
        }
        LAB_8001d750:
        piVar3 = piVar3 + 1;
        piVar4 = piVar4 + 1;
    }
}
