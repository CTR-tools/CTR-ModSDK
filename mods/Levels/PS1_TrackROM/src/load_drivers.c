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
        char driversLoaded[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int mpkid = data.characterIDs[0];
        driversLoaded[mpkid] = 1;
        int j = 0;
        for (int i = 1; i < 4; i++)
        {
            if (driversLoaded[data.characterIDs[i]] == 0)
            {
                LOAD_AppendQueue(param_1, LT_DRAM, BI_RACERMODELHI + data.characterIDs[i], &g_charModelPtrs[j++], (void(*)(struct LoadQueueSlot*))0xfffffffe);
                driversLoaded[data.characterIDs[i]] = 1;
            }
        }
        LOAD_AppendQueue(param_1, LT_DRAM, BI_TIMETRIALPACK + mpkid, NULL, param_3);
    }
}