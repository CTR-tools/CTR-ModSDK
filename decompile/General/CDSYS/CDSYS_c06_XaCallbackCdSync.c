#include <common.h>

void DECOMP_CDSYS_XaCallbackCdSync(char result)
{
	unsigned char com;
	
	if(result == CdlComplete)
	{
		// determine CdlSeekL or CdlSeekP
		com = CdLastCom() - 0x15;
		
		if(com < 2)
		{
			sdata->XA_State = 0;
		}
		
		return;
	}
	
	sdata->countFail_CdSyncCallback++;
}