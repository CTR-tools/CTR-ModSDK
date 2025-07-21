#include <common.h>

int MEMCARD_NewFunc_AsyncCRC(unsigned char* saveBytes, int len);

int DECOMP_MEMCARD_ChecksumSave(unsigned char* saveBytes, int len)
{
	int ret = MEMCARD_NewFunc_AsyncCRC(saveBytes, len);
	if (ret == MC_RETURN_PENDING)
		return ret;
	
	int crc = sdata->crc16_checkpoint_status;
	
	// finishing check
	crc = MEMCARD_CRC16(crc, 0);
	crc = MEMCARD_CRC16(crc, 0);
	
	// write checksum to data (last 2 bytes),
	// swap endians to throw off hackers,
	// which didn't really throw anyone off at all
	saveBytes[len-2] = (char)(crc>>8);
	saveBytes[len-1] = (char)(crc);
	
	return MC_RETURN_IOE;
}
