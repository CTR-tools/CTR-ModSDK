#include <common.h>

void DECOMP_CDSYS_SpuEnableIRQ()
{
	// === Naughty Dog Bug ===
	// Fix for the bug in CDSYS_SpuCallbackTransfer
#if 0
	int* ptr = &sdata->SpuDecodedBuf[0];
	for(int i = 0; i < 0x100; i++)
		ptr[i] = 0;
#endif
	
	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
	SpuSetTransferCallback(DECOMP_CDSYS_SpuCallbackTransfer);
	SpuSetIRQCallback(DECOMP_CDSYS_SpuCallbackIRQ);
	
	sdata->irqAddr = 0; // OG game did "= 1"
	SpuSetIRQAddr(sdata->irqAddr << 9);
	SpuSetIRQ(1);
	
	// === Naughty Dog Bug (fixed) ===
	sdata->XA_MaxSampleIndex = 0;
	sdata->XA_MaxSampleNumSaved = 0;
}