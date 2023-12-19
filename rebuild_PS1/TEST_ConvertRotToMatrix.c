#include <common.h>

/*
https://en.wikipedia.org/wiki/Rotation_matrix
CTRL + F and look for "Other 3D rotation matrices can be obtained from these three using"
*/

void TEST_ConvertRotToMatrix(MATRIX* m, short* rot)
{
	#define mSIN DECOMP_MATH_Sin
	#define mCOS DECOMP_MATH_Cos
	
// This is a ZYX
// gimbal lock on Z axis, bugs Hot Air Skyway's "blade" no good,
// I need to make an optimal version of YXZ (confirmed to match the game)
#if 0
	m->m[0][0] = (mCOS(rot[2]) * mCOS(rot[1])) >> 0xC;
	m->m[0][1] = ((((mCOS(rot[2]) * mSIN(rot[1])) >> 0xC) * mSIN(rot[0])) >> 0xC) - ((mSIN(rot[2]) * mCOS(rot[0])) >> 0xC);
	m->m[0][2] = ((((mCOS(rot[2]) * mSIN(rot[1])) >> 0xC) * mCOS(rot[0])) >> 0xC) + ((mSIN(rot[2]) * mSIN(rot[0])) >> 0xC);
	
	m->m[1][0] = (mSIN(rot[2]) * mCOS(rot[1])) >> 0xC;
	m->m[1][1] = ((((mSIN(rot[2]) * mSIN(rot[1])) >> 0xC) * mSIN(rot[0])) >> 0xC) + ((mCOS(rot[2]) * mCOS(rot[0])) >> 0xC);
	m->m[1][2] = ((((mSIN(rot[2]) * mSIN(rot[1])) >> 0xC) * mCOS(rot[0])) >> 0xC) - ((mCOS(rot[2]) * mSIN(rot[0])) >> 0xC);
	
	m->m[2][0] = -mSIN(rot[1]);
	m->m[2][1] = (mCOS(rot[1]) * mSIN(rot[0])) >> 0xC;
	m->m[2][2] = (mCOS(rot[1]) * mCOS(rot[0])) >> 0xC;
#endif

	MATRIX rotZ;
	rotZ.m[0][0] = mCOS(rot[2]);
	rotZ.m[0][1] = -mSIN(rot[2]);
	rotZ.m[0][2] = 0;

	rotZ.m[1][0] = mSIN(rot[2]);
	rotZ.m[1][1] = mCOS(rot[2]);
	rotZ.m[1][2] = 0;

	rotZ.m[2][0] = 0;
	rotZ.m[2][1] = 0;
	rotZ.m[2][2] = 0x1000;

	MATRIX rotY;
	rotY.m[0][0] = mCOS(rot[1]);
	rotY.m[0][1] = 0;
	rotY.m[0][2] = mSIN(rot[1]);

	rotY.m[1][0] = 0;
	rotY.m[1][1] = 0x1000;
	rotY.m[1][2] = 0;

	rotY.m[2][0] = -mSIN(rot[1]);
	rotY.m[2][1] = 0;
	rotY.m[2][2] = mCOS(rot[1]);

	MATRIX rotX;
	rotX.m[0][0] = 0x1000;
	rotX.m[0][1] = 0;
	rotX.m[0][2] = 0;

	rotX.m[1][0] = 0;
	rotX.m[1][1] = mCOS(rot[0]);
	rotX.m[1][2] = -mSIN(rot[0]);

	rotX.m[2][0] = 0;
	rotX.m[2][1] = mSIN(rot[0]);
	rotX.m[2][2] = mCOS(rot[0]);

// YXZ is definitely correct,
// tested with camera gimbal lock
#define m1 rotY
#define m2 rotX
#define m3 rotZ

	MATRIX mix;

#define RCC(row, col, index) \
	((int)((int)m1.m[row][index] * (int)m2.m[index][col]) >> 0xC)

	mix.m[0][0] = RCC(0, 0, 0) + RCC(0, 0, 1) + RCC(0, 0, 2);
	mix.m[0][1] = RCC(0, 1, 0) + RCC(0, 1, 1) + RCC(0, 1, 2);
	mix.m[0][2] = RCC(0, 2, 0) + RCC(0, 2, 1) + RCC(0, 2, 2);

	mix.m[1][0] = RCC(1, 0, 0) + RCC(1, 0, 1) + RCC(1, 0, 2);
	mix.m[1][1] = RCC(1, 1, 0) + RCC(1, 1, 1) + RCC(1, 1, 2);
	mix.m[1][2] = RCC(1, 2, 0) + RCC(1, 2, 1) + RCC(1, 2, 2);

	mix.m[2][0] = RCC(2, 0, 0) + RCC(2, 0, 1) + RCC(2, 0, 2);
	mix.m[2][1] = RCC(2, 1, 0) + RCC(2, 1, 1) + RCC(2, 1, 2);
	mix.m[2][2] = RCC(2, 2, 0) + RCC(2, 2, 1) + RCC(2, 2, 2);

#define RCC2(row, col, index) \
	((int)((int)mix.m[row][index] * (int)m3.m[index][col]) >> 0xC)

	m->m[0][0] = RCC2(0, 0, 0) + RCC2(0, 0, 1) + RCC2(0, 0, 2);
	m->m[0][1] = RCC2(0, 1, 0) + RCC2(0, 1, 1) + RCC2(0, 1, 2);
	m->m[0][2] = RCC2(0, 2, 0) + RCC2(0, 2, 1) + RCC2(0, 2, 2);
													
	m->m[1][0] = RCC2(1, 0, 0) + RCC2(1, 0, 1) + RCC2(1, 0, 2);
	m->m[1][1] = RCC2(1, 1, 0) + RCC2(1, 1, 1) + RCC2(1, 1, 2);
	m->m[1][2] = RCC2(1, 2, 0) + RCC2(1, 2, 1) + RCC2(1, 2, 2);
													
	m->m[2][0] = RCC2(2, 0, 0) + RCC2(2, 0, 1) + RCC2(2, 0, 2);
	m->m[2][1] = RCC2(2, 1, 0) + RCC2(2, 1, 1) + RCC2(2, 1, 2);
	m->m[2][2] = RCC2(2, 2, 0) + RCC2(2, 2, 1) + RCC2(2, 2, 2);
}