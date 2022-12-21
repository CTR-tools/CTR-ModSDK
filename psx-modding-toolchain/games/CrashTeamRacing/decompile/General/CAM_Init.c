#include <common.h>

void CAM_ThTick();
struct Thread* THREAD_BirthWithObject();

void DECOMP_CAM_Init(struct CameraDC* cDC, int cameraID, struct Driver* d, struct Camera110* c110)
{
	// Naughty Dog debug printf
	#if BUILD == SepReview
	printf("camera init\n");
	#endif

	THREAD_BirthWithObject(0x30f, CAM_ThTick, 0,0)->inst = (struct Instance*)cDC;

	memset(cDC, 0, sizeof(struct CameraDC));

	// needed?
	//cDC->cameraID = cameraID;

	cDC->driverToFollow = d;
	cDC->cam110 = c110;

	// dont set cameraMode to zero,
	// memset makes it already zero

	// needed?
	//cDC->flags |= 8;
}