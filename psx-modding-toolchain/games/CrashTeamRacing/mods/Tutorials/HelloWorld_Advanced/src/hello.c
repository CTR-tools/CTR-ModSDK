#include <common.h>

// draw the string, while rearranging the ordering table,
// to always assert that the text is drawn on top
void PrintText()
{
	struct GameTracker* gGT;
	u_long* backup;

	#if BUILD == SepReview

	// In Sep3, font is wiped in stage 5,
	// and not restored until the end
	if (sdata->Loading.stage >= 5) return;

	#elif BUILD >= UsaRetail

	// In all further builds, font is wiped in 5,
	// and restored before the end of 5
	if(sdata->Loading.stage == 5) return;

	#endif

	gGT = sdata->gGT;

	// backup
	backup = gGT->tileView_UI.ptrOT;

	// modify
	gGT->tileView_UI.ptrOT = gGT->ot_tileView_UI[gGT->swapchainIndex];

	// draw
	DecalFont_DrawLine("Hello World!", 10, 200, 2, 0xffff0000);

	// restore
	gGT->tileView_UI.ptrOT = backup;
}