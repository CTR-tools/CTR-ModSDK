#include <common.h>

void RunEntryHook()
{
	for(int i = 0; i < 0x10; i++)
	{
		printf("0x%02X,\n", 
			data.pauseScreenStrip[i]
			); 
	}
}