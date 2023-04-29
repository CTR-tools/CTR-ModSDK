#include <common.h>

void RB_MinePool_Remove(struct MineWeapon* mw);

void DECOMP_RB_MinePool_Add(struct MineWeapon* mw)
{
	struct WeaponSlot231* ws;
	
    // if no more items on free list
	if ( ((struct LinkedList*)0x800b2ea8)->count == 0 )
	{
		// remove oldest mine
		RB_MinePool_Remove(
			((struct WeaponSlot231*)((struct LinkedList*)0x800b2e9c)->last)->mineWeapon
		);
	}
	
	// LIST_RemoveBack free list
	ws = (struct WeaponSlot231*)LIST_RemoveBack((struct LinkedList*)0x800b2ea8);

	// link together
	ws->mineWeapon = mw;
	mw->weaponSlot231 = ws;

	// LIST_AddFront to taken list
	LIST_AddFront((struct LinkedList*)0x800b2e9c, (struct Item*)ws);
}