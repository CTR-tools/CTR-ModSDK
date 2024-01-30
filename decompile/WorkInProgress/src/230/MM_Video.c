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

    char unk800b67f8[4];

    // 800b67fc
    u_long* in_Buf[4];

    // char field33_0x5c;
    // char field34_0x5d;
    // char field35_0x5e;
    // char field36_0x5f;

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
};

void MM_Video_DecDCToutCallbackFunc(void)
{
    if (((OVR_230_VideoBSS.flags & 1) != 0) && (*(u_int *)0x8009ebf8 != 0))
    {
        StCdInterrupt();

        // StCdIntrFlag
        *(u_int *)0x8009ebf8 = 0;
    }

    u_long *ot = BreakDraw();

    LoadImage(&OVR_230_VideoBSS.slice, OVR_230_VideoBSS.out_Buf[OVR_230_VideoBSS.imgId]);

    /* update slice (rectangular strip) area to next one on the right */
    OVR_230_VideoBSS.slice.x += OVR_230_VideoBSS.slice.w;
    OVR_230_VideoBSS.imgId ^= 1;

    if (OVR_230_VideoBSS.frameCounter == OVR_230_VideoBSS.totalFrames)
    {
        OVR_230_VideoBSS.isDone = 1;
    }
    else
    {
        OVR_230_VideoBSS.frameCounter++;
        DecDCTout(OVR_230_VideoBSS.out_Buf[OVR_230_VideoBSS.imgId], OVR_230_VideoBSS.field32_0x58)
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

    if ((location != NULL) && ((char *)0x800b6830 != &OVR_230_VideoBSS.cdLocation2))
    {
        OVR_230_VideoBSS.field12_0x20 = 0;
        (char *)0x800b6830 = location;
    }

    if (OVR_230_VideoBSS.field12_0x20 != 1)
    {
        if (1 < OVR_230_VideoBSS.field12_0x20)
        {
            if (OVR_230_VideoBSS.field12_0x20 == 2)
            {
                OVR_230_VideoBSS.field12_0x20 = 3;
                return;
            }

            if (OVR_230_VideoBSS.field12_0x20 != 3)
                return;

            // CdlModeStream2|CdlModeSpeed
            CdlMode = 0x1a0;

            // scrapbook
            // if video contains audio
            if ((OVR_230_VideoBSS.flags & 2) != 0)
            {
                // CdlModeStream2|CdlModeSpeed|CdlModeRT
                CdlMode = 0x1e0;
            }

            OVR_230_VideoBSS.field12_0x20 = 0;

            iVar1 = CdRead2(CdlMode);

            // fails?
            if (iVar1 == 0)
                return;

            *(char *)0x800b6830 = 0;

            return;
        }

        if (OVR_230_VideoBSS.field12_0x20 != 0)
            return;

        // 2 = CdlSetloc
        iVar1 = CdControl(2, (char *)0x800b6830, 0);

        // fails?
        if (iVar1 == 0)
            return;

        OVR_230_VideoBSS.field12_0x20 = 1;
    }

    // CdlModeSpeed
    local_18[0] = 0x80;

    // 0xe = CdlSetmode
    iVar1 = CdControl(0xe, local_18, 0);

    if (iVar1 != 0)
    {
        OVR_230_VideoBSS.field12_0x20 = 2;
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

    iVar2 = StGetBackloc(&OVR_230_VideoBSS.cdLocation2);

    sVar1 = OVR_230_VideoBSS.field9_0x1a;
    if ((OVR_230_VideoBSS.field9_0x1a == 1) &&
        ((OVR_230_VideoBSS.RING_SIZE - (OVR_230_VideoBSS.RING_SIZE >> 2)) <= local_30))
    {
        OVR_230_VideoBSS.field14_0x24++;

        if (400 < OVR_230_VideoBSS.field14_0x24)
        {
            OVR_230_VideoBSS.field14_0x24 = 0;
            StClearRing();
            OVR_230_VideoBSS.field8_0x18 = 0;
            OVR_230_VideoBSS.frameCount = 0;
            OVR_230_VideoBSS.field19_0x30 = 0;
            OVR_230_VideoBSS.field20_0x34 = 0;
            OVR_230_VideoBSS.field0_0x0 = -1;
            OVR_230_VideoBSS.field1_0x4 = -1;
            OVR_230_VideoBSS.field2_0x8 = 0;
            OVR_230_VideoBSS.field13_0x22 = 0;
            OVR_230_VideoBSS.field14_0x24 = 0;
            OVR_230_VideoBSS.field21_0x38 = 0xffffffff;
            OVR_230_VideoBSS.field9_0x1a = sVar1;

            MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation1);
        }
    }
    else
    {
        OVR_230_VideoBSS.field14_0x24 = 0;

        // Scrapbook
        if (((OVR_230_VideoBSS.flags & 8) == 0) &&
            (local_30 < (OVR_230_VideoBSS.RING_SIZE >> 4)))
        {
            MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation2);
        }

        if (iVar2 == OVR_230_VideoBSS.field20_0x34)
        {
            OVR_230_VideoBSS.field13_0x22++;
            if (0x40 < OVR_230_VideoBSS.field13_0x22)
            {
                {
                    OVR_230_VideoBSS.field13_0x22 = 0;
                    OVR_230_VideoBSS.drawNextFrame = 0;
                    StClearRing();
                    OVR_230_VideoBSS.field19_0x30 = 0;
                    OVR_230_VideoBSS.field0_0x0 = -1;
                    OVR_230_VideoBSS.field1_0x4 = -1;
                    OVR_230_VideoBSS.field2_0x8 = 0;
                    OVR_230_VideoBSS.field14_0x24 = 0;
                    OVR_230_VideoBSS.field20_0x34 = 0;
                    OVR_230_VideoBSS.field13_0x22 = 0;
                    OVR_230_VideoBSS.field21_0x38 = 0xffffffff;

                    MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation3);
                }
            }
            else
            {
                OVR_230_VideoBSS.field13_0x22 = 0;
            }
            OVR_230_VideoBSS.field9_0x1a = 0;

            // if reached end of video,
            // choose to loop or not loop
            if (
                (OVR_230_VideoBSS.field0_0x0 < 0) &&

                // length of video
                ((OVR_230_VideoBSS.numFrames <= iVar2 ||

                  (iVar2 < OVR_230_VideoBSS.field20_0x34))))
            {
                // scrapbook not track select,
                // if video is not looping
                if ((OVR_230_VideoBSS.flags & 4) == 0)
                {
                    do
                    {
                        // 9 = CdlPause
                        iVar3 = CdControl(9, 0, 0);
                    } while (iVar3 == 0);
                    // end of scrapbook
                    OVR_230_VideoBSS.field8_0x18 = 1;
                }

                // track select, not scrapbook,
                // if video is looping
                else
                {
                    OVR_230_VideoBSS.field21_0x38 = 0xffffffff;
                    if (OVR_230_VideoBSS.field1_0x4 < 1)
                    {
                        MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation1);

                        if (iVar2 == OVR_230_VideoBSS.numFrames)
                        {
                            OVR_230_VideoBSS.field1_0x4 = CdPosToInt(&OVR_230_VideoBSS.cdLocation2);
                        }
                        else
                        {
                            OVR_230_VideoBSS.field0_0x0 = CdPosToInt(&OVR_230_VideoBSS.cdLocation2);
                            OVR_230_VideoBSS.field0_0x0--;
                            OVR_230_VideoBSS.field2_0x8 = 0;
                        }
                    }
                    else
                    {
                        if (iVar2 != OVR_230_VideoBSS.numFrames)
                        {
                            iVar3 = CdPosToInt(&OVR_230_VideoBSS.cdLocation2);
                            if (OVR_230_VideoBSS.field1_0x4 < iVar3)
                            {
                                OVR_230_VideoBSS.field0_0x0 = CdPosToInt(&OVR_230_VideoBSS.cdLocation2);
                                OVR_230_VideoBSS.field0_0x0 = OVR_230_VideoBSS.field0_0x0 + -1;
                                OVR_230_VideoBSS.field2_0x8 = 0;

                                MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation1);
                            }
                            OVR_230_VideoBSS.field1_0x4 = -1;
                        }
                    }
                }
            }
            OVR_230_VideoBSS.field19_0x3 = OVR_230_VideoBSS.frameCount;
            OVR_230_VideoBSS.field20_0x34 = iVar2;
        LAB_800b5fec:

            // retrieve data with timeout (10 frames)
            do
            {
                iVar3 = StGetNext(&local_2c, local_28);
                if (iVar3 == 0)
                {
                    // sector->frameCount
                    OVR_230_VideoBSS.frameCount = *(int *)(local_28[0] + 8);

                    if (OVR_230_VideoBSS.frameCount == OVR_230_VideoBSS.field19_0x3)
                    {
                        StFreeRing(local_2c);
                        goto LAB_800b5fec;
                    }

                    if (0 < OVR_230_VideoBSS.field0_0x0)
                    {
                        // sector->loc
                        iVar3 = CdPosToInt(local_28[0] + 0x1c);

                        WAIT_TIME = 10;

                        if (OVR_230_VideoBSS.field0_0x0 <= iVar3)
                        {
                            OVR_230_VideoBSS.field2_0x8 = 1;
                            StFreeRing(local_2c);
                            goto LAB_800b5fec;
                        }
                        if (OVR_230_VideoBSS.field2_0x8 == 1)
                        {
                            OVR_230_VideoBSS.field0_0x0 = -1;
                            OVR_230_VideoBSS.field2_0x8 = 0;
                            OVR_230_VideoBSS.field20_0x34 = iVar2;
                        }
                    }

                    size = DecDCTBufSize(local_2c);

                    if (size <= OVR_230_VideoBSS.field25_0x48)
                    {
                        // sector->loc
                        OVR_230_VideoBSS.cdLocation3.minute = *(char *)((int)local_28[0] + 0x1c);
                        OVR_230_VideoBSS.cdLocation3.second = *(char *)((int)local_28[0] + 0x1d);
                        OVR_230_VideoBSS.cdLocation3.sector = *(char *)((int)local_28[0] + 0x1e);
                        OVR_230_VideoBSS.cdLocation3.track = *(char *)((int)local_28[0] + 0x1f);

                        // VLC Decode
                        // last parameter is "VLC Table"
                        DecDCTvlc2(local_2c, OVR_230_VideoBSS.in_buf[OVR_230_VideoBSS.field10_0x1c], sdata->ptrVlcTable);

                        // ready to draw next frame
                        OVR_230_VideoBSS.drawNextFrame = 1;

                        StFreeRing(local_2c);
                        return;
                    }
                    OVR_230_VideoBSS.drawNextFrame = 0;
                    StFreeRing(local_2c);
                    return;
                }
                WAIT_TIME--;
            } while (WAIT_TIME != 0);
        }
        OVR_230_VideoBSS.drawNextFrame = 0;
    }
}

