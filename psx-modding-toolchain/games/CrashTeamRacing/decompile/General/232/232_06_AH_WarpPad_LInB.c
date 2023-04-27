#include <common.h>

void AH_WarpPad_ThDestroy(struct Thread* t);

void AH_WarpPad_LInB(struct Instance* inst)
{
	struct Thread* t;
	struct WarpPad* warppadObj;
	
    t =	
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct WarpPad), 
				NONE, 
				MEDIUM, 
				WARPPAD
			), 
			
			AH_WarpPad_ThTick,	// behavior
			0,					// debug name
			0					// thread relative
		);
		
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	t->funcThDestroy = AH_WarpPad_ThDestroy;
}