#include <common.h>

void DECOMP_howl_UnPauseAudio()
{
	int i;
	int backupNext;
	struct ChannelStats* curr;
	struct ChannelStats* pausedStats;
	
	// if no paused audio, skip
	if(sdata->numBackup_ChannelStats == 0) 
		return;

	pausedStats = &sdata->channelStatsCurr[0];

	Smart_EnterCriticalSection();
	for(
			i = 0, curr = sdata->channelFree.first;
			i < sdata->numBackup_ChannelStats;
			i++, curr = backupNext
		)
	{
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
		
		LIST_RemoveMember(&sdata->channelFree, curr);
		LIST_AddBack(&sdata->channelTaken, curr);
	
		howl_UnPauseChannel(curr);
		printf("%08x %08x\n", backupNext, curr->next);
	}
	Smart_ExitCriticalSection();
	
	//CseqMusic_Resume();
	
	sdata->numBackup_ChannelStats = 0;
}