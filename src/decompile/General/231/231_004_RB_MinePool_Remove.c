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
	DECOMP_LIST_RemoveMember(&D231.minePoolTaken, (struct Item*)ws);
	DECOMP_LIST_AddFront(&D231.minePoolFree, (struct Item*)ws);
}