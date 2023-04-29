#include <common.h>

// specific instance of soundID
void OtherFX_Stop1(int soundID_count)
{
	Smart_EnterCriticalSection();
	
	// specific instance of soundID
	Channel_SearchFX_Destroy(1, soundID_count, 0xffffffff);
	
	Smart_ExitCriticalSection();
}