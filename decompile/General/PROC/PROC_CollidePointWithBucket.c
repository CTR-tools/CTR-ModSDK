#include <common.h>

void DECOMP_PROC_CollidePointWithBucket(struct Thread* th, short* vec3_pos)
{
	struct Thread* other;
	
	while(th != 0)
	{
		DECOMP_PROC_CollidePointWithSelf(th, vec3_pos);
		
		// next
		th = th->siblingThread;
	}
}