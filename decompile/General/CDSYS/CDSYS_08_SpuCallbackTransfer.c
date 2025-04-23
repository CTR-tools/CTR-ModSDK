#include <common.h>

void DECOMP_CDSYS_SpuCallbackTransfer()
{
	if (sdata->irqAddr == 0)
		sdata->irqAddr = 0x200;
	
	else
		sdata->irqAddr = 0;
	
	SpuSetIRQAddr(sdata->irqAddr);
	SpuSetIRQ(1);
	
	#if 0 // unused
	sdata->countPass_CdTransferCallback++;
	#endif
	
	DECOMP_CDSYS_SpuGetMaxSample();
}