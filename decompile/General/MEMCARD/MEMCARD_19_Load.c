#include <common.h>

uint8_t MEMCARD_Load(
	int slotIdx, char *name, uint8_t *ptrMemcard, 
	int memcardFileSize, unsigned int param5)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
        return MC_RETURN_TIMEOUT;

    MEMCARD_NewTask(slotIdx, name, ptrMemcard, memcardFileSize, 0);

    sdata->memcard_fd = open(sdata->s_memcardFileCurr, FASYNC|FREAD);

    if (sdata->memcard_fd == -1)
    {
        MEMCARD_CloseFile();
        return MC_RETURN_NODATA;
    }
    else
    {
		sdata->memcardIconSize = 0x100;
        sdata->crc16_checkpoint_byteIndex = 0;
        sdata->crc16_checkpoint_status = 0;
        sdata->memcard_stage = MC_STAGE_LOAD_PART0_START;
        return MC_RETURN_PENDING;
	}
}