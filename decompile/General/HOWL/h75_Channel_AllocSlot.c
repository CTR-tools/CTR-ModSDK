#include <common.h>

struct ChannelStats* DECOMP_Channel_AllocSlot(
	int flags,
	struct ChannelAttr* attr)
{
	int i;
	struct ChannelAttr* newAttr;
	struct ChannelStats* stats;
	
	// get free slot
	stats = sdata->channelFree.first;
	
	// quit if no free slots
	if(stats == 0) return 0;
	
	// allocate
	DECOMP_LIST_RemoveMember(&sdata->channelFree, stats);
	DECOMP_LIST_AddBack(&sdata->channelTaken, stats);
	
	// start playing
	sdata->ChannelUpdateFlags[stats->channelID] |= (flags | 2);
	
	// make new ChanenlAttr
	newAttr = &sdata->channelAttrNew[stats->channelID];
	
	// copy all 0x10 bytes in ChannelAttr
	for(i = 0; i < 4; i++)
	{
		((int*)newAttr)[i] = ((int*)attr)[i];
	}
	
	stats->flags = 1;
	
	return stats;
}