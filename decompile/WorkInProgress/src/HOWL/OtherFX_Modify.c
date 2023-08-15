#include <common.h>

u_int DECOMP_OtherFX_Modify(u_int soundId, u_int flags) {
    struct ChannelStats* channel;
    struct ChannelAttr channelAttr;
    char modify;
    struct OtherFX* ptrOtherFX;
    u_int distort;
    u_int volume;
    u_short echo;

    if (
        // if audio is disabled
        (sdata->boolAudioEnabled == 0) ||
        ((sdata->ptrHowlHeader + 0x14) <= (soundId & 0xffff))
    ) 
    {
        // return failure
        return 0;
    } 

    // metaOtherFX
    ptrOtherFX = &sdata->howl_metaOtherFX[soundId & 0xffff];
    volume = flags >> 0x10 & 0xff;
    distort = flags >> 8 & 0xff;
    echo = flags >> 0x18;

    // volume of FX
    modify = sdata->vol_FX;
    if ((ptrOtherFX->flags & 4) != 0) {
        // volume of Voice
        modify = sdata->vol_Voice;
    }
    if (distort == 0x80) {
        channelAttr.pitch = ptrOtherFX->pitch;
    } else {
        channelAttr.pitch = ptrOtherFX->pitch * (data.distortConst_OtherFX[distort] >> 0x10);
    }

    channelAttr.reverb = echo;

    Channel_SetVolume(&channelAttr, modify * ptrOtherFX->volume * volume >> 10, flags & 0xff);

    channelAttr.reverb = echo;

    Smart_EnterCriticalSection();

        // 1 - otherFX
        channel = Channel_SearchFX_EditAttr(1, soundId, 0x70, &channelAttr);

        if (channel != NULL) {
            channel->echo = (char)echo;
            channel->vol = (char)volume;
            channel->distort = (char)distort;
            channel->LeftRight = (char)(flags & 0xff);
        }

    Smart_ExitCriticalSection();
    // return success
    return 1;
}