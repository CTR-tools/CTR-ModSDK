#include <common.h>

void DECOMP_MM_Battle_Init(void)
{
    D230.battle_transitionState = 0;
    D230.battle_transitionFrames = FPS_DOUBLE(0xc);
}
