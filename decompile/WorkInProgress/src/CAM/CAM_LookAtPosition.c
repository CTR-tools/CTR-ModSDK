#include <common.h>

void DECOMP_CAM_LookAtPosition(int scratchpad, int *positions, short *desiredPos, short *desiredRot)
{
    int dirX = desiredPos[0] - (positions[0] >> 8);
    int dirY = desiredPos[1] - ((positions[1] >> 8) + data.Spin360_heightOffset_driverPos[sdata->gGT->numPlyrCurrGame]);
    int dirZ = desiredPos[2] - (positions[2] >> 8);

    int rotY = ratan2(dirX, dirZ);

    int distance = SquareRoot0(dirX * dirX + dirZ * dirZ);
    
    int elevation = ratan2(dirY, distance);

    // rotations
    desiredRot[0] = 0x800 - (short)elevation;
    desiredRot[1] = (short)rotY;
    desiredRot[2] = 0;

    // Store dirX, dirY, dirZ in scratchpad
    *(int *)(scratchpad + 0x24c) = dirX;
    *(int *)(scratchpad + 0x250) = dirY;
    *(int *)(scratchpad + 0x254) = dirZ;

    return;
}