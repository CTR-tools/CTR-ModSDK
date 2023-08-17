#include <common.h>

void DECOMP_howl_ParseHeader(struct HowlHeader* hh)
{
	unsigned int addr = hh;
	
	sdata->ptrHowlHeader = addr;
	addr += sizeof(struct HowlHeader);
	
	sdata->howl_spuAddrs = addr;
	addr += sizeof(struct SpuAddrEntry) * hh->numSpuAddrs;
	
	sdata->howl_metaOtherFX = addr;
	addr += sizeof(struct OtherFX) * hh->numOtherFX;
	
	sdata->howl_metaEngineFX = addr;
	addr += sizeof(struct EngineFX) * hh->numEngineFX;
	
	sdata->howl_bankOffsets = addr;
	addr += sizeof(short) * hh->numBanks;
	
	sdata->howl_songOffsets = addr;
	
	// unused
	//addr += sizeof(short) * hh->numSequences;
	//sdata->howl_endOfHowl = addr;
}