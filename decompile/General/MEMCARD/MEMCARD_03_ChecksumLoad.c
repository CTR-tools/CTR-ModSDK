#include <common.h>

unsigned int DECOMP_MEMCARD_ChecksumLoad(unsigned char* saveBytes, int len)
{
	int i;
	int crc;
	int byteIndexEnd;
	int byteIndexStart;
	int memcardStatusFlags;
		
	// load checkpoints (both zero on first call),
	// also group all $gp variables together, save asm
	crc = sdata->crc16_checkpoint_status;
	byteIndexStart = sdata->crc16_checkpoint_byteIndex;
	memcardStatusFlags = sdata->memcardStatusFlags;
	
	// end of memcard "before" checksum,
	// checksum goes in last 2 bytes
	len -= 2;
	byteIndexEnd = len;
	
	// if not running full checksum in one frame
	if((memcardStatusFlags & 8) == 0)
	{	
		// if more than 512 bytes remain, cap it
		if(byteIndexEnd > (byteIndexStart + 0x200))
			byteIndexEnd = (byteIndexStart + 0x200);
	}
	
	// checksum 10% of the profile
	for (i = byteIndexStart; i < byteIndexEnd; i++)
	{
		crc = MEMCARD_CRC16(crc, saveBytes[i]);
	}
	
	// at this point, 'i' equals byteIndexEnd,
	// but can't use 'i' cause that's too much asm
	
	// save checkpoints
	sdata->crc16_checkpoint_status = crc;
	sdata->crc16_checkpoint_byteIndex = byteIndexEnd;
	
	// if end is not reached
	if(byteIndexEnd != len) return 7;
	
	// finalize checksum twice (dont loop)
	crc = MEMCARD_CRC16(crc, saveBytes[byteIndexEnd]);
	crc = MEMCARD_CRC16(crc, saveBytes[byteIndexEnd+1]);	
	return (unsigned int)(crc != 0);
}