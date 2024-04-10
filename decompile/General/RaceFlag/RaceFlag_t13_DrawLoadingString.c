#include <common.h>

void DECOMP_RaceFlag_DrawLoadingString(void)
{
    struct GameTracker *gGT = sdata->gGT;
    int iVar2;
    int iVar3;
    int iVar4;
    int uVar5;
    int iVar6;
    char *pbVar7;
    char *pbVar8;
    int iVar9;
    int iVar10;
    u_int *uVar11;
    char local_30;
    char local_2f;

    // LOADING...
    pbVar7 = sdata->lngStrings[0x231];

    // pointer to OT mem
    uVar11 = gGT->pushBuffer_UI.ptrOT;

    // pointer to OT mem
    gGT->pushBuffer_UI.ptrOT = gGT->otSwapchainDB[gGT->swapchainIndex];

    // get length of "LOADING..." string
    iVar2 = 10;

    iVar3 = DECOMP_DecalFont_GetLineWidth(pbVar7, 1);

    // loop counter
    iVar6 = 0;

    // if game is not loading
    if (sdata->Loading.stage == -1)
    {
        if (-1000 < (int)sdata->RaceFlag_Transition)
        {
            sdata->RaceFlag_Transition -= FPS_HALF(0x28);
        }
    }
    else
    {
        sdata->RaceFlag_Transition = 0;
    }

    iVar10 = 
		(sdata->RaceFlag_Transition & 0xffff) - 
		(
			(
				((iVar3 << 0x10) >> 0x10) -
				((iVar3 << 0x10) >> 0x1f)
			) >> 1
		);

    iVar3 = FPS_HALF(sdata->RaceFlag_LoadingTextAnimFrame);

    if (0 < iVar2)
    {

        iVar9 = iVar3 * -0x3c + 0x23c;

        // for iVar6 = 0; iVar6 < strlen("LOADING..."); iVar6++)
        do
        {
            if (iVar3 < 0)
            {
            LAB_800443c4:

                // draw text off screen
                iVar4 = 0x23c;
            }
            else
            {
                iVar4 = iVar9;
                if (
                    // if frame > 4,
                    // if text starts moving on-screen?
                    (4 < iVar3) &&
                    (
                        // draw letter at midpoint of screen
                        iVar4 = 0x100,

                        // if frame > 0x4a,
                        // if text starts moving off-screen?
                        0x4a < iVar3))
                {
                    // if frame > 0x4f,
                    // if letter is fully off-screen
                    if (0x4f < iVar3)
                        goto LAB_800443c4;

                    // letter is moving off-screen
                    iVar4 = (0x4b - iVar3) * 0x3c + 0x100;
                }
            }
            local_30 = *pbVar7;
            pbVar8 = pbVar7 + 1;
            uVar5 = 1;
            if (local_30 < 4)
            {
                local_2f = *pbVar8;
                pbVar8 = pbVar7 + 2;

                // increment loop counter
                iVar6 = iVar6 + 1;

                uVar5 = 2;
            }
            if ((short)iVar4 != 0x23c)
            {
                DECOMP_DecalFont_DrawLineStrlen(&local_30, uVar5, (iVar10 + iVar4), 0x6c, 1, 0);
            }

            iVar4 = DECOMP_DecalFont_GetLineWidthStrlen(&local_30, uVar5, 1);

            iVar10 = iVar10 + iVar4;
            iVar9 = iVar9 + 0xf0;

            // increment loop counter
            iVar6 = iVar6 + 1;

            // treat all letters with 4 frame difference
            iVar3 = iVar3 + -4;

            pbVar7 = pbVar8;
        } while (iVar6 < iVar2);
    }

    // pointer to OT mem
    gGT->pushBuffer_UI.ptrOT = uVar11;

    if (iVar3 < 0x50)
    {
        iVar2 = gGT->elapsedTimeMS >> 5;

        if (iVar2 < 1)
        {
            iVar2 = 1;
        }

        sdata->RaceFlag_LoadingTextAnimFrame += iVar2;
    }

    else
    {

        sdata->RaceFlag_LoadingTextAnimFrame = -1;
        if ((u_int)(sdata->Loading.stage - 6U) < 2)
        {
            sdata->RaceFlag_LoadingTextAnimFrame = 0;
        }
    }
    return;
}