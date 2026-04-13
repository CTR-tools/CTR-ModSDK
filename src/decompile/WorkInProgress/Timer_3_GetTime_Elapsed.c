#include <common.h>

// Rig so elapsed time is constantly 30fps,
// This means we can test against OG game without framerate interfering for BOTS
int DECOMP_Timer_GetTime_Elapsed(int oldVal, int* retVal)
{
	return 100;
}