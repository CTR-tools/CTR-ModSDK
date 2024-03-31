#include <common.h>

void DECOMP_PushBuffer_SetPsyqGeom(struct PushBuffer* pb)
{
	gte_SetGeomOffset(pb->rect.w/2, pb->rect.h/2);
	gte_SetGeomScreen(pb->distanceToScreen_PREV);
	return;
}