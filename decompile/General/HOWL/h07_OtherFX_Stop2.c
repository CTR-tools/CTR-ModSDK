#include <common.h>

// all instances of soundID
void DECOMP_OtherFX_Stop2(int soundID_count)
{
	DECOMP_Smart_EnterCriticalSection();
	
	// all instances of soundID
	DECOMP_Channel_SearchFX_Destroy(1, soundID_count & 0xffff, 0xffff);
	
	DECOMP_Smart_ExitCriticalSection();
}