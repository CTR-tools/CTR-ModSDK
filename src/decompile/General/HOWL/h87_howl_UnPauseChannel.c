#include <common.h>

void DECOMP_howl_UnPauseChannel(struct ChannelStats* stats)
{
	int type;
	int soundID;
	struct ChannelAttr attr;

	type = stats->type;
	soundID = stats->soundID & 0xffff;
	
	// engineFX
	if(type == 0)
	{
		DECOMP_howl_InitChannelAttr_EngineFX(
			&sdata->howl_metaEngineFX[soundID],
			&attr, stats->vol, stats->LR, stats->distort);
	}
	
	// otherFX
	else if(type == 1)
	{
		DECOMP_howl_InitChannelAttr_OtherFX(
			&sdata->howl_metaOtherFX[soundID],
			&attr, stats->vol, stats->LR, stats->distort);
	}
	
	// music
	else // type == 2
	{
		DECOMP_howl_InitChannelAttr_Music(
			&sdata->songSeq[soundID],
			&attr, stats->drumIndex_pitchIndex, stats->vol);
	}
	
	// enable all bits in ChannelUpdate flag
	sdata->ChannelUpdateFlags[stats->channelID] |= 0x7e;
	
	memcpy(&sdata->channelAttrNew[stats->channelID], &attr, sizeof(struct ChannelAttr));
}