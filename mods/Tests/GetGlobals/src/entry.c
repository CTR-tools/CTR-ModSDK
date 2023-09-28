#include <common.h>

void RunEntryHook()
{
	int num = 0;
	while(num < 0x100)
	{
		for(int i = 0; i < 0x10; i++)
		{
			printf("0x%X, ", 
				data.distortConst_OtherFX[num]
			); 
			
			num++;
		}
	
		printf("\n");
	}
}