#include <common.h>

int RB_Banner_Animate_Init(struct ModelHeader *headers)
{
    u_int command;
    u_int uVar3;
    int *ptrCommand;
    char *vertex;
    char *nextVertex;
    short angle;
    int *scratchpad = 0x1f800300;

    angle = 0;

    // modelHeader->ptrCommands, skip 2 bytes (skip numColors)
    ptrCommand = (u_int *)(headers->ptrCommandList + 2);

    // modelHeader->ptrVertexData
    vertex = (char *)(headers->ptrFrameData[headers->ptrFrameData->unk16[12]]);

    // if less than 64 colors found, quit
    if (*(int *)headers->ptrCommandList < 64) return 0;

    command = *ptrCommand;

    while ((int)command != -1)
    {
        if ((command & 0xffff0000) == 0)
        {
        LAB_800b563c:
            ptrCommand++;
        }
        else
        {
            if (-1 < (int)command)
            {
                if ((command & 0x4000000) == 0)
                {
                    scratchpad[0] = (u_int)CONCAT12(vertex[2], (u_short)*vertex);
                    scratchpad[1] &= 0xffff0000 | (u_int)vertex[1];
                    *(u_int *)((u_int) * (char *)((int)ptrCommand + 2) * 8 + 0x1f800000) = scratchpad[0];
                    ((int *)0x1f800004)[(u_int) * (char *)((int)ptrCommand + 2) * 2] = scratchpad[1];
                    *ptrCommand &= 0xf7ff01ff;
                    command = (u_int)(*vertex >> 2);
                    vertex += 3;
                    angle++;
                }
                else
                {
                    scratchpad[0] = *(u_int *)((command >> 0xd & 0x7f8) + 0x1f800000);
                    scratchpad[1] = ((int *)0x1f800004)[(u_int) * (char *)((int)ptrCommand + 2) * 2];
                    *ptrCommand &= 0xf7ff01ff;
                    command = (scratchpad[0] >> 2);
                }
                *ptrCommand |= (command << 9);
                goto LAB_800b563c;
            }
            nextVertex = vertex + 1;
            for (int i = 0; i < 4; i++)
            {
                if ((*ptrCommand & 0x4000000) == 0)
                {
                    scratchpad[0] = (u_int)CONCAT12(nextVertex[1], (u_short)*vertex);
                    scratchpad[1] = scratchpad[1] & 0xffff0000 | (uint)*nextVertex;
                    *(u_int *)((u_int) * (char *)((int)ptrCommand + 2) * 8 + 0x1f800000) = scratchpad[0];
                    ((int *)0x1f800004)[(u_int) * (char *)((int)ptrCommand + 2) * 2] = scratchpad[1];
                    *ptrCommand &= 0xf7ff01ff;
                    command = (u_int)(*vertex >> 2);
                    vertex += 3;
                    nextVertex += 3;
                    angle++;
                }
                else
                {
                    scratchpad[0] = *(u_int *)((*ptrCommand >> 0xd & 0x7f8) + 0x1f800000);
                    scratchpad[1] = ((int *)0x1f800004)[(u_int) * (char *)((int)ptrCommand + 2) * 2];
                    *ptrCommand &= 0xf7ff01ff;
                    command = (scratchpad[0] >> 2);
                }
                *ptrCommand |= (command << 9);
                ptrCommand++;
            }
        }
        command = *ptrCommand;
    }

    // Only if there are four players,
    // do not wave the banner, leave it flat
    if (3 < sdata->gGT->numPlyrCurrGame)
    {
        // modelHeader->ptrVertexData
        vertex = (char *)(headers->ptrFrameData[headers->ptrFrameData->unk16[12]]);

        uVar3 = vertex + (angle * 3);
        while (vertex < uVar3)
        {
            *(char *)(vertex + 1) = 0x80;
            vertex += 3;
        }
    }
    return angle;
}
