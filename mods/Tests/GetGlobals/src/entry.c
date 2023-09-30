#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x140)
	{
		for(int i = 0; i < 16; i++)
		{
			printf("0x%02x, ",
				(unsigned char)data.data144_beforeSaveDataString[num]
				);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}