#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

// param_1 0: keep menu fx, 1: destroy all fx
// param_2 0: destroy music, 1: keep music
void DECOMP_Channel_DestroyAll_LowLevel(int opt1, int boolKeepMusic, char type)
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
			// destroy if not music
			(curr->type != type) ||
		
			// override and remove music too
			(boolKeepMusic == 0)
		)
		{
			if(
				// if override
				(opt1 != 0) ||
				
				(
					// if not otherFX, erase
					(curr->type != 1) ||
					
					// if otherFX and not menu sounds,
					// cause those should ring out
					((short)curr->soundID > 5)
				)
			)
			{
				Channel_DestroySelf(curr);
			}
		}
	}
}