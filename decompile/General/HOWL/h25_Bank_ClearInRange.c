#include <common.h>

void DECOMP_Bank_ClearInRange(unsigned short min, unsigned short max)
{
	int i;
	struct SpuAddrEntry* sae;
	sae = &sdata->howl_spuAddrs[0];
	
	for(i = 0; i < sdata->ptrHowlHeader->numSpuAddrs; i++)
	{
		if(sae[i].spuAddr < min) continue;
		if(sae[i].spuAddr >= (min+max)) continue;
		sae[i].spuAddr = 0;
	}
}