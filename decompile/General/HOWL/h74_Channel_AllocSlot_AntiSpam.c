#include <common.h>

void Channel_DestroySelf(struct ChannelStats* stats);

struct ChannelStats* DECOMP_Channel_AllocSlot_AntiSpam(
	short soundID,
	char boolUseAntiSpam,
	int flags,
	struct ChannelAttr* attr)
{
	int backupNext;
	struct ChannelAttr* newAttr;
	struct ChannelStats* curr;
	
	// with AntiSpam, a new sound started within
	// 10 frames of another, will replace the older
	
	// without AntiSpam, sounds within 10 frames
	// of each other will play until they all finish
	
	if(boolUseAntiSpam == 1)
	{	
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
				((short)curr->soundID == soundID)
			)
			{
				int duration = 
				sdata->gGT->frameTimer_MainFrame_ResetDB -
				curr->startFrame;
				
				// if started within 10 frames, cancel old and start new,
				// otherwise you'll allocate too many sounds and overflow
				if(duration < FPS_DOUBLE(10))
				{
					Channel_DestroySelf(curr);
				}
			}
		}
	}
	
	return DECOMP_Channel_AllocSlot(flags, attr);
}

void Channel_DestroySelf(struct ChannelStats* stats)
{
	// set channel to OFF, and remove PLAYING bit
	u_int* flagPtr = &sdata->ChannelUpdateFlags[stats->channelID];
	*flagPtr |= 1;
	*flagPtr &= ~(2);
	
	stats->flags &= ~(1);
	
	// recycle
	DECOMP_LIST_RemoveMember(&sdata->channelTaken, stats);
	DECOMP_LIST_AddBack(&sdata->channelFree, stats);
}	
