#include <common.h>

// 272/304

// Initialize car engine audio system for one driver
char DECOMP_EngineAudio_InitOnce(u_int soundID,u_int flags)

{
  struct EngineFX* ptrEngineFX;
  struct ChannelStats* channel; 
  u_int distortion = flags >> 8;
  u_int volume = flags >> 0x10;
  u_short echo = flags >> 0x18;
  u_short LR = flags & 0xff;
  struct ChannelAttr channelAttr;

  if (sdata->boolAudioEnabled == 0) return 0;
  
  // check out of bounds
  soundID = soundID & 0xffff;
  if (soundID >= sdata->ptrHowlHeader->numEngineFX) return 0;

  // check sound is loaded
  ptrEngineFX = &sdata->howl_metaEngineFX[soundID];
  if (sdata->howl_spuAddrs[ptrEngineFX->spuIndex].spuAddr == 0) return 0;
  
  // make ChannelAttr from howl pointer somehow
  DECOMP_howl_InitChannelAttr_EngineFX(ptrEngineFX,&channelAttr,volume,LR,distortion);
  
  DECOMP_Smart_EnterCriticalSection();
  
  channel = DECOMP_Channel_AllocSlot(0x7c,&channelAttr);
  
  // if channel was found
  if (channel != 0)
  {
	// type engineFX
    channel->type = 0;
    channel->unk2 = 0;
    channel->echo = echo;
    channel->vol = volume;
    channel->distort = distortion;
    channel->LR = LR;
    channel->timeLeft = 0;
    channel->soundID = soundID;
    channel->flags |= 4;
  }
  
  DECOMP_Smart_ExitCriticalSection();
  
  return (channel != 0);
}