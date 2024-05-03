#include <common.h>

void DECOMP_MM_Video_StartStream(int param_1, int numFrames)
{
    V230.field3_0xc = 0;
    V230.field8_0x18 = 0;
    V230.field9_0x1a = 1;

    V230.isDone = 0;

    V230.frameCount = 0;
    V230.field19_0x30 = 0;
    V230.field20_0x34 = 0;
    V230.field0_0x0 = 0xffffffff;
    V230.field1_0x4 = 0xffffffff;
    V230.field2_0x8 = 0;
    V230.field13_0x22 = 0;
    V230.field14_0x24 = 0;
    V230.field21_0x38 = 0xffffffff;
    V230.drawNextFrame = 0;

    V230.numFrames = numFrames;

    // start streaming video
    CdIntToPos(param_1, &V230.cdLocation1);

    // V230.flags & 1 = IS_RGB24
    // next parameter (0) = START_FRAME
    StSetStream((V230.flags & 1), 0, 0xffffffff, 0, 0);

    DECOMP_CDSYS_SetMode_StreamData();

    // 800b6814 = Ring_Buf (mempack)
    StSetRing(V230.out_Buf[2], V230.RING_SIZE);

    StClearRing();

    V230.field12_0x20 = 0;

    V230.ptrCdLoc = &V230.cdLocation1;
}
