#include <common.h>

void DECOMP_LOAD_RunPtrMap(char* origin, int* patchArr, int numPtrs)
{
	int* ptrCurrOffset = patchArr;
	
	for(
			ptrCurrOffset = &patchArr[0];
			ptrCurrOffset < &patchArr[numPtrs];
			ptrCurrOffset++
		)
	{
		*(int*)&origin[*ptrCurrOffset] =
		*(int*)&origin[*ptrCurrOffset] + origin;
	}
}