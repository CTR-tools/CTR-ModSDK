#include <common.h>

extern int mainFreezeFlags[5];
extern struct RectMenu* mainFreezeMenuArr[5];

struct RectMenu* DECOMP_MainFreeze_GetMenuPtr(void)
{
    struct GameTracker *gGT = sdata->gGT;
	
    // Set string to "Uka Uka Hints", 
    // or if boolGoodGuy, then set "Aku Aku Hints"
    int var1 = 0xc;
    if (DECOMP_VehPickupItem_MaskBoolGoodGuy(gGT->drivers[0]) != 0)
		var1 = 0xb;
	
	data.rowsAdvHub[1].stringIndex = var1;

	if ((gGT->gameMode2 & CUP_ANY_KIND) != 0)
	{
		return &data.menuArcadeCup;
	}

    u_int gameMode = gGT->gameMode1;
	int* flagPtr = &mainFreezeFlags[0]; 
	struct RectMenu** menuPtrToPtr = &mainFreezeMenuArr[0];
	
	for(
			/**/;
			*flagPtr != 0;
			
			flagPtr++, menuPtrToPtr++
		)
	{
		if((gameMode & (*flagPtr)) != 0)
			break;
	}

	// if nothing else,
	// then menuArcadeRace
    return (* menuPtrToPtr);
}

extern int mainFreezeFlags[5] =
{
	BATTLE_MODE,
	ADVENTURE_ARENA,
	ADVENTURE_CUP,
	ADVENTURE_MODE,
	0 // null terminator
};

extern struct RectMenu* mainFreezeMenuArr[5] =
{
	&data.menuBattle,
	&data.menuAdvHub,
	&data.menuAdvCup,
	&data.menuAdvRace,
	&data.menuArcadeRace
};