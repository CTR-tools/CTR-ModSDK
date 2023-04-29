#include <common.h>

void DECOMP_RB_MinePool_Remove(struct MineWeapon* mw)
{
	struct WeaponSlot231* ws = mw->weaponSlot231;
	
	mw->boolDestroyed = 1;
	mw->weaponSlot231 = 0;
	
	#if 0
	// useless check?
	if(ws == 0) return;
	#endif
	
	// remove from taken, add to free
	LIST_RemoveMember((struct LinkedList*)0x800b2e9c, (struct Item*)ws);
	LIST_AddFront((struct LinkedList*)0x800b2ea8, (struct Item*)ws);
}