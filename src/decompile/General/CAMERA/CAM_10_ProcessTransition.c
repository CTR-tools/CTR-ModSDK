#include <common.h>

void DECOMP_CAM_ProcessTransition(short* currPos, short* currRot, short* startPos, short* startRot, short* endPos, short* endRot, int frame)
{
    int deltaRot;

    currPos[0] = startPos[0] + (short)(((int)endPos[0] - (int)startPos[0]) * frame >> 0xc);
    currPos[1] = startPos[1] + (short)(((int)endPos[1] - (int)startPos[1]) * frame >> 0xc);
    currPos[2] = startPos[2] + (short)(((int)endPos[2] - (int)startPos[2]) * frame >> 0xc);

    deltaRot = (int)endRot[0] - (int)startRot[0] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }

    currRot[0] = startRot[0] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    deltaRot = (int)endRot[1] - (int)startRot[1] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }
    currRot[1] = startRot[1] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    deltaRot = (int)endRot[2] - (int)startRot[2] & 0xfff;
    if (0x7ff < deltaRot)
    {
        deltaRot -= 0x1000;
    }
    currRot[2] = startRot[2] + (short)((int)(deltaRot * frame) >> 0xc) & 0xfff;
    return;
}