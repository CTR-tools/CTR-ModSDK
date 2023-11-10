#include <common.h>

// real Naughty Dog name
int DECOMP_howl_VolumeGet(int type)
{
	if(type == 0) return sdata->vol_FX;
	if(type == 1) return sdata->vol_Music;
	if(type == 2) return sdata->vol_Voice;
	
	return 0;
}