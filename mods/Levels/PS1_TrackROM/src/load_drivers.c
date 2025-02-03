#include <common.h>
#include "utils.h"

void TimeTrialCallback(struct LoadQueueSlot* lqs);

void LoadDriverModels(unsigned int param_1, int levelLOD, void (*param_3)(struct LoadQueueSlot*))
{
    if (sdata->gGT->gameMode1 & MAIN_MENU)
    {
        LOAD_AppendQueue(param_1, LT_DRAM, BI_ADVENTUREPACK, NULL, param_3);
    }
    else
    {
        // load oxide time trial pack
        LOAD_AppendQueue(param_1, LT_DRAM, BI_TIMETRIALPACK + 15, NULL, param_3);
    }
}