#include <common.h>

int DECOMP_RaceFlag_MoveModels(int frameIndex, int numFrames)
{
    // need a better prefix than TitleFlag,
    // all this does is move the intro logo models
    // from the center of the screen, to the right

    // also used for transitioning driver models
    // on and off the screen in character selection

    int angle;
    int midpoint;
    int result;

    if (frameIndex < 0)
        return 0;

    if (frameIndex > numFrames)
        return 0x1000;

    // cut in half
    midpoint = numFrames / 2;

    // if less than half done
    if (frameIndex < midpoint)
    {
        angle = (midpoint - frameIndex) * 0x400;

        // 50% - sin(angle) / 2
        result = 0x800 - DECOMP_MATH_Sin(angle / midpoint) / 2;
    }
    // if more than half done
    else
    {
        angle = (frameIndex - midpoint) * 0x400;

        // sin(angle) / 2 + 50%
        result = DECOMP_MATH_Sin(angle / midpoint) / 2 + 0x800;
    }
    return result;
}
