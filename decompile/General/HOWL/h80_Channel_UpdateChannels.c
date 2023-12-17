#include <common.h>

void DECOMP_Channel_UpdateChannels()
{
	//int voice_bit;
	int vNum;
	
	// find all OFF channels
	int voiceBitOn=0;
	int voiceBitOff=0;
	
	struct ChannelAttr* cur;
	struct ChannelAttr* new;
	int* ptrFlag;
	int updateFlags;
	
	for(
			vNum = 0,
			ptrFlag = &sdata->ChannelUpdateFlags[0];
			
			vNum < NUM_SFX_CHANNELS; 
			
			vNum++,
			ptrFlag++
		)
	{
		int updateFlags = *ptrFlag;
		
		// if need to turn off
		if((updateFlags & 1) != 0)
		{
			voiceBitOff |= 1<<vNum;
			
			if((updateFlags & 2) != 0)
			{
				*ptrFlag &= ~(1);
			}
			
			else
			{
				*ptrFlag = 0;
			}
		}
	}
	
	SpuSetKey(0,voiceBitOff);
	
	for(
			vNum = 0,
			cur = &sdata->channelAttrCur[0],
			new = &sdata->channelAttrNew[0],
			ptrFlag = &sdata->ChannelUpdateFlags[0];
			
			vNum < NUM_SFX_CHANNELS; 
			
			vNum++,
			cur++,
			new++,
			ptrFlag++
		)
	{
		int updateFlags = *ptrFlag;
		
		// if need to turn on
		if((updateFlags & 2) != 0)
		{
			voiceBitOn |= 1<<vNum;
		}
		
		// start address needs to change
		if((updateFlags & 4) != 0)
		{
			int startAddr = new->spuStartAddr;
			
			if(startAddr != cur->spuStartAddr)
			{
				cur->spuStartAddr = startAddr;
				
				SpuSetVoiceStartAddr(vNum, startAddr);
			}
		}
		
		// ADSR needs to change
		if((updateFlags & 8) != 0)
		{
			int adsr = *(int*)&new->ad;
			
			if(adsr != *(int*)&cur->ad)
			{
				int ad = new->ad;
				int sr = new->sr;
				
				cur->ad = ad;
				cur->sr = sr;
				
				int local_38;
				int local_34;
				int RRmode;
				
				if((short)ad < 0)	local_38 = 5;
				else				local_38 = 1;
				
				if((short)sr < 0)
				{
					if((sr >> 0xe & 1) == 0)	local_34 = 5;
					else						local_34 = 7;
				}
				else
				{
					if((sr >> 0xe & 1) == 0)	local_34 = 1;
					else						local_34 = 3;
				}
				
				if((sr >> 5 & 1) == 0)	RRmode = 3;
				else					RRmode = 7;
				
				SpuSetVoiceADSRAttr(vNum, 
					(ad>>8)&0x7f, (ad>>4)&0xf,
					(sr>>6)&0x7f, sr&0x1f, ad&0xf,
					local_38, local_34, RRmode);
			}
		}
		
		// pitch needs to change
		if((updateFlags & 0x10) != 0)
		{
			int pitch = new->pitch;
			
			if(pitch != cur->pitch)
			{
				cur->pitch = pitch;
				SpuSetVoicePitch(vNum, pitch);
			}
		}
		
		// reverb needs to change
		if((updateFlags & 0x20) != 0)
		{
			int reverb = new->reverb;
			
			if(reverb != cur->reverb)
			{
				cur->reverb = reverb;
				SpuSetReverbVoice(reverb!=0, 1<<vNum);
			}
		}
		
		// volume needs to change
		if((updateFlags & 0x40) != 0)
		{
			int audioLR = *(int*)&new->audioL;
			
			if(audioLR != *(int*)&cur->audioL)
			{
				int audioL = new->audioL;
				int audioR = new->audioR;
				
				cur->audioL = audioL;
				cur->audioR = audioR;
				
				SpuSetVoiceVolume(vNum, audioL, audioR);
			}
		}
		
		*ptrFlag = 0;
	}
	
	SpuSetKey(1,voiceBitOn);
}