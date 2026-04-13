#include <common.h>

void DECOMP_howl_StopAudio(int boolErasePauseBackup, int boolEraseMusic, int boolDestroyAllFX)
{
	if(boolEraseMusic != 0)
		DECOMP_CseqMusic_StopAll();
	
	DECOMP_Smart_EnterCriticalSection();
	DECOMP_Channel_DestroyAll_LowLevel(boolDestroyAllFX, boolEraseMusic==0, 2);
	DECOMP_Smart_ExitCriticalSection();
	
	if(boolErasePauseBackup != 0)
		sdata->numBackup_ChannelStats = 0;
}