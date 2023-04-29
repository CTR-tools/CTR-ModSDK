#include <common.h>

struct ChannelStats* Channel_FindSound(int soundID)
{
	struct ChannelStats* stats = 
		sdata->channelTaken.first;
		
	while(stats != 0)
	{
		if(
			// type == OtherFX
			(stats->type == 1) &&
		
			// matching ID
			(stats->soundID == soundID)
		)
		{
			// sound already playing
			return 1;
		}
		
		stats = stats->next;
	}
	
	// sound not playing
	return 0;
}