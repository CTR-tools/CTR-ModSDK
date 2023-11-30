#include <common.h>

void DECOMP_TileView_Init(struct TileView* tileView, int id, int total)
{
	// need to add to this later
	#if BUILD == EurRetail
	#define SIZEY_TOP 0x74
	#define SIZEY_1P 0xEC
	#else
	#define SIZEY_TOP 0x6a
	#define SIZEY_1P 0xD8
	#endif
	
	tileView->fade_step = 0x88;
	tileView->cameraID = id;

	tileView->fadeFromBlack_currentValue = 0x1000;
	tileView->fadeFromBlack_desiredResult = 0x1000;

	// dont write Projection matrix, waste of time,
	// dont write Aspect Ratio, waste of time,

	// 3P 4P
	if(total > 2)
	{
		tileView->distanceToScreen_PREV = 0x80;
		tileView->distanceToScreen_CURR = 0x80;

		tileView->rect.w = 0xfd;
		tileView->rect.h = SIZEY_TOP;

		tileView->rect.x = (id&1) * 0x103;
		tileView->rect.y = (id>>1) * (SIZEY_TOP+4);

		return;
	}

	// 1P 2P
	tileView->distanceToScreen_PREV = 0x100;
	tileView->distanceToScreen_CURR = 0x100;

	tileView->rect.w = 0x200;
	tileView->rect.h = (total == 1) ? SIZEY_1P : SIZEY_TOP;

	tileView->rect.x = 0;
	tileView->rect.y = (id == 0) ? 0 : SIZEY_TOP+4;
	
	return;
}