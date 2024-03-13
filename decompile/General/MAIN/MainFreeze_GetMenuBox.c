#include <common.h>

extern int mainFreezeFlags[5];
extern struct MenuBox* mainFreezeBoxArr[5];

struct MenuBox* DECOMP_MainFreeze_GetMenuBox(void)
{
    struct GameTracker *gGT = sdata->gGT;
	
    // Set string to "Uka Uka Hints", 
    // or if boolGoodGuy, then set "Aku Aku Hints"
    int var1 = 0xc;
    if (DECOMP_VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]) != 0)
		var1 = 0xb;
	
	data.menuRow_advHub[1].stringIndex = var1;

	if ((gGT->gameMode2 & CUP_ANY_KIND) != 0)
	{
		return &data.menuBox_arcadeCup;
	}

    u_int gameMode = gGT->gameMode1;
	int* flagPtr = &mainFreezeFlags[0]; 
	struct MenuBox** mbPtrToPtr = &mainFreezeBoxArr[0];
	
	for(
			/**/;
			*flagPtr != 0;
			
			flagPtr++, mbPtrToPtr++
		)
	{
		if((gameMode & (*flagPtr)) != 0)
			break;
	}

	// if nothing else,
	// then menuBox_arcadeRace
    return (*mbPtrToPtr);
}

extern int mainFreezeFlags[5] =
{
	BATTLE_MODE,
	ADVENTURE_ARENA,
	ADVENTURE_CUP,
	ADVENTURE_MODE,
	0 // null terminator
};

extern struct MenuBox* mainFreezeBoxArr[5] =
{
	&data.menuBox_battle,
	&data.menuBox_advHub,
	&data.menuBox_advCup,
	&data.menuBox_advRace,
	&data.menuBox_arcadeRace
};