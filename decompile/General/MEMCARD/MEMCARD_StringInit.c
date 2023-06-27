#include <common.h>

char *DECOMP_MEMCARD_StringInit(int slotIndex, char *dstString)
{
	if (!dstString)
	{
		// if no string is provided, use global string
		dstString = &sdata->s_memcardDirHeader[0];
	}

	// *dstString = (((int)slotIndex >> 4 & 1U) + 0x30) * 0x10000 |
	//          ((slotIndex & 3) + 0x30) * 0x1000000 | 0x7562;
	*(int *)&dstString[0] = 0x30307562; // bu00
	dstString[3] = '0' + slotIndex; 	// bu0X where X = slotIndex

	// ':' and null terminator
	*(short *)&dstString[4] = ':';

	// result is: "bu00:\0"
	return dstString;
}