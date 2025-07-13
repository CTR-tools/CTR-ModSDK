#include <common.h>

uint8_t DECOMP_MEMCARD_Format(int slotIdx)
{
    if (sdata->memcard_stage != MC_STAGE_IDLE)
		return 1;
	
    if (!format(MEMCARD_StringInit(slotIdx, 0)))
		return 1;

	// discard any pending events
    MEMCARD_SkipEvents();

	// submit a load to make sure format worked,
	// check the result of a NEW CARD
	// 8 tries to see if it worked
    while (!_card_load(sdata->memcardSlot));
	sdata->memcard_stage = MC_STAGE_NEWCARD;
    sdata->memcard_remainingAttempts = 8;
    sdata->memcardSlot = slotIdx;
	
    return 7;
}