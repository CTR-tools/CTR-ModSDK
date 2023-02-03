#include <common.h>

void DECOMP_Camera110_InitPsyqGeom(struct Camera110* c110)
{
	gte_SetGeomOffset(c110->rect.w/2, c110->rect.h/2);
	gte_SetGeomScreen(c110->distanceToScreen_PREV);

	return;
}