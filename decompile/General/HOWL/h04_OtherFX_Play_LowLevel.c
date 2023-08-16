#include <common.h>

int DECOMP_OtherFX_Play_LowLevel(u_int soundID, char boolAntiSpam, u_int flags)
{
  struct GameTracker* gGT = sdata->gGT;
  struct ChannelStats* channel;
  int count;
  short id;
  struct OtherFX* ptrOtherFX;
  u_int LR = (flags) & 0xff;
  u_int distortion = (flags >> 8) & 0xff;
  u_int volume = (flags >> 0x10) & 0xff;
  u_short echo = (flags >> 0x18) & 0xff;
  struct ChannelAttr channelAttr;

  if (sdata->boolAudioEnabled == 0) return 0;
  
  id = soundID & 0xffff;
  
  // quit if out of bounds
  if (id >= sdata->ptrHowlHeader->numOtherFX) return 0;
  
  // get pointer to cseq audio, given soundID
  ptrOtherFX = &sdata->howl_metaOtherFX[id];
  
  // quit if effect is not loaded
  if (sdata->howl_spuAddrs[ptrOtherFX->spuIndex].spuAddr == 0) return 0;
  
  howl_InitChannelAttr_OtherFX(ptrOtherFX, &channelAttr, volume, LR, distortion);
  
  Smart_EnterCriticalSection();
  
  // does this ever happen?
  // breakpoint 8002b5b4 in OG CTR
  if (
		// if can not play with duplicates (at all)
		(boolAntiSpam == 2) &&
		(
			channel = Channel_FindSound(id),
			
			// if sound is already playing
			channel != 0
		)
    )
  {
	Smart_ExitCriticalSection();
	return 0;
  }
    
  // This function allows duplicates of functions, 
  // but not within 10 frames of each other, depending on boolAntiSpam
  channel = Channel_AllocSlot_AntiSpam(id,boolAntiSpam,0x7c,&channelAttr);
  
  if(channel == 0)
  {
	Smart_ExitCriticalSection();
	return 0; 
  }

  if ((ptrOtherFX->flags & 2) != 0) {
	channel->flags |= 4;
  }
  
  // type otherFX
  channel->type = 1;
  
  channel->unk2 = 0;
  
  channel->echo = echo;
  
  channel->vol = volume;
  
  channel->distort = distortion;
  
  channel->LeftRight = LR;
  
  channel->timeLeft = ptrOtherFX->duration;
  
  // soundID, shift in CountSounds for 
  // this specific instance of the sound
  count = CountSounds();
  channel->soundID = (count << 0x10) | id;
  
  // save the frame that the channel started, frameTimer_MainFrame_ResetDB
  channel->startFrame = gGT->frameTimer_MainFrame_ResetDB;
  
  Smart_ExitCriticalSection();
  return channel->soundID;
}