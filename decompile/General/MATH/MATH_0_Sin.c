#include <common.h>

int DECOMP_MATH_Sin(unsigned int angle)
{
	/*int sine;

	struct TrigTable trigApprox = data.trigApprox[angle & 0x3ff];
	
	if ((angle & 0x400) == 0)
	{
		sine = trigApprox.sin;
	}
	else
	{
		sine = trigApprox.cos;
	}
	if ((angle & 0x800) != 0)
	{
		sine = -sine;
	}
	return sine;*/

	//u_int uVar1;
	//int iVar2;

	//uVar1 = *(u_int*)&data.trigApprox[angle & 0x3ff];
	//if ((angle & 0x400) == 0) {
	//	uVar1 = uVar1 << 0x10;
	//}
	//iVar2 = (int)uVar1 >> 0x10;
	//if ((angle & 0x800) != 0) {
	//	iVar2 = -iVar2;
	//}
	//return iVar2;


	//this definition is overbudget
    int sine;
    
    if (IS_ANG_FIRST_OR_THIRD_QUADRANT(angle))
        sine = data.trigApprox[ANG_MODULO_HALF_PI(angle)].sin;
    else
        sine = data.trigApprox[ANG_MODULO_HALF_PI(angle)].cos;

    if (IS_ANG_THIRD_OR_FOURTH_QUADRANT(angle))
        sine = -sine;

    return sine;
}
