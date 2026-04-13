#include <common.h>

void DECOMP_CDSYS_SpuCallbackTransfer()
{
	// === Naughty Dog Bug (fixed) ===
	// Use this frame's sample on this frame
	#if 1
	DECOMP_CDSYS_SpuGetMaxSample();
	#endif
	
	
	// 0->1 and 1->0
	sdata->irqAddr = (sdata->irqAddr + 1) & 1;
	SpuSetIRQAddr(sdata->irqAddr << 9);
	SpuSetIRQ(1);
	
	
	#if 0 // unused
	sdata->countPass_CdTransferCallback++;
	#endif
	
	
	// === Naughty Dog Bug ===
	// this uses "last" sample's data,
	// which is why CDSYS_SpuEnableIRQ does a clear
	#if 0
	DECOMP_CDSYS_SpuGetMaxSample();
	#endif
}