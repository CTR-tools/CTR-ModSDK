#include <common.h>

void DECOMP_CAM_SetDesiredPosRot(struct CameraDC* cDC, short* pos, short* rot)
{
	int i;

	// save desired pos and rot
	for(i = 0; i < 3; i++)
	{
		cDC->transitionTo.pos[i] = pos[i];
		cDC->transitionTo.rot[i] = rot[i];
	}

	// 1 second, 30 frames
	cDC->frameCounterTransition = FPS_DOUBLE(0x1e);

	cDC->unk8E = 0;
	cDC->unk8C = 0x1000;

	cDC->flags |= 0x200;
}