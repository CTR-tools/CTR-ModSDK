#include <common.h>

void DECOMP_RB_Baron_LInB(struct Instance* inst)
{
	struct Baron* baronObj;
	
	// NGin Labs 60fps test,
	// make invisible, and quit thread
	#ifdef USE_REAL60PS1
	inst->flags |= 0x80;
	return;
	#endif
	
	struct Thread* t =
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Baron),
				NONE,
				SMALL,
				STATIC
			),

			DECOMP_RB_Baron_ThTick,	// behavior
			0,						// debug name
			0						// thread relative
		);

	if (t == 0) return;
	inst->thread = t;
	t->inst = inst;

	inst->scale[0] = 0x1000;
	inst->scale[1] = 0x1000;
	inst->scale[2] = 0x1000;

#if 0
	// Removed, Baron Plane would spawn two
	// planes, one starts at pointIndex=1,
	// the other one at pointIndex=NumPoints/2
#endif

	baronObj = ((struct Baron*)t->object);
	baronObj->otherInst = 0;
	baronObj->pointIndex = 1;
	baronObj->soundID_flags = 0;
}