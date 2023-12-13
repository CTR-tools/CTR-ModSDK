#include <common.h>

void DECOMP_Bank_DestroyAll()
{
	struct Bank* ptrLastBank;
	
	while(sdata->numAudioBanks != 0)
	{		
		DECOMP_Bank_DestroyLast();
	}
}