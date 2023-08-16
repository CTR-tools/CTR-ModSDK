#include <common.h>

int DECOMP_Bank_Load(int bankID, struct Bank* ptrBank)
{
	int numBanks = sdata->numAudioBanks;
	
	// if out of banks, quit
	if(numBanks >= 8) return 0;
	
	// Naughty Dog Bug?
	sdata->bank[numBanks].bankID = bankID;
	
	// if bank is in use, quit
	if((sdata->bank[numBanks].flags & 3) != 0) return 0;
	
	ptrBank = &sdata->bank[numBanks];
	if(Bank_Alloc(bankID, ptrBank) == 0) return 0;
	
	ptrBank->bankID = sdata->numAudioBanks++;
	return 1;
}