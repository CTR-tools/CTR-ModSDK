#include <common.h>

void DECOMP_RB_Explosion_ThTick(struct Thread* t)
{
	struct Instance* inst = t->inst;
	
	int frame = inst->animFrame;
	int total = DECOMP_INSTANCE_GetNumAnimFrames(inst, 0);
	
	if ((frame+1) < total)
	{
		inst->animFrame++;
		return;
	}
	
	// dead thread
	t->flags |= 0x800;
}