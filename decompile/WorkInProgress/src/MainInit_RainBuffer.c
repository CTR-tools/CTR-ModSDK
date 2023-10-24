#include <common.h>

void MainInit_RainBuffer(struct GameTracker *gGT)
{
    char i;
    char numPlyr;
    struct RainBuffer *levelBuffer;
    struct RainBuffer *globalBuffer;

    numPlyr = gGT->numPlyrCurrGame;

    // if numPlyrCurrGame is not zero
    if (numPlyr)
    {
        
        // copy rain buffer from level, to player's global rain buffer
        levelBuffer = &gGT->level1->rainBuffer;
        
        for (i = 0; i < numPlyr; i++)
        {
            // Rain Buffer
            globalBuffer = &gGT->rainBuffer[i];

            memcpy(globalBuffer, levelBuffer, sizeof(struct RainBuffer));

            // if there are zero screens, crash the game
            if (!numPlyr)
                trap(0x1c00);

            // if there are -1 screens, crash the game
            if ((numPlyr == -1) && ((gGT->rainBuffer[i].numParticles_curr == -0x80000000) || (gGT->rainBuffer[i].numParticles_curr == 0x80000000)))
                trap(0x1800);

            gGT->rainBuffer[i].numParticles_curr /= numPlyr;
        }
    }
}