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
		// use ASYNC checksum load (ALWAYS)
        if ((param5 & 2) == 0)
        {
            // Process 0x200 bytes per frame
            sdata->memcardStatusFlags = sdata->memcardStatusFlags & 0xfffffff7;
        }
		
		// skip ASYNC and use the check the full card (UNUSED)
        else
        {
			// process crc16 to the end of memory
			sdata->memcardStatusFlags = sdata->memcardStatusFlags | 8;
		}
		
        sdata->memcard_stage = MC_STAGE_LOAD_PART1_ICON;
        return MEMCARD_ReadFile(0, 0x80);
	}
}