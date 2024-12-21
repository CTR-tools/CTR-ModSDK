#include <common.h>
// tests all events until no events left for both cards
void DECOMP_MEMCARD_SkipEvents(void)

{
    // Non infinite, bot functions have timeouts
    while ((MEMCARD_GetNextSwEvent() != 7) && (MEMCARD_GetNextHwEvent() != 7))
        ;
}
