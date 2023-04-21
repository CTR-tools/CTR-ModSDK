#include <common.h>

void DECOMP_CAM_ProcessTransition(short* currPos, short* currRot, short* desiredPos, short* desiredRot, short* startPos, short* startRot, int frame)
{
    int deltaRot;

    currPos[0] = desiredPos[0] + (short)(((int)startPos[0] - (int)desiredPos[0]) * frame >> 0xc);
    currPos[1] = desiredPos[1] + (short)(((int)startPos[1] - (int)desiredPos[1]) * frame >> 0xc);
    currPos[2] = desiredPos[2] + (short)(((int)startPos[2] - (int)desiredPos[2]) * frame >> 0xc);

    deltaRot = (int)startRot[0] - (int)desiredRot[0] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }

    currRot[0] = desiredRot[0] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    deltaRot = (int)startRot[1] - (int)desiredRot[1] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }
    currRot[1] = desiredRot[1] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    deltaRot = (int)startRot[2] - (int)desiredRot[2] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }
    currRot[2] = desiredRot[2] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    return;
}