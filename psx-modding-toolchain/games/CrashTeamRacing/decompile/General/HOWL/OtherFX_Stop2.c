#include <common.h>

// all instances of soundID
void OtherFX_Stop2(int soundID_count)
{
	Smart_EnterCriticalSection();
	
	// all instances of soundID
	Channel_SearchFX_Destroy(1, soundID_count & 0xffff, 0xffff);
	
	Smart_ExitCriticalSection();
}