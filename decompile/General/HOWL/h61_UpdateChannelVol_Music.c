#include <common.h>

void DECOMP_UpdateChannelVol_Music(
	struct SongSeq* songSeq, struct ChannelAttr* attr, int index, int vol)
{
	int sampleVol;
	
	int newVol = 
		(sdata->vol_Music * 
		sdata->songPool[songSeq->songPoolIndex].vol_Curr *
		songSeq->vol_Curr) >> 10;
	
	if((songSeq->flags & 4) == 0)
	{
		sampleVol = 
			sdata->ptrCseqLongSamples[songSeq->instrumentID].volume;
	}
	
	else
	{
		sampleVol = 
			sdata->ptrCseqShortSamples[index].volume;
	}
	
	DECOMP_Channel_SetVolume(attr, (newVol * sampleVol * vol) >> 0xf, songSeq->LR);
}