#include <common.h>

void DECOMP_AH_MaskHint_SetAnim(int scale)
{
	MATRIX* m;
	struct GameTracker* gGT = sdata->gGT;
	struct PushBuffer* pb = &gGT->pushBuffer[0];

	m = &pb->matrix_Camera;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

	gte_ldv0(&D232.maskOffsetPos[0]);
	gte_rt();

	int posEndINT[3];
	short posEnd[3];

	gte_stlvnl(&posEndINT[0]);

	posEnd[0] = posEndINT[0];
	posEnd[1] = posEndINT[1];
	posEnd[2] = posEndINT[2];

	short rotEnd[3];
	rotEnd[0] = pb->rot[0] - D232.maskOffsetRot[0];
	rotEnd[1] = pb->rot[1] + D232.maskOffsetRot[1];
	rotEnd[2] = pb->rot[2] - D232.maskOffsetRot[2];

	short posCurr[3];
	short rotCurr[3];
	DECOMP_CAM_ProcessTransition(
		&posCurr[0], &rotCurr[0],
		&D232.maskCamPosStart[0], &D232.maskCamRotStart[0],
		&posEnd[0], &rotEnd[0],
		scale);

	int rot = 0x1000;
	if (D232.maskSpawnFrame - FPS_DOUBLE(20) < D232.maskFrameCurr)
	{
		rot = ((D232.maskSpawnFrame - D232.maskFrameCurr) * rot) / FPS_DOUBLE(20);
	}

	// 4096->50
	rot = (rot * 50) >> 0xc;

	int angle =  (scale << 0xf) >> 0xc;
	D232.maskAngle = angle;

	int sin = DECOMP_MATH_Sin(angle);
	int cos = DECOMP_MATH_Cos(angle);

	struct Instance* mhInst = sdata->instMaskHints3D;
	mhInst->matrix.t[0] = posCurr[0] + (short)((sin*rot)>>0xc);
	mhInst->matrix.t[2] = posCurr[2] + (short)((cos*rot)>>0xc);

	rotCurr[1] += angle;
	ConvertRotToMatrix(&mhInst->matrix, rotCurr);

	((struct MaskHint*)mhInst->thread->object)->scale = scale * 4 - 1;

	angle = (sdata->frameCounter + gGT->timer) * FPS_HALF(0x20);
	sin = DECOMP_MATH_Sin(angle);
	mhInst->matrix.t[1] = posCurr[1] + (short)(((sin << 4) >> 0xc) * scale >> 0xc);
}