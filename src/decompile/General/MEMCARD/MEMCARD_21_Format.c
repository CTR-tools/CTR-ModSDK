#include <common.h>

uint8_t DECOMP_MEMCARD_Format(int slotIdx)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
		return MC_RETURN_TIMEOUT;
	
    if (!format(MEMCARD_StringInit(slotIdx, 0)))
		return MC_RETURN_TIMEOUT;

	// discard any previous events
	// submit a load to make sure format worked,
	// check the result of a NEW CARD
	// 8 tries to see if it worked
    MEMCARD_SkipEvents();
    while (!_card_load(sdata->memcardSlot));
	sdata->memcard_stage = MC_STAGE_NEWCARD;
    sdata->memcard_remainingAttempts = 8;
    sdata->memcardSlot = slotIdx;

	// The "format" has started, the result will be found
	// the next time we wait for an event result
    return MC_RETURN_PENDING;
}