#include <common.h>

void DECOMP_howl_PauseAudio()
{
	int* ptrFlag;
	struct ChannelStats* curr;
	
	CDSYS_XAPauseRequest();
	
	// if already paused, quit
	if(sdata->numBackup_ChannelStats != 0)
		return;
	
	CseqMusic_Pause();
	
	Smart_EnterCriticalSection();
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{
		ptrFlag = &sdata->ChannelUpdateFlags[curr->channelID];
		*ptrFlag |= 1;
		*ptrFlag &= ~(2);
		
		// Naughty Dog has inline copy that runs faster
		memcpy(
			&sdata->channelStatsCurr[sdata->numBackup_ChannelStats++],
			curr,
			sizeof(struct ChannelStats)
		);
		
		LIST_RemoveMember(&sdata->channelTaken, curr);
		LIST_AddBack(&sdata->channelFree, curr);
	}
	Smart_ExitCriticalSection();
}