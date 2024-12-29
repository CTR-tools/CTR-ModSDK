#include <common.h>

void DECOMP_UpdateChannelVol_OtherFX_All()
{
	struct ChannelStats* curr, *backupNext;
	
	for(
			curr = (struct ChannelStats*)sdata->channelTaken.first;
			curr != NULL;
			curr = backupNext
		)
	{	
		backupNext = curr->next;
	
		// type != OtherFX, skip
		if(curr->type != 1) continue;
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
		
		DECOMP_UpdateChannelVol_OtherFX(
			&sdata->howl_metaOtherFX[curr->soundID & 0xffff],
			&sdata->channelAttrNew[curr->channelID],
			curr->vol, curr->LR);
	}
}