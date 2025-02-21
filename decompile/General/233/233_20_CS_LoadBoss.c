#include <common.h>

void DECOMP_CS_LoadBossCallback(struct LoadQueueSlot * lqs);

void DECOMP_CS_LoadBoss(struct BossCutsceneData* bcd)
{
    unsigned int *ptrDestination;
    int index;

    index = 3 - sdata->gGT->activeMempackIndex;

    CDSYS_XAPauseRequest();

	// CTR Model file (body)
    ptrDestination = &OVR_233.ptrModelBossBody;
	
	// erase HEAD + BODY
	ptrDestination[0] = 0;
	ptrDestination[-1] = 0;

    sdata->gGT->levID_in_each_mempack[index] = -1;

    MEMPACK_SwapPacks(index);
    MEMPACK_ClearLowMem();

    sdata->load_inProgress = 1;
	
	// This will be 1 or 2,
	// now equals 0 or 1
	index -= 1;

	#if 0 // UNUSED
    if (bcd->vrmFile != 0)
    {
		// CTR vram file (body and head)
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_VRAM, bcd->vrmFile+index, 0, 0);
    }
	#endif

	// skip null check
    //if (bcd->bodyFile != 0)
    {
		// CTR Model File (body)
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, bcd->bodyFile+index, ptrDestination, 0);
    }

	// CTR Model File (head)
    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, bcd->headFile+index, 0, DECOMP_CS_LoadBossCallback);
}