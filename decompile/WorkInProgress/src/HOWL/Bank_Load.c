#include <common.h>

int DECOMP_Bank_Load(int bankID, struct Bank* ptrBank)
{
	int numBanks = sdata->numAudioBanks;
	
	// if out of banks, quit
	if(numBanks >= 8) return 0;
	
	// should this happen after next IF?
	sdata->bank[numBanks].bankID = bankID;
	
	// if bank is in use, quit
	if((sdata->bank[numBanks].flags & 3) != 0) return 0;
	
	// === Call Bank_Alloc ===
}