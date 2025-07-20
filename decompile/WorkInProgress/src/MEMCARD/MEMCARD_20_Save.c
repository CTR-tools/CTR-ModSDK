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

	// === Note for Niko ===
	// We can potentially do 1-block ghost,
	// One block = 0x2000 bytes, minus 0x100 icon, thats 0x1F00, NOT 0x1680 ND used
	// Two Block = 0x4000 bytes, minus 0x100 icon, thats 0x3F00, NOT 0x3e00 ND used

	// Search for "MEMCARD_SET_SIZE_BYTE3"
	// TODO: struct MemcardWORD
	// S, C, iconSize, blockSize

    // ALWAYS USED,
	// param_6 is always zero, (used to determine 1-block or 2-block)
	// fileSize*2 is always 2 blocks, rigged to make sure this path happens
    if (((param6 & 1) == 0) && (1 < sdata->memcardIconSize + fileSize * 2 + 0x1fff >> 0xd))
    {
        sdata->memcardStatusFlags = sdata->memcardStatusFlags | 4;
        *((uint8_t *)(data.memcardIcon_PsyqHand) + 3) = ((sdata->memcardIconSize + fileSize * 1 + 0x1fff) >> 0xd);
    }
	
	// UNUSED
	// This is likely from a time when "fileSize" was "blockSize",
	// then this path would be used to write a 2-block file
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

	// === Naughty Dog Bug ===
	// This can not happen async because the MEMCARD_HandleEvent
	// will only run AFTER the memcard request (write) begins,
	// That is why the first frame lags, can be fixed with a new
	// MEMCARD_HandleEvent stage that happens while memcard is PENDING
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