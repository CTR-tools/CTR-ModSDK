#include <common.h>

void DECOMP_CS_Boss_Init(int* boss_cutscene)
{
    unsigned int *ptrDestination;
    int index;

    index = 3 - sdata->gGT->activeMempackIndex;

    CDSYS_XAPauseRequest();

    ptrDestination = 0x800b777c;
	ptrDestination[0] = 0;
	ptrDestination[1] = 0;

    sdata->gGT->levID_in_each_mempack[index] = -1;

    MEMPACK_SwapPacks(index);
    MEMPACK_ClearLowMem();

    sdata->load_inProgress = 1;

    if (boss_cutscene[0])
    {
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_VRAM, boss_cutscene[0] - 1 + index, 0, 0);
    }

    if (boss_cutscene[2])
    {
        LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, boss_cutscene[2] - 1 + index, ptrDestination, -0x2);
    }

    LOAD_AppendQueue(sdata->ptrBigfileCdPos_2, LT_DRAM, boss_cutscene[1] - 1 + index, 0, CS_Boss_Init_Callback);
}