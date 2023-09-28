#include <common.h>

void RunEntryHook()
{
	int num = 0;
	while(num < 0x40)
	{
		for(int i = 0; i < 8; i++)
		{
			printf("0x%04X, ", 
				data.distortConst_Music[num]
			); 
			
			num++;
		}
	
		printf("\n");
	}
}