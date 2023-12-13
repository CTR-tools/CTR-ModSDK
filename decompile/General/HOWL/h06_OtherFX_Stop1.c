#include <common.h>

// specific instance of soundID
void DECOMP_OtherFX_Stop1(int soundID_count)
{
	DECOMP_Smart_EnterCriticalSection();
	
	// specific instance of soundID
	DECOMP_Channel_SearchFX_Destroy(1, soundID_count, 0xffffffff);
	
	DECOMP_Smart_ExitCriticalSection();
}