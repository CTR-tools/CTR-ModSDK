#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

// param_1 0: keep menu fx, 1: destroy all fx
// param_2 0: destroy music, 1: keep music
void Channel_DestroyAll_LowLevel(int opt1, int boolKeepMusic, char type)
{	
	struct ChannelStats* stats = 
		sdata->channelTaken.first;
		
	while(stats != 0)
	{
		if(
			// destroy if not music
			(stats->type != type) ||
		
			// override and remove music too
			(boolKeepMusic == 0)
		)
		{
			if(
				// if override
				(opt1 != 0) ||
				
				(
					// if not otherFX, erase
					(stats->type != 1) ||
					
					// if otherFX and not menu sounds,
					// cause those should ring out
					((short)stats->soundID > 5)
				)
			)
			{
				Channel_DestroySelf(stats);
			}
		}
		
		stats = stats->next;
	}
}