#include <common.h>

void RunEntryHook()
{
	for(int i = 0; i < 0x2ae/2; i++)
	{
		printf("0x%04x, 0x%04x,\n", 
			data.ghostScrambleData[i*2+0],
			data.ghostScrambleData[i*2+1]); 
	}
}