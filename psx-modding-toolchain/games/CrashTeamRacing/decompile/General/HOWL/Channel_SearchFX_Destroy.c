#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

struct ChannelStats* Channel_SearchFX_Destroy(
	int type, int soundID_count, int soundID)
{	
	struct ChannelStats* stats = 
		sdata->channelTaken.first;
		
	while(stats != 0)
	{
		if(
			// matching type
			(stats->type == type) &&
		
			// matching ID and bit-shifted soundCount
			((stats->soundID & soundID) == (soundID_count & soundID))
		)
		{
			Channel_DestroySelf(stats);
			
			// OG code does this, but what if
			// there's multiple of the same sound?
			return stats;
		}
		
		stats = stats->next;
	}
	
	// sound not playing
	return 0;
}