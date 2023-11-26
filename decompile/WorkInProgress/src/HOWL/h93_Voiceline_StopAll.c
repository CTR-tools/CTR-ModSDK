#include <common.h>

void Voiceline_StopAll(void)
{
    if (sdata->VoiceLine2.last != 0)
    {
        do
        {
            LIST_RemoveMember(&sdata->Voiceline2.first, sdata->VoiceLine2.last);

            LIST_AddFront(&sdata->Voiceline1, sdata->VoiceLine2.last);

        } while (sdata->VoiceLine2.last != 0);
    }
}