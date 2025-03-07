#include <common.h>

int DECOMP_Timer_GetTime_Total()
{
	int sysClock =
		GetRCnt(0xf2000001) +
		sdata->rcntTotalUnits;
		
	return (sysClock * 1000) / 0x147e;
}