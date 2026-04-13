#include <common.h>

void DECOMP_MM_Video_VLC_Decode(void)
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

                    size = DecDCTBufSize(local_2c);

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
