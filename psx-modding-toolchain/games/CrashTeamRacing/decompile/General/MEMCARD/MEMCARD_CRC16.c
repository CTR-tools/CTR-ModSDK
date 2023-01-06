#include <common.h>

unsigned int MEMCARD_CRC16(unsigned int crc, int nextInt)
{
	int i;
	int bitCheck;
	
	for(i = 7; i >= 0; i--)
	{
		bitCheck = crc << 1;
		crc = bitCheck | nextInt >> i & 1;
		
		if((bitCheck & 0x10000) != 0)
		{
			crc = crc ^ 0x11021;
		}
	}
	
	return crc;
}