void MM_Video_StartStream(int param_1, int numFrames)
{
    OVR_230_VideoBSS.field3_0xc = 0;
    OVR_230_VideoBSS.field8_0x18 = 0;
    OVR_230_VideoBSS.field9_0x1a = 1;

    OVR_230_VideoBSS.isDone = 0;

    OVR_230_VideoBSS.frameCount = 0;
    OVR_230_VideoBSS.field19_0x3 = 0;
    OVR_230_VideoBSS.field20_0x34 = 0;
    OVR_230_VideoBSS.field0_0x0 = 0xffffffff;
    OVR_230_VideoBSS.field1_0x4 = 0xffffffff;
    OVR_230_VideoBSS.field2_0x8 = 0;
    OVR_230_VideoBSS.field13_0x22 = 0;
    OVR_230_VideoBSS.field14_0x24 = 0;
    OVR_230_VideoBSS.field21_0x38 = 0xffffffff;
    OVR_230_VideoBSS.drawNextFrame = 0;

    OVR_230_VideoBSS.numFrames = numFrames;

    // start streaming video
    CdIntToPos(param_1, &OVR_230_VideoBSS.cdLocation1);

    // OVR_230_VideoBSS.flags & 1 = IS_RGB24
    // next parameter (0) = START_FRAME
    StSetStream((OVR_230_VideoBSS.flags & 1), 0, 0xffffffff, 0, 0);

    CDSYS_SetMode_StreamData();

    // 800b6814 = Ring_Buf (mempack)
    StSetRing(OVR_230_VideoBSS.out_Buf[2], OVR_230_VideoBSS.RING_SIZE);

    StClearRing();

    OVR_230_VideoBSS.field12_0x20 = 0;

    (char *)0x800b6830 = &OVR_230_VideoBSS.cdLocation1;
}

