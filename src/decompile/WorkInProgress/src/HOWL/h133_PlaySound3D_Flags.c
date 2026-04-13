#include <common.h>

// Play 3D Audio with flags
// audio changes in Left and Right speakers
void PlaySound3D_Flags(u_int *soundID_count, u_int param_2, struct Instance *inst)
{
    u_int length;
    u_int balance;
    u_int volume;
    long arc;
    int p_index;
    int iVar5;
    int iVar6;
    int currIndex;
    u_int distance;
    VECTOR dir[4];
    u_int playerDistances[4];
    struct GameTracker *gGT = sdata->gGT;

    if ((*soundID_count != 0) && ((*soundID_count & 0xffff) != param_2))
    {
        OtherFX_Stop1(*soundID_count);

        *soundID_count = 0;
    }

    if ((int)param_2 == -1) return;

    // maximum distance a 3D sound
    // can be heard from, 9000 units
    distance = 9000;

    // find closest camera to the instance
    for (p_index = 0; p_index < gGT->numPlyrCurrGame; p_index++)
    {
        dir[p_index].vx = inst->matrix.t[0] - gGT->pushBuffer[p_index].pos[0];
        dir[p_index].vy = inst->matrix.t[1] - gGT->pushBuffer[p_index].pos[1];
        dir[p_index].vz = inst->matrix.t[2] - gGT->pushBuffer[p_index].pos[2];

        length = GTE_GetSquaredLength();

        // square root of squared length,
        // get "true" length of vector
        length = SquareRoot0_stub();

        // save length in array
        // (waste, never used)
        playerDistances[p_index] = length;

        // if this camera is closer to the instance
        // than the closest known camera
        if (length < distance)
        {
            // save new camera index
            currIndex = p_index;

            // set new shortest distance
            distance = length;
        }
    }

    // if no camera is close enough to hear the sound,
    // then return, and do not play the sound
    if (distance == 9000) return;

    GTE_AudioLR_Inst(gGT->pushBuffer[currIndex].matrix_Camera, &dir[currIndex].vx);

    // parameters calculated from previous function
    arc = ratan2(dir[currIndex].vx, -dir[currIndex].vz);

    iVar6 = (arc + 0x800) * -0x100000 >> 0x17;

    if (iVar6 < 0x81)
    {
        iVar5 = -0x100;
        if (-0x81 < iVar6)
            goto PLAY_AUDIO;
    }
    else
    {
        iVar5 = 0x100;
    }
    iVar6 = iVar5 - iVar6;

PLAY_AUDIO:

    // convert range of:
    // left: negative
    // mid: zero
    // right: positive

    // to range of:
    // left: 0x0
    // mid: 0x80
    // right: 0xff
    balance = p_index + 0x80;

    // if L/R is less than 0.0
    if ((int)balance < 0)
    {
        // can't go lower than 0.0
        balance = 0;
    }
    // If L/R is more than 1.0
    else if (0xff < (int)balance)
    {
        // cap at 1.0
        balance = 0xff;
    }

    if (distance < 0x12d)
    {
        volume = 0xff;
    }

    else
    {
        // Map value from [oldMin, oldMax] to [newMin, newMax]
        // inverting newMin and newMax will give an inverse range mapping
        volume = DECOMP_VehCalc_MapToRange(distance, 300, 9000, 0xff, 0);
    }

    // if sound hasn't played
    if (*soundID_count == 0)
    {
        *soundID_count = OtherFX_Play_LowLevel(param_2 & 0xffff, 0,

                                       // if quadblock under camera is able to make an echo
                                       ((gGT->cameraDC[currIndex].ptrQuadBlock->quadFlags & 0x80) << 0x18)

                                           // volume
                                           | (volume & 0xff) << 0x10

                                           // left/right
                                           | balance & 0xff

                                           // distortion
                                           | 0x8000);
    }
    // modify sound already playing
    else
    {
        OtherFX_Modify(*soundID_count,

                       // if quadblock under camera is able to make an echo
                       ((gGT->cameraDC[currIndex].ptrQuadBlock->quadFlags & 0x80) << 0x18)

                           // volume
                           | (distance & 0xff) << 0x10

                           // left/right
                           | length & 0xff

                           // distortion
                           | 0x8000);
    }
}