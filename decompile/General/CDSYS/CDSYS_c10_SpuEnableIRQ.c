#include <common.h>

void DECOMP_CDSYS_SpuEnableIRQ()
{
	for(int i = 0; i < 0x100; i++)
	{
		sdata->SpuDecodedData[i] = 0;
	}
	
	SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
	SpuSetTransferCallback(CDSYS_SpuCallbackTransfer);
	SpuSetIRQCallback(CDSYS_SpuCallbackIRQ);
	
	sdata->irqAddr = 0x200;
	SpuSetIRQAddr(0x200);
	SpuSetIRQ(1);
}