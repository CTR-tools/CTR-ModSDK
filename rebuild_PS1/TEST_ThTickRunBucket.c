#include <common.h>

void TEST_ThTickRunBucket(struct Thread* t)
{
	while(t != 0)
	{
		// if thread wasn't killed in a menu -- this is required cause dead threads
		// aren't cleaned until after bucket execution, and menu is before bucket execution
		if((t->flags & 0x800) == 0)
			t->funcThTick(t);
		
		t = t->siblingThread;
	}
}