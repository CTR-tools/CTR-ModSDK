#include <common.h>

void DECOMP_THREAD_DestroyInstance(struct Thread* t)
{
	DECOMP_INSTANCE_Death(t->inst);
}