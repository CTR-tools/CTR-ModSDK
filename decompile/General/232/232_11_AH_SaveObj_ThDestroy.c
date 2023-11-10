#include <common.h>

void DECOMP_AH_SaveObj_ThDestroy(struct Thread *saveTh)
{
    struct SaveObj *save;

    save = saveTh->object;

    if (save->inst != NULL)
    {
        INSTANCE_Death(save->inst);
        save->inst = NULL;
    }
    return;
}