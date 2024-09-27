#include <common.h>

#ifdef USE_ONLINE
#include "../AltMods/OnlineCTR/global.h"
void Online_CollidePointWithBucket(struct Thread* th, short* vec3_pos);
#endif

void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	struct Thread* other;

	// only used with drivers colliding
	// with other drivers, disabled online
#if defined(USE_ONLINE) //this puts us over the byte budget by 4 bytes, but idk how to shrink it.
	Online_CollidePointWithBucket(th, vec3_pos);
#endif
//#if !defined(USE_ONLINE) //this may not be a valid optimization, leaving it enabled for now.
	while(th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, vec3_pos);
		
		// next
		th = th->siblingThread;
	}
//#endif
}