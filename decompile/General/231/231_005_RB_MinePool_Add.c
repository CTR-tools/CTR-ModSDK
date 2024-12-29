#include <common.h>

void DECOMP_RB_MinePool_Add(struct MineWeapon* mw)
{
	struct WeaponSlot231* ws;
	
    // if no more items on free list
	if ( (&D231.minePoolFree)->count == 0 )
	{
		// remove oldest mine
		DECOMP_RB_MinePool_Remove(
			((struct WeaponSlot231*)(&D231.minePoolTaken)->last)->mineWeapon
		);
	}
	
	// LIST_RemoveBack free list
	ws = (struct WeaponSlot231*)DECOMP_LIST_RemoveBack(&D231.minePoolFree);

	// link together
	ws->mineWeapon = mw;
	mw->weaponSlot231 = ws;

	// LIST_AddFront to taken list
	DECOMP_LIST_AddFront(&D231.minePoolTaken, (struct Item*)ws);
}