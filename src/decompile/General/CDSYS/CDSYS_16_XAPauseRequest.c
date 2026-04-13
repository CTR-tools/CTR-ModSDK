#include <common.h>

void DECOMP_CDSYS_XAPauseRequest()
{
	// XnfLoaded will be false without boolUseDisc
	// if(sdata->boolUseDisc == 0) return;

	if(sdata->bool_XnfLoaded == 0) return;
	if(sdata->XA_State < 2) return;
	if(sdata->XA_State > 3) return;
	
	sdata->XA_State = 4;
	sdata->XA_VolumeDeduct = 0x400;
}