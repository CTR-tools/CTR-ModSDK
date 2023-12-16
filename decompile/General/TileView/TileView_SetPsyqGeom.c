#include <common.h>

void DECOMP_TileView_SetPsyqGeom(struct TileView* tileView)
{
	gte_SetGeomOffset(tileView->rect.w/2, tileView->rect.h/2);
	gte_SetGeomScreen(tileView->distanceToScreen_PREV);
	return;
}