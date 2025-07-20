#include <common.h>

int DECOMP_MEMCARD_ChecksumLoad(unsigned char* saveBytes, int len)
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
	// Option 2: Set ZERO for first-frame of multi-frame load
	// Option 3: Set existing checkpoint from previous frame
	crc = sdata->crc16_checkpoint_status;
	byteIndexStart = sdata->crc16_checkpoint_byteIndex;
	
	// if this is not a one-frame load
	if((sdata->memcardStatusFlags & 8) == 0)
	{	
		// if more than 512 bytes remain
		if (byteIndexEnd > (byteIndexStart + 0x200))
		{
			// cap to 512 bytes, and then continue next frame
			byteIndexEnd = (byteIndexStart + 0x200);
			boolFinishThisFrame = 0;
		}
	}
	
	// run checksum
	for (i = byteIndexStart; i < byteIndexEnd; i++)
	{
		crc = MEMCARD_CRC16(crc, saveBytes[i]);
	}
		
	// save checkpoints for next frame
	if (boolFinishThisFrame == 0)
	{	
		sdata->crc16_checkpoint_status = crc;
		sdata->crc16_checkpoint_byteIndex = byteIndexEnd;
		return MC_RETURN_PENDING;
	}
	
	// finishing check
	crc = MEMCARD_CRC16(crc, saveBytes[byteIndexEnd]);
	crc = MEMCARD_CRC16(crc, saveBytes[byteIndexEnd+1]);

	// Will return one of these:
	// 0: MC_RETURN_IOE
	// 1: MC_RETURN_TIMEOUT
	return (unsigned int)(crc != 0);
}