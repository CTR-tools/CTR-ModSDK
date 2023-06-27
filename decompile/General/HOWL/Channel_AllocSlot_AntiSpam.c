#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

struct ChannelStats* DECOMP_Channel_AllocSlot_AntiSpam(
	short soundID,
	char boolUseAntiSpam,
	int flags,
	struct ChannelAttr* attr)
{
	struct ChannelAttr* newAttr;
	struct ChannelStats* stats;
	
	// with AntiSpam, a new sound started within
	// 10 frames of another, will replace the older
	
	// without AntiSpam, sounds within 10 frames
	// of each other will play until they all finish
	
	if(boolUseAntiSpam == 1)
	{
		stats = (struct ChannelStats*)sdata->channelTaken.first;
		
		while(stats != 0)
		{
			if(
				// type == OtherFX
				(stats->type == 1) &&
			
				// matching ID
				((short)stats->soundID == soundID)
			)
			{
				int duration = 
				sdata->gGT->frameTimer_MainFrame_ResetDB -
				stats->startFrame;
				
				// if started within 10 frames, cancel old and start new,
				// otherwise you'll allocate too many sounds and overflow
				if(duration < 10)
				{
					Channel_DestroySelf(stats);
				}
			}
			
			stats = stats->next;
		}
	}
	
	return Channel_AllocSlot(flags, attr);
}

void Channel_DestroySelf(struct ChannelStats* stats)
{
	// set channel to OFF, and remove PLAYING bit
	sdata->ChannelUpdateFlags[stats->channelID] |= 1;
	sdata->ChannelUpdateFlags[stats->channelID] &= ~(2);
	
	stats->flags &= 0xfe;
	
	// recycle
	LIST_RemoveMember(&sdata->channelTaken, stats);
	LIST_AddBack(&sdata->channelFree, stats);
}	
