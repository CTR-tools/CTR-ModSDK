#include <common.h>

// Shared between VolumeSet and Get
extern int* settingsPtrArr[3];

// real Naughty Dog name
int DECOMP_howl_VolumeGet(int type)
{
	return *settingsPtrArr[type];
}

// Reminder, ONLY use sdata_static
// for compile-time pointers, NEVER runtime
int* settingsPtrArr[3] =
{
	&sdata_static.vol_FX,
	&sdata_static.vol_Music,
	&sdata_static.vol_Voice
};