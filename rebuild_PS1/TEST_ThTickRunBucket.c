#include <common.h>

void TEST_ThTickRunBucket(struct Thread* t)
{
	while(t != 0)
	{
		t->funcThTick(t);
		t = t->siblingThread;
	}
}