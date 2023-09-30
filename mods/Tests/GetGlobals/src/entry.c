#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x40)
	{
		for(int i = 0; i < 8; i++)
		{
			printf("0x%08x, ",
				(unsigned int)data.memcardIcon_PsyqHand[num]
				);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}