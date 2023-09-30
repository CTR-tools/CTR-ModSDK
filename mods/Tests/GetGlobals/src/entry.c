#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x400)
	{
		for(int i = 0; i < 8; i++)
		{
			printf("{0x%04x, 0x%04x}, ",
				(unsigned short)data.trigApprox[num].sin,
				(unsigned short)data.trigApprox[num].cos
				);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}