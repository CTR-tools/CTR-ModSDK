#include <common.h>

void DECOMP_RB_Blade_PerFrame(struct Thread* t)
{
	struct Blade* bladeObj;
	struct Instance* bladeInst;
	short rot[3];
	
	bladeObj = (struct Blade*)t->object;
	bladeInst = t->inst;
	
	rot[0] = bladeInst->instDef->rot[0];
	rot[1] = bladeInst->instDef->rot[1] + 0x400;
	rot[2] = bladeObj->angle;
	
	bladeObj->angle += 0x100;
	
	ConvertRotToMatrix(&bladeInst->matrix, &rot[0]);
	
	bladeInst->scale[0] = 0x1000;
	bladeInst->scale[1] = 0x1000;
	bladeInst->scale[2] = 0x1000;
	
	// do not use infinite loop optimization,
	// modern GCC "without" the $RA skip is more
	// optimized than PSYQ "with" the $RA skip
}