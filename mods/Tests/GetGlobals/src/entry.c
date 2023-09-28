#include <common.h>

void RunEntryHook()
{
	int num = 0;
	while(num < 9*12)
	{
		for(int i = 0; i < 12; i++)
		{
			printf("0x%04X, ", 
				data.noteFrequency[num]
			); 
			
			num++;
		}
	
		printf("\n");
	}
}