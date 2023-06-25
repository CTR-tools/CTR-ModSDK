#include <common.h>

void DECOMP_THREAD_DestroyInstance(struct Thread* t)
{
	INSTANCE_Death(t->inst);
}