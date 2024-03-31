#include <common.h>

void RB_MaskWeapon_FadeAway(struct Thread *);

void DECOMP_RB_MaskWeapon_ThTick(struct Thread* maskTh)
{
    char i;
    char numPlyr;
    short sVar1;
    struct GameTracker *gGT;
    struct PushBuffer* pb;
    int ratio;
    int iVar6;
    struct MaskHeadWeapon* mask;
    struct Instance* maskInst;
	struct Instance* maskBeamInst;
    struct Instance* driverInst;
    struct Driver* d;

    gGT = sdata->gGT;
    numPlyr = gGT->numPlyrCurrGame;

    mask = maskTh->object;
    maskInst = maskTh->inst;
	maskBeamInst = mask->maskBeamInst;

    d = maskTh->parentThread->object;
    driverInst = maskTh->parentThread->inst;

    if (d->invisibleTimer == 0)
    {
        for (i = 0; i < numPlyr; i++)
        {
            pb = &gGT->pushBuffer[i];
            maskInst->idpp[i].pushBuffer = pb;
            maskBeamInst->idpp[i].pushBuffer = pb;
        }
    }
	
    else
    {
        for (i = 0; i < numPlyr; i++)
        {
            if (i != d->driverID)
            {
                maskInst->idpp[i].pushBuffer = NULL;
                maskBeamInst->idpp[i].pushBuffer = NULL;
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
        maskBeamInst->flags |= 0x4000;

        // copy split line
        maskBeamInst->vertSplit = driverInst->vertSplit;
    }
    maskInst->unk50 = driverInst->unk50;
    maskInst->unk51 = driverInst->unk51;

    // Sine(angle)
    ratio = MATH_Sin((int)mask->rot[1]);
    *(short*)0x1f800130 = (short)(((ratio << 6) >> 0xc) * (int)mask->scale >> 0xc);

    // Cosine(angle)
    ratio = MATH_Cos((int)mask->rot[1]);
    *(short*)0x1f800134 = (short)(((ratio << 6) >> 0xc) * (int)mask->scale >> 0xc);
	
    *(short*)0x1f800132 = ((short *)0x800b2cc4)[(int)maskBeamInst->animFrame] + 0x40;
	
    *(short*)0x1f800128 = 0;
    *(short*)0x1f80012a = mask->rot[1];
    *(short*)0x1f80012c = 0;

    if ((mask->rot[2] & 1) == 0)
    {
        // Copy Matrix:
        // To: Mask
        // From: Player
        LHMatrix_Parent(maskInst, driverInst, 0x1f800130);

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(0x1f800108, 0x1f800128);

        MatrixRotate(&maskInst->matrix, &maskInst->matrix, 0x1f800108);
    }
    else
    {
        maskInst->matrix.t[0] = (int)mask->pos[0] + *(short*)0x1f800130;
        maskInst->matrix.t[1] = (int)mask->pos[1] + *(short*)0x1f800132;
        maskInst->matrix.t[2] = (int)mask->pos[2] + *(short*)0x1f800134;

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(&maskInst->matrix, 0x1f800128);
    }
    
	*(short*)0x1f800130 = 0;
    *(short*)0x1f800132 = 0x40;
    *(short*)0x1f800134 = 0;
	
    *(short*)0x1f800128 = 0;
    *(short*)0x1f80012a = mask->rot[1];
    *(short*)0x1f80012c = 0;

    if ((mask->rot[2] & 1) == 0)
    {
        LHMatrix_Parent(maskBeamInst, driverInst, 0x1f800130);

        ConvertRotToMatrix(0x1f800108, 0x1f800128);

        driverInst = maskBeamInst->matrix;
        MatrixRotate(driverInst, driverInst, 0x1f800108);
    }
    else
    {
        maskBeamInst->matrix.t[0] = (int)mask->pos[0];
        maskBeamInst->matrix.t[1] = (int)mask->pos[1] + *(short*)0x1f800132;
        maskBeamInst->matrix.t[2] = (int)mask->pos[2];

        // convert 3 rotation shorts into rotation matrix
        ConvertRotToMatrix(&maskBeamInst->matrix, 0x1f800128);
    }

    // get animFrame
    sVar1 = INSTANCE_GetNumAnimFrames(maskBeamInst, 0);

    // if animation is not finished
    if ((int)maskBeamInst->animFrame < sVar1 - 1)
    {
        // increment animation frame
        maskBeamInst->animFrame += 1;
    }
    // if animation is finished
    else
    {
        // restart animation
        maskBeamInst->animFrame = 0;
    }

    // adjust rotation
    mask->rot[1] += -0x100;

    // If duration is over
    if (mask->duration == 0)
    {
        // end duration
        mask->duration = 0;

        ThTick_SetAndExec(maskTh, RB_MaskWeapon_FadeAway);
		return;
    }

    // if duration is not over

    // reduce duration time by milliseconds
    iVar6 = (u_int)mask->duration - gGT->elapsedTimeMS;

    // set new duration
    mask->duration = (short)iVar6;

    // check for negatives
    if (iVar6 * 0x10000 < 0)
    {
        mask->duration = 0;
    }

    // make Beam visible
    maskBeamInst->flags &= 0xffffff7f;

    // Set Beam Scale (x, y, z)
    maskBeamInst->scale[0] = mask->scale;
    maskBeamInst->scale[1] = mask->scale;
    maskBeamInst->scale[2] = mask->scale;

    maskBeamInst->alphaScale = 0;

    // make Head visible
    maskInst->flags &= 0xffffff7f;

    // Set Head Scale (x, y, z)
    maskInst->scale[0] = mask->scale;
    maskInst->scale[1] = mask->scale;
    maskInst->scale[2] = mask->scale;
    return;
}