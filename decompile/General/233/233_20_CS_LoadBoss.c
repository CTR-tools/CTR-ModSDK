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

	// CTR Model File (body)
    DECOMP_LOAD_AppendQueue(0, LT_GETADDR, bcd->bodyFile+index, 
		&OVR_233.ptrModelBossBody, DECOMP_LOAD_DramFileCallback);

	// CTR Model File (head)
    DECOMP_LOAD_AppendQueue(0, LT_GETADDR, bcd->headFile+index, 
		&OVR_233.ptrModelBossHead, DECOMP_LOAD_DramFileCallback);
}