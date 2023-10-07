#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x850)
	{
		for(int i = 0; i < 0x10; i++)
		{
			printf("0x%02x, ", data.data850[num]);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}