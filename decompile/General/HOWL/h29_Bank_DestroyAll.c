#include <common.h>

void DECOMP_Bank_DestroyAll()
{
	struct Bank* ptrLastBank;
	
	while(sdata->numAudioBanks != 0)
	{		
		Bank_DestroyLast();
	}
}