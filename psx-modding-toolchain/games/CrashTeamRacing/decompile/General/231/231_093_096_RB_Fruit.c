#include <common.h>

void RB_Fruit_GetScreenCoords(struct Camera110* c110, struct Instance* inst, short* output)
{
	MATRIX* m;
	short posWorld[4];
	
	// load camera matrix
	m = &c110->matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
	
	// load input vector, each int casts to short
	posWorld[0] = (short)inst->matrix.t[0];
	posWorld[1] = (short)inst->matrix.t[1];
	posWorld[2] = (short)inst->matrix.t[2];
	posWorld[3] = 0;
	gte_ldv0(&posWorld[0]);
	
// inline_c.h gte_rtps() is broken? swap for mine:
// copied from 231.c, address 800B514C, CTR Letter World->HUD
#define gte_rtps_NikoVersion() __asm__ volatile ( \
	"nop;"							\
	"nop;"							\
	".word 0x4A180001" )

	// perspective projection
	gte_rtps_NikoVersion();
	
	// get result
	gte_stsxy(&output[0]);
}

void DECOMP_RB_Fruit_LInB(struct Instance* inst)
{
	RB_Default_LInB(inst);
	inst->animIndex = 0;
	inst->flags |= 0x10;
}