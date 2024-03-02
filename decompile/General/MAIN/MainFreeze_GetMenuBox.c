#include <common.h>

struct MenuBox * DECOMP_MainFreeze_GetMenuBox(void)
{
    struct MenuBox * mb;
    struct GameTracker *gGT = sdata->gGT;
    u_int gameMode = gGT->gameMode1;

	if ((gameMode & BATTLE_MODE) != 0)
	{
		mb = &data.menuBox_battle;
	}

    else if ((gameMode & ADVENTURE_ARENA) != 0)
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
	
    else if((gameMode & ADVENTURE_MODE) != 0)
    {
        if ((gameMode & ADVENTURE_CUP) != 0)
        {
			mb = &data.menuBox_advCup;
        }
        else
        {
			mb = &data.menuBox_advRace;
        }
    }

    else if ((gGT->gameMode2 & CUP_ANY_KIND) != 0)
	{
		mb = &data.menuBox_arcadeCup;
	}
	
    else
	{
		mb = &data.menuBox_arcadeRace;
    }

    return mb;
}
