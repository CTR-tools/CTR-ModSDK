#include <common.h>

void DECOMP_Bank_ResetAllocator()
{
	sdata->numAudioBanks = 0;
	sdata->audioAllocPtr = 0x202;
	sdata->bankLoadStage = 4; // Stage 4: Finished
}