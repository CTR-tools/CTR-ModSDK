#include <common.h>

void DECOMP_UpdateChannelVol_EngineFX(
	struct EngineFX* engineFX, struct ChannelAttr* attr, int vol, int LR)
{
	DECOMP_Channel_SetVolume(
		attr,
		(sdata->vol_FX * engineFX->volume * vol) >> 10,
		LR
	);
}