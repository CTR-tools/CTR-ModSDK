#include <common.h>

uint8_t MEMCARD_Save(
	int slotIdx, char *name, char *param_3, 
	uint8_t *ptrMemcard, int memcardFileSize, unsigned int param6)

{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
        return MC_RETURN_TIMEOUT;

    MEMCARD_NewTask(slotIdx, name, ptrMemcard, memcardFileSize, 0);


	int numBlock = 1;
	if (memcardFileSize == 0x3E00)
		numBlock = 2;

	// ====== Open 1 ======
	
    sdata->memcard_fd = open(sdata->s_memcardFileCurr, (numBlock << 16) | FCREATE);

    if (sdata->memcard_fd == -1)
    {
        // do NOT return,
		// the -1 could mean the file already exists
        #if 0
		// MEMCARD_CloseFile();
        // return MC_RETURN_FULL;
		#endif
    }
    else
    {
        close(sdata->memcard_fd);
        sdata->memcard_fd = -1;
    }

	// ====== Open 2 ======

    sdata->memcard_fd = open(sdata->s_memcardFileCurr, FASYNC|FWRITE);

    if (sdata->memcard_fd == -1)
    {
        MEMCARD_CloseFile();
        return MC_RETURN_FULL;
    }
    else
    {
		sdata->memcardIconSize = 0x100;
        sdata->crc16_checkpoint_byteIndex = 0;
        sdata->crc16_checkpoint_status = 0;
        sdata->memcard_stage = MC_STAGE_SAVE_PART0_START;
		return MC_RETURN_PENDING;
    }
}