#include <common.h>

// Overbudget by 16 bytes

void DECOMP_CS_Thread_AnimateScale(struct Thread *t)
{
    struct Instance *inst = t->inst;
    struct CutsceneObj *cs = t->object;

    // If instance and scaleSpeed exist
    if ((inst != 0) && (cs->scaleSpeed != 0))
    {
        short desiredScale = cs->desiredScale;
        short scaleSpeed = cs->scaleSpeed;
        short newScale = inst->scale[0] + scaleSpeed;

        // Check if scale change is not done
        u_char animate = (scaleSpeed > 0) ? (newScale < desiredScale) : (newScale > desiredScale);

        if (!animate)
        {
            // Change is done, erase scale speed
            cs->scaleSpeed = 0;
            newScale = desiredScale;
        }

        // Set instance scale (x, y, z)
        inst->scale[0] = newScale;
        inst->scale[1] = newScale;
        inst->scale[2] = newScale;
    }
}