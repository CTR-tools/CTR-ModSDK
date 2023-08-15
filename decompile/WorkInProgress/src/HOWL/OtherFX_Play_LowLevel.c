#include <common.h>

short DECOMP_OtherFX_Play_LowLevel(u_int soundID, char boolAntiSpam, u_int flags)
{
  struct GameTracker* gGT = sdata->gGT;;
  struct ChannelStats* channel;
  int count;
  short id;
  struct OtherFX* ptrOtherFX;
  u_int distortion = flags >> 8;
  u_int volume = flags >> 0x10;
  u_short echo = flags >> 0x18;

  struct ChannelAttr* channelAttr [10];

  if (sdata->boolAudioEnabled != 0)
  {
	// cast to short
    id = soundID & 0xffff;
	if (
			// if not out of bounds
			(id < (sdata->ptrHowlHeader + 0x14)) &&
			(
				// get pointer to cseq audio, given soundID
				ptrOtherFX = &sdata->howl_metaOtherFX[id],

				// spu addresses
				sdata->howl_spuAddrs[ptrOtherFX->spuIndex] != 0
			)
        )
	{
      howl_InitChannelAttr_OtherFX(ptrOtherFX, channelAttr, volume, flags & 0xff, distortion);

      Smart_EnterCriticalSection();

      if (
			// if play with duplicates
			(boolAntiSpam != 2) ||
			(
				channel = Channel_FindSound(id),
				// if sound is not playing
				channel == 0
			)
		  )
	  {
        channel = Channel_AllocSlot_AntiSpam(id,boolAntiSpam,0x7c,channelAttr);

		// if free channel slot was found
		if (channel != 0)
		{
          if ((ptrOtherFX->flags & 2) != 0) {
            channel->flags |= 4;
          }

		  // type otherFX
		  channel->type = 1;

          channel->unk2 = 0;

          channel->echo = echo;

          channel->vol = volume;

          channel->distort = distortion;

          channel->LeftRight = flags;

		  // duration
          channel->timeLeft = ptrOtherFX->duration;

          count = CountSounds();

		  // CountSounds shifted in
          channel->soundID = count << 0x10 | id;

		  // save the frame that the channel started, frameTimer_MainFrame_ResetDB
          channel->startFrame = gGT->frameTimer_MainFrame_ResetDB;
        }
        Smart_ExitCriticalSection();

        return channel->soundID;
      }
      Smart_ExitCriticalSection();
    }
  }
  return 0;
}