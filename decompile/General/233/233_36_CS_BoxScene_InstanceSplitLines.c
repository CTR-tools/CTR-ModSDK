#include <common.h>

void DECOMP_CS_BoxScene_InstanceSplitLines(void)
{
    short split = OVR_233.VertSplitLine;
    struct Thread* t = sdata->gGT->threadBuckets[GHOST].thread;

    // loop through ghosts
    while (t != NULL)
    {
        t->inst->vertSplit = split;
        // go to next ghost
        t = t->siblingThread;
    }
}