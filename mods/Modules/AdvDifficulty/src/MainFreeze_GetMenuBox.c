#include <common.h>

void GetMenuDifficulty(struct RectMenu* menu);

struct RectMenu *DECOMP_MainFreeze_GetMenuPtr(void)
{
    struct RectMenu* menu;
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

    if (gameMode & ADVENTURE_MODE)
    {
        if (gameMode & ADVENTURE_CUP)
        {
            mb = &data.menuAdvCup;
        }
        else
        {
            mb = &data.menuAdvRace;
            GetMenuDifficulty(mb);
        }
        if (gameMode & ADVENTURE_ARENA)
        {
            
            mb = &data.menuAdvHub;
            GetMenuDifficulty(mb);
        }
    }
    else
    {
        if (gGT->gameMode2 & CUP_ANY_KIND)
        {
            mb = &data.menuArcadeCup;
        }
        else
        {
            mb = &data.menuArcadeRace;
            GetMenuDifficulty(mb);
        }
        if (gameMode & BATTLE_MODE)
        {
            mb = &data.menuBattle;
        }
    }

    return mb;
}
