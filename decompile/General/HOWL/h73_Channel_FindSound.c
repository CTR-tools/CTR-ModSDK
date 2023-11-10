#include <common.h>

struct ChannelStats* DECOMP_Channel_FindSound(int soundID)
{
	int backupNext;
	struct ChannelStats* curr;
		
	for(
		curr = sdata->channelTaken.first;
		curr != 0;
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