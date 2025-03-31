#include <common.h>

void DECOMP_CDSYS_XAPauseAtEnd()
{
	// wait until IRQ says XA is finished
	if(sdata->XA_boolFinished == 0) return;
	
	DECOMP_CDSYS_XAPauseForce();
}