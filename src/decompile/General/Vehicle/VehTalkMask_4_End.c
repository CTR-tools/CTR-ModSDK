#include <common.h>

void DECOMP_VehTalkMask_End()
{	
	sdata->boolIsMaskThreadAlive = 0;
	sdata->talkMask_boolDead = 1;
	
	// optimization, end function on JMP
	DECOMP_CDSYS_XAPauseRequest();
}