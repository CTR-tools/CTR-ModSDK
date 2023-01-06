#include <common.h>

char* MEMCARD_StringInit(int slotIndex, char* dstString)
{
	// if no string is provided
	if(dstString == 0)
	{
		// use global string
		dstString = &sdata->s_memcardDirHeader[0];
	}
	
	// bu00
	*(int*)&dstString[0] = 0x30307562;

	// slot index
	dstString[3] = '0'+slotIndex;
	
	// ':' and null terminator
	*(short*)&dstString[4] = ':';
	
	// result is:
	// "bu00:\0"
}