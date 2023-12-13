#include <common.h>

u_int DECOMP_OtherFX_Modify(u_int soundId, u_int flags)
{
    struct ChannelStats* channel;
    struct ChannelAttr channelAttr;
    int modify;
    struct OtherFX* ptrOtherFX;
    u_int distort;
    u_int volume;
    u_short echo;
	u_short LR;

	if (sdata->boolAudioEnabled == 0) return 0;

	// quit if out of bounds
    if ((sdata->ptrHowlHeader->numOtherFX) <= (soundId & 0xffff))
        return 0;

    // metaOtherFX
    ptrOtherFX = &sdata->howl_metaOtherFX[soundId & 0xffff];
    volume = flags >> 0x10 & 0xff;
    distort = flags >> 8 & 0xff;
    echo = flags >> 0x18;
	LR = flags & 0xff;

    // volume of FX
    modify = sdata->vol_FX;
    if ((ptrOtherFX->flags & 4) != 0) {
        // volume of Voice
        modify = sdata->vol_Voice;
    }
	
	// no distortion
    if (distort == 0x80) 
	{
        channelAttr.pitch = ptrOtherFX->pitch;
    } 
	
	// distortion
	else 
	{
        channelAttr.pitch = ptrOtherFX->pitch * data.distortConst_OtherFX[distort] >> 0x10;
    }

    DECOMP_Channel_SetVolume(&channelAttr, modify * ptrOtherFX->volume * volume >> 10, LR);
    channelAttr.reverb = echo;

    DECOMP_Smart_EnterCriticalSection();

    // 1 - otherFX
	// soundID & 0xffffffff, search for specific instance
    channel = DECOMP_Channel_SearchFX_EditAttr(1, soundId, 0x70, &channelAttr);

    if (channel != 0) 
	{
        channel->echo = echo;
        channel->vol = volume;
        channel->distort = distort;
        channel->LR = LR;
    }

    DECOMP_Smart_ExitCriticalSection();
	
    return 1;
}