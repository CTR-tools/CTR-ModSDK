#include <common.h>

void DECOMP_howl_UnPauseAudio()
{
	int i;
	int backupID;
	int backupNext;
	struct ChannelStats* curr;
	struct ChannelStats* pausedStats;
	
	// if no paused audio, skip
	if(sdata->numBackup_ChannelStats == 0) 
		return;

	pausedStats = &sdata->channelStatsCurr[0];

	DECOMP_Smart_EnterCriticalSection();
	for(
			i = 0, curr = sdata->channelFree.first;
			i < sdata->numBackup_ChannelStats;
			i++, curr = backupNext
		)
	{
		backupID = curr->channelID;
		backupNext = curr->next;
		
		// psx's kernel memcpy does NOT work inside "critical" sections
		int* src = pausedStats++;
		int* dest = curr;
		
		// skip first two, which are pointers
		dest[2] = src[2];
		dest[3] = src[3];
		dest[4] = src[4];
		dest[5] = src[5];
		dest[6] = src[6];
		dest[7] = src[7];
		
		DECOMP_LIST_RemoveMember(&sdata->channelFree, curr);
		DECOMP_LIST_AddBack(&sdata->channelTaken, curr);
	
		curr->channelID = backupID;
		DECOMP_howl_UnPauseChannel(curr);
	}
	DECOMP_Smart_ExitCriticalSection();
	
	DECOMP_CseqMusic_Resume();
	
	sdata->numBackup_ChannelStats = 0;
}