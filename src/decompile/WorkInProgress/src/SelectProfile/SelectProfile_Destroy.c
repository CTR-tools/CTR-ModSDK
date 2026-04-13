#include <common.h>

void DECOMP_SelectProfile_Destroy(void)
{
    char i;
    struct Thread *t;
    struct Instance *inst;

    // if loadsave object exists
    if (sdata->ptrLoadSaveObj != NULL)
    {
        inst = (struct Instance *)sdata->ptrLoadSaveObj[1];

        // destroy 12 instances, for LoadSave's
        // 4x trophy, 4x relic, and 4x key

        for (i = 0; i < 0xc; i++)
        {
            if (inst->next != 0)
            {
                INSTANCE_Death();
            }
            // increment loop counter
            inst = (int)inst + 3;
        }

        // get pointer to thread, from object
        t = (struct Thread *)sdata->ptrLoadSaveObj[0];

        // erase pointer to object
        sdata->ptrLoadSaveObj = NULL;

        // 0x800 = this thread needs to be deleted
        t->flags |= 0x800;
    }
    return;
}