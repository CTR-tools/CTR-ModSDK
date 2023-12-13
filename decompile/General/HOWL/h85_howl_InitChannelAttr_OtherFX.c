#include <common.h>

void DECOMP_howl_InitChannelAttr_OtherFX(
		struct OtherFX* otherFX, struct ChannelAttr* attr,
		int vol, int LR, int distort)
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
	
	short pitch = otherFX->pitch;
	
	if(distort != 0x80)
		pitch = ((int)pitch * (int)data.distortConst_OtherFX[distort]) >> 0x10;
	
	attr->pitch = pitch;
	
	// ADSR
	attr->ad = 0x80ff;
	attr->sr = 0x1fc2;
	
	attr->spuStartAddr = 
		sdata->howl_spuAddrs[otherFX->spuIndex].spuAddr << 3;
}