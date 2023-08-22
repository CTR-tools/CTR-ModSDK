#include <common.h>

void UpdateChannelVol_EngineFX_All()
{
	struct ChannelStats* curr;
	u_int* flagPtr;
	
	for(
			curr = sdata->channelTaken.first;
			curr != 0;
			curr = curr->next
		)
	{
		// type == MUSIC, skip
		if(curr->type == 2) continue;
		
		// update volume
		sdata->ChannelUpdateFlags[curr->channelID] |= 0x40;
		
		// type == EngineFX
		if(curr->type == 0)
		{
			UpdateChannelVol_EngineFX(
				&sdata->howl_metaEngineFX[curr->soundID],
				&sdata->channelAttrCurr[curr->channelID],
				curr->vol, curr->LR);
		}
		
		// type == OtherFX
		else
		{
			UpdateChannelVol_OtherFX(
				&sdata->howl_metaOtherFX[curr->soundID],
				&sdata->channelAttrCurr[curr->channelID],
				curr->vol, curr->LR);
		}
		
	}
}