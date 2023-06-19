#include <common.h>

void DECOMP_AH_Pause_Destroy(void)
{
    char i;
    struct Instance *inst;
    struct Thread *t;
    int iVar3;

    // if PAUSE object exists
    if (*(int*)0x800b5578 != NULL)
    {
        iVar3 = DAT_800b5578 + 0xd0;

        // loop through 14 instances, destroy them
        for (i = 0; i < 0xe; i++)
        {
            inst = (struct Instance *)(iVar3 + 0xc);
            iVar3 = iVar3 + -0x10;
            INSTANCE_Death(inst->next);
        }

        // thread from object
        t = (struct Thread *)(DAT_800b5578 + 0xe0);

        // erase pointer to PAUSE object
        *(int*)0x800b5578 = NULL;

        // This AdvPause thread is now dead
        t->flags |= 0x800;
    }
    return;
}