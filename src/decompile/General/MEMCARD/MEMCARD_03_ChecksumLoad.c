#include <common.h>

int MEMCARD_NewFunc_AsyncCRC(unsigned char* saveBytes, int len);

int DECOMP_MEMCARD_ChecksumLoad(unsigned char* saveBytes, int len)
{
	int ret = MEMCARD_NewFunc_AsyncCRC(saveBytes, len);
	if (ret == MC_RETURN_PENDING)
		return ret;
	
	int crc = sdata->crc16_checkpoint_status;

	// finishing check
	crc = MEMCARD_CRC16(crc, saveBytes[len-2]);
	crc = MEMCARD_CRC16(crc, saveBytes[len-1]);

	// Will return one of these:
	// 0: MC_RETURN_IOE
	// 1: MC_RETURN_TIMEOUT
	return (unsigned int)(crc != 0);
}