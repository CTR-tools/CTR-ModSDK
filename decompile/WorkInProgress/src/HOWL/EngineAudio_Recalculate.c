#include <common.h>

short DECOMP_EngineAudio_Recalculate(u_int soundID,u_int sfx)
{
  int iVar1;
  u_int distortion = sfx >> 8;
  u_int volume = sfx >> 0x10;
  u_short echo = sfx >> 0x18;
  u_short leftRight = sfx & 0xff;
  struct ChannelStats* channel;

  struct ChanneAttr* channelAttr;

  if (sdata->boolAudioEnabled == 0) {
    return 0;
  }
  if ((sdata->ptrHowlHeader + 0x18) <= (soundID & 0xffff)) {
    return 0;
  }

  // === Use EngineFX* not Channel* for this ===

  channel = &sdata->howl_metaEngineFX[soundID & 0xffff];

  // if numPlyrCurrGame is 2
  if (sdata->gGT->numPlyrCurrGame == 2) {
    iVar1 = volume * 0x37;
  }

  // if numPlyrCurrGame is not 2
  else
  {
	// if numPlyrCurrGame is less than 3
	// which would only be for 1P mode
    if (sdata->gGT->numPlyrCurrGame < 3) goto LAB_80028a78;

	// this line \/ only happens in 3P or 4P
	// cause 1P will use GOTO on the line above ^^^
	iVar1 = volume * 0x2d;
  }
  volume = (iVar1 << 2) >> 8;
LAB_80028a78:

  Channel_SetVolume(&channelAttr,sdata->vol_FX * (channel + 1) * volume >> 10, sfx);

  if (distortion == 0x80)
  {
    channelAttr.pitch = (channel + 2);
  }

  else
  {
    channelAttr.pitch = ((channel + 2) * (&data.distortConst_Engine[distortion]) >> 0x10);
  }

  channelAttr.reverb = echo;

  Smart_EnterCriticalSection();

  // 0 - engineFX
  channel = Channel_SearchFX_EditAttr(0,soundID & 0xffff,0x70,&channelAttr);

  // if slot found
  if (channel != 0)
  {
    channel->echo = echo;
    channel->vol = volume;
    channel->distort = distortion;
    channel->LeftRight = leftRight;
  }

  Smart_ExitCriticalSection();

  return 1;
}
