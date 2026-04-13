#include <common.h>

void DECOMP_RB_Blade_LInB(struct Instance* inst)
{
	// Four "blades" from two blimps, Hot Air Skyway
	// One "blade" is a group of three fins,

	struct Blade* bladeObj;

	struct Thread* t =
		DECOMP_PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Blade),
				NONE,
				SMALL,
				STATIC
			),

			DECOMP_RB_Blade_ThTick,	// behavior
			0,						// debug name
			0						// thread relative
		);

	if (t == 0) return;
	inst->thread = t;
	t->inst = inst;

	bladeObj = ((struct Blade*)t->object);
	bladeObj->angle = 0;
}