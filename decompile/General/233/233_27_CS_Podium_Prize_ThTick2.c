#include <common.h>

// Make the trophy bounce 3 times
// Then start ThTick3
void CS_Podium_Prize_ThTick2(struct Thread *th)
{
    int currScale;

    // get object from thread
	// should replace with struct Prize in 233
    int prize = th->object;

    // get instance from thread
    struct Instance *inst = th->inst;

    short frameIndex = *(short *)(prize + 0x2a);

	// bouncing scale animation
    if (frameIndex < 5)
    {
        // if even frame
        if ((frameIndex & 1) == 0)
        {
            // scaleX
            currScale = inst->scale[0] + FPS_HALF(800) + frameIndex * 400;

            if ((frameIndex + 1) * 0x28a + 0x2000 < currScale)
            {
                // frame counter
                frameIndex += 1;
            }
        }
        else
        {
            // scaleX
            currScale = inst->scale[0] - FPS_HALF(800);

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
		void CS_Podium_Prize_ThTick3();
        ThTick_SetAndExec(th, CS_Podium_Prize_ThTick3);
    }
}