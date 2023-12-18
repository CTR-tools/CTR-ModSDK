#include <common.h>

/*
https://en.wikipedia.org/wiki/Rotation_matrix
CTRL + F and look for "Other 3D rotation matrices can be obtained from these three using"
*/

void TEST_ConvertRotToMatrix(MATRIX* m, short* rot)
{
	#define mSIN DECOMP_MATH_Sin
	#define mCOS DECOMP_MATH_Cos
	
	// a = z
	// b = y
	// v = x
	
	m->m[0][0] = (mCOS(rot[2]) * mCOS(rot[1])) >> 0xC;
	m->m[0][1] = ((((mCOS(rot[2]) * mSIN(rot[1])) >> 0xC) * mSIN(rot[0])) >> 0xC) - ((mSIN(rot[2]) * mCOS(rot[0])) >> 0xC);
	m->m[0][2] = ((((mCOS(rot[2]) * mSIN(rot[1])) >> 0xC) * mCOS(rot[0])) >> 0xC) + ((mSIN(rot[2]) * mSIN(rot[0])) >> 0xC);
	
	m->m[1][0] = (mSIN(rot[2]) * mCOS(rot[1])) >> 0xC;
	m->m[1][1] = ((((mSIN(rot[2]) * mSIN(rot[1])) >> 0xC) * mSIN(rot[0])) >> 0xC) + ((mCOS(rot[2]) * mCOS(rot[0])) >> 0xC);
	m->m[1][2] = ((((mSIN(rot[2]) * mSIN(rot[1])) >> 0xC) * mCOS(rot[0])) >> 0xC) - ((mCOS(rot[2]) * mSIN(rot[0])) >> 0xC);
	
	m->m[2][0] = -mSIN(rot[1]);
	m->m[2][1] = (mCOS(rot[1]) * mSIN(rot[0])) >> 0xC;
	m->m[2][2] = (mCOS(rot[1]) * mCOS(rot[0])) >> 0xC;
}