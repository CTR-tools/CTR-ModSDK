#include <common.h>

void DECOMP_CDSYS_XaCallbackCdSync(char result)
{
	unsigned char comstr;
	
	if(result == CdlComplete)
	{
		comstr = CdComstr(result) - 0x15;
		
		if(comstr < 2)
		{
			sdata->XA_State = 0;
		}
		
		return;
	}
	
	sdata->countFail_CdSyncCallback++;
}