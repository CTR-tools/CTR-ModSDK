#include <common.h>

void CDSYS_XAPauseForce();

void CDSYS_SetMode_StreamData()
{
	char buf[8];

	// quit if using parallel
	if(sdata->boolUseDisc == 0) return;
	
	// if already in StreamData mode
	if(sdata->discMode == 0) return;
	
	// if XAs "might" be in play, cause XNF loaded
	if(sdata->bool_XnfLoaded != 0)
	{
		// force stop, and cancel callbacks
		CDSYS_XAPauseForce();
		CdSyncCallback(0);
		CdReadyCallback((CdlCB)0x0);
	}
	
	// https://www.cybdyn-systems.com.au/forum/viewtopic.php?t=1956
    // CdControl('\x0e',local_10,(u_char *)0x0);
	// param_1: 0xe = CdlSetmode
	// param_2: 0x80 = Speed mode (separate modes exist)
	// param_3: 0 = normal speed, 1 = double speed
	
	// Set Mode to Data
	buf[0] = CdlModeSpeed;
	CdControl(CdlSetmode, buf, 0);
	sdata->discMode = 0;
	
	sdata->XA_State = 0;
}