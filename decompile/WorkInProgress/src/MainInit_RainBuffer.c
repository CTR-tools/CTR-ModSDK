#include <common.h>

void MainInit_RainBuffer(struct GameTracker *gGT)
{
    char i;
    char numPlyr;
    int* src, dst;
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

            src = (int*)levelBuffer;
            dst = (int*)globalBuffer;

            while(src != ((int)levelBuffer + sizeof(struct RainBuffer)))
            {  
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
                dst[3] = src[3];
                src += 4;
                dst += 4;
            }

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