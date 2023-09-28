#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x84)
	{
		for(int i = 0; i < 8; i++)
		{
			printf("0x%02x, ",
				data.levAmbientSound[num]);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}