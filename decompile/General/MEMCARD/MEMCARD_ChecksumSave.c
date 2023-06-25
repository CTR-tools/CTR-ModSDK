#include <common.h>

void DECOMP_MEMCARD_ChecksumSave(unsigned char* saveBytes, int len)
{
	int i;
	int crc = 0;
	int nextByte;
	
	for(i = 0; i < len; i++)
	{
		nextByte = 0;
		if(i < len-2) nextByte = (int)saveBytes[i];
		crc = MEMCARD_CRC16(crc, nextByte);
	}
	
	// write checksum to data (last 2 bytes),
	// swap endians to throw off hackers,
	// which didn't really throw anyone off at all
	saveBytes[len-2] = (char)(crc>>8);
	saveBytes[len-1] = (char)(crc);
}