#include <common.h>

unsigned int DECOMP_MEMCARD_CRC16(unsigned int crc, int nextByte)
{
	int i;
	int bitCheck;
	
	for(i = 7; i >= 0; i--)
	{
		bitCheck = crc << 1;
		crc = bitCheck | nextByte >> i & 1;
		
		if((bitCheck & 0x10000) != 0)
		{
			crc = crc ^ 0x11021;
		}
	}
	
	return crc;
}