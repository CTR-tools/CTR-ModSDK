#include <common.h>

// Initialize car engine audio system for one driver
short EngineAudio_InitOnce(u_int soundID,u_int sfx)

{
  struct ChannelStats* channel;
  u_int distortion = sfx >> 8;
  u_int volume = sfx >> 0x10;
  u_short echo = sfx >> 0x18;
  u_short leftRight = sfx & 0xff;

  struct ChannelAttr* auStack48 [10];

  if (sdata->boolAudioEnabled != 0) {
    soundID = soundID & 0xffff;

	if (soundID < (sdata->ptrHowlHeader + 0x18))
	{
      channel = sdata->howl_metaEngineFX + soundID * 8;

      if (((channel + 6) * 4 + sdata->howl_spuAddrs) != 0)
	  {
		// make ChannelAttr from howl pointer somehow
		howl_InitChannelAttr_EngineFX(channel,auStack48,volume,leftRight,distortion);

        Smart_EnterCriticalSection();

		// Channel_AllocSlot
        channel = FUN_8002b7d0(0x7c,auStack48);

		// if channel was found
        if (channel != 0)
		{
          channel->type = 0;
          channel->unk2 = 0;
          channel->echo = echo;
          channel->vol = volume;
          channel->distort = distortion;
          channel->LeftRight = leftRight;

		  // duration
          channel->timeLeft = 0;

          channel->soundID = soundID;
          channel->flags |= 4;
        }

        Smart_ExitCriticalSection();

		return (channel != 0);
      }
    }
  }
  return 0;
}