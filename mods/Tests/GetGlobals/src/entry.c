#include <common.h>

void RunEntryHook()
{
	int num = 0;
	while(num < 0x14)
	{
		printf("0x%02x, ",
			data.advHubSongSetBytes[num]);
		
		num++;
	}
	
	printf("\n");
}