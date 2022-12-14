#include <common.h>

struct Instance* RB_Hazard_CollideWithBucket(
	struct Instance* weaponInst, 
	struct Thread* weaponTh, struct Thread* bucket, 
	char boolCanHitParent, int hitRadius, struct Instance* mineDriverInst
)
{
	int j;
	struct Instance* threadInst;
	
	int distComponent;
	int distCheck;
	
	while(bucket != 0)
	{
		threadInst = bucket->inst;
		
		if (
		
			// if mine can not hit parent
			(boolCanHitParent == 0) &&
			
			// then do not check parent
			(threadInst == mineDriverInst)
			)
		{
			continue;
		}
		
		for(j = 0; j < 3; j++)
		{
			distComponent = threadInst->matrix.t[j] - weaponInst->matrix.t[j];
			distComponent *= distComponent;
			distCheck += distComponent;
		}
		
		if(distCheck < hitRadius)
		{
			return threadInst;
		}
		
		bucket = bucket->siblingThread;
	}
	
	return 0;
}