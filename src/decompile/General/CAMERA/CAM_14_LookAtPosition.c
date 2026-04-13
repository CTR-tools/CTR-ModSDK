#include <common.h>

void DECOMP_CAM_LookAtPosition(int scratchpad, int *positions, short *desiredPos, short *desiredRot)
{
	// One IF results in less instructions than,
	// this: data.Spin360_heightOffset_driverPos[sdata->gGT->numPlyrCurrGame]);
	// the instruction save is required to fit the byte budget
	
	int yOffset = 0x40;
	if(sdata->gGT->numPlyrCurrGame != 2)
		yOffset = 0x60;
	
    int dirX = desiredPos[0] - (positions[0] >> 8);
    int dirY = desiredPos[1] - ((positions[1] >> 8) + yOffset);
    int dirZ = desiredPos[2] - (positions[2] >> 8);

    // Store dirX, dirY, dirZ in scratchpad
    *(int *)(scratchpad + 0x24c) = dirX;
    *(int *)(scratchpad + 0x250) = dirY;
    *(int *)(scratchpad + 0x254) = dirZ;

    int distance = SquareRoot0_stub(dirX * dirX + dirZ * dirZ);

    // rotations
    desiredRot[0] = 0x800 - (short)ratan2(dirY, distance);
    desiredRot[1] = (short)ratan2(dirX, dirZ);
    desiredRot[2] = 0;

    return;
}