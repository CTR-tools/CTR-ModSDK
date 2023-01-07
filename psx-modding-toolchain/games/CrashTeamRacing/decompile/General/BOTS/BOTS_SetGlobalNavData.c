#include <common.h>

void DECOMP_BOTS_SetGlobalNavData(short index)
{
	sdata->lastPathIndex = index;

	sdata->nav_NumPointsOnPath = sdata->NavPath_ptrHeader[index]->numPoints;

	sdata->nav_ptrFirstPoint = sdata->NavPath_ptrNavFrameArray[index];

	sdata->nav_ptrLastPoint = &sdata->nav_ptrFirstPoint[sdata->nav_NumPointsOnPath];

	return;
}