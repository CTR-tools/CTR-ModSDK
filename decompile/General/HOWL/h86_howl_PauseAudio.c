#include <common.h>

void DECOMP_howl_PauseAudio()
{
	int* ptrFlag;
	int backupNext;
	struct ChannelStats* curr;
	struct ChannelStats* pausedStats;
	
	CDSYS_XAPauseRequest();
	
	// if already paused, quit
	if(sdata->numBackup_ChannelStats != 0)
		return;
	
	pausedStats = &sdata->channelStatsCurr[0];
	
	CseqMusic_Pause();
	
	Smart_EnterCriticalSection();
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = backupNext
		)
	{
		backupNext = curr->next;
		
		ptrFlag = &sdata->ChannelUpdateFlags[curr->channelID];
		*ptrFlag |= 1;
		*ptrFlag &= ~(2);
		
		// psx's kernel memcpy does NOT work inside "critical" sections
		int* dest = pausedStats++;
		int* src = curr;
		
		// skip first two, which are pointers
		dest[2] = src[2];
		dest[3] = src[3];
		dest[4] = src[4];
		dest[5] = src[5];
		dest[6] = src[6];
		dest[7] = src[7];
		
		LIST_RemoveMember(&sdata->channelTaken, curr);
		LIST_AddBack(&sdata->channelFree, curr);
	
		sdata->numBackup_ChannelStats++;
	}
	Smart_ExitCriticalSection();
}