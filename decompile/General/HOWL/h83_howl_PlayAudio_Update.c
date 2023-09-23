#include <common.h>

void DECOMP_howl_PlayAudio_Update()
{
	int* ptrFlag;
	int backupNext;
	struct ChannelStats* curr;
	
	if(sdata->boolAudioEnabled != 0)
	{
		// if copy exists, make audio fade slowly
		if(sdata->boolStoringVolume != 0)
		{
			sdata->currentVolume -= 2;
			if(sdata->currentVolume < 0)
				sdata->currentVolume = 0;
			
			sdata->criticalSectionCount = 1;
			howl_VolumeSet(0, sdata->currentVolume);
			sdata->criticalSectionCount = 0;
		}
		
		for(
				curr = sdata->channelTaken.first;
				curr != 0;
				curr = backupNext
			)
		{
			backupNext = curr->next;
		
			// if sound is on a timer (not stacatto)
			if((curr->flags & 4) == 0)
			{
				curr->timeLeft -= 5;
				
				if(curr->timeLeft < 1)
				{
					ptrFlag = &sdata->ChannelUpdateFlags[curr->channelID];
					*ptrFlag |= 1;
					*ptrFlag &= ~(2);
					
					curr->flags &= ~(1);
					
					LIST_RemoveMember(&sdata->channelTaken, curr);
					LIST_AddBack(&sdata->channelFree, curr);
				}
			}
		}
		
		Channel_ParseSongToChannels();
	}
	
	Channel_UpdateChannels();
}