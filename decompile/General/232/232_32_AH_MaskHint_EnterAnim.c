#include <common.h>

void DECOMP_AH_MaskHint_EnterAnim(int param_1)
{
	MATRIX* m;
	struct GameTracker* gGT = sdata->gGT;
	struct TileView* tView = &gGT->tileView[0];
	
	m = &tView->matrix_ViewProj;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);
	
	gte_ldv0(0x800b51f0);
	
	gte_rt();
	
	int posEndINT[3];
	short posEnd[3];
	gte_stlvnl(&posEndINT[0]);
	posEnd[0] = posEndINT[0];
	posEnd[1] = posEndINT[1];
	posEnd[2] = posEndINT[2];
	
	short rotEnd[3];
	rotEnd[0] = tView->rot[0] - *(short*)0x800b51f8;
	rotEnd[1] = tView->rot[1] + *(short*)0x800b51fa;
	rotEnd[2] = tView->rot[2] - *(short*)0x800b51fc;
	
	short posCurr[3];
	short rotCurr[3];
	CAM_ProcessTransition(
		posCurr, rotCurr,
		0x800b5560, 0x800b5568, // pos/rot Start
		posEnd, rotEnd,
		param_1);
		
	printf("%d\n", param_1);
		
#if 1
	struct Instance* dInst = sdata->gGT->drivers[0]->instSelf;
	
	posCurr[0] = *(short*)0x800b5560;
	posCurr[1] = *(short*)0x800b5562;
	posCurr[2] = *(short*)0x800b5564;
#endif
		
	int rot = 0x1000;
	if (*(short*)0x800b566c + -0x14 < *(short*)0x800b5218)
	{
		rot = ((*(short*)0x800b566c - *(short*)0x800b5218) * rot) / 0x14;
	}
	
	// 4096->50
	rot = (rot * 50) >> 0xc;
	
	int angle =  (param_1 << 0xf) >> 0xc;
	*(short*)0x800b555c = angle;
	
	int cos = DECOMP_MATH_Cos(angle);
	int sin = DECOMP_MATH_Sin(angle);
	
	struct Instance* mhInst = *(int*)0x8008d860;
	mhInst->matrix.t[0] = posCurr[0] + (short)((cos*rot)>>0xc);
	mhInst->matrix.t[2] = posCurr[2] + (short)((sin*rot)>>0xc);
	
	rotCurr[1] += angle;
	ConvertRotToMatrix(&mhInst->matrix, rotCurr);
	
	((struct MaskHint*)mhInst->thread->object)->scale = param_1 * 4 - 1;
	
	angle = (sdata->frameCounter + sdata->gGT->timer) * 0x20;
	cos = DECOMP_MATH_Sin(angle);
	mhInst->matrix.t[1] = posCurr[1] + (short)(((cos << 4) >> 0xc) * param_1 >> 0xc);
}