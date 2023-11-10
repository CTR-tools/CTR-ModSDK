#include <common.h>

void DECOMP_CDSYS_SetMode_StreamAudio()
{
	char buf[8];

	// dont check boolUseDisc,
	// already checked in XaPlay() and XaSeek()

	if(
		// quit if already in AUDIO mode, or
		// playing game without XNF loaded
		(sdata->discMode == DM_AUDIO) ||
		(sdata->bool_XnfLoaded == 0)
	)
	{
		return;
	}
	
	// https://www.cybdyn-systems.com.au/forum/viewtopic.php?t=1956
    // CdControl('\x0e',local_10,(u_char *)0x0);
	// param_1: 0xe = CdlSetmode
	// param_2: 0xE8 = set speed, play ADPCM, set sector
	// param_3: 0 = normal speed, 1 = double speed
	
	// Set Mode to Audio
	buf[0] = 0xE8;
	CdControl(CdlSetmode, buf, 0);

	sdata->discMode = DM_AUDIO;	
	sdata->XA_State = 0;
	
	CdSyncCallback(DECOMP_CDSYS_XaCallbackCdSync);
	CdReadyCallback(DECOMP_CDSYS_XaCallbackCdReady);
}