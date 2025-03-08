#include <common.h>

void DECOMP_howl_PlayAudio_Update()
{
	int* ptrFlag;
	struct ChannelStats* curr, *backupNext;
	u_char statFlags;
	
	if(sdata->boolAudioEnabled != 0)
	{
		// if copy exists, make audio fade slowly
		if(sdata->boolStoringVolume != 0)
		{
			sdata->currentVolume -= 2;
			if(sdata->currentVolume < 0)
				sdata->currentVolume = 0;
			
			sdata->criticalSectionCount = 1;
			DECOMP_howl_VolumeSet(0, sdata->currentVolume);
			sdata->criticalSectionCount = 0;
		}
		
		for(
				curr = (struct ChannelStats*)sdata->channelTaken.first;
				curr != NULL;
				curr = backupNext
			)
		{
			backupNext = curr->next;
		
			// if sound has no timer (plays inf)
			statFlags = curr->flags;
			if((statFlags & 4) != 0) continue;
			
			// play sound until timer runs out
			curr->timeLeft -= 5;	
			if(curr->timeLeft > 0) continue;
				
			ptrFlag = &sdata->ChannelUpdateFlags[curr->channelID];
			*ptrFlag |= 1;
			*ptrFlag &= ~(2);
					
			curr->flags = statFlags & ~(1);
					
			DECOMP_LIST_RemoveMember(&sdata->channelTaken, (struct Item*)curr);
			DECOMP_LIST_AddBack(&sdata->channelFree, (struct Item*)curr);
		}
		
		DECOMP_Channel_ParseSongToChannels();
	}
	
	DECOMP_Channel_UpdateChannels();
}