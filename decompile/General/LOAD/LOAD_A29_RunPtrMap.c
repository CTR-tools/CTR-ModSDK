#include <common.h>

void DECOMP_LOAD_RunPtrMap(int origin, int* patchArr, int numPtrs)
{
	for(int i = 0; i < numPtrs; i++)
	{
		*(unsigned int*)(origin + patchArr[i]) += origin;
	}
}