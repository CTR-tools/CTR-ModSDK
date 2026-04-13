#include <common.h>

// Usage: elapsed(frameStart, &frameStart)
// will overwrite new frameStart, and return
// elapsed time since previous frameStart
int DECOMP_Timer_GetTime_Elapsed(int oldVal, int* retVal)
{
	int newVal = DECOMP_Timer_GetTime_Total();
	
	if(retVal != 0)
		*retVal = newVal;
	
	// impossible?
	if(newVal < oldVal)
		newVal += 0xc7e18;
	
	return newVal - oldVal;
}