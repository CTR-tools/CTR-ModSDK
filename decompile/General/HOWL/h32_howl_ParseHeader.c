#include <common.h>

void DECOMP_howl_ParseHeader(struct HowlHeader* hh)
{
	unsigned int addr = (unsigned int)hh;
	
	sdata->ptrHowlHeader = (struct HowlHeader*)addr;
	addr += sizeof(struct HowlHeader);
	
	sdata->howl_spuAddrs = (struct SpuAddrEntry*)addr;
	addr += sizeof(struct SpuAddrEntry) * hh->numSpuAddrs;
	
	sdata->howl_metaOtherFX = (struct OtherFX*)addr;
	addr += sizeof(struct OtherFX) * hh->numOtherFX;
	
	sdata->howl_metaEngineFX = (struct EngineFX*)addr;
	addr += sizeof(struct EngineFX) * hh->numEngineFX;
	
	sdata->howl_bankOffsets = (unsigned short*)addr;
	addr += sizeof(short) * hh->numBanks;
	
	sdata->howl_songOffsets = (unsigned short*)addr;
	
	// unused
	//addr += sizeof(short) * hh->numSequences;
	//sdata->howl_endOfHowl = addr;
}