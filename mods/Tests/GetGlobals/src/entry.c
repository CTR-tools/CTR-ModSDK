#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	while(num < 9)
	{
		//for(int i = 0; i < 2; i++)
		{
			printf("0x%04x, 0x%04x,",
				data.Options_HighlightBar[num].posY,
				data.Options_HighlightBar[num].sizeY);
		
			num++;
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}