void MM_Video_StopStream(void)
{
    int iVar1;

    iVar1 = FUN_80078bf8(1);
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

    OVR_230_VideoBSS.drawNextFrame = 0;
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

    OVR_230_VideoBSS.RING_SIZE = size;

    if (size < 1)
    {
        OVR_230_VideoBSS.RING_SIZE = 0x40;
    }

    isRGB24 = (flags & 1);

    iVar3 = (isRGB24) ? 3 : 2;
    
    OVR_230_VideoBSS.DCT_MODE = (u_short)isRGB24;

    uVar2 = (((height - 1) >> 4) + 1) * 0x10;
    OVR_230_VideoBSS.totalFrames = (((width - 1) >> 4) + 1U) - 1;
    OVR_230_VideoBSS.imgId = 0;
    OVR_230_VideoBSS.field10_0x1c = 0;
    OVR_230_VideoBSS.field32_0x58 = (int)(iVar3 * 8 * uVar2) >> 1;
    OVR_230_VideoBSS.field25_0x48 = (int)(((width * iVar3) >> 1) * uVar2) >> (param_5 + 1U);
    OVR_230_VideoBSS.flags = flags;

    OVR_230_VideoBSS.out_Buf[0] = MEMPACK_AllocMem(OVR_230_VideoBSS.field32_0x58 << 3, OVR_230.s_SliceBuf);
    OVR_230_VideoBSS.out_Buf[1] = (int)OVR_230_VideoBSS.out_Buf[0] + OVR_230_VideoBSS.field32_0x58 * 4;

    OVR_230_VideoBSS.in_buf[0] = MEMPACK_AllocMem(OVR_230_VideoBSS.field25_0x48 << 3, OVR_230.s_VlcBuf);
    OVR_230_VideoBSS.in_buf[1] = (int)OVR_230_VideoBSS.in_buf[0] + OVR_230_VideoBSS.field25_0x48 * 4;

    OVR_230_VideoBSS.out_Buf[2] = MEMPACK_AllocMem(OVR_230_VideoBSS.RING_SIZE << 0xb, OVR_230.s_RingBuf);

    OVR_230_VideoBSS.slice.x = 0;
    OVR_230_VideoBSS.slice.y = 0;
    OVR_230_VideoBSS.slice.w = (short)(iVar3 << 3);
    OVR_230_VideoBSS.slice.h = height;

    // reinitialize everything
    DecDCTReset(0);

    DecDCTvlcSize2(OVR_230_VideoBSS.field25_0x48);

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

    iVar1 = FUN_80078bf8(1);
    if (OVR_230_VideoBSS.field3_0xc == 1)
    {
        if (iVar1 == 2)
        {
            OVR_230_VideoBSS.field3_0xc = 0;
            OVR_230_VideoBSS.drawNextFrame = 0;
            MM_Video_KickCD(&OVR_230_VideoBSS.cdLocation3);
            return 0;
        }
    }
    else
    {
        if (iVar1 == 0x10)
        {
            OVR_230_VideoBSS.field9_0x1a = 1;
            OVR_230_VideoBSS.field14_0x24 = 0;
            OVR_230_VideoBSS.field3_0xc = 1;
            OVR_230_VideoBSS.field20_0x34 = OVR_230_VideoBSS.frameCount - 1;
            StClearRing();
        }
    }
    if (OVR_230_VideoBSS.field3_0xc == 1)
    {
        OVR_230_VideoBSS.drawNextFrame = 0;
        boolDraw = 0;
    }
    else
    {
        if ((char*)0x800b6830 != 0)
        {
            MM_Video_KickCD(0);
        }

        MM_Video_VLC_Decode();

        // if value is zero, return zero,
        // not ready to draw
        boolDraw = OVR_230_VideoBSS.drawNextFrame;

        if (OVR_230_VideoBSS.drawNextFrame == 1)
        {
            OVR_230_VideoBSS.frameCounter = 0;

            OVR_230_VideoBSS.slice.x = offsetX;
            OVR_230_VideoBSS.slice.y = offsetY;

            // start decoding video
            DecDCTin(OVR_230_VideoBSS.in_buf[OVR_230_VideoBSS.field10_0x1c], OVR_230_VideoBSS.DCT_MODE);

            OVR_230_VideoBSS.field10_0x1c ^= 1;

            // get result of decoding
            DecDCTout(OVR_230_VideoBSS.out_Buf[OVR_230_VideoBSS.imgId], OVR_230_VideoBSS.field32_0x58);

            // return 1, ready to draw
            boolDraw = (u_int)OVR_230_VideoBSS.drawNextFrame;
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

    if (OVR_230_VideoBSS.drawNextFrame == 0)
    {
        uVar2 = 0;
    }
    else
    {

        do
        {
            if ((param_1 == 1) && (local_1c--, local_1c == 0))
            {
                iVar3 = FUN_80078bf8(1);
                
                if (iVar3 == 0x10)
                {
                    bVar1 = true;
                    OVR_230_VideoBSS.isDone = 1;
                }
                else
                {
                    local_1c = 0x28;
                }
            }

            local_20--;

            if (local_20 == 0)
            {
                OVR_230_VideoBSS.isDone = 1;
            }

        } while (!OVR_230_VideoBSS.isDone);

        do
        {
            iVar3 = FUN_80077ae8(10000);

        } while (iVar3 != 0);

        OVR_230_VideoBSS.isDone = 0;

        OVR_230_VideoBSS.drawNextFrame = 0;

        if ((!bVar1) && (OVR_230_VideoBSS.frameCounter != OVR_230_VideoBSS.totalFrames))
        {
            // Discontinue current decoding,
            // does not affect internal states (libref)
            DecDCTReset(1);
        }

        // end of scrapbook
        uVar2 = (u_int)OVR_230_VideoBSS.field8_0x18;
    }
    return uVar2;
}
