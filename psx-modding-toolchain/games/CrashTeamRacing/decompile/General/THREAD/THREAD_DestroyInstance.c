#include <common.h>

void THREAD_DestroyInstance(struct Thread* t)
{
	INSTANCE_Death(t->inst);
}