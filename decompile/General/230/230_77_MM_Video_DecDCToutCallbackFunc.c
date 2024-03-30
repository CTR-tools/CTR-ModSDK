#include <common.h>

void DECOMP_MM_Video_DecDCToutCallbackFunc(void)
{
	// part of PSYQ BSS
	#define StCdIntrFlag *(u_int *)0x8009ebf8
	
    if (((V230.flags & 1) != 0) && (StCdIntrFlag != 0))
    {
        StCdInterrupt();

        StCdIntrFlag = 0;
    }

    u_long *ot = BreakDraw();

    LoadImage(&V230.slice, V230.out_Buf[V230.imgId]);

    /* update slice (rectangular strip) area to next one on the right */
    V230.slice.x += V230.slice.w;
    V230.imgId ^= 1;

    if (V230.frameCounter == V230.totalFrames)
    {
        V230.isDone = 1;
    }
    else
    {
        V230.frameCounter++;
        DecDCTout(V230.out_Buf[V230.imgId], V230.field32_0x58);
    }

    if (ot != 0)
    {
        DrawOTag(ot);
    }
}