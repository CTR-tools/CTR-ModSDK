#include <common.h>

void DECOMP_howl_VolumeSet(int type, unsigned char vol)
{
	if(type == 0)
	{
		if(sdata->vol_FX == vol) return;
		sdata->vol_FX = vol;
		
		DECOMP_Smart_EnterCriticalSection();
		DECOMP_UpdateChannelVol_EngineFX_All();
	}
	
	else if(type == 1)
	{
		if(sdata->vol_Music == vol) return;
		sdata->vol_Music = vol;
		
		DECOMP_Smart_EnterCriticalSection();
		DECOMP_UpdateChannelVol_Music_All();
	}
	
	else // == 2
	{
		if(sdata->vol_Voice == vol) return;
		sdata->vol_Voice = vol;
		
		DECOMP_Smart_EnterCriticalSection();
		DECOMP_UpdateChannelVol_OtherFX_All();
	}
	
	DECOMP_Smart_ExitCriticalSection();
}