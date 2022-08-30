#include <common.h>

int RB_Hazard_OnCollide_Generic(struct Thread* thread)
{
	struct Instance* inst;
	struct MineWeapon* mw;
	
	inst = thread->inst;
	mw = thread->object;
	
	// need the rest of MineWeapon struct for this
	
	// kill thread
	thread->flags |= 0x800;
	return 1;
}