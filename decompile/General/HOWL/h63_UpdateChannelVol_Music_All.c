#include <common.h>

void DECOMP_UpdateChannelVol_Music_All()
{
	struct ChannelStats* curr;
	u_int* flagPtr;
	
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{
		// type != MUSIC, skip
		if(curr->type != 2) continue;
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
		
		UpdateChannelVol_Music(
			&sdata->songSeq[curr->soundID],
			&sdata->channelAttrNew[curr->channelID],
			curr->drumIndex_pitchIndex, curr->vol);
	}
}