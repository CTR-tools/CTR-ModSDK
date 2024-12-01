#include <common.h>

void DECOMP_UpdateChannelVol_Music_All()
{
	int backupNext;
	struct ChannelStats* curr;
	
	for(
			curr = (struct ChannelStats*)sdata->channelTaken.first;
			curr != NULL;
			curr = (struct ChannelStats*)backupNext
		)
	{
		backupNext = (int)curr->next;
		
		// type != MUSIC, skip
		if(curr->type != 2) continue;
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
		
		DECOMP_UpdateChannelVol_Music(
			&sdata->songSeq[curr->soundID & 0xffff],
			&sdata->channelAttrNew[curr->channelID],
			curr->drumIndex_pitchIndex, curr->vol);
	}
}