#include <common.h>

void DECOMP_howl_InitChannelAttr_Music(
	struct SongSeq* seq, struct ChannelAttr* attr, int index, int channelVol)
{
	int pitch;
	int sampleVol;
	int songIndex = seq->songPoolIndex;
	
	// instrument
	if((seq->flags & 4) == 0)
	{
		struct SampleInstrument* longSample = 
			&sdata->ptrCseqLongSamples[seq->instrumentID];
	
		pitch = howl_InstrumentPitch(longSample->basePitch, index, seq->distort);
		
		attr->spuStartAddr = sdata->howl_spuAddrs[longSample->spuIndex].spuAddr << 3;
		
		// audio ADSR
		attr->ad = longSample->ad;
		attr->sr = longSample->sr;
		
		sampleVol = 
			(
				(int)(
					(u_int)sdata->vol_Music *
					(u_int)sdata->songPool[songIndex].vol_Curr *
					(u_int)seq->vol_Curr
				) >> 10
			) * (u_int)longSample->volume;
	}
	
	// drums
	else
	{
		struct SampleDrums* shortSample =
			&sdata->ptrCseqShortSamples[index];
			
		// if( == 0x80)
		{
			pitch = shortSample->pitch;
		}
		
		//else {}
		
		attr->spuStartAddr = sdata->howl_spuAddrs[shortSample->spuIndex].spuAddr << 3;
		
		// audio ADSR
		attr->ad = 0x80ff;
		attr->sr = 0x1fc2;
		
		sampleVol = 
			(
				(int)(
					(u_int)sdata->vol_Music *
					(u_int)sdata->songPool[songIndex].vol_Curr *
					(u_int)seq->vol_Curr
				) >> 10
			) * (u_int)shortSample->volume;
		
		return;
	}
	
	Channel_SetVolume(attr, (u_int)(sampleVol*channelVol) >> 0xf, seq->LR);
	
	attr->pitch = pitch;
	attr->reverb = seq->reverb;
}