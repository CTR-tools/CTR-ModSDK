#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

// depending on flags, you might have:
//	16-bit soundID, which destroys all of this type of sound
//	32-bit soundID_count, which destroys specific instance of sound
struct ChannelStats* DECOMP_Channel_SearchFX_Destroy(
	int type, int soundID, int flags)
{	
	struct ChannelStats* stats = 
		sdata->channelTaken.first;
		
	while(stats != 0)
	{
		if(
			// matching type
			(stats->type == type) &&
		
			// matching ID and bit-shifted soundCount
			((stats->soundID & flags) == (soundID & flags))
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