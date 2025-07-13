#include <common.h>

uint8_t DECOMP_MEMCARD_GetInfo(int slotIdx)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
        return MC_RETURN_TIMEOUT;

	// discard any previous events
	// submit a card_info request,
	// check the result of a GET INFO
	// 8 tries to see if it worked
    MEMCARD_SkipEvents();
    while (!_card_info(slotIdx));
    sdata->memcard_stage = MC_STAGE_GETINFO;
    sdata->memcard_remainingAttempts = 8;
    sdata->memcardSlot = slotIdx;
	
	// The "info" has started, the result will be found
	// the next time we wait for an event result
    return MC_RETURN_PENDING;
}