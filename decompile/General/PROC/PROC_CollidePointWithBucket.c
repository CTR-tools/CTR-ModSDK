#include <common.h>

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
#endif

void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	struct Thread* other;

// only used with drivers colliding
// with other drivers, disabled online
#ifdef USE_ONLINE
	//NOTE: I tried re-enabling collision in item mode, but that causes a startline crash (idk why)
	//if (octr->serverRoom < 8) //itemless rooms have no collision.
		return;
#endif
	
	while(th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, vec3_pos);
		
		// next
		th = th->siblingThread;
	}
}