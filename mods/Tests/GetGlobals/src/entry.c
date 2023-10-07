#include <common.h>

void RunEntryHook()
{
	printf("\n");
	printf("\n");
	printf("\n");
	
	int num = 0;
	{
		for(int i = 0; i < 0x10; i++)
		{
			printf(".name_Debug = 0x%08x,\n", data.MetaDataCharacters[i].name_Debug);
		}
		
		printf("\n");
	}
	
	printf("\n");
	printf("\n");
	printf("\n");
}