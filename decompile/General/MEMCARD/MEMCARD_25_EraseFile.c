#include <common.h>

// NOTE: unused function?
uint8_t DECOMP_MEMCARD_EraseFile(int slotIdx, char *srcString)
{
    if (sdata->memcard_stage != 0)
        return 1;
	
    char name[64];
    MEMCARD_StringSet(name, slotIdx, srcString);
	
    sdata->memcard_stage = 
		(erase(name)) 
			? MC_STAGE_ERASE_PASS 
			: MC_STAGE_ERASE_FAIL;
    
	MEMCARD_GetFreeBytes(slotIdx);
    return 7;
}