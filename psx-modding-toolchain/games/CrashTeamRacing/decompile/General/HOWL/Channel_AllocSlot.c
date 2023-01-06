#include <common.h>

struct ChannelAttr* Channel_AllocSlot(
	int flags,
	struct ChannelAttr* attr)
{
	struct ChannelAttr* newAttr;
	struct ChannelStats* stats;
	
	// get free slot
	stats = sdata->channelFree.first;
	
	// quit if no free slots
	if(stats == 0) return 0;
	
	// allocate
	LIST_RemoveMember(&sdata->channelFree, stats);
	LIST_AddBack(&sdata->channelTaken, stats);
	
	// start playing
	sdata->ChannelUpdateFlags[stats->channelID] |= (flags | 2);
	
	// make new ChanenlAttr
	newAttr = &sdata->channelAttrCurr[stats->channelID];
	
	((int*)newAttr)[0] = ((int*)attr)[0];
	((int*)newAttr)[1] = ((int*)attr)[1];
	((int*)newAttr)[2] = ((int*)attr)[2];
	((int*)newAttr)[3] = ((int*)attr)[3];
	
	newAttr->pitch = 1;
	
	return newAttr;
}