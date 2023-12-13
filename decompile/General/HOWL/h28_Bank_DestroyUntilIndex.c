#include <common.h>

void DECOMP_Bank_DestroyUntilIndex(int index)
{
	struct Bank* ptrLastBank;
	
	while(sdata->numAudioBanks != 0)
	{
		ptrLastBank = &sdata->bank[sdata->numAudioBanks-1];
		
		if(ptrLastBank->bankID == index) return;
		
		DECOMP_Bank_DestroyLast();
	}
}