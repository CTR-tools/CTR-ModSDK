#include <common.h>

void DECOMP_ElimBG_Deactivate(struct GameTracker *gGT)
{
	u_char backup = (u_char)sdata->pause_backup_hudFlags;
	
	if (sdata->pause_state)
	{
		sdata->pause_state = 3;
		gGT->renderFlags &= 0x1000 | (backup & 0xffffefff);
		gGT->hudFlags = backup;
	}
}