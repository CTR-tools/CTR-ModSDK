#include <common.h> 

int DECOMP_RB_Hazard_InterpolateValue(short currRot, short desiredRot, short rotSpeed)
{
	if (currRot == desiredRot) return currRot;

	int delta = (rotSpeed * sdata->gGT->elapsedTimeMS) >> 5;

	int diff = ((desiredRot - currRot) & 0xfff);
	if (diff == 0) return currRot & 0xfff;
	if (diff > 0x7ff) diff -= 0x1000;
	
	if (desiredRot < 0) 
		desiredRot = -desiredRot;

	if (rotSpeed > desiredRot)
		return desiredRot & 0xfff;

	if (diff < 0) currRot -= delta;
	else currRot += delta;

	return currRot & 0xfff;
}
