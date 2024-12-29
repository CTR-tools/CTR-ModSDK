#include <common.h>

void DECOMP_CDSYS_XAPauseForce()
{
	if(sdata->boolUseDisc == 0) return;
	if(sdata->bool_XnfLoaded == 0) return;
	if(sdata->XA_State == 0) return;
	
	sdata->XA_State = 0;
	sdata->XA_boolFinished = 0;
	
	// dont call SpuSetIRQ here, 
	// it's called in SpuDisableIRQ anyway
	DECOMP_CDSYS_SpuDisableIRQ();
	
	CdControl(CdlPause, 0, 0);
	
	sdata->XA_PauseFrame = sdata->gGT->frameTimer_MainFrame_ResetDB;
}