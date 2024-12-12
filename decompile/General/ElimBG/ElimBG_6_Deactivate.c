#include <common.h>

void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT)
{
	//it's written this way for bytebudget reasons.
	u_char backup = (u_char)sdata->pause_backup_hudFlags;
	if (sdata->pause_state != 0)
	{ //if game is not paused
		sdata->pause_state = 3; //this is the last frame of pause
		gGT->renderFlags = gGT->renderFlags & 0x1000 | (sdata->pause_backup_renderFlags & 0xffffefff);
		gGT->hudFlags = backup;
	}
}