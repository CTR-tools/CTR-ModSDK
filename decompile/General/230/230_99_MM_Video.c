#include <common.h>

// starts at 800b67ac
struct OVR_230_VideoBSS
{
    int field0_0x0;
    int field1_0x4;
    int field2_0x8;
    int field3_0xc;

    // 800b67b8
    short totalFrames;

    // 800b67bc
    short frameCounter;

    // 800b67c0
    short DCT_MODE;

    // 800b67c2
    short drawNextFrame;

    short field8_0x18;
    short field9_0x1a;
    short field10_0x1c;

    // 800b67ca
    short imgId;

    short field12_0x20;
    short field13_0x22;
    short field14_0x24;

    // padding?
    char unk800b67d0[2];

    // 800b67d4
    int numFrames;

    // 800b67d8
    int frameCount;

    int field19_0x30;
    int field20_0x34;
    int field21_0x38;

    // 800b67e8
    // 1 - IS_RGB24
    // 2 - has Audio
    // 4 - is looping
    // 8 - is Scrapbook (?)
    u_int flags;

    // 800b67ec
    int RING_SIZE;

    // 800b67f0
    u_int isDone;

    int field25_0x48;

	// field 26,27,28,29
    char unk800b67f8[4];

	// 30,31...
    // 800b67fc
    u_long* in_Buf[2];
	
	int field32_0x58;

    char field33_0x5c;
    char field34_0x5d;
    char field35_0x5e;
    char field36_0x5f;

    // 800b680c
    u_long *out_Buf[4];

    // 800b681c
    RECT slice;

    // 800b6824
    CdlLOC cdLocation1;

    // 800b6828
    CdlLOC cdLocation2;

    // 800b682c
    CdlLOC cdLocation3;
	
	// 800b6830
    CdlLOC* ptrCdLoc;
};

extern struct OVR_230_VideoBSS V230;

