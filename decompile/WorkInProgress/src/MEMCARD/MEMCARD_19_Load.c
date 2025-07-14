#include <common.h>

// ghidra couldn't detect parameters,
// because they were passed directly from this func to another
// TODO: proper flags from #defines
// NOTE: param5 is unused and passed as 0 from the only caller to this function. Kept in to not mess up $sp allocation
uint8_t MEMCARD_Load(int slotIdx, char *name, uint8_t *ptrMemcard, int memcardFileSize, unsigned int param5)

{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
        return MC_RETURN_TIMEOUT;

    MEMCARD_NewTask(slotIdx, name, ptrMemcard, memcardFileSize, param5); // Too many params to NewTask. param5 is always 0

    sdata->memcard_fd = open(sdata->s_bu00_BASCUS_94426_slots, FASYNC|FREAD);

    if (sdata->memcard_fd == -1)
    {
        MEMCARD_CloseFile();
        return MC_RETURN_NODATA;
    }
    else
    {
        // NOTE: Commented out because param5 is always 0, Will always eval to false
        /*
        if ((param5 & 2) == 0)
            {
                // dont process crc16 to the end of memory,
                // just the next 0x200 bytes (async)
                sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffff7;
            }
            else
            {
        */
        // process crc16 to the end of memory
        sdata->memcardStatusFlags = sdata->memcardStatusFlags | 8;
        sdata->memcard_stage = MC_STAGE_LOAD_PART1_ICON;

        // Read memory card
        return MEMCARD_ReadFile(0, 0x80);
        /*
            }
        */
    }
}