#include <common.h>

void RunEntryHook()
{
	int num = 0;
	while(num < 0xb)
	{
		for(int i = 0; i < 0xb; i++)
		{
			printf("0x%02X, ", 
				data.opcodeOffset[num]
			); 
			
			num++;
		}
	
		printf("\n");
	}
}