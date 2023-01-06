#include <common.h>

void MEMCARD_ChecksumSave(unsigned char* saveBytes, int len)
{
	int i;
	int crc = 0;
	
	for(i = 0; i < len-2; i++)
	{
		crc = MEMCARD_CRC16(crc, (int)saveBytes[i]);
	}
	
	// finalize CRC twice
	crc = MEMCARD_CRC16(crc, 0);
	crc = MEMCARD_CRC16(crc, 0);
	
	*(unsigned short*)&saveBytes[i] = 
		(unsigned short)crc;
}