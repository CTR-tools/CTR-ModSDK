#include <common.h> 

int DECOMP_RB_Hazard_InterpolateValue(short currRot, short desiredRot, short rotSpeed)
{
	if (currRot == desiredRot) return currRot;

	int delta = (rotSpeed * sdata->gGT->elapsedTimeMS) >> 5;

	// adjust for range of "short" [0-0xffff]
	// compared to range of degrees [0-0xfff]
	int diff = ((desiredRot - currRot) & 0xfff);
	if (diff == 0) return currRot & 0xfff;
	if (diff > 0x7ff) diff -= 0x1000;
	if (diff < 0) diff = -diff;

	// skip to end, if close enough
	if (diff < rotSpeed) return desiredRot & 0xfff;

	// interpolate
	if (diff < 0) currRot -= delta;
	else currRot += delta;
	return currRot & 0xfff;
}
