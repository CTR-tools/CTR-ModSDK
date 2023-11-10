#include <common.h>

void DECOMP_RB_Spider_DrawWebs(struct Thread *t, struct TileView *view)
{
    struct GameTracker *gGT;
    struct PrimMem *primMem;
    MATRIX *m;
    LINE_F2 *p;

    short sVar1;
    u_short uVar2;
    struct InstDef *iVar3;
    int iVar4;
    u_int lineColor;
    u_int *ot;
    int depth;
    u_int *puVar8;
    u_int *piVar9;
    u_int *scratchpad;
    int iVar11;
    int numSpiders;
    int iVar13;
    int iVar16;
    u_int uVar17;
    int iVar19;

    gGT = sdata->gGT;
    primMem = gGT->backBuffer->primMem;

    // if first thread is valid
    if (t != NULL)
    {
        scratchpad = (u_int *)0x1f800000;
        piVar9 = (int *)0x1f800008;

        // all threads
        for (numSpiders = 0; t != NULL; numSpiders++)
        {
            iVar3 = t->inst->instDef;

            sVar1 = iVar3->pos[2];

            uVar2 = iVar3->pos[0];

            iVar4 = t->inst->matrix.t[1];

            // scratchpad meta data for generating Prims
            // puVar10 holds instDef->posY + 0x540,
            // piVar9 holds posX, posY, and posZ
            *scratchpad = (u_int)uVar2 | (iVar3->pos[1] + 0x540) * 0x10000;
            piVar9[-1] = (u_int)uVar2 | (iVar4 + 0x60) * 0x10000;

            *piVar9 = (int)sVar1;

            // advance in scratchpad
            piVar9 = piVar9 + 3;

            t = t->siblingThread;

            // advance in scratchpad
            p = p + 3;
        }

        p = (LINE_F2 *)primMem->curr;

        if (p + (numSpiders * gGT->numPlyrCurrGame * 6) < primMem->endMin100)
        {
            iVar4 = 0x1200;

            // if there are players
            if (-1 < iVar3)
            {
                uVar17 = 0xe1000a20;

                iVar11 = 0x1f800000;

                // loop through all players
                for (iVar3 = gGT->numPlyrCurrGame - 1; iVar3 > -1; iVar3--)
                {
                    m = &view->matrix_ViewProj;

                    // store on GTE
                    gte_SetRotMatrix(m);
                    gte_SetTransMatrix(m);

                    // scratchpad pointer
                    iVar16 = iVar11;

                    if (numSpiders != 0)
                    {
                        // primMem offset 0xC
                        puVar8 = p + 3;

                        // loop through spiders
                        for (; numSpiders > -1; numSpiders--)
                        {
                            // point0
                            gte_ldVXY0(iVar11);
                            gte_ldVZ0(iVar11 + 8);

                            // point1
                            gte_ldVXY1(iVar11 + 4);
                            gte_ldVZ1(iVar11 + 8);

                            // perspective projection
                            gte_rtpt();
                            gte_stsxy01c((long *)(p + 4));

                            // depth of vertex on screen
                            depth = gte_stSZ1();

                            // color (gray)
                            lineColor = 0x3f;

                            // if line is close enough to the screen
                            // to be seen, then generate primitives
                            if (depth - 1U < 0x11ff)
                            {
                                p->r0 = uVar17;
                                p->g0 = 0;
                                if (0xa00 < depth)
                                {
                                    iVar19 = (iVar4 - depth) * 0x3f;
                                    lineColor = iVar19 >> 0xb;
                                    if (iVar19 < 0)
                                    {
                                        lineColor = iVar19 + 0x7ff >> 0xb;
                                    }
                                }

                                // prim offset 0x4,
                                // R,G,B,code(0x42) LINE_F2
                                p->code = 0x42;
                                p->b0 = (lineColor | lineColor << 8 | lineColor << 0x10);

                                depth = depth >> 6;
                                if (0x3ff < depth)
                                {
                                    depth = 0x3ff;
                                }

                                // tileView 0xf4, ptrOT
                                ot = (uint *)(view->ptrOT + depth * 4);

                                // prim header, OT and prim len
                                *(int *)p = *ot | 0x5000000;
                                *ot = (u_int)p & 0xffffff;

                                p = p + 1;
                            }

                            // advance scratchpad
                            iVar11 = iVar11 + 0xc;
                        }
                    }

                    // next tileView
                    view = &gGT->tileView[--iVar3];

                    // reset spider loop count,
                    // reset scratchpad pointer
                    iVar12 = iVar13;
                    iVar11 = iVar16;
                }
            }
            primMem->curr = p;
        }
    }
    return;
}