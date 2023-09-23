#include <common.h>

void DECOMP_howl_UnPauseChannel(struct ChannelStats* stats)
{
	int type;
	struct ChannelAttr attr;

	type = stats->type;
	
	// engineFX
	if(type == 0)
	{
		howl_InitChannelAttr_EngineFX(
			&sdata->howl_metaEngineFX[stats->soundID],
			&attr, stats->vol, stats->LR, stats->distort);
	}
	
	// otherFX
	else if(type == 1)
	{
		howl_InitChannelAttr_OtherFX(
			&sdata->howl_metaOtherFX[stats->soundID],
			&attr, stats->vol, stats->LR, stats->distort);
	}
	
	// music
	else // type == 2
	{
		howl_InitChannelAttr_Music(
			&sdata->songSeq[stats->soundID],
			&attr, stats->drumIndex_pitchIndex, stats->vol);
	}
	
	// enable all bits in ChannelUpdate flag
	sdata->ChannelUpdateFlags[stats->channelID] |= 0x7e;
	
	memcpy(&sdata->channelAttrNew[stats->channelID], &attr, sizeof(struct ChannelAttr));
}