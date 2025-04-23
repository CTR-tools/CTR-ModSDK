#include <common.h>

void DECOMP_CDSYS_SpuEnableIRQ()
{
	// erase 0x400 bytes
	int* ptr = &sdata->SpuDecodedBuf[0];
	for(int i = 0; i < 0x100; i++)
		ptr[i] = 0;
	
	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
	SpuSetTransferCallback(DECOMP_CDSYS_SpuCallbackTransfer);
	SpuSetIRQCallback(DECOMP_CDSYS_SpuCallbackIRQ);
	
	sdata->irqAddr = 0x200;
	SpuSetIRQAddr(sdata->irqAddr);
	SpuSetIRQ(1);
	
	// === Naughty Dog Bug (fixed) ===
	sdata->XA_MaxSampleIndex = 0;
	sdata->XA_MaxSampleNumSaved = 0;
}