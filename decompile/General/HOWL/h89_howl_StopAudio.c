#include <common.h>

void DECOMP_howl_StopAudio(int boolErasePauseBackup, int boolEraseMusic, int boolDestroyAllFX)
{
	if(boolEraseMusic != 0)
		CseqMusic_StopAll();
	
	Smart_EnterCriticalSection();
	Channel_DestroyAll_LowLevel(boolDestroyAllFX, boolEraseMusic==0, 2);
	Smart_ExitCriticalSection();
	
	if(boolErasePauseBackup != 0)
		sdata->numBackup_ChannelStats = 0;
}