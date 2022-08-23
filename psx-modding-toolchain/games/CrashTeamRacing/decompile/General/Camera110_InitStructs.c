#include <common.h>

void DECOMP_Camera110_InitStructs(struct Camera110* c110, int id, int total)
{
	// need to add to this later
	#if BUILD == EurRetail
	#define SIZEY_TOP 0x74
	#define SIZEY_1P 0xEC
	#else
	#define SIZEY_TOP 0x6a
	#define SIZEY_1P 0xD8
	#endif
	
	c110->fade_step = 0x88;
	c110->cameraID = id;

	c110->fadeFromBlack_currentValue = 0x1000;
	c110->fadeFromBlack_desiredResult = 0x1000;

	// dont write Projection matrix, waste of time,
	// dont write Aspect Ratio, waste of time,

	// 3P 4P
	if(total > 2)
	{
		c110->distanceToScreen_PREV = 0x80;
		c110->distanceToScreen_CURR = 0x80;

		c110->windowSizeX = 0xfd;
		c110->windowSizeY = SIZEY_TOP;

		c110->windowStartX = (id&1) * 0x103;
		c110->windowStartY = (id>>1) * SIZEY_TOP+4;

		return;
	}

	// 1P 2P
	c110->distanceToScreen_PREV = 0x100;
	c110->distanceToScreen_CURR = 0x100;

	c110->windowSizeX = 0x200;
	c110->windowSizeY = (total == 1) ? SIZEY_1P : SIZEY_TOP;

	c110->windowStartX = 0;
	c110->windowStartY = (id == 0) ? 0 : SIZEY_TOP+4;

	return;
}