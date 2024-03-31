#include <common.h>

void DECOMP_RB_Blade_ThTick(struct Thread* t)
{
	struct Blade* bladeObj;
	struct Instance* bladeInst;
	short rot[3];
	
	bladeObj = (struct Blade*)t->object;
	bladeInst = t->inst;
	
	rot[0] = bladeInst->instDef->rot[0];
	rot[1] = bladeInst->instDef->rot[1] + 0x400;
	rot[2] = bladeObj->angle;
	
	bladeObj->angle += FPS_HALF(0x100);

	// converted to TEST in rebuildPS1	
	ConvertRotToMatrix(&bladeInst->matrix, &rot[0]);
	
	bladeInst->scale[0] = 0x1000;
	bladeInst->scale[1] = 0x1000;
	bladeInst->scale[2] = 0x1000;
	
	// do not use infinite loop optimization,
	// modern GCC "without" the $RA skip is more
	// optimized than PSYQ "with" the $RA skip
}

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
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	bladeObj = ((struct Blade*)t->object);
	bladeObj->angle = 0;
}