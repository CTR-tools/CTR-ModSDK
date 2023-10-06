#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x38)
	{
		for(int i = 0; i < 4; i++)
		{
			printf("0x%02x, ", data.data38[num]);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}