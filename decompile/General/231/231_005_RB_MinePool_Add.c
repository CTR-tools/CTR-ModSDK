#include <common.h>

extern struct WeaponSlot231 minePoolItem[40];
extern struct LinkedList minePoolTaken;
extern struct LinkedList minePoolFree;

void DECOMP_RB_MinePool_Add(struct MineWeapon* mw)
{
	struct WeaponSlot231* ws;
	
    // if no more items on free list
	if ( (&minePoolFree)->count == 0 )
	{
		// remove oldest mine
		DECOMP_RB_MinePool_Remove(
			((struct WeaponSlot231*)(&minePoolTaken)->last)->mineWeapon
		);
	}
	
	// LIST_RemoveBack free list
	ws = (struct WeaponSlot231*)DECOMP_LIST_RemoveBack(&minePoolFree);

	// link together
	ws->mineWeapon = mw;
	mw->weaponSlot231 = ws;

	// LIST_AddFront to taken list
	DECOMP_LIST_AddFront(&minePoolTaken, (struct Item*)ws);
}