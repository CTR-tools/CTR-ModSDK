#include <common.h>

void CS_Thread_ThTick(struct Thread *t)
{
    struct GameTracker *gGT;
    struct Instance *parentInst;
    struct Instance *inst;
    RECT box;

    int iVar5; // Cutscene obj

    iVar5 = t->object;
    gGT = sdata->gGT;

    if (
        // if cutscene thread needs to die
        (CS_Thread_UseOpcode(t->inst, iVar5) != NULL) &&

        // thread is now dead
        (t->flags |= 0x800,

         // if going to credits
         (gGT->gameMode2 & CREDITS) != 0))
    {
        return;
    }

    CS_Thread_MoveOnPath(t);

    CS_Thread_AnimateScale(t);

    CS_Thread_Particles(t);

    // if this is a time animation, not a frame animation
    if ((*(u_short *)(iVar5 + 0x16) & 0x40) != 0)
    {
        //
        CS_Thread_InterpolateFramesMS(t);
    }

    // get instance from thread
    inst = t->inst;

    // if instance exists
    if (inst)
    {

#define SPS \
    ((struct ScratchpadStruct *)0x1f800108)

        if (
            // if parent thread exists
            (t->parentThread != 0) &&
            // some flag
            ((*(u_short *)(iVar5 + 0x16) & 4) == 0))
        {
            parentInst = t->parentThread->inst;

            CS_Instance_GetFrameData(parentInst, parentInst->animIndex, parentInst->animFrame, SPS->Input1.pos[0], SPS->Union.ThBuckColl.distance[0], 0);

            // position from thread
            inst->matrix.t[0] = parentInst->matrix.t[0] + SPS->Input1.pos[0];
            inst->matrix.t[1] = parentInst->matrix.t[1] + SPS->Input1.pos[1];
            inst->matrix.t[2] = parentInst->matrix.t[2] + SPS->Input1.pos[2];

            // some flag
            if ((*(u_short *)(iVar5 + 0x16) & 0x10) == 0)
            {
                // convert 3 rotation shorts into rotation matrix
                ConvertRotToMatrix(&inst->matrix.m[0][0], &SPS->Union.ThBuckColl.distance[0]);
            }
        }

        // cutscene obj flag
        if ((*(u_short *)(iVar5 + 0x16) & 8) != 0)
        {
            CS_Instance_GetFrameData(inst, inst->animIndex, inst->animFrame, &box, 0, 0);

            *(short *)0x800b0b7c = box.y;
            
            if (inst == NULL)
                goto LAB_800ae744;
        }
        // flag
        if (((*(u_short *)(iVar5 + 0x16) & 2) != 0) &&
            (inst->alphaScale = 0, (gGT->timer & 1) != 0))
        {
            inst->alphaScale = (MixRNG_Scramble() & 0x7ff) + 0x400;
        }
    }

LAB_800ae744:
    // if pointer to subtitles exists
    if (0 < *(short *)(iVar5 + 0x32))
    {
        // Ripper Roo's cutscene subtitles

        box.h = DecalFont_DrawMultiLine(sdata->lngStrings[*(short *)(iVar5 + 0x32)],
                                        *(short *)(iVar5 + 0x2e), *(short *)(iVar5 + 0x30),
                                        0x1cc,
                                        *(short *)(iVar5 + 0x34), *(short *)(iVar5 + 0x36));
        box.w = 0x1d8;
        box.x = *(short *)(iVar5 + 0x2e) - 236;
        box.h = +8;
        box.y = *(short *)(iVar5 + 0x30) - 4;

        // Draw 2D Menu rectangle background
        MENUBOX_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
    }

    // if cutscene is over
    if (OVR_233.isCutsceneOver != 0)
    {
        // This thread is now dead
        t->flags |= 0x800;
    }
    return;
}