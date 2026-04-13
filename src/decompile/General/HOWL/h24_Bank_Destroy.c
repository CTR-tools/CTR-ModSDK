#include <common.h>

void DECOMP_Bank_Destroy(struct Bank* ptrLastBank)
{
	short flags;
	
	if(sdata->boolAudioEnabled == 0) return;

	flags = ptrLastBank->flags;
	
	DECOMP_Bank_ClearInRange(ptrLastBank->min, ptrLastBank->max);
	
	if((flags & 1) == 0)
	{
		// this works cause Bank_Destroy
		// is only called on the "last" bank
		sdata->audioAllocPtr = ptrLastBank->min;
	}
	
	ptrLastBank->flags = flags & ~(2);
}