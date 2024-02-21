#include <common.h>

void CS_Podium_Prize_ThTick2(struct Thread *th)
{
    int currScale;

    // get object from thread
    int prize = th->object;

    // get instance from thread
    struct Instance *inst = th->inst;

    short frameIndex = *(short *)(prize + 0x2a);

    if (frameIndex < 5)
    {
        // if even frame
        if ((frameIndex & 1) == 0)
        {
            // scaleX
            currScale = inst->scale[0] + 800 + frameIndex * 400;

            if ((frameIndex + 1) * 0x28a + 0x2000 < currScale)
            {
                // frame counter
                frameIndex += 1;
            }
        }
        else
        {
            // scaleX
            currScale = inst->scale[0] - 800;

            if (currScale < 0x1001)
            {
                // frame counter
                frameIndex += 1;
            }
        }

        *(short *)(prize + 0x2a) = frameIndex;

        // scaleY and scaleZ
        inst->scale[0] = currScale;
        inst->scale[1] = currScale;
        inst->scale[2] = currScale;

        CS_Podium_Prize_Spin(inst, prize);
    }
    else
    {
        // execute, then assign per-frame funcPtr to thread
        ThTick_SetAndExec(th, CS_Podium_Prize_ThTick3);
    }
}