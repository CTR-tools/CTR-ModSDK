#include <common.h>

void DECOMP_BOTS_InitNavPath(struct GameTracker* gGT, short index)
{
	// if level has no data
	if(gGT->level1->LevNavHeader == 0)
	{
		// use a template, which cancels AIs
		sdata.NavPath_ptrHeader[index] = &sdata.blank_NavHeader;
		sdata.NavPath_ptrNavFrameArray[index] = &sdata.blank_NavHeader.frame[0];

		// dont bother setting numNavPoints in header to zero,
		// it's already zero
	}

	// if data exists
	else
	{
		// grab the data
		sdata.NavPath_ptrHeader[index] = gGT->level1->LevNavHeader[index];
		sdata.NavPath_ptrNavFrameArray[index] = &sdata.NavPath_ptrHeader[index]->frame[0];

		// if data is outdated
		if(sdata.NavPath_ptrHeader[index]->magicNumber != -0x1303)
		{
			// never mind then
			sdata.NavPath_ptrHeader[index]->numPoints = 0;
		}
	}

	// save number of points
	sdata.nav_NumPointsOnPath = sdata.NavPath_ptrHeader[index]->numPoints;

	// global last point
	sdata.nav_ptrLastPoint = &sdata.NavPath_ptrNavFrameArray[index][sdata.nav_NumPointsOnPath];

	// header last point
	sdata.NavPath_ptrHeader[index]->last = sdata.nav_ptrLastPoint;

	// global first point
	sdata.nav_ptrFirstPoint = sdata.NavPath_ptrNavFrameArray[index];

	return;
}