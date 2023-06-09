#include <common.h>

void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT)
{
	u_char uVar1;
	
	uVar1 = (u_char)sdata->pause_backup_hudFlags;
	if (sdata->pause_state)
	{
		sdata->pause_state = 3;
		gGT->renderFlags = gGT->renderFlags & 0x1000 | sdata->pause_backup_renderFlags & 0xffffefff;
		gGT->hudFlags = uVar1;
	}
	return;
}