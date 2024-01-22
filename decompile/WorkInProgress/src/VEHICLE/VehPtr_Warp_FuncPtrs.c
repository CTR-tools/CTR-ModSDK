#include <common.h>

// Not sure what the params of MoveDustPuff yet

// Add DustPuff particle to warp pad
void VehPtr_Warp_AddDustPuff1(struct ScratchpadStruct *sps)
{
    struct GameTracker *gGT = sdata->gGT;

    // if even frame don't spawn
    if (gGT->timer & 1) return;

    struct Particle *p = Particle_CreateInstance(0, gGT->iconGroup[1], &data.emSet_Warppad[0]);

    if (p == NULL) return;

    // position variables
    for (char i = 0; i < 3; i++)
        p->axis[i].startVal += sps->Input1.pos[i];
}

// not doing AddDustPuff2 yet

// animate rotation and scale in warppad
void DECOMP_VehPtr_Warp_PhysAngular(struct Thread *th, struct Driver *d)
{
    int uVar1;
    short sVar2;
    int iVar3;
    int *ksWarp;
    short pos[3];

    // get instance from driver object
    struct Instance* inst = d->instSelf;

    ksWarp = &d->KartStates.Warp;

    // if driver is visible
    if ((inst->flags & HIDE_MODEL) == 0)
    {
        // height + 0x100
        iVar3 = d->posCurr[1] + 0x100;

        d->KartStates.Warp.beamHeight = iVar3;
        
        if (iVar3 < d->KartStates.Warp.quadHeight)
        {
            d->KartStates.Warp.beamHeight = d->KartStates.Warp.quadHeight;
        }

        // if driver is visible
        if ((inst->flags & HIDE_MODEL) == 0)
        {
            // stop particle spawning
            d->KartStates.Warp.numParticle -= 100;
        }

        // add dust puff
        VehPtr_Warp_AddDustPuff2(d, ksWarp);
    }

    int timer = ksWarp[0] + FPS_DOUBLE(26);
    ksWarp[0] = timer;

    if (timer < FPS_DOUBLE(801))
    {
        // interpolate until scale is [0x12c0, 0x960, 0x12c0],
        // car is wide and short

        for (char i = 0 ; i < 3;i++)
            inst->scale[i] = InterpBySpeed(inst->scale[i], 120, 4800 >> (i & 1));

        uVar1 = d->posCurr[2] + 0x800;

        if (d->quadBlockHeight + 0x8000 <= d->posCurr[1])
            goto LAB_80068db0;
    }
    else
    {
        // cap to 800
        ksWarp[0] = FPS_DOUBLE(800);

        d->engineRevState = 2;

        // interpolate until scale is [0, 24000, 0],
        // car is tall and thin

        for (char i = 0 ; i < 3;i++)
            inst->scale[i] = InterpBySpeed(inst->scale[i], (i == 1) ? 3200 : 600, 24000 * (i & 1));

        // if scale shrinks to zero
        if (inst.scale[0] == 0)
        {
            // if car is visible
            if ((inst->flags & HIDE_MODEL) == 0)
            {
                // position above kart
                pos[0] = (short)(d->posCurr[0] >> 8);
                pos[1] = (short)(d->KartStates.Warp.quadHeight >> 8) + 0x40;
                pos[2] = (short)(d->posCurr[2] >> 8);

                FLARE_Init(&pos);
            }

            // make invisible
            inst->flags |= HIDE_MODEL;

            goto LAB_80068db0;
        }

        uVar1 = d->KartStates.Warp.unk4 - 0x1800;
        d->KartStates.Warp.unk4 = uVar1;

        uVar1 = d->posCurr[1] + uVar1;
    }

    // set current height
    d->posCurr[1] = uVar1;

LAB_80068db0:

    // drift angle = ((drift angle + warp timer + 0x800) & 0xfff) - 0x800
    sVar2 = (d->turnAngleCurr + (short)(ksWarp[0]) + 0x800U & 0xfff) - 0x800;
    d->turnAngleCurr = sVar2;

    // cameraRotY = ??? + kart angle + drift angle
    d->rotCurr.y = d->unk3D4[0] + d->angle + sVar2;

    // driver is warping
    d->actionsFlagSet |= 0x4000;
}

void *PlayerWarpingFuncTable[13] =
    {
        NULL,
        NULL,
        NULL,
        VehPtr_Driving_Audio,
        DECOMP_VehPtr_Warp_PhysAngular,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        OnRender,
        OnAnimate_Driving,
        VehParticle_DriverMain};

void DECOMP_VehPtr_Warp_Init(struct Thread *th, struct Driver *d)
{
    if (d->kartState == KS_WARP_PAD) return;

    // If you are not in a warp pad

    d->KartStates.Warp.timer = 0x3c;
    d->KartStates.Warp.unk4 = 0;
    d->KartStates.Warp.quadHeight = d->quadBlockHeight;

    // Warp sound?
    OtherFX_Play(0x97, 1);

    char i;

    //  (three sounds)
    for (i = 0; i < 3; i++)
    {
        OtherFX_Stop1(d->driverAudioPtrs[i]);
        d->driverAudioPtrs[i] = NULL;
    }

    u_char playerID = d->driverID;

    // engineID from metadata, given characterID
    EngineAudio_Stop((playerID + (data.MetaDataCharacters[data.characterIDs[playerID]].engineID * 4)) & 0xffff);

    // CameraDC, freecam mode
    sdata->gGT->cameraDC[playerID] = 3;

    // driver -> instSelf
    struct Instance *inst = d->instSelf;

    // instance flags, now reflective
    inst->flags | 0x4000;

    // vertical line for split or reflection
    inst->vertSplit = (short)(d->quadBlockHeight >> 8);

    // you are now in a warp pad
    d->kartState = KS_WARP_PAD;

    d->speed = 0;
    d->speedApprox = 0;

    for (i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerWarpingFuncTable[i];
    }

    // driver is warping
    d->actionsFlagSet |= 0x4000;
}