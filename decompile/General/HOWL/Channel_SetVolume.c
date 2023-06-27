#include <common.h>

void DECOMP_Channel_SetVolume(
	struct ChannelAttr* attr,
	int volume, int LR)
{
	if(volume > 0x3fff)
		volume = 0x3fff;
	
	if(sdata->boolStereoEnabled == 1)
	{
		attr->audioL = (volume * data.volumeLR[0xFF-LR]) >> 8;
		attr->audioR = (volume * data.volumeLR[0x00+LR]) >> 8;
		return;
	}
	
	attr->audioL = volume;
	attr->audioR = volume;
	return;
}