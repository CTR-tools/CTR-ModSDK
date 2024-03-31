#include <common.h>

void CS_Thread_ThTick(struct Thread *t)
{
    struct Instance* parentInst;
    struct Instance* inst;
    RECT box;

    struct CutsceneObj* cs = t->object; // Cutscene obj
    struct GameTracker* gGT = sdata->gGT;
    
    // if cutscene thread needs to die
    if ((CS_Thread_UseOpcode(t->inst, cs) != NULL) &&

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
    if ((cs->flags & 0x40) != 0)
    {
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
            ((cs->flags & 4) == 0))
        {
            parentInst = t->parentThread->inst;

            CS_Instance_GetFrameData(parentInst, parentInst->animIndex, parentInst->animFrame, SPS->Input1.pos[0], SPS->Union.ThBuckColl.distance[0], 0);

            // position from thread
            inst->matrix.t[0] = parentInst->matrix.t[0] + SPS->Input1.pos[0];
            inst->matrix.t[1] = parentInst->matrix.t[1] + SPS->Input1.pos[1];
            inst->matrix.t[2] = parentInst->matrix.t[2] + SPS->Input1.pos[2];

            // some flag
            if ((cs->flags & 0x10) == 0)
            {
                // convert 3 rotation shorts into rotation matrix
                ConvertRotToMatrix(&inst->matrix.m[0][0], &SPS->Union.ThBuckColl.distance[0]);
            }
        }

        // cutscene obj flag
        if ((cs->flags & 8) != 0)
        {
            CS_Instance_GetFrameData(inst, inst->animIndex, inst->animFrame, &box, 0, 0);

            OVR_233.VertSplitLine = box.y;
            
            if (inst == NULL)
                goto DRAW_SUBTITLES;
        }

        // flag
        if (((cs->flags & 2) != 0) &&
            (inst->alphaScale = 0, (gGT->timer & 1) != 0))
        {
            inst->alphaScale = (DECOMP_MixRNG_Scramble() & 0x7ff) + 0x400;
        }
    }

DRAW_SUBTITLES:
    // if pointer to subtitles exists
    if (0 < cs->Subtitles.lngIndex)
    {
        // Ripper Roo's cutscene subtitles

        box.h = DecalFont_DrawMultiLine(sdata->lngStrings[cs->Subtitles.lngIndex],
                                        cs->Subtitles.textPos[0], cs->Subtitles.textPos[1],
                                        460,
                                        cs->Subtitles.font, cs->Subtitles.colors);
        box.w = 472;
        box.x = cs->Subtitles.textPos[0] - 236;
        box.h =+ 8;
        box.y = cs->Subtitles.textPos[1] - 4;

        // Draw 2D Menu rectangle background
        RECTMENU_DrawInnerRect(&box, 4, gGT->backBuffer->otMem.startPlusFour);
    }

    // if cutscene is over
    if (OVR_233.isCutsceneOver != 0)
    {
        // This thread is now dead
        t->flags |= 0x800;
    }
}