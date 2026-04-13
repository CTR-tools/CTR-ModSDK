#include <common.h>

void DECOMP_AH_SaveObj_ThDestroy(struct Thread* t)
{
    struct SaveObj* save;
    save = t->object;

    if (save->inst != NULL)
    {
        DECOMP_INSTANCE_Death(save->inst);
        save->inst = NULL;
    }
    return;
}