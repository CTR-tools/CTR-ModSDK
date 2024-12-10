#include <common.h>

void DECOMP_CDSYS_SpuDisableIRQ()
{	
	sdata->XA_MaxSampleValInArr = 0;
	sdata->XA_MaxSampleVal = 0;

	SpuSetIRQ(0);
	SpuSetIRQCallback(0);
	SpuSetTransferCallback(0);
}