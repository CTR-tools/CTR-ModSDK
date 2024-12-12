#include <common.h>

void DECOMP_LOAD_StringToUpper(char* path)
{
	for(char* letter = &path[0]; letter[0] != 0; letter++)
	{
		// if lowercase letter
		if((unsigned int)(letter[0] - 0x61) < 0x1a)
		{
			// uppercase
			letter[0] -= 0x20;
		}
	}		
}