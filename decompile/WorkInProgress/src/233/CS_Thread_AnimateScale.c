#include <common.h>

void DECOMP_CS_Thread_AnimateScale(struct Thread* t)
{
    struct Instance* inst = t->inst;
    struct CutsceneObj* cs = t->object;

    // If instance and scaleSpeed exist
    if (inst && cs->scaleSpeed != 0)
    {
        short desiredScale = cs->desiredScale;
        int scaleSpeed = cs->scaleSpeed;

        int newScale = inst->scale[0] + scaleSpeed;
        short currScale = newScale;

        // Check if scale change is not done
        char animate = (scaleSpeed < 1) ? (desiredScale < newScale) : (newScale < desiredScale);

        if (!animate)
        {
            // Change is done, erase scale speed
            cs->scaleSpeed = 0;
            currScale = desiredScale;
        }

        // Set instance scale (x, y, z)
        inst->scale[0] = currScale;
        inst->scale[1] = currScale;
        inst->scale[2] = currScale;
    }
}