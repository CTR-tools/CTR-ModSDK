#include <common.h>

void DECOMP_howl_InitChannelAttr_Music(
	struct SongSeq* seq, struct ChannelAttr* attr, int index, int channelVol)
{
	int pitch;
	unsigned int sampleVol;
	int songIndex = seq->songPoolIndex;
	
	sampleVol = (
					sdata->vol_Music *
					sdata->songPool[songIndex].vol_Curr *
					seq->vol_Curr
				) >> 10;
	
	// instrument
	if((seq->flags & 4) == 0)
	{
		struct SampleInstrument* longSample = 
			&sdata->ptrCseqLongSamples[seq->instrumentID];
	
		pitch = DECOMP_howl_InstrumentPitch(longSample->basePitch, index, seq->distort);
		
		attr->spuStartAddr = sdata->howl_spuAddrs[longSample->spuIndex].spuAddr << 3;
		
		// audio ADSR
		attr->ad = longSample->ad;
		attr->sr = longSample->sr;
		
		sampleVol *= (u_int)longSample->volume;
	}
	
	// drums
	else
	{
		struct SampleDrums* shortSample =
			&sdata->ptrCseqShortSamples[index];
			
		if(seq->distort == 0x80)
		{
			pitch = shortSample->pitch;
		}
		
		else
		{
			pitch = shortSample->pitch * data.distortConst_OtherFX[seq->distort] >> 0x10;
		}
		
		attr->spuStartAddr = sdata->howl_spuAddrs[shortSample->spuIndex].spuAddr << 3;
		
		// audio ADSR
		attr->ad = 0x80ff;
		attr->sr = 0x1fc2;
		
		sampleVol *= (u_int)shortSample->volume;
	}
	
	DECOMP_Channel_SetVolume(attr, (u_int)(sampleVol*channelVol) >> 0xf, seq->LR);
	
	attr->pitch = pitch;
	attr->reverb = seq->reverb;
}