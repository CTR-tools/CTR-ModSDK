#include <common.h>

void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT)
{	
	if (sdata->pause_state == 0)
		return;
	
	sdata->pause_state = 3;
	gGT->renderFlags &= 0x1000;
	gGT->renderFlags |= (sdata->pause_backup_renderFlags & 0xffffefff);
	gGT->hudFlags = (u_char)sdata->pause_backup_hudFlags;
}