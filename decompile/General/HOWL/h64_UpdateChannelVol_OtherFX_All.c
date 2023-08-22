#include <common.h>

void DECOMP_UpdateChannelVol_OtherFX_All()
{
	struct ChannelStats* curr;
	u_int* flagPtr;
	
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{		
		// type != OtherFX, skip
		if(curr->type != 1) continue;
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
		
		UpdateChannelVol_EngineFX(
			&sdata->howl_metaEngineFX[curr->soundID],
			&sdata->channelAttrCurr[curr->channelID],
			curr->vol, curr->LR);
	}
}