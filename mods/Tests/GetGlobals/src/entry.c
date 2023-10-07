#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x12*3)
	{
		for(int i = 0; i < 3; i++)
		{
			printf("0x%08x, ", data.RelicTime[num]);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}