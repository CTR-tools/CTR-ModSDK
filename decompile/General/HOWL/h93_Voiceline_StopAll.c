#include <common.h>

void DECOMP_Voiceline_StopAll(void)
{
	while(sdata->Voiceline2.last != 0)
	{
		DECOMP_LIST_RemoveMember(&sdata->Voiceline2.first, sdata->Voiceline2.last);
	
		DECOMP_LIST_AddFront(&sdata->Voiceline1, sdata->Voiceline2.last);
	}
}