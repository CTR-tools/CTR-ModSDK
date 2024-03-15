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
	gte_rtv0tr();
	
	int posStart[3];
	gte_stlvnl(&posStart[0]);
	
	short rotStart[3];
	rotStart[0] = tView->rot[0] - *(short*)0x800b51f8;
	rotStart[1] = tView->rot[1] + *(short*)0x800b51fa;
	rotStart[2] = tView->rot[2] - *(short*)0x800b51fc;
	
	short posCurr[3];
	short rotCurr[3];
	CAM_ProcessTransition(
		posCurr, rotCurr,
		0x800b5560, 0x800b5568, // pos/rot desired
		posStart, rotStart,
		param_1);
		
	// === Need To Finish ===
	
}