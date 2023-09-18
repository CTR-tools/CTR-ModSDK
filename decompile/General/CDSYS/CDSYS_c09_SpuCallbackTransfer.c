#include <common.h>

void DECOMP_CDSYS_SpuCallbackTransfer()
{
	if (sdata->irqAddr == 0)
		sdata->irqAddr = 0x200;
	
	else
		sdata->irqAddr = 0;
	
	SpuSetIRQAddr(sdata->irqAddr);
	
	SpuSetIRQ(1);
	
	sdata->countPass_CdTransferCallback++;
	
	#ifndef REBUILD_PS1
	CDSYS_SpuGetMaxSample();
	#endif
}