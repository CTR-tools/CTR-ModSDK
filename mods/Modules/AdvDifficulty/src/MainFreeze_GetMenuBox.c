#include <common.h>

void GetMenuDifficulty(struct MenuBox* mb);

struct MenuBox *DECOMP_MainFreeze_GetMenuBox(void)
{
    struct MenuBox *mb;
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

    if (gameMode & ADVENTURE_MODE)
    {
        if (gameMode & ADVENTURE_CUP)
        {
            mb = &data.menuBox_advCup;
        }
        else
        {
            mb = &data.menuBox_advRace;
            GetMenuDifficulty(mb);
        }
        if (gameMode & ADVENTURE_ARENA)
        {
            
            mb = &data.menuBox_advHub;
            GetMenuDifficulty(mb);
        }
    }
    else
    {
        if (gGT->gameMode2 & CUP_ANY_KIND)
        {
            mb = &data.menuBox_arcadeCup;
        }
        else
        {
            mb = &data.menuBox_arcadeRace;
            GetMenuDifficulty(mb);
        }
        if (gameMode & BATTLE_MODE)
        {
            mb = &data.menuBox_battle;
        }
    }

    return mb;
}
