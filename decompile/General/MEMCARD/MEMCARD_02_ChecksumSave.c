#include <common.h>

#if 1 // 132
// Rewrite looks like this
// Potentially allowing inline optimizations
// Problem: Does not use multi-frame checksum (like loading)
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
#endif

#if 0 // 156
// Closer resembles the loading function
void DECOMP_MEMCARD_ChecksumSave(unsigned char* saveBytes, int len)
{
	int i;
	int crc;
	int byteIndexEnd;
	int byteIndexStart;
	int boolFinishThisFrame = 1;
	
	// Leave 2 bytes at the end,
	// the checksum is stored there
	len -= 2;
	byteIndexEnd = len;
	
	// Option 1: Set ZERO for a one-frame load
	crc = 0;
	byteIndexStart = 0;
	
	// run checksum
	for (i = byteIndexStart; i < byteIndexEnd; i++)
	{
		crc = MEMCARD_CRC16(crc, (int)saveBytes[i]);
	}
	
	// finishing check
	crc = MEMCARD_CRC16(crc, 0);
	crc = MEMCARD_CRC16(crc, 0);
	
	// write checksum to data (last 2 bytes),
	// swap endians to throw off hackers,
	// which didn't really throw anyone off at all
	saveBytes[i+0] = (char)(crc>>8);
	saveBytes[i+1] = (char)(crc);
}
#endif

#if 0 // 156
// Original game looked like this
void DECOMP_MEMCARD_ChecksumSave(unsigned char* saveBytes, int len)
{
	int i;
	int crc = 0;
	
	for(i = 0; i < len-2; i++)
	{
		crc = MEMCARD_CRC16(crc, (int)saveBytes[i]);
	}
	
	crc = MEMCARD_CRC16(crc, 0);
	crc = MEMCARD_CRC16(crc, 0);
	
	// write checksum to data (last 2 bytes),
	// swap endians to throw off hackers,
	// which didn't really throw anyone off at all
	saveBytes[i+0] = (char)(crc>>8);
	saveBytes[i+1] = (char)(crc);
}
#endif