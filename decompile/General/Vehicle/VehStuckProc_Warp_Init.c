#include <common.h>

extern void* PlayerWarpingFuncTable[13];

void DECOMP_VehStuckProc_Warp_Init(struct Thread *th, struct Driver *d)
{
    if (d->kartState == KS_WARP_PAD) return;

    // If you are not in a warp pad

    d->KartStates.Warp.timer = 0x3c;
    d->KartStates.Warp.heightOffset = 0;
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
	
	int engine = data.MetaDataCharacters
		[data.characterIDs[playerID]].engineID;

    EngineAudio_Stop((engine * 4) + playerID);

    // CameraDC, freecam mode
    sdata->gGT->cameraDC[playerID].cameraMode = 3;

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

    // driver is warping
    d->actionsFlagSet |= 0x4000;

    for (i = 0; i < 13; i++)
    {
        d->funcPtrs[i] = PlayerWarpingFuncTable[i];
    }
}

void *PlayerWarpingFuncTable[13] =
{
    NULL,
    NULL,
    NULL,
    VehPhysProc_Driving_Audio,
    VehStuckProc_Warp_PhysAngular,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    VehPhysForce_TranslateMatrix,
    VehFrameProc_Driving,
    VehEmitter_DriverMain
};