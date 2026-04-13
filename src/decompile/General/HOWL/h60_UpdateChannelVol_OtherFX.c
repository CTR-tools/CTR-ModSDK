#include <common.h>

void DECOMP_UpdateChannelVol_OtherFX(
	struct OtherFX* otherFX, struct ChannelAttr* attr, int vol, int LR)
{
	int otherVol;
	
	otherVol = sdata->vol_FX;
	
	if((otherFX->flags & 4) != 0)
		otherVol = sdata->vol_Voice;
	
	DECOMP_Channel_SetVolume(
		attr,
		(otherVol * otherFX->volume * vol) >> 10,
		LR
	);
}