#include <common.h>

void DECOMP_CS_LoadBossCallback(struct LoadQueueSlot * lqs);

void DECOMP_CS_LoadBoss(struct BossCutsceneData* bcd)
{
    unsigned int *ptrArr;
    int index;

    index = 3 - sdata->gGT->activeMempackIndex;

    CDSYS_XAPauseRequest();

	// erase HEAD + BODY
	OVR_233.ptrModelBossHead = 0;
	OVR_233.ptrModelBossBody = 0;

	// invalidate alternative-hub, because
	// the boss will load in that level's RAM
    sdata->gGT->levID_in_each_mempack[index] = -1;

    DECOMP_MEMPACK_SwapPacks(index);
    DECOMP_MEMPACK_ClearLowMem();

	// This will be 1 or 2,
	// now equals 0 or 1
	index -= 1;

	#if 0 // UNUSED
    if (bcd->vrmFile != 0)
    {
		// CTR vram file (body and head)
        DECOMP_LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_VRAM, bcd->vrmFile+index, 0, 0);
    }
	#endif

	// skip null check
    //if (bcd->bodyFile != 0)
    {
		// CTR Model File (body)
        DECOMP_LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, bcd->bodyFile+index, &OVR_233.ptrModelBossBody, 0);
    }

	// CTR Model File (head)
    DECOMP_LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, bcd->headFile+index, &OVR_233.ptrModelBossHead, 0);
}