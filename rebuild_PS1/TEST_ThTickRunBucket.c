#include <common.h>

void TEST_ThTickRunBucket(struct Thread* t)
{
	for(/**/; t != 0; t = t->siblingThread)
	{
		if((t->flags & 0x800) != 0) continue;
		
		if(t->funcThTick == 0) continue;
		
		if(t->cooldownFrameCount != 0)
		{
			t->cooldownFrameCount--;
			continue;
		}
		
		t->funcThTick(t);
	}
}