#include <common.h>

void DECOMP_RB_Crystal_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* crystalInst;
	struct Crystal* crystalObj;
	
	crystalInst = t->inst;
	crystalObj = t->object;
	
	// rotate each frame
	crystalObj->rot[1] += 0x80;
	ConvertRotToMatrix(&crystalInst->matrix, &crystalObj->rot[0]);
	
	// sine curve for vertical bounce
	sine = MATH_Sin(crystalObj->rot[1]);
	
	// set posY
	crystalInst->matrix.t[1] =
		crystalInst->instDef->pos[1] + 	// original posY
		((sine << 4) >> 0xc) +			// sine (bounce up/down)
		0x30;							// airborne bump
	
	// to do: find 0x800b5968 and reallocate (probably light dir)
	SpecularLight_Spinning3D(crystalInst, &crystalObj->rot[0], 0x800b5968);
}

void DECOMP_RB_Crystal_LInB(struct Instance* inst)
{
	struct Crystal* crystalObj;
	
	struct Thread* t = 
		THREAD_BirthWithObject
		(
			// creation flags
			SIZE_RELATIVE_POOL_BUCKET
			(
				sizeof(struct Crystal), 
				NONE, 
				SMALL, 
				STATIC
			), 
			
			DECOMP_RB_Crystal_ThTick,	// behavior
			0,							// debug name
			0							// thread relative
		);
	
	if(t == 0) return;
	inst->thread = t;
	t->inst = inst;
	
	crystalObj = ((struct Crystal*)t->object);
	crystalObj->rot[0] = 0;
	crystalObj->rot[1] = 0;
	crystalObj->rot[2] = 0;
	
	inst->colorRGB = 0xd22fff0;
	
	// specular light
	inst->flags |= 0x20000;
	
	RB_Default_LInB(inst);
}

void DECOMP_RB_Crystal_LInC(
	struct Instance* cystalInst, 
	struct Thread* crystalTh,
	struct WeaponSearchData* info)
{
	int modelID = info->modelID;
	
	if ((modelID != 0x18) 
}