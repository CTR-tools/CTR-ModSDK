#include <common.h>

void DECOMP_MEMCARD_SkipEvents(void)
{
    // Flush all Events until everything shows NONE
    while (
			(MEMCARD_GetNextSwEvent() != MC_EVENT_NONE) && 
			(MEMCARD_GetNextHwEvent() != MC_EVENT_NONE)
		);
}
