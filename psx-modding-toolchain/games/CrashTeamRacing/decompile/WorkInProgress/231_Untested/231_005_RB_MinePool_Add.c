#include <common.h>

void DECOMP_RB_MinePool_Add(struct MineWeapon* mw)
{
	struct WeaponSlot231* ws;
	
    // if no more items on free list
    // (800b2ea8 + 8 = 800b2eb0)
	if (*(int*)0x800b2ea8 == 0)
	{
		// remove oldest mine
	
		// RB_MinePool_Remove
		// (800b2e9c + 4 = 800b2ea0) (taken->last)
		// (*(int*)800b2ea0 + 8) (taken->last->mineWeapon)
		RB_MinePool_Remove(*(int*)(*(int*)0x800b2ea0 + 8)
	}
	
	// LIST_RemoveBack free list, AddFront to taken list
	ws = LIST_RemoveBack(0x800b2ea8);
	LIST_AddFront(0x800b2e9c, ws);
	
	// link together
	ws->mineWeapon = mw;
	mw->weaponSlot231 = ws;

}