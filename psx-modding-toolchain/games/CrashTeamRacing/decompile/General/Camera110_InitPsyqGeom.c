#include <common.h>
#include <gte.h>

void DECOMP_Camera110_InitPsyqGeom(struct Camera110* c110)
{
	gte_SetGeomOffset(c110->windowSizeX/2, c110->windowSizeY/2);
	gte_SetGeomScreen(c110->distanceToScreen_PREV);

	return;
}