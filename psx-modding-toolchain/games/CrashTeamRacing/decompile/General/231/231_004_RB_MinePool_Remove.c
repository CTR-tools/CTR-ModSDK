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
	LIST_RemoveMember(0x800b2e9c, ws);
	LIST_AddFront(0x800b2ea8, ws);
}