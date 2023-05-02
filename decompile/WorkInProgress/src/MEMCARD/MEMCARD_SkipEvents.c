#include <common.h>
// tests all events until no events left for both cards
void MEMCARD_SkipEvents(void)

{
    // Non infinite, bot functions have timeouts
    while ((MEMCARD_GetNextSlot1Event() != 7) && (MEMCARD_GetNextSlot2Event() != 7))
        ;
}
