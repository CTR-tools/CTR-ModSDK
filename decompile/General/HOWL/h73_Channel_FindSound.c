#include <common.h>

int DECOMP_Channel_FindSound(int soundID)
{
	struct ChannelStats* curr, *backupNext;
		
	for(
		curr = (struct ChannelStats*)sdata->channelTaken.first;
		curr != NULL;
		curr = backupNext
	)
	{
		backupNext = curr->next;
		
		if(
			// type == OtherFX
			(curr->type == 1) &&
		
			// matching ID
			(curr->soundID == soundID)
		)
		{
			// sound already playing
			return 1;
		}
	}
	
	// sound not playing
	return 0;
}