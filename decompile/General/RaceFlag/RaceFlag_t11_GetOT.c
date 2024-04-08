#include <common.h>

u_int* DECOMP_RaceFlag_GetOT(void)
{
    short sVar1;
    int iVar2;
    struct GameTracker* gGT = sdata->gGT;
	
	u_int* otDrawFirst_FarthestDepth;
	u_int* otDrawLast_ClosestDepth;
	
	otDrawFirst_FarthestDepth = &gGT->pushBuffer[0].ptrOT[0x3FF];
	otDrawLast_ClosestDepth = gGT->otSwapchainDB[gGT->swapchainIndex];

    if (sdata->unk_CheckFlag2 == 0)
    {
        sdata->unk_CheckFlag2 = 1;
    }

	// transitioning on-screen
    if (sdata->RaceFlag_AnimationType == 0)
    {
		// set fully "off" to start transition "on"
        if (sdata->RaceFlag_Position < 0)
            sdata->RaceFlag_Position = 5000;

        sdata->unk_CheckFlag1 = 300;

        iVar2 = sdata->RaceFlag_Position;
		
		// if transitioning
        if(iVar2 != 0)
        {
            // skip last 8 frames to zero
            if (iVar2 < 8)
                sdata->RaceFlag_Position = 0;

            // transition for frame >= 8
            else
            {
				// rate of transition
                
				iVar2 = ((u_short)sdata->RaceFlag_Position >> 3) * gGT->elapsedTimeMS;
				iVar2 = iVar2 >> 5;
				
                sVar1 = -(short)iVar2;
                if (iVar2 < 1)
                {
                    sVar1 = -1;
                }

                sdata->RaceFlag_Position += sVar1;
            }
        }
		
		// transition is finished
        else
        {
			if (sdata->RaceFlag_DrawOrder != 1)
			{
			
				if (sdata->RaceFlag_DrawOrder != -1)
					return otDrawFirst_FarthestDepth;
				
				sdata->RaceFlag_DrawOrder = 0;
			}
        }

    }

    // transition off-screen
    if (sdata->RaceFlag_AnimationType == 2)
    {
        if ((short)sdata->unk_CheckFlag1 < 1000)
        {
            sdata->unk_CheckFlag1 += (short)((gGT->elapsedTimeMS * 10) >> 5);
        }

        // If transitioning "off"
        if (sdata->RaceFlag_Position > -5000)
        {
            sdata->RaceFlag_Position -= 
				(((u_int)sdata->unk_CheckFlag1 >> 2) * gGT->elapsedTimeMS) >> 5;
        }
		
		// finished transitioning off
        else
        {
            sdata->RaceFlag_Position = 5000;
            sdata->RaceFlag_AnimationType = 0;
            gGT->renderFlags &= ~(0x1000);
        }
    }

    return otDrawLast_ClosestDepth;
}