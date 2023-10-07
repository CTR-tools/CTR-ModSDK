#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 0x94)
	{
		for(int i = 0; i < 8; i++)
		{
			printf("0x%02x, ", data.unk_between_hudStructPtr_menuRow_arcadeEndRace[num]);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}