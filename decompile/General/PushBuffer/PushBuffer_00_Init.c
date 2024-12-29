#include <common.h>

void DECOMP_PushBuffer_Init(struct PushBuffer* pb, int id, int total)
{
	// need to add to this later
	#if BUILD == EurRetail
	#define SIZEY_TOP 0x74
	#define SIZEY_1P 0xEC
	#else
	#define SIZEY_TOP 0x6a
	#define SIZEY_1P 0xD8
	#endif
	
	pb->fade_step = 0x88;
	pb->cameraID = id;

	pb->fadeFromBlack_currentValue = 0x1000;
	pb->fadeFromBlack_desiredResult = 0x1000;

	// dont write Projection matrix, waste of time,
	// dont write Aspect Ratio, waste of time,

	// 3P 4P
	if(total > 2)
	{
		pb->distanceToScreen_PREV = 0x80;
		pb->distanceToScreen_CURR = 0x80;

		pb->rect.w = 0xfd;
		pb->rect.h = SIZEY_TOP;

		pb->rect.x = (id&1) * 0x103;
		pb->rect.y = (id>>1) * (SIZEY_TOP+4);

		return;
	}

	// 1P 2P
	pb->distanceToScreen_PREV = 0x100;
	pb->distanceToScreen_CURR = 0x100;

#ifdef USE_NEW2P

	pb->rect.w = (total == 1) ? 0x200 : 0xfd;
	pb->rect.h = SIZEY_1P;

	pb->rect.x = (id&1) * 0x103;
	pb->rect.y = 0;

// default 4:3
#else

	pb->rect.w = 0x200;
	pb->rect.h = (total == 1) ? SIZEY_1P : SIZEY_TOP;

	pb->rect.x = 0;
	pb->rect.y = (id == 0) ? 0 : SIZEY_TOP+4;
	
#endif
	
	return;
}