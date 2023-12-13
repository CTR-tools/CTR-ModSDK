#include <common.h>

void DECOMP_howl_InitChannelAttr_EngineFX(
		struct EngineFX* engineFX, struct ChannelAttr* attr,
		int vol, int LR, int distort)
{
	DECOMP_Channel_SetVolume(
		attr,
		(sdata->vol_FX * engineFX->volume * vol) >> 10,
		LR
	);
	
	short pitch = engineFX->pitch;
	
	if(distort != 0x80)
		pitch = ((unsigned int)pitch * data.distortConst_Engine[distort]) >> 0x10;
	
	attr->pitch = pitch;
	
	// ADSR
	attr->ad = 0x80ff;
	attr->sr = 0x1fc2;
	
	attr->spuStartAddr = 
		sdata->howl_spuAddrs[engineFX->spuIndex].spuAddr << 3;
}