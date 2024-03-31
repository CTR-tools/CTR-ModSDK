#include <common.h>

void DECOMP_CAM_Init(struct CameraDC* cDC, int cameraID, struct Driver* d, struct PushBuffer* pb)
{
	// Naughty Dog debug printf
	#if BUILD == SepReview
	printf("camera init\n");
	#endif
	
#ifndef REBUILD_PS1
	DECOMP_PROC_BirthWithObject(0x30f, CAM_ThTick, 0,0)->inst = (struct Instance*)cDC;
#endif

	memset(cDC, 0, sizeof(struct CameraDC));

	// needed or L2 breaks
	cDC->cameraID = cameraID;

	cDC->driverToFollow = d;
	cDC->pushBuffer = pb;

	// dont set cameraMode to zero,
	// memset makes it already zero

	// needed?
	//cDC->flags |= 8;
}