#include <common.h>

void DECOMP_BOTS_InitNavPath(struct GameTracker* gGT, short index)
{
	struct NavHeader* nh = 0;
	struct NavHeader** LevNavTable = gGT->level1->LevNavTable;
	
	if(LevNavTable != 0)
	{
		// nullptr on Nitro Court
		nh = LevNavTable[index];
	}
	
	// if path exists
	if(nh != 0)
	{
		// grab the data
		sdata->NavPath_ptrHeader[index] = nh;
		
		sdata->NavPath_ptrNavFrameArray[index] = 
			NAVHEADER_GETFRAME(sdata->NavPath_ptrHeader[index]);

		// if data is outdated
		if(sdata->NavPath_ptrHeader[index]->magicNumber != -0x1303)
		{
			// never mind then
			sdata->NavPath_ptrHeader[index]->numPoints = 0;
		}
	}
	
	// if no path data is found
	else
	{
		// use a template, which cancels AIs
		sdata->NavPath_ptrHeader[index] = &sdata->blank_NavHeader;
		
		sdata->NavPath_ptrNavFrameArray[index] = 
			NAVHEADER_GETFRAME(&sdata->blank_NavHeader);

		// dont bother setting numNavPoints in header to zero,
		// it's already zero
	}

	// save number of points
	sdata->nav_NumPointsOnPath = sdata->NavPath_ptrHeader[index]->numPoints;

	// global last point
	sdata->nav_ptrLastPoint = &sdata->NavPath_ptrNavFrameArray[index][sdata->nav_NumPointsOnPath];

	// header last point
	sdata->NavPath_ptrHeader[index]->last = sdata->nav_ptrLastPoint;

	// global first point
	sdata->nav_ptrFirstPoint = sdata->NavPath_ptrNavFrameArray[index];

	return;
}