#include <common.h>

// Shared between VolumeSet and Get
extern int* settingsPtrArr[3];

extern void (*settingsFuncArr[3])();

void DECOMP_howl_VolumeSet(int type, unsigned char vol)
{
	if(*settingsPtrArr[type] == vol) return;
	*settingsPtrArr[type] = vol;
	
	DECOMP_Smart_EnterCriticalSection();
	
	settingsFuncArr[type]();
	
	DECOMP_Smart_ExitCriticalSection();
}

void (*settingsFuncArr[3])() =
{
	DECOMP_UpdateChannelVol_EngineFX_All,
	DECOMP_UpdateChannelVol_Music_All,
	DECOMP_UpdateChannelVol_OtherFX_All
};