#include <common.h>

void DECOMP_UpdateChannelVol_EngineFX_All()
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
		
		// just the sound, not the instance of sound
		int soundID = curr->soundID & 0xffff;
		
		// type == EngineFX
		if(curr->type == 0)
		{
			DECOMP_UpdateChannelVol_EngineFX(
				&sdata->howl_metaEngineFX[soundID],
				&sdata->channelAttrNew[curr->channelID],
				curr->vol, curr->LR);
		}
		
		// type == OtherFX
		else
		{
			DECOMP_UpdateChannelVol_OtherFX(
				&sdata->howl_metaOtherFX[soundID],
				&sdata->channelAttrNew[curr->channelID],
				curr->vol, curr->LR);
		}
	}
}