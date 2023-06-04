#include <common.h>

struct MenuBox * DECOMP_MainFreeze_GetMenuBox(void)
{
    struct MenuBox * mb;
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

    // If you're not in Adventure Arena or Adventure Mode or Battle
    if ((gameMode & (ADVENTURE_ARENA | ADVENTURE_MODE | BATTLE_MODE)) == 0)
    {
        // If you are not in Arcade or VS cup
        if ((gGT->gameMode2 & 0x10) == 0)
        {
            // Single Race Pause
            mb = &data.menuBox_arcadeRace;
        }
        else
        {
            // Cup Pause
            mb = &data.menuBox_arcadeCup;
        }
    }
    else
    {
        // If you're in Adventure Hub
        if (gameMode & ADVENTURE_ARENA)
        {
            // use Uka as default.

            // Set string to Uka Uka Hints
            data.menuRow_advHub[1].stringIndex = 0xc;

            // if you use aku
            if ((Weapon_Mask_boolGoodGuy(gGT->drivers[0]) & 0xffff) != 0)
            {
                // Set string to Aku Aku Hints
                data.menuRow_advHub[1].stringIndex = 0xb;
            }

            // Adventure Hub Pause
            mb = &data.menuBox_advHub;
        }
        else
        {
            // if you're in a race
            if ((gameMode & 0x10000000) == 0)
            {
                // adventure race pause
                mb = &data.menuBox_advRace;
            }
            else
            {
                // adventure cup pause
                mb = &data.menuBox_advCup;
            }
        }
    }
    return mb;
}
