#include <common.h>

struct Instance* DECOMP_RB_Hazard_CollideWithBucket(
	struct Instance* weaponInst, 
	struct Thread* weaponTh, struct Thread* bucket, 
	char boolCanSkipParent, int hitRadius, struct Instance* mineDriverInst
)
{
	int i;
	struct Instance* threadInst;
	
	int distComponent;
	int distCheck;
	
	for(; bucket != 0; bucket = bucket->siblingThread)
	{
		distCheck = 0;
		threadInst = bucket->inst;
		
		if (
		
			// if mine can skip parent
			(boolCanSkipParent != 0) &&
			
			// then do not check parent
			(threadInst == mineDriverInst)
			)
		{
			continue;
		}
		
		for(i = 0; i < 3; i++)
		{
			distComponent = threadInst->matrix.t[i] - weaponInst->matrix.t[i];
			distComponent *= distComponent;
			distCheck += distComponent;
		}
		
		if(distCheck < hitRadius)
		{
			return threadInst;
		}
		
		//printf("%d %d\n", distCheck, hitRadius);
	}
	
	return 0;
}