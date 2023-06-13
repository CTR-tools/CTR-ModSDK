#include <common.h>
#include "header.h"

void MM_AdvDifficulty(struct MenuBox *mb)
{
    short row = mb->rowSelected;

    // if uninitialized
    if (row == -1)
    {
        mb->ptrPrevBox_InHierarchy->state &= 0xffffffeb;
        return;
    }

    // if you are on a valid row
    if ((unsigned char)row < 4)
    {
        if (row == 3)
        {
            sdata->gGT->arcadeDifficulty = 0x280;
        }
        else
        {
            sdata->gGT->arcadeDifficulty = OVR_230.cupDifficultySpeed[row];
        }
        // If this is arcade difficulty.
        if (mb->ptrPrevBox_InHierarchy == &OVR_230.menubox_players1P2P)
        {
            OVR_230.desiredMenu = 2;
            mb->state |= 4;
            return;
        }
        OVR_230.desiredMenu = 0; // assumes it's always a new adventure
        OVR_230.MM_State = 2; // transition out
        mb->state |= 4;
    }
}