void MM_Video_DecDCToutCallbackFunc(void)
{
    if (((V230.flags & 1) != 0) && (*(u_int *)0x8009ebf8 != 0))
    {
        StCdInterrupt();

        // StCdIntrFlag
        *(u_int *)0x8009ebf8 = 0;
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

    if (BreakDraw() != 0)
    {
        DrawOTag(ot);
    }
}

void MM_Video_KickCD(CdlLOC *location)
{
    int iVar1;
    int CdlMode;
    u_char local_18[8];

    if ((location != NULL) && (V230.ptrCdLoc != &V230.cdLocation2))
    {
        V230.field12_0x20 = 0;
        V230.ptrCdLoc = location;
    }

    if (V230.field12_0x20 != 1)
    {
        if (1 < V230.field12_0x20)
        {
            if (V230.field12_0x20 == 2)
            {
                V230.field12_0x20 = 3;
                return;
            }

            if (V230.field12_0x20 != 3)
                return;

            // CdlModeStream2|CdlModeSpeed
            CdlMode = 0x1a0;

            // scrapbook
            // if video contains audio
            if ((V230.flags & 2) != 0)
            {
                // CdlModeStream2|CdlModeSpeed|CdlModeRT
                CdlMode = 0x1e0;
            }

            V230.field12_0x20 = 0;

            iVar1 = CdRead2(CdlMode);

            // fails?
            if (iVar1 == 0)
                return;

            V230.ptrCdLoc = 0;

            return;
        }

        if (V230.field12_0x20 != 0)
            return;

        // 2 = CdlSetloc
        iVar1 = CdControl(2, V230.ptrCdLoc, 0);

        // fails?
        if (iVar1 == 0)
            return;

        V230.field12_0x20 = 1;
    }

    // CdlModeSpeed
    local_18[0] = 0x80;

    // 0xe = CdlSetmode
    iVar1 = CdControl(0xe, local_18, 0);

    if (iVar1 != 0)
    {
        V230.field12_0x20 = 2;
    }
}

void MM_Video_VLC_Decode(void)
{
    short sVar1;
    int iVar2;
    int iVar3;
    u_long size;
    int WAIT_TIME;
    short local_30;
    short sStack_2e;
    u_long *local_2c;
    u_long *local_28[2];

    WAIT_TIME = 10; // frames

    // free sectors and over sectors
    StRingStatus(&local_30, sStack_2e);

    iVar2 = StGetBackloc(&V230.cdLocation2);

    sVar1 = V230.field9_0x1a;
    if ((V230.field9_0x1a == 1) &&
        ((V230.RING_SIZE - (V230.RING_SIZE >> 2)) <= local_30))
    {
        V230.field14_0x24++;

        if (400 < V230.field14_0x24)
        {
            V230.field14_0x24 = 0;
            StClearRing();
            V230.field8_0x18 = 0;
            V230.frameCount = 0;
            V230.field19_0x30 = 0;
            V230.field20_0x34 = 0;
            V230.field0_0x0 = -1;
            V230.field1_0x4 = -1;
            V230.field2_0x8 = 0;
            V230.field13_0x22 = 0;
            V230.field14_0x24 = 0;
            V230.field21_0x38 = 0xffffffff;
            V230.field9_0x1a = sVar1;

            MM_Video_KickCD(&V230.cdLocation1);
        }
    }
    else
    {
        V230.field14_0x24 = 0;

        // Scrapbook
        if (((V230.flags & 8) == 0) &&
            (local_30 < (V230.RING_SIZE >> 4)))
        {
            MM_Video_KickCD(&V230.cdLocation2);
        }

        if (iVar2 == V230.field20_0x34)
        {
            V230.field13_0x22++;
            if (0x40 < V230.field13_0x22)
            {
                {
                    V230.field13_0x22 = 0;
                    V230.drawNextFrame = 0;
                    StClearRing();
                    V230.field19_0x30 = 0;
                    V230.field0_0x0 = -1;
                    V230.field1_0x4 = -1;
                    V230.field2_0x8 = 0;
                    V230.field14_0x24 = 0;
                    V230.field20_0x34 = 0;
                    V230.field13_0x22 = 0;
                    V230.field21_0x38 = 0xffffffff;

                    MM_Video_KickCD(&V230.cdLocation3);
                }
            }
            else
            {
                V230.field13_0x22 = 0;
            }
            V230.field9_0x1a = 0;

            // if reached end of video,
            // choose to loop or not loop
            if (
                (V230.field0_0x0 < 0) &&

                // length of video
                ((V230.numFrames <= iVar2 ||

                  (iVar2 < V230.field20_0x34))))
            {
                // scrapbook not track select,
                // if video is not looping
                if ((V230.flags & 4) == 0)
                {
                    do
                    {
                        // 9 = CdlPause
                        iVar3 = CdControl(9, 0, 0);
                    } while (iVar3 == 0);
                    // end of scrapbook
                    V230.field8_0x18 = 1;
                }

                // track select, not scrapbook,
                // if video is looping
                else
                {
                    V230.field21_0x38 = 0xffffffff;
                    if (V230.field1_0x4 < 1)
                    {
                        MM_Video_KickCD(&V230.cdLocation1);

                        if (iVar2 == V230.numFrames)
                        {
                            V230.field1_0x4 = CdPosToInt(&V230.cdLocation2);
                        }
                        else
                        {
                            V230.field0_0x0 = CdPosToInt(&V230.cdLocation2);
                            V230.field0_0x0--;
                            V230.field2_0x8 = 0;
                        }
                    }
                    else
                    {
                        if (iVar2 != V230.numFrames)
                        {
                            iVar3 = CdPosToInt(&V230.cdLocation2);
                            if (V230.field1_0x4 < iVar3)
                            {
                                V230.field0_0x0 = CdPosToInt(&V230.cdLocation2);
                                V230.field0_0x0 = V230.field0_0x0 + -1;
                                V230.field2_0x8 = 0;

                                MM_Video_KickCD(&V230.cdLocation1);
                            }
                            V230.field1_0x4 = -1;
                        }
                    }
                }
            }
            V230.field19_0x30 = V230.frameCount;
            V230.field20_0x34 = iVar2;
        LAB_800b5fec:

            // retrieve data with timeout (10 frames)
            do
            {
                iVar3 = StGetNext(&local_2c, local_28);
                if (iVar3 == 0)
                {
                    // sector->frameCount
                    V230.frameCount = *(int *)(local_28[0] + 8);

                    if (V230.frameCount == V230.field19_0x30)
                    {
                        StFreeRing(local_2c);
                        goto LAB_800b5fec;
                    }

                    if (0 < V230.field0_0x0)
                    {
                        // sector->loc
                        iVar3 = CdPosToInt(local_28[0] + 0x1c);

                        WAIT_TIME = 10;

                        if (V230.field0_0x0 <= iVar3)
                        {
                            V230.field2_0x8 = 1;
                            StFreeRing(local_2c);
                            goto LAB_800b5fec;
                        }
                        if (V230.field2_0x8 == 1)
                        {
                            V230.field0_0x0 = -1;
                            V230.field2_0x8 = 0;
                            V230.field20_0x34 = iVar2;
                        }
                    }

                    size = DecDCTGetEnv(local_2c);

                    if (size <= V230.field25_0x48)
                    {
                        // sector->loc
                        V230.cdLocation3.minute = *(char *)((int)local_28[0] + 0x1c);
                        V230.cdLocation3.second = *(char *)((int)local_28[0] + 0x1d);
                        V230.cdLocation3.sector = *(char *)((int)local_28[0] + 0x1e);
                        V230.cdLocation3.track = *(char *)((int)local_28[0] + 0x1f);

                        // VLC Decode
                        // last parameter is "VLC Table"
                        DecDCTvlc2(local_2c, V230.in_Buf[V230.field10_0x1c], sdata->ptrVlcTable);

                        // ready to draw next frame
                        V230.drawNextFrame = 1;

                        StFreeRing(local_2c);
                        return;
                    }
                    V230.drawNextFrame = 0;
                    StFreeRing(local_2c);
                    return;
                }
                WAIT_TIME--;
            } while (WAIT_TIME != 0);
        }
        V230.drawNextFrame = 0;
    }
}

void MM_Video_StartStream(int param_1, int numFrames)
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

    CDSYS_SetMode_StreamData();

    // 800b6814 = Ring_Buf (mempack)
    StSetRing(V230.out_Buf[2], V230.RING_SIZE);

    StClearRing();

    V230.field12_0x20 = 0;

    V230.ptrCdLoc = &V230.cdLocation1;
}

