#include <common.h>

short letterLightDir[4] =
{
	0x94F, 0x94F, -0x94F, 0
};

void DECOMP_RB_CtrLetter_ThTick(struct Thread* t)
{
	int sine;
	struct Instance* letterInst;
	struct CtrLetter* letterObj;

	letterInst = t->inst;
	letterObj = t->object;

	// rotate each frame
	letterObj->rot[1] += FPS_HALF(0x40);
	ConvertRotToMatrix(&letterInst->matrix, &letterObj->rot[0]);

	Vector_SpecLightSpin3D(letterInst, &letterObj->rot[0], &letterLightDir[0]);
}