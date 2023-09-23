#include <common.h>

struct ChannelStats* DECOMP_Channel_SearchFX_EditAttr(
	int type, int soundID, int updateFlags, 
	struct ChannelAttr* attr)
{
	struct ChannelAttr* editAttr;
	
	struct ChannelStats* stats = 
		sdata->channelTaken.first;
		
	while(stats != 0)
	{
		if(
			// matching type
			(stats->type == type) &&
		
			// matching ID
			(stats->soundID == soundID)
		)
		{
			// update flags
			sdata->ChannelUpdateFlags[stats->channelID] |= updateFlags;
			
			// edit ChanenlAttr
			editAttr = &sdata->channelAttrNew[stats->channelID];
			
			// change in spu addr
			if((updateFlags & 0x4) != 0)
			{
				editAttr->spuStartAddr = attr->spuStartAddr;
			}
			
			// change in ADSR
			if((updateFlags & 0x8) != 0)
			{
				editAttr->ad = attr->ad;
				editAttr->sr = attr->sr;
			}
			
			// change in pitch
			if((updateFlags & 0x10) != 0)
			{
				editAttr->pitch = attr->pitch;
			}
			
			// change in reverb
			if((updateFlags & 0x20) != 0)
			{
				editAttr->reverb = attr->reverb;
			}
			
			// change in volume
			if((updateFlags & 0x20) != 0)
			{
				// OG game treats this as one int
				editAttr->audioL = attr->audioL;
				editAttr->audioR = attr->audioR;
			}
			
			// OG code does this, but what if
			// there's multiple of the same sound?
			return stats;
		}
		
		stats = stats->next;
	}
	
	// sound not playing
	return 0;
}