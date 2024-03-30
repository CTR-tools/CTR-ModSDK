#include <common.h>

u_int DECOMP_MM_Video_DecodeFrame(short offsetX, short offsetY)

{
    int iVar1;
    u_int boolDraw;

    iVar1 = CdDiskReady(1);
    if (V230.field3_0xc == 1)
    {
        if (iVar1 == 2)
        {
            V230.field3_0xc = 0;
            V230.drawNextFrame = 0;
            MM_Video_KickCD(&V230.cdLocation3);
            return 0;
        }
    }
    else
    {
        if (iVar1 == 0x10)
        {
            V230.field9_0x1a = 1;
            V230.field14_0x24 = 0;
            V230.field3_0xc = 1;
            V230.field20_0x34 = V230.frameCount - 1;
            StClearRing();
        }
    }
    if (V230.field3_0xc == 1)
    {
        V230.drawNextFrame = 0;
        boolDraw = 0;
    }
    else
    {
        if (V230.ptrCdLoc != 0)
        {
            MM_Video_KickCD(0);
        }

        MM_Video_VLC_Decode();

        // if value is zero, return zero,
        // not ready to draw
        boolDraw = V230.drawNextFrame;

        if (V230.drawNextFrame == 1)
        {
            V230.frameCounter = 0;

            V230.slice.x = offsetX;
            V230.slice.y = offsetY;

            // start decoding video
            DecDCTin(V230.in_Buf[V230.field10_0x1c], V230.DCT_MODE);

            V230.field10_0x1c ^= 1;

            // get result of decoding
            DecDCTout(V230.out_Buf[V230.imgId], V230.field32_0x58);

            // return 1, ready to draw
            boolDraw = (u_int)V230.drawNextFrame;
        }
    }
    return boolDraw;
}
