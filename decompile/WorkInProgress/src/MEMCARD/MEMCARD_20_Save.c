#include <common.h>

// NOTE: param6 is unused and passed as 0 from the only caller to this function. Kept in to not mess up $sp allocation
// ERROR: Does not write title in save. Should be "C T R: GAME SAVE AND SCORES" or something. Not blank
uint8_t MEMCARD_Save(int slotIdx, char *name,
                     char *param_3, uint8_t *ptrData, int fileSize, unsigned int param6)

{

    if (sdata->memcard_stage != MC_STAGE_IDLE)
        return MC_RETURN_TIMEOUT;

    sdata->memcardIconSize = 0x100;

    // this will always return 0, no need to check
    MEMCARD_NewTask(slotIdx, name, ptrData, fileSize);

	// Search for "MEMCARD_SET_SIZE_BYTE3"

    // NOTE: Commented out because param6 always 0, will always eval to false
    if (((param6 & 1) == 0) && (1 < sdata->memcardIconSize + fileSize * 2 + 0x1fff >> 0xd))
    {
        sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
        *((uint8_t *)(data.memcardIcon_PsyqHand) + 3) = ((sdata->memcardIconSize + fileSize * 1 + 0x1fff) >> 0xd);
    }
    else
    {
		sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffffb;
		*((uint8_t *)(data.memcardIcon_PsyqHand) + 3) = ((sdata->memcardIconSize + fileSize * 2 + 0x1fff) >> 0xd);
	}

    uint8_t *memcardIconPtr = (uint8_t *)data.memcardIcon_PsyqHand[1];
    for (int i = 0; i < 64; i += 2)
    {
        *(memcardIconPtr + i) = 0x81;
        *(memcardIconPtr + i + 1) = 0x40;
    }

    // NOTE: Something most likely wrong here
    for (int i = 0; *param_3 != '\0' && i < 64; i++, param_3++)
    {
        // starts at 800857a4 and not 800857a0
        *(memcardIconPtr + i) = *param_3;
    }

    MEMCARD_ChecksumSave(ptrData, fileSize);



	// ====== Open 1 ======



	// Search for "MEMCARD_SET_SIZE_BYTE3"
	int whatIsThis = (unsigned int)*((uint8_t *)(data.memcardIcon_PsyqHand) + 3) << 0x10;
	
    sdata->memcard_fd = open(sdata->s_memcardFileCurr, whatIsThis | FCREATE);

    if (sdata->memcard_fd != -1)
    {
        close(sdata->memcard_fd);
        sdata->memcard_fd = -1;
    }


	// ====== Open 2 ======


    sdata->memcard_fd = open(sdata->s_memcardFileCurr, FASYNC|FWRITE);

    if (sdata->memcard_fd != -1)
    {
        sdata->memcard_stage = MC_STAGE_SAVE_PART1_ICON;
        return MEMCARD_WriteFile(0, data.memcardIcon_PsyqHand, sdata->memcardIconSize);
    }

    MEMCARD_CloseFile();
    return MC_RETURN_FULL;
}