#include <common.h>

void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	struct Thread* other;

// only used with drivers colliding
// with other drivers, disabled online
#ifdef USE_ONLINE
	return;
#endif
	
	while(th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, vec3_pos);
		
		// next
		th = th->siblingThread;
	}
}