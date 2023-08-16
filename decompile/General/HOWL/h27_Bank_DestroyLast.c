#include <common.h>

int DECOMP_Bank_DestroyLast()
{
	if(sdata->numAudioBanks == 0) return 0;
	
	Bank_Destroy(&sdata->bank[--sdata->numAudioBanks]);
	return 1;
}