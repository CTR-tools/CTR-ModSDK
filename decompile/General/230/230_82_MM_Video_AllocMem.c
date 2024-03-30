#include <common.h>

void DECOMP_MM_Video_AllocMem(u_int width, u_short height, u_int flags, int size, int param_5)
{
    char isRGB24;
    u_int uVar2;
    int iVar3;

    MEMPACK_PushState();

    // just in case
    width &= 0xffff;
    height &= 0xffff;

    V230.RING_SIZE = size;

    if (size < 1)
    {
        V230.RING_SIZE = 0x40;
    }

    isRGB24 = (flags & 1);

    iVar3 = (isRGB24) ? 3 : 2;
    
    V230.DCT_MODE = (u_short)isRGB24;

    uVar2 = (((height - 1) >> 4) + 1) * 0x10;
    V230.totalFrames = (((width - 1) >> 4) + 1U) - 1;
    V230.imgId = 0;
    V230.field10_0x1c = 0;
    V230.field32_0x58 = (int)(iVar3 * 8 * uVar2) >> 1;
    V230.field25_0x48 = (int)(((width * iVar3) >> 1) * uVar2) >> (param_5 + 1U);
    V230.flags = flags;

    V230.out_Buf[0] = MEMPACK_AllocMem(V230.field32_0x58 << 3);//, OVR_230.s_SliceBuf);
    V230.out_Buf[1] = (int)V230.out_Buf[0] + V230.field32_0x58 * 4;

    V230.in_Buf[0] = MEMPACK_AllocMem(V230.field25_0x48 << 3);//, OVR_230.s_VlcBuf);
    V230.in_Buf[1] = (int)V230.in_Buf[0] + V230.field25_0x48 * 4;

    V230.out_Buf[2] = MEMPACK_AllocMem(V230.RING_SIZE << 0xb);//, OVR_230.s_RingBuf);

    V230.slice.x = 0;
    V230.slice.y = 0;
    V230.slice.w = (short)(iVar3 << 3);
    V230.slice.h = height;

    // reinitialize everything
    DecDCTReset(0);

    DecDCTvlcSize2(V230.field25_0x48);

    EnterCriticalSection();

    DecDCToutCallback(&MM_Video_DecDCToutCallbackFunc);

    ExitCriticalSection();
}
