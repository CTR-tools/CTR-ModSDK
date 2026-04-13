#include <common.h>

// volume depends on distance from Instance
// to the nearest player's camera
void PlaySound3D(u_int sound, struct Instance *inst)
{
    u_int balance;
    u_int distance;
    u_int length;
    long arc;
    u_char *puVar3;
    int p_index;
    int iVar5;
    int iVar6;
    int currIndex;
    u_int volume;
    VECTOR dir[4];
    u_int playerDistances[4];
    struct GameTracker *gGT = sdata->gGT;

    // assume too far
    distance = 9000;

    for (p_index = 0; p_index < gGT->numPlyrCurrGame; p_index++)
    {
        // Get distance from Instance and each Camera position (pushBuffer)
        dir[p_index].vx = inst->matrix.t[0] - gGT->pushBuffer[p_index].pos[0];
        dir[p_index].vy = inst->matrix.t[1] - gGT->pushBuffer[p_index].pos[1];
        dir[p_index].vz = inst->matrix.t[2] - gGT->pushBuffer[p_index].pos[2];

        // in: vec3, out: squared length
        length = GTE_GetSquaredLength();

        // square root of squared length,
        // get "true" length of vector
        length = SquareRoot0_stub();

        playerDistances[p_index] = length;

        if (length < distance)
        {
            currIndex = p_index;
            distance = length;
        }
    }

    // if still too far
    if (distance == 9000) return;

    GTE_AudioLR_Inst(gGT->pushBuffer[currIndex].matrix_Camera, &dir[currIndex].vx);

    // parameters calculated from previous function
    arc = ratan2(dir[currIndex].vx, -dir[currIndex].vz);

    iVar6 = (arc + 0x800) * -0x100000 >> 0x17;

    if (iVar6 < 0x81)
    {
        iVar5 = -0x100;
        if (-0x81 < p_index)
            goto PLAY_AUDIO;
    }
    else
    {
        iVar5 = 0x100;
    }
    iVar6 = iVar5 - iVar6;

PLAY_AUDIO:

    balance = iVar6 + 0x80;

    // overflow limit
    if ((int)balance < 0)
    {
        balance = 0;
    }
    else if (255 < (int)balance)
    {
        balance = 255;
    }

    if (distance < 301)
    {
        volume = 255;
    }
    // if overflow, rescale
    else
    {
        // Map value from [oldMin, oldMax] to [newMin, newMax]
        volume = DECOMP_VehCalc_MapToRange(distance, 300, 9000, 0xff, 0);
    }

    OtherFX_Play_LowLevel(
		sound & 0xffff, 1,

        // if quadblock under camera is able to make an echo
        ((gGT->cameraDC[currIndex].ptrQuadBlock->quadFlags & 0x80) << 0x18)

			// volume
			| ((volume & 0xff) << 0x10)
	
			// Left/Right
			| (balance & 0xff)
	
			// distortion
			| 0x8000);
}