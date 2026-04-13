#include <common.h>

void DECOMP_MEMCARD_SkipEvents(void)
{
    // Flush all "previous" Events until everything shows PENDING
    while (DECOMP_MEMCARD_GetNextSwEvent() != MC_RETURN_PENDING);
    while (DECOMP_MEMCARD_GetNextHwEvent() != MC_RETURN_PENDING);
}
