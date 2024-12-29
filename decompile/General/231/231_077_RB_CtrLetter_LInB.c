#include <common.h>

void DECOMP_RB_CtrLetter_LInB(struct Instance* inst)
{
	struct CtrLetter* letterObj;

	struct Thread* t =
		PROC_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct CtrLetter),
				NONE,
				SMALL,
				STATIC
			),

			DECOMP_RB_CtrLetter_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);

	if (t == 0) return;
	inst->thread = t;
	t->inst = inst;

	letterObj = ((struct CtrLetter*)t->object);
	letterObj->rot[0] = 0;
	letterObj->rot[1] = 0;
	letterObj->rot[2] = 0;

	inst->scale[0] = 0x1800;
	inst->scale[1] = 0x1800;
	inst->scale[2] = 0x1800;

	inst->colorRGBA = 0xffc8000;

	// specular light, plus another
	inst->flags |= 0x30000;

	RB_Default_LInB(inst);
}