void MM_Video_StopStream(void)
{
    int iVar1;

    iVar1 = CdDiskReady(1);
    if (iVar1 == 2)
    {
        do
        {
            // 9 = CdlPause
            iVar1 = CdControl(9, 0, 0);

        } while (iVar1 == 0);
    }

    StClearRing();

    StSetMask(1, 0, 0);

    CdDataCallback(0);

    CdReadyCallback(0);

    // Discontinue current decoding,
    // does not affect internal states (libref)
    DecDCTReset(1);

    V230.drawNextFrame = 0;
}

void MM_Video_AllocMem(u_int width, u_short height, u_int flags, int size, int param_5)
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

void MM_Video_ClearMem(void)
{
    MEMPACK_PopState();
}

u_int MM_Video_DecodeFrame(short offsetX, short offsetY)

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

u_int MM_Video_CheckIfFinished(int param_1)
{
    char bVar1;
    u_int uVar2;
    int iVar3;
    int local_20;
    int local_1c;

    local_20 = 40000;
    local_1c = 0x28;

    bVar1 = false;

    if (V230.drawNextFrame == 0)
    {
        uVar2 = 0;
    }
    else
    {

        do
        {
            if ((param_1 == 1) && (local_1c--, local_1c == 0))
            {
                iVar3 = CdDiskReady(1);
                
                if (iVar3 == 0x10)
                {
                    bVar1 = true;
                    V230.isDone = 1;
                }
                else
                {
                    local_1c = 0x28;
                }
            }

            local_20--;

            if (local_20 == 0)
            {
                V230.isDone = 1;
            }

        } while (!V230.isDone);

        do
        {
            iVar3 = IsIdleGPU(10000);

        } while (iVar3 != 0);

        V230.isDone = 0;

        V230.drawNextFrame = 0;

        if ((!bVar1) && (V230.frameCounter != V230.totalFrames))
        {
            // Discontinue current decoding,
            // does not affect internal states (libref)
            DecDCTReset(1);
        }

        // end of scrapbook
        uVar2 = (u_int)V230.field8_0x18;
    }
    return uVar2;
}
