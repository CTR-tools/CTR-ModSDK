#include <common.h>

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
void Online_CollidePointWithBucket(struct Thread* th, short* vec3_pos);
#endif

void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	// only used with drivers colliding
	// with other drivers, disabled online
#if defined(USE_ONLINE)
	Online_CollidePointWithBucket(th, vec3_pos);
#else
	while(th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, vec3_pos);
		
		// next
		th = th->siblingThread;
	}
#endif
}