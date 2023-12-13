#include <common.h>

short DECOMP_EngineAudio_Recalculate(u_int soundID,u_int sfx)
{
  int iVar1;
  u_int distortion = (sfx >> 8) & 0xff;
  u_int volume = (sfx >> 0x10) & 0xff;
  u_short echo = (sfx >> 0x18) & 0xff;
  u_short LR = sfx & 0xff;
  
  struct EngineFX* ptrEngineFX;
  struct ChannelStats* channel;
  struct ChannelAttr channelAttr;
  struct GameTracker* gGT;

  if (sdata->boolAudioEnabled == 0) 
	return 0;

  soundID = soundID & 0xffff;
  if (sdata->ptrHowlHeader->numEngineFX <= soundID)
	return 0;

  gGT = sdata->gGT;

  ptrEngineFX = &sdata->howl_metaEngineFX[soundID];

  if (gGT->numPlyrCurrGame > 1)
  {
	// 3P/4P game
	iVar1 = volume * 0x2d;
	  
	// 2P game
	if (gGT->numPlyrCurrGame == 2) {
		iVar1 = volume * 0x37;
	}

	volume = (iVar1 << 2) >> 8;
  }

  // no distortion
  if (distortion == 0x80)
  {
    channelAttr.pitch = ptrEngineFX->pitch;
  }

  // distortion
  else
  {
    channelAttr.pitch = ptrEngineFX->pitch * data.distortConst_Engine[distortion] >> 0x10;
  }
  
  DECOMP_Channel_SetVolume(&channelAttr, sdata->vol_FX * ptrEngineFX->volume * volume >> 10, LR);
  channelAttr.reverb = echo;

  DECOMP_Smart_EnterCriticalSection();

  // 0 - engineFX
  // soundID & 0xffff, dont search for specific instance
  channel = DECOMP_Channel_SearchFX_EditAttr(0,soundID,0x70,&channelAttr);

  if (channel != 0)
  {
    channel->echo = echo;
    channel->vol = volume;
    channel->distort = distortion;
    channel->LR = LR;
  }

  DECOMP_Smart_ExitCriticalSection();

  return 1;
}
