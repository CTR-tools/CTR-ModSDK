#include <common.h>

void RB_MaskWeapon_FadeAway(struct Thread *);

void DECOMP_RB_MaskWeapon_ThTick(struct Thread* maskTh)
{
    char i;
    char numPlyr;
    short sVar1;
    struct GameTracker *gGT;
    struct TileView *view;
    int ratio;
    int iVar6;
    struct MaskHeadWeapon* mask;
    struct Instance* maskInst;
    struct Instance* driverInst;
    struct Driver* d;

    gGT = sdata->gGT;

    numPlyr = gGT->numPlyrCurrGame;

    maskInst = maskTh->inst;

    mask = maskInst->thread->object;

    driverInst = maskTh->parentThread->inst;

    d = maskTh->parentThread->object;

    if (d->invisibleTimer == 0)
    {
        // If driver is visible

        // numPlyrCurrGame is not zero
        if (numPlyr)
        {

            for (i = 0; i < numPlyr; i++)
            {
                view = &gGT->tileView[i];
                maskInst->idpp[i].tileView = view;
                mask->maskBeamInst->idpp[i].tileView = view;
            }
        }
    }
    // if driver is invisible
    else
    {

        // if numPlyrCurrGame is not zero
        if (numPlyr)
        {

            for (i = 0; i < numPlyr; i++)
            {
                if (i != d->driverID)
                {
                    maskInst->idpp[i].tileView = NULL;
                    mask->maskBeamInst->idpp[i].tileView = NULL;
                }
            }
        }
    }

    // if driverInst is not reflective
    if ((driverInst->flags & 0x4000) == 0)
    {
        // mask is not reflective
        maskInst->flags &= 0xffffbfff;
    }
    // if driverInst is reflective
    else
    {
        // mask is reflective
        maskInst->flags |= 0x4000;

        // copy split line
        maskInst->vertSplit = driverInst->vertSplit;

        // mask beam is reflective
        mask->maskBeamInst->flags |= 0x4000;

        // copy split line
        mask->maskBeamInst->vertSplit = driverInst->vertSplit;
    }
    maskInst->unk50 = driverInst->unk50;
    maskInst->unk51 = driverInst->unk51;

    // Sine(angle)
    ratio = MATH_Sin((int)mask->rot[1]);

    DAT_1f800130._0_2_ = (short)(((ratio << 6) >> 0xc) * (int)mask->scale >> 0xc);
    DAT_1f800130._2_2_ = ((short *)0x800b2cc4)[(int)mask->maskBeamInst->animFrame] + 0x40;

    // Cosine(angle)
    ratio = MATH_Cos((int)mask->rot[1]);

    DAT_1f800128 = 0;
    DAT_1f800134._0_2_ = (short)(((ratio << 6) >> 0xc) * (int)mask->scale >> 0xc);
    DAT_1f80012a = mask->rot[1];
    DAT_1f80012c._0_2_ = 0;

    if ((mask->rot[2] & 1) == 0)
    {
        // Copy Matrix:
        // To: Mask
        // From: Player
        LHMatrix_Parent(maskInst, driverInst, &DAT_1f800130);

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(&DAT_1f800108, &DAT_1f800128);

        MatrixRotate(&maskInst->matrix, &maskInst->matrix, &DAT_1f800108);
    }
    else
    {
        maskInst->matrix.t[0] = (int)mask->pos[0] + (int)(short)DAT_1f800130;
        maskInst->matrix.t[1] = (int)mask->pos[1] + (int)DAT_1f800130._2_2_;
        maskInst->matrix.t[2] = (int)mask->pos[2] + (int)(short)DAT_1f800134;

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(&maskInst->matrix, &DAT_1f800128);
    }
    DAT_1f800130._0_2_ = 0;
    DAT_1f800130._2_2_ = 0x40;
    DAT_1f800134._0_2_ = 0;
    DAT_1f800128 = 0;
    DAT_1f80012a = mask->rot[1];
    DAT_1f80012c._0_2_ = 0;

    if ((mask->rot[2] & 1) == 0)
    {
        LHMatrix_Parent(mask->maskBeamInst, driverInst, &DAT_1f800130);

        ConvertRotToMatrix(&DAT_1f800108, &DAT_1f800128);

        driverInst = mask->maskBeamInst->matrix;
        MatrixRotate(driverInst, driverInst, &DAT_1f800108);
    }
    else
    {
        mask->maskBeamInst->matrix.t[0] = (int)mask->pos[0];
        mask->maskBeamInst->matrix.t[1] = (int)mask->pos[1] + (int)DAT_1f800130._2_2_;
        mask->maskBeamInst->matrix.t[2] = (int)mask->pos[2] + (int)(short)DAT_1f800134;

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(&mask->maskBeamInst->matrix, &DAT_1f800128);
    }

    // get animFrame
    sVar1 = INSTANCE_GetNumAnimFrames(mask->maskBeamInst, 0);

    // if animation is not finished
    if ((int)mask->maskBeamInst->animFrame < sVar1 - 1)
    {
        // increment animation frame
        mask->maskBeamInst->animFrame += 1;
    }
    // if animation is finished
    else
    {
        // restart animation
        mask->maskBeamInst->animFrame = 0;
    }

    // adjust rotation
    mask->rot[1] += -0x100;

    // If duration is over
    if (mask->duration == 0)
    {
        // end duration
        mask->duration = 0;

        ThTick_SetAndExec(maskTh, RB_MaskWeapon_FadeAway);
    }

    // if duration is not over
    else
    {
        // reduce duration time by milliseconds
        iVar6 = (u_int)mask->duration - gGT->elapsedTimeMS;

        // set new duration
        mask->duration = (short)iVar6;

        // check for negatives
        if (iVar6 * 0x10000 < 0)
        {
            mask->duration = 0;
        }
    }

    // make Beam visible
    mask->maskBeamInst->flags &= 0xffffff7f;

    // Set Beam Scale (x, y, z)
    mask->maskBeamInst->scale[0] = mask->scale;
    mask->maskBeamInst->scale[1] = mask->scale;
    mask->maskBeamInst->scale[2] = mask->scale;

    mask->maskBeamInst->alphaScale = 0;

    // make Head visible
    maskInst->flags &= 0xffffff7f;

    // Set Head Scale (x, y, z)
    maskInst->scale[0] = mask->scale;
    maskInst->scale[1] = mask->scale;
    maskInst->scale[2] = mask->scale;
    